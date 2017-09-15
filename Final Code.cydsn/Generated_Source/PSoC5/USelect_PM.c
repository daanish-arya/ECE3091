/*******************************************************************************
* File Name: USelect_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "USelect.h"

/* Check for removal by optimization */
#if !defined(USelect_Sync_ctrl_reg__REMOVED)

static USelect_BACKUP_STRUCT  USelect_backup = {0u};

    
/*******************************************************************************
* Function Name: USelect_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void USelect_SaveConfig(void) 
{
    USelect_backup.controlState = USelect_Control;
}


/*******************************************************************************
* Function Name: USelect_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void USelect_RestoreConfig(void) 
{
     USelect_Control = USelect_backup.controlState;
}


/*******************************************************************************
* Function Name: USelect_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void USelect_Sleep(void) 
{
    USelect_SaveConfig();
}


/*******************************************************************************
* Function Name: USelect_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void USelect_Wakeup(void)  
{
    USelect_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
