
/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

// For 50 cm, PWM 20 for Left, 18 for Right, we get LeftCount = 16991, RightCount = 18447. Implies 1cm = 289 Left, 1cm = 369 for Right
// To turn left, set direction as 1 in Turn() function. To turn right, set direction as 0 in Turn() function.
// 
#include "project.h"
#include "stdio.h"
#include "math.h"
#include "colour.h"
#include "stdlib.h"
#include "wheels.h"



// Function Prototypes
void Finish_Tasks(void);
void OnOff();
float Ultrasonic_Sensor(int usonic);
void Reset_Tasks();
void UltraSonics();
int * Read_Order();
int Move_to_Pucks(int obstacle_location);
int Line_Up_Puck(int colour);
void Pick_Up_Puck();
void Backtrack(int obstacle_location);
void Stack();

// Defining Variables
char string[100];
int i = 0;
int flag = 1;
int obstacle_location; // 0 for left or centre, 1 for right
int pucks_stacked = 0;
int given_pattern[5];
int * pattern_pointer;
int32 LeftCount = 0;
int32 RightCount = 0;
int ratio;
int orientation;
int location[2];
float F1Coord = 0;
float F2Coord = 0;
float LeftCoord = 0;
float RightCoord = 0;


// Declare Ultrasonic Interrupts
CY_ISR(TimerF1_ISR_Handler) {
  Timer_ULTRASONIC_F1_ReadStatusRegister();
   uint16  TimerCount = Timer_ULTRASONIC_F1_ReadCounter();
  F1Coord = (65535.0 - TimerCount) / 58.0; //distance measured in cm
}

CY_ISR(TimerF2_ISR_Handler) {
  Timer_ULTRASONIC_F2_ReadStatusRegister();
  uint16  TimerCount = Timer_ULTRASONIC_F2_ReadCounter();
  F2Coord = (65535.0 - TimerCount) / 58.0; //distance measured in cm
}

CY_ISR(TimerL_ISR_Handler) {
  Timer_ULTRASONIC_L_ReadStatusRegister();
  uint16  TimerCount = Timer_ULTRASONIC_L_ReadCounter();
  LeftCoord = (65535.0 - TimerCount) / 58.0; //distance measured in cm
}

CY_ISR(TimerR_ISR_Handler) {
  Timer_ULTRASONIC_R_ReadStatusRegister();
  uint16 TimerCount = Timer_ULTRASONIC_R_ReadCounter();
  RightCoord = (65535.0 - TimerCount) / 58.0; //distance measured in cm
}

int * pattern(int yus[]) {
    int ayus[5];
    for (int i = 0; i < 5; i++) {
        ayus[i] = yus[i];
    }
     
    return yus; // Returns pointer to first element of array
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
        Clock_1_Start();
//        QuadDec_Left_Start();
//        QuadDec_Right_Start();        
        UART_Start(); 
//        IDAC8_Start();
//        ADC_Start(); 
//        TIA_Start();
//        IDAC8_Sleep();
//		Clock_PWM_Start();
//        PWM_Grip_Start();
//        PWM_Lift_Start();
//		
//		// Initialise all interrupts 
//		isr_F1_StartEx(TimerF1_ISR_Handler);
//		isr_F2_StartEx(TimerF2_ISR_Handler);
//		isr_L_StartEx(TimerL_ISR_Handler);
//		isr_R_StartEx(TimerR_ISR_Handler);
//
//		// Start all timers
//		Timer_ULTRASONIC_F1_Start();
//		Timer_ULTRASONIC_F2_Start();
//		Timer_ULTRASONIC_L_Start();
//		Timer_ULTRASONIC_R_Start();
//      zero stepper
    char lul[] = "2 plus 2 is 4 - 1 thats 3 quick maffs\n";
    UART_PutString(lul);
    
    int array[] = {1, 2, 3, 5, 6};
    char skrrt[30];
//    pattern_pointer = Read_Order();
    int * das_it;
    das_it = pattern(array);
    int i;
    for (i = 0; i < 5; i++) {
        given_pattern[i] = *(das_it + i);
        sprintf(lul, "The ting go %d\n", given_pattern[i]);
        UART_PutString(lul);
        CyDelay(1000);
    }
    // Obstacle location defined using switch
    
    while (pucks_stacked < 5) {
        // Initialise stepper
        Move_to_Pucks(obstacle_location);
        Line_Up_Puck(given_pattern[pucks_stacked]);
        Pick_Up_Puck();
        Backtrack(obstacle_location);
        Stack();
        pucks_stacked++;
        Backtrack(obstacle_location);
        
    }
}

