/*******************************************************************************
* File Name: Trigger_F1.h  
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

#if !defined(CY_PINS_Trigger_F1_H) /* Pins Trigger_F1_H */
#define CY_PINS_Trigger_F1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Trigger_F1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Trigger_F1__PORT == 15 && ((Trigger_F1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Trigger_F1_Write(uint8 value);
void    Trigger_F1_SetDriveMode(uint8 mode);
uint8   Trigger_F1_ReadDataReg(void);
uint8   Trigger_F1_Read(void);
void    Trigger_F1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Trigger_F1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Trigger_F1_SetDriveMode() function.
     *  @{
     */
        #define Trigger_F1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Trigger_F1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Trigger_F1_DM_RES_UP          PIN_DM_RES_UP
        #define Trigger_F1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Trigger_F1_DM_OD_LO           PIN_DM_OD_LO
        #define Trigger_F1_DM_OD_HI           PIN_DM_OD_HI
        #define Trigger_F1_DM_STRONG          PIN_DM_STRONG
        #define Trigger_F1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Trigger_F1_MASK               Trigger_F1__MASK
#define Trigger_F1_SHIFT              Trigger_F1__SHIFT
#define Trigger_F1_WIDTH              1u

/* Interrupt constants */
#if defined(Trigger_F1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Trigger_F1_SetInterruptMode() function.
     *  @{
     */
        #define Trigger_F1_INTR_NONE      (uint16)(0x0000u)
        #define Trigger_F1_INTR_RISING    (uint16)(0x0001u)
        #define Trigger_F1_INTR_FALLING   (uint16)(0x0002u)
        #define Trigger_F1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Trigger_F1_INTR_MASK      (0x01u) 
#endif /* (Trigger_F1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Trigger_F1_PS                     (* (reg8 *) Trigger_F1__PS)
/* Data Register */
#define Trigger_F1_DR                     (* (reg8 *) Trigger_F1__DR)
/* Port Number */
#define Trigger_F1_PRT_NUM                (* (reg8 *) Trigger_F1__PRT) 
/* Connect to Analog Globals */                                                  
#define Trigger_F1_AG                     (* (reg8 *) Trigger_F1__AG)                       
/* Analog MUX bux enable */
#define Trigger_F1_AMUX                   (* (reg8 *) Trigger_F1__AMUX) 
/* Bidirectional Enable */                                                        
#define Trigger_F1_BIE                    (* (reg8 *) Trigger_F1__BIE)
/* Bit-mask for Aliased Register Access */
#define Trigger_F1_BIT_MASK               (* (reg8 *) Trigger_F1__BIT_MASK)
/* Bypass Enable */
#define Trigger_F1_BYP                    (* (reg8 *) Trigger_F1__BYP)
/* Port wide control signals */                                                   
#define Trigger_F1_CTL                    (* (reg8 *) Trigger_F1__CTL)
/* Drive Modes */
#define Trigger_F1_DM0                    (* (reg8 *) Trigger_F1__DM0) 
#define Trigger_F1_DM1                    (* (reg8 *) Trigger_F1__DM1)
#define Trigger_F1_DM2                    (* (reg8 *) Trigger_F1__DM2) 
/* Input Buffer Disable Override */
#define Trigger_F1_INP_DIS                (* (reg8 *) Trigger_F1__INP_DIS)
/* LCD Common or Segment Drive */
#define Trigger_F1_LCD_COM_SEG            (* (reg8 *) Trigger_F1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Trigger_F1_LCD_EN                 (* (reg8 *) Trigger_F1__LCD_EN)
/* Slew Rate Control */
#define Trigger_F1_SLW                    (* (reg8 *) Trigger_F1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Trigger_F1_PRTDSI__CAPS_SEL       (* (reg8 *) Trigger_F1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Trigger_F1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Trigger_F1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Trigger_F1_PRTDSI__OE_SEL0        (* (reg8 *) Trigger_F1__PRTDSI__OE_SEL0) 
#define Trigger_F1_PRTDSI__OE_SEL1        (* (reg8 *) Trigger_F1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Trigger_F1_PRTDSI__OUT_SEL0       (* (reg8 *) Trigger_F1__PRTDSI__OUT_SEL0) 
#define Trigger_F1_PRTDSI__OUT_SEL1       (* (reg8 *) Trigger_F1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Trigger_F1_PRTDSI__SYNC_OUT       (* (reg8 *) Trigger_F1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Trigger_F1__SIO_CFG)
    #define Trigger_F1_SIO_HYST_EN        (* (reg8 *) Trigger_F1__SIO_HYST_EN)
    #define Trigger_F1_SIO_REG_HIFREQ     (* (reg8 *) Trigger_F1__SIO_REG_HIFREQ)
    #define Trigger_F1_SIO_CFG            (* (reg8 *) Trigger_F1__SIO_CFG)
    #define Trigger_F1_SIO_DIFF           (* (reg8 *) Trigger_F1__SIO_DIFF)
#endif /* (Trigger_F1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Trigger_F1__INTSTAT)
    #define Trigger_F1_INTSTAT            (* (reg8 *) Trigger_F1__INTSTAT)
    #define Trigger_F1_SNAP               (* (reg8 *) Trigger_F1__SNAP)
    
	#define Trigger_F1_0_INTTYPE_REG 		(* (reg8 *) Trigger_F1__0__INTTYPE)
#endif /* (Trigger_F1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Trigger_F1_H */


/* [] END OF FILE */
