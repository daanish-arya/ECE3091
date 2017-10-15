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


float FCoord = 0;
float LeftCoord = 0;
float RightCoord = 0;

CY_ISR(TimerF_ISR_Handler) {
  Timer_ULTRASONIC_F_ReadStatusRegister();
   uint16  TimerCount = Timer_ULTRASONIC_F_ReadCounter();
  FCoord = (65535.0 - TimerCount) / 58.0; //distance measured in cm
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

void UltraSonic_F()
{
    int Delay = 60;
    
//        isr_F1_StartEx(TimerF1_ISR_Handler);
//        Timer_ULTRASONIC_F1_Start();
    
    while (Echo_F_Read() == 0) {
        Trigger_F_Write(1);
        CyDelayUs(10);
        Trigger_F_Write(0);  
    }
    
    CyDelay(Delay);
}

void UltraSonic_L()
{
    int Delay = 60;
    
//        isr_F1_StartEx(TimerF1_ISR_Handler);
//        Timer_ULTRASONIC_F1_Start();
    
    while (Echo_L_Read() == 0) {
        Trigger_L_Write(1);
        CyDelayUs(10);
        Trigger_L_Write(0);  
    }
    
    CyDelay(Delay);
}

void UltraSonic_R()
{
    int Delay = 60;
    
//        isr_F1_StartEx(TimerF1_ISR_Handler);
//        Timer_ULTRASONIC_F1_Start();
    
    while (Echo_R_Read() == 0) {
        Trigger_R_Write(1);
        CyDelayUs(10);
        Trigger_R_Write(0);  
    }
    
    CyDelay(Delay);
}
/* [] END OF FILE */
