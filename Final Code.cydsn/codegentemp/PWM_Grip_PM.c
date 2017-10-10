/*******************************************************************************
* File Name: PWM_Grip_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Grip.h"

static PWM_Grip_backupStruct PWM_Grip_backup;


/*******************************************************************************
* Function Name: PWM_Grip_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Grip_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Grip_SaveConfig(void) 
{

    #if(!PWM_Grip_UsingFixedFunction)
        #if(!PWM_Grip_PWMModeIsCenterAligned)
            PWM_Grip_backup.PWMPeriod = PWM_Grip_ReadPeriod();
        #endif /* (!PWM_Grip_PWMModeIsCenterAligned) */
        PWM_Grip_backup.PWMUdb = PWM_Grip_ReadCounter();
        #if (PWM_Grip_UseStatus)
            PWM_Grip_backup.InterruptMaskValue = PWM_Grip_STATUS_MASK;
        #endif /* (PWM_Grip_UseStatus) */

        #if(PWM_Grip_DeadBandMode == PWM_Grip__B_PWM__DBM_256_CLOCKS || \
            PWM_Grip_DeadBandMode == PWM_Grip__B_PWM__DBM_2_4_CLOCKS)
            PWM_Grip_backup.PWMdeadBandValue = PWM_Grip_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Grip_KillModeMinTime)
             PWM_Grip_backup.PWMKillCounterPeriod = PWM_Grip_ReadKillTime();
        #endif /* (PWM_Grip_KillModeMinTime) */

        #if(PWM_Grip_UseControl)
            PWM_Grip_backup.PWMControlRegister = PWM_Grip_ReadControlRegister();
        #endif /* (PWM_Grip_UseControl) */
    #endif  /* (!PWM_Grip_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Grip_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Grip_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Grip_RestoreConfig(void) 
{
        #if(!PWM_Grip_UsingFixedFunction)
            #if(!PWM_Grip_PWMModeIsCenterAligned)
                PWM_Grip_WritePeriod(PWM_Grip_backup.PWMPeriod);
            #endif /* (!PWM_Grip_PWMModeIsCenterAligned) */

            PWM_Grip_WriteCounter(PWM_Grip_backup.PWMUdb);

            #if (PWM_Grip_UseStatus)
                PWM_Grip_STATUS_MASK = PWM_Grip_backup.InterruptMaskValue;
            #endif /* (PWM_Grip_UseStatus) */

            #if(PWM_Grip_DeadBandMode == PWM_Grip__B_PWM__DBM_256_CLOCKS || \
                PWM_Grip_DeadBandMode == PWM_Grip__B_PWM__DBM_2_4_CLOCKS)
                PWM_Grip_WriteDeadTime(PWM_Grip_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Grip_KillModeMinTime)
                PWM_Grip_WriteKillTime(PWM_Grip_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Grip_KillModeMinTime) */

            #if(PWM_Grip_UseControl)
                PWM_Grip_WriteControlRegister(PWM_Grip_backup.PWMControlRegister);
            #endif /* (PWM_Grip_UseControl) */
        #endif  /* (!PWM_Grip_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Grip_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Grip_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Grip_Sleep(void) 
{
    #if(PWM_Grip_UseControl)
        if(PWM_Grip_CTRL_ENABLE == (PWM_Grip_CONTROL & PWM_Grip_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Grip_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Grip_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Grip_UseControl) */

    /* Stop component */
    PWM_Grip_Stop();

    /* Save registers configuration */
    PWM_Grip_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Grip_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Grip_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Grip_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Grip_RestoreConfig();

    if(PWM_Grip_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Grip_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
