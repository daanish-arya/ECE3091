
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
#include "time.h"
#include "colour.h"
#include "stdlib.h"
#include "wheels.h"
#include "ultrasonics.h"
#include "servos_stepper.h"



// Function Prototypes
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

time_t t;
//srand((unsigned) time(&t)); // Initialize random number generator
    

// Declare Ultrasonic Interrupts

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
//    // Obstacle location defined using switch
//    
//    while (pucks_stacked < 5) {
//        // Initialise stepper
//        Move_to_Pucks(obstacle_location);
//        Line_Up_Puck(given_pattern[pucks_stacked]);
//        Pick_Up_Puck();
//        Backtrack(obstacle_location);
//        Stack();
//        pucks_stacked++;
//        Backtrack(obstacle_location);
//        
//    }
    
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
    int wall_right = 0;
    
    while (1) {
        puck_colour = LED();
        if (puck_colour == colour) {
            return 1;
        }
        else {
            // Turn a few degrees in either direction
            // Move straight
            // Do ultrasonic shit, if right wall is close then turn left 
            // and if left wall is close turn right
            int wall_proximity;
            int turning_direction;
            MoveStraight(20, 3.5, 1);
            if (obstacle_location) {
                UltraSonic_R();
                turning_direction = (RightCoord < 4.0);
                Turn(40, 20, ~turning_direction);
            }
            else {
                UltraSonic_L();
                turning_direction = (LeftCoord < 4.0);
                Turn(40, 20, turning_direction);
            }
            MoveStraight(20, 3.5, 0);
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
