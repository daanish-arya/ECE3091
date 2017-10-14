/*******************************************************************************
* File Name: Echo_F.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Echo_F_ALIASES_H) /* Pins Echo_F_ALIASES_H */
#define CY_PINS_Echo_F_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Echo_F_0			(Echo_F__0__PC)
#define Echo_F_0_INTR	((uint16)((uint16)0x0001u << Echo_F__0__SHIFT))

#define Echo_F_INTR_ALL	 ((uint16)(Echo_F_0_INTR))

#endif /* End Pins Echo_F_ALIASES_H */


/* [] END OF FILE */
