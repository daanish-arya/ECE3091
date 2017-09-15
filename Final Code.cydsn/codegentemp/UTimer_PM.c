/*******************************************************************************
* File Name: UTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "UTimer.h"

static UTimer_backupStruct UTimer_backup;


/*******************************************************************************
* Function Name: UTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void UTimer_SaveConfig(void) 
{
    #if (!UTimer_UsingFixedFunction)
        UTimer_backup.TimerUdb = UTimer_ReadCounter();
        UTimer_backup.InterruptMaskValue = UTimer_STATUS_MASK;
        #if (UTimer_UsingHWCaptureCounter)
            UTimer_backup.TimerCaptureCounter = UTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!UTimer_UDB_CONTROL_REG_REMOVED)
            UTimer_backup.TimerControlRegister = UTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: UTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void UTimer_RestoreConfig(void) 
{   
    #if (!UTimer_UsingFixedFunction)

        UTimer_WriteCounter(UTimer_backup.TimerUdb);
        UTimer_STATUS_MASK =UTimer_backup.InterruptMaskValue;
        #if (UTimer_UsingHWCaptureCounter)
            UTimer_SetCaptureCount(UTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!UTimer_UDB_CONTROL_REG_REMOVED)
            UTimer_WriteControlRegister(UTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: UTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void UTimer_Sleep(void) 
{
    #if(!UTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(UTimer_CTRL_ENABLE == (UTimer_CONTROL & UTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            UTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            UTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    UTimer_Stop();
    UTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: UTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void UTimer_Wakeup(void) 
{
    UTimer_RestoreConfig();
    #if(!UTimer_UDB_CONTROL_REG_REMOVED)
        if(UTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                UTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
