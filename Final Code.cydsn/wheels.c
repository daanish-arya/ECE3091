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
#include <project.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ultrasonics.h>

float LeftDelta = 290.0; // Ratio to convert shaft count to distance
int orientation = 0;

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
    char otis[30];
    for(;;)
    {
		LeftMotor(speed,~Direction);
    	RightMotor(speed,Direction);
    	
        float tempCount = fabs((float)QuadDec_Left_GetCounter() / LeftDelta);
        
        sprintf(otis, "Count = %0.2f\n", tempCount); 
		UART_PutString(otis);
    	if ( tempCount >= Distance)
    	{
			PWM_M1_Stop();                 // stop left PWM
    		PWM_M2_Stop();                 // stop right PWM
            orientation += Distance;
            break;
    	}
    }
    
}


void MoveStraight(float FinalSpeed, float Distance, int Direction)
{
    float LeftSpeed = 30 - 0.15;
    float RightSpeed = 30;
    int i = 0;
    int32 count = 0;
    char outstr[30];
    QuadDec_Right_SetCounter(0);
    QuadDec_Left_SetCounter(0);
    LeftMotor(LeftSpeed,Direction);
	RightMotor(RightSpeed,Direction);
    
    while(QuadDec_Left_GetCounter() < 5 * LeftDelta)   // Wait for couts of Shaft Encoder to settle
    {
        i++;
        count = QuadDec_Right_GetCounter();
		LeftMotor(LeftSpeed,Direction);
		RightMotor(RightSpeed,Direction);
        
        sprintf(outstr, "count = %ld\ni = %d\n", count, i);
        UART_PutString(outstr);
        
        UltraSonic_F();
        
        if (FCoord < 10) {
            PWM_M1_Stop();                 // stop left PWM
    		PWM_M2_Stop();                 // stop right PWM
            break;
        }
    }
    i = 0;
	for(;;)
	{        
        i++;
        float checkCount = -20;
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
        if (i % 200) {
            float checkCount = tempCount;
            continue;
        }
        if (checkCount == tempCount) { 
            // Check whether robot is stuck
            MoveStraight(30, 5, 0);
            UltraSonic_L();
            UltraSonic_R();
            int turning_direction = (LeftCoord < RightCoord);
            Turn(50, 20, turning_direction);
            orientation = (orientation + (20*(-1)^turning_direction)) % 360;
        }
        
    }
   
}
void ParallelRobot() // NOTE: THIS FUNCTION IS OBSOLETE AND WILL NOT WORK.
                     // MICROS NEED TO BE IMPLEMENTED WITH INTERRUPTS
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
    
    orientation = (int) (round(((double) orientation)/90) * 90) % 360;

}

/* [] END OF FILE */
