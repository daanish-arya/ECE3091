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

/* [] END OF FILE */
#include <project.h>

int32 red;
int32 blue;
int32 green;

int LED() 
{
    red = 0;
    green = 0;
    blue = 0;
    
    int colour = 0;
    
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
        colour = 1;
        CyDelay(1000);
        LED_Red_Write(0);
    }
    else if ((green-red > 4000) && (green-blue > 4000))
    {
        LED_Green_Write(1);
        colour = 2;
        CyDelay(500);
        LED_Green_Write(0);
    }
    else if ((blue-red > 4000) && (blue-green > 4000))
    {
        LED_Blue_Write(1);
        colour = 3;
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
    
    return colour;
    //LED_Write(0);
}