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

float LeftDelta = 290.0; // Ratio to convert shaft count to distance

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

}

/* [] END OF FILE */
