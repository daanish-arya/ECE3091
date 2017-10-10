
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
#include "stdlib.h"



// Function Prototypes
void LeftMotor(float speed, int direction);
void RightMotor(float speed, int direction);
void Finish_Tasks(void);
void RightTurn();
void LeftTurn();
void MoveStraight(float FinalSpeed, float Distance, int Direction);
void Turn(float speed, float Distance, int Direction);
void OnOff();
float Ultrasonic_Sensor(int usonic);
void Reset_Tasks();
void UltraSonics();
void ParallelRobot();
void LED();

// Defining Variables
char string[100];
int i = 0;
int flag = 1;
int32 LeftCount = 0;
int32 RightCount = 0;
int32 red;
int32 blue;
int32 green;
int ratio;
float LeftDelta = 290.0; // Ratio to convert shaft count to distance
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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
//        Clock_1_Start();
//        QuadDec_Left_Start();
//        QuadDec_Right_Start();        
//        UART_Start(); 
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

        for(;;)
        {
                LED_Write(1);
                CyDelay(1000);
                //ParallelRobot();
                LED_Write(0);
                CyDelay(1000);
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

void LeftMotor(float speed, int direction)
{
        speed = (65535*speed)/100.0;      // speed as duty cycle
        M1_Direction_Write(direction);  // write 1 or 0 for direction
        PWM_M1_WriteCompare(speed);     // write speed in terms of duty cycle// start left PWM
        PWM_M1_Start();
}

void RightMotor(float speed, int direction)
{
        speed = (65535*speed)/100.0;      // speed as duty cycle
        M2_Direction_Write(direction);  // write 1 or 0 for direction
        PWM_M2_WriteCompare(speed);     // write speed in terms of duty cycle
        PWM_M2_Start();                 // start left PWM   
}


void Turn(float speed, float Distance, int Direction)
{
    QuadDec_Left_SetCounter(0);
    QuadDec_Right_SetCounter(0);

    for(;;)
    {
		LeftMotor(speed,~Direction);
    	RightMotor(speed,Direction);
    	
        float tempCount = fabs((float)QuadDec_Left_GetCounter() / LeftDelta);
		
    	if ( tempCount >= Distance)
    	{
			PWM_M1_Stop();                 // stop left PWM
    		PWM_M2_Stop();                 // stop right PWM
            break;
    	}
    }
    
}


void MoveStraight(float FinalSpeed, float Distance, int Direction)
{
    float LeftSpeed = 30 - 0.15;
    float RightSpeed = 30;
    QuadDec_Right_SetCounter(0);
    QuadDec_Left_SetCounter(0);
    LeftMotor(LeftSpeed,Direction);
	RightMotor(RightSpeed,Direction);
    
    while(QuadDec_Left_GetCounter() < 5 * LeftDelta)   // Wait for couts of Shaft Encoder to settle
    {
		LeftMotor(LeftSpeed,Direction);
		RightMotor(RightSpeed,Direction);
    }
    
	for(;;)
		{        
       
        RightSpeed = FinalSpeed * (float)QuadDec_Left_GetCounter()/ (float)QuadDec_Right_GetCounter(); // Calc Right Speed with respect to Left Speed
    	RightMotor(RightSpeed,Direction);
    	LeftMotor(FinalSpeed,Direction);
        float tempCount = fabs((float)QuadDec_Left_GetCounter() / LeftDelta);

    	if ( tempCount >= Distance)
    	{
			PWM_M1_Stop();                 // stop left PWM
    		PWM_M2_Stop();                 // stop right PWM
            break;
    	}
           
		}
   
}
void ParallelRobot()
{   
//    while (Left_bumper_Read() == 1 || Right_bumper_Read() == 1) 
//    {
//        LeftMotor(50,0);
//        RightMotor(50,0);
//        
//        if (Left_bumper_Read() == 0 && Right_bumper_Read() == 0) 
//        {
//            PWM_M2_Stop(); // stop left PWM
//            PWM_M1_Stop(); // stop right PWM
//            break;
//        }
//    }
    
    LeftMotor(50,0);
    RightMotor(50,0);
    
        while (Left_bumper_Read() == 0 || Right_bumper_Read() == 0) 
    {

        if (Left_bumper_Read() == 1) 
        {
            RightMotor(50,0);
            PWM_M1_Stop(); // stop left PWM
        }
        
        else if (Right_bumper_Read() == 1) 
        {
            LeftMotor(50,0);
            PWM_M2_Stop(); // stop left PWM
        }
        
        else if (Left_bumper_Read() == 1 && Right_bumper_Read() == 1) 
        {
            PWM_M1_Stop(); // stop left PWM
            PWM_M2_Stop(); // stop right PWM
            break;
        }
        
        
    }

}



void LED() 
{
    red = 0;
    green = 0;
    blue = 0;
    
    LED_Blue_Write(0);
    LED_Red_Write(0);
    LED_Green_Write(0);
    
    CyDelay(10);
    
    IDAC8_Wakeup();
    LED_Red_Write(1);
    CyDelay(40);
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    red = ADC_GetResult32();
    LED_Red_Write(0);
    IDAC8_Sleep();
    
    CyDelay(10);
    
    IDAC8_Wakeup();
    LED_Green_Write(1);
    CyDelay(40);
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    green = ADC_GetResult32();
    LED_Green_Write(0);
    IDAC8_Sleep();
    
    CyDelay(10);
    
    IDAC8_Wakeup();
    LED_Blue_Write(1);
    CyDelay(40);
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    blue = ADC_GetResult32();
    LED_Blue_Write(0);
    IDAC8_Sleep();
    
    CyDelay(200);
    
    if ((red-blue > 4000) && (red-green > 4000))
    {
        LED_Red_Write(1);
        CyDelay(1000);
        LED_Red_Write(0);
    }
    else if ((green-red > 4000) && (green-blue > 4000))
    {
        LED_Green_Write(1);
        CyDelay(500);
        LED_Green_Write(0);
    }
    else if ((blue-red > 4000) && (blue-green > 4000))
    {
        LED_Blue_Write(1);
        CyDelay(500);
        LED_Blue_Write(0);
    }
    else
    {  
        LED_Red_Write(0);
        LED_Green_Write(0);
        LED_Blue_Write(0);
        
        CyDelay(500);
    }
    //LED_Write(0);
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

// Code to print Distance, diff and stuff

/*         int32 diff2 = QuadDec_Left_GetCounter()-QuadDec_Right_GetCounter();
        float dist = (float)QuadDec_Left_GetCounter() / LeftDelta;
        sprintf(string, "Distance = %f Count left: %ld Count right: %ld, diff2 = %ld \n ",dist , QuadDec_Left_GetCounter(), QuadDec_Right_GetCounter(), diff2);
        UART_PutString(string); */
        
        //CyDelay(100);
            

/* [] END OF FILE */
