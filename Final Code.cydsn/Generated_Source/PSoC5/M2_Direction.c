/*******************************************************************************
* File Name: M2_Direction.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "M2_Direction.h"

/* Check for removal by optimization */
#if !defined(M2_Direction_Sync_ctrl_reg__REMOVED)

    
/*******************************************************************************
* Function Name: M2_Direction_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void M2_Direction_Write(uint8 control) 
{
    M2_Direction_Control = control;
}


/*******************************************************************************
* Function Name: M2_Direction_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 M2_Direction_Read(void) 
{
    return M2_Direction_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