void Finish_Tasks(void) 
{
	i = 1000;
}

void OnOff()
{
    if (Flag_Read() == 1)
    {
        CyDelay(20);
        if (Flag_Read() == 1)
        {
            flag = 1;
            LED_Write(1);
            i++;
            if(i == 5)
            {
                i=4;   
            }
        }
    }
}

void Reset_Tasks()
{
    if (Reset_Read() == 0)
    {
        CyDelay(20);
        if (Reset_Read() == 0)
        {
            flag = 0;
            LED_Write(1);
            CyDelay(100);
            LED_Write(0);
            CyDelay(100);
            LED_Write(1);
            CyDelay(100);
            LED_Write(0);
            CyDelay(100);
            LED_Write(1);
            CyDelay(100);
            LED_Write(0);
            CyDelay(100);
            Buzzer_Write(1);
            CyDelay(100);
            Buzzer_Write(0);
            i = 0;
        }
    }
}


int Grip_Open()
    {
        PWM_Grip_WriteCompare(1050);
        CyDelay(1000);
        
        return 0;
    } 

int Grip_Close()
    {
        PWM_Grip_WriteCompare(1290);
        CyDelay(1000);
        
        return 0;
    }    
    
    
int Lift_Up(int pucks)
{
    int i = 0;
    
    switch(pucks)
    {
         case 1:
        {
             for(i=0; i<1000000; i++)
                {
                 PWM_Lift_WriteCompare(1650);
                }
    
            PWM_Lift_WriteCompare(1475);
            break;
        }
         case 2:
        {
             for(i=0; i<1800000; i++)
                {
                 PWM_Lift_WriteCompare(1600);
                }
    
            PWM_Lift_WriteCompare(1475);
            break;
        }
         case 3:
        {
             for(i=0; i<2300000; i++)
                {
                 PWM_Lift_WriteCompare(1600);
                }
    
            PWM_Lift_WriteCompare(1475);
            break;
        }
         case 4:
        {
             for(i=0; i<2900000; i++)
                {
                 PWM_Lift_WriteCompare(1600);
                }
    
            PWM_Lift_WriteCompare(1475);
            break;
        }
        case 5:
        {
             for(i=0; i<3500000; i++)
                {
                 PWM_Lift_WriteCompare(1600);
                }
    
            PWM_Lift_WriteCompare(1475);
            break;
        }
    }
    
   
    return 0;
}

int Lift_Down()
{
    int i = 0;
    for(i=0; i<1200000; i++)
    {
        PWM_Lift_WriteCompare(1350);
    }
    
    PWM_Lift_WriteCompare(1475);
    return 0;
}

int * Read_Order() {
    
    int pucks_read = 0;
    int pattern[5];
    
    
    MoveStraight(40, 3.2, 1);
    while (pucks_read < 5) {
        pattern[4-i] = LED();
        pucks_read++;
        MoveStraight(40, 3.2, 0);
    }
    return pattern;
}

int Move_to_Pucks(int obstacle_location) {
    
    if (obstacle_location) {
        Turn(50, 180, 0);
        MoveStraight(50, 50, 0); // Until back wall is reached?
        Turn(50, 90, 1); 
        // Parallel robot?
        MoveStraight(50, 100, 0); // Move to pucks
    }
    
    return 0;
}

int Line_Up_Puck(int colour) {
    // To be done once robot is in position
    int correct_puck = 0;
    int puck_colour = 0;
    
    while (1) {
        puck_colour = LED();
        if (puck_colour == colour) {
            return 1;
        }
        else {
            // Turn a few degrees in either direction
            // Move straight
            continue;
        }
        
    }
}

void Pick_Up_Puck() {
    // TODO: Implement this. Have the ting close its gripper and then
    // lift it up.
}

void Backtrack(int obstacle_location) {
    if (obstacle_location) {
        // Code for obstacle in centre or right
    }
    else {
        // Code for obstacle on left
    }
}

void Stack() {
    // Move to construction zone
    // Read number of already stacked pucks
    // Raise platform to appropriate height
    // Drop it on top
}

// Code to print Distance, diff and stuff

/*         int32 diff2 = QuadDec_Left_GetCounter()-QuadDec_Right_GetCounter();
        float dist = (float)QuadDec_Left_GetCounter() / LeftDelta;
        sprintf(string, "Distance = %f Count left: %ld Count right: %ld, diff2 = %ld \n ",dist , QuadDec_Left_GetCounter(), QuadDec_Right_GetCounter(), diff2);
        UART_PutString(string); */
        
        //CyDelay(100);
            

/* [] END OF FILE */
