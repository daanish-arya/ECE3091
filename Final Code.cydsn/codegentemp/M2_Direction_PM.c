/*******************************************************************************
* File Name: M2_Direction_PM.c
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

#include "M2_Direction.h"

/* Check for removal by optimization */
#if !defined(M2_Direction_Sync_ctrl_reg__REMOVED)

static M2_Direction_BACKUP_STRUCT  M2_Direction_backup = {0u};

    
/*******************************************************************************
* Function Name: M2_Direction_SaveConfig
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
void M2_Direction_SaveConfig(void) 
{
    M2_Direction_backup.controlState = M2_Direction_Control;
}


/*******************************************************************************
* Function Name: M2_Direction_RestoreConfig
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
void M2_Direction_RestoreConfig(void) 
{
     M2_Direction_Control = M2_Direction_backup.controlState;
}


/*******************************************************************************
* Function Name: M2_Direction_Sleep
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
void M2_Direction_Sleep(void) 
{
    M2_Direction_SaveConfig();
}


/*******************************************************************************
* Function Name: M2_Direction_Wakeup
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
void M2_Direction_Wakeup(void)  
{
    M2_Direction_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
