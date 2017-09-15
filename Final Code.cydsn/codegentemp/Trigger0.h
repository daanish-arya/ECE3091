/*******************************************************************************
* File Name: Trigger0.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Trigger0_H) /* Pins Trigger0_H */
#define CY_PINS_Trigger0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Trigger0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Trigger0__PORT == 15 && ((Trigger0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Trigger0_Write(uint8 value);
void    Trigger0_SetDriveMode(uint8 mode);
uint8   Trigger0_ReadDataReg(void);
uint8   Trigger0_Read(void);
void    Trigger0_SetInterruptMode(uint16 position, uint16 mode);
uint8   Trigger0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Trigger0_SetDriveMode() function.
     *  @{
     */
        #define Trigger0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Trigger0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Trigger0_DM_RES_UP          PIN_DM_RES_UP
        #define Trigger0_DM_RES_DWN         PIN_DM_RES_DWN
        #define Trigger0_DM_OD_LO           PIN_DM_OD_LO
        #define Trigger0_DM_OD_HI           PIN_DM_OD_HI
        #define Trigger0_DM_STRONG          PIN_DM_STRONG
        #define Trigger0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Trigger0_MASK               Trigger0__MASK
#define Trigger0_SHIFT              Trigger0__SHIFT
#define Trigger0_WIDTH              1u

/* Interrupt constants */
#if defined(Trigger0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Trigger0_SetInterruptMode() function.
     *  @{
     */
        #define Trigger0_INTR_NONE      (uint16)(0x0000u)
        #define Trigger0_INTR_RISING    (uint16)(0x0001u)
        #define Trigger0_INTR_FALLING   (uint16)(0x0002u)
        #define Trigger0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Trigger0_INTR_MASK      (0x01u) 
#endif /* (Trigger0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Trigger0_PS                     (* (reg8 *) Trigger0__PS)
/* Data Register */
#define Trigger0_DR                     (* (reg8 *) Trigger0__DR)
/* Port Number */
#define Trigger0_PRT_NUM                (* (reg8 *) Trigger0__PRT) 
/* Connect to Analog Globals */                                                  
#define Trigger0_AG                     (* (reg8 *) Trigger0__AG)                       
/* Analog MUX bux enable */
#define Trigger0_AMUX                   (* (reg8 *) Trigger0__AMUX) 
/* Bidirectional Enable */                                                        
#define Trigger0_BIE                    (* (reg8 *) Trigger0__BIE)
/* Bit-mask for Aliased Register Access */
#define Trigger0_BIT_MASK               (* (reg8 *) Trigger0__BIT_MASK)
/* Bypass Enable */
#define Trigger0_BYP                    (* (reg8 *) Trigger0__BYP)
/* Port wide control signals */                                                   
#define Trigger0_CTL                    (* (reg8 *) Trigger0__CTL)
/* Drive Modes */
#define Trigger0_DM0                    (* (reg8 *) Trigger0__DM0) 
#define Trigger0_DM1                    (* (reg8 *) Trigger0__DM1)
#define Trigger0_DM2                    (* (reg8 *) Trigger0__DM2) 
/* Input Buffer Disable Override */
#define Trigger0_INP_DIS                (* (reg8 *) Trigger0__INP_DIS)
/* LCD Common or Segment Drive */
#define Trigger0_LCD_COM_SEG            (* (reg8 *) Trigger0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Trigger0_LCD_EN                 (* (reg8 *) Trigger0__LCD_EN)
/* Slew Rate Control */
#define Trigger0_SLW                    (* (reg8 *) Trigger0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Trigger0_PRTDSI__CAPS_SEL       (* (reg8 *) Trigger0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Trigger0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Trigger0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Trigger0_PRTDSI__OE_SEL0        (* (reg8 *) Trigger0__PRTDSI__OE_SEL0) 
#define Trigger0_PRTDSI__OE_SEL1        (* (reg8 *) Trigger0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Trigger0_PRTDSI__OUT_SEL0       (* (reg8 *) Trigger0__PRTDSI__OUT_SEL0) 
#define Trigger0_PRTDSI__OUT_SEL1       (* (reg8 *) Trigger0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Trigger0_PRTDSI__SYNC_OUT       (* (reg8 *) Trigger0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Trigger0__SIO_CFG)
    #define Trigger0_SIO_HYST_EN        (* (reg8 *) Trigger0__SIO_HYST_EN)
    #define Trigger0_SIO_REG_HIFREQ     (* (reg8 *) Trigger0__SIO_REG_HIFREQ)
    #define Trigger0_SIO_CFG            (* (reg8 *) Trigger0__SIO_CFG)
    #define Trigger0_SIO_DIFF           (* (reg8 *) Trigger0__SIO_DIFF)
#endif /* (Trigger0__SIO_CFG) */

/* Interrupt Registers */
#if defined(Trigger0__INTSTAT)
    #define Trigger0_INTSTAT            (* (reg8 *) Trigger0__INTSTAT)
    #define Trigger0_SNAP               (* (reg8 *) Trigger0__SNAP)
    
	#define Trigger0_0_INTTYPE_REG 		(* (reg8 *) Trigger0__0__INTTYPE)
#endif /* (Trigger0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Trigger0_H */


/* [] END OF FILE */
