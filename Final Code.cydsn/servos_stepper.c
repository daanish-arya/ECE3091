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

/* [] END OF FILE */
