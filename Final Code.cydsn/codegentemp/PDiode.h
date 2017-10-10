/*******************************************************************************
* File Name: PDiode.h  
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

#if !defined(CY_PINS_PDiode_H) /* Pins PDiode_H */
#define CY_PINS_PDiode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PDiode_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PDiode__PORT == 15 && ((PDiode__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PDiode_Write(uint8 value);
void    PDiode_SetDriveMode(uint8 mode);
uint8   PDiode_ReadDataReg(void);
uint8   PDiode_Read(void);
void    PDiode_SetInterruptMode(uint16 position, uint16 mode);
uint8   PDiode_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PDiode_SetDriveMode() function.
     *  @{
     */
        #define PDiode_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PDiode_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PDiode_DM_RES_UP          PIN_DM_RES_UP
        #define PDiode_DM_RES_DWN         PIN_DM_RES_DWN
        #define PDiode_DM_OD_LO           PIN_DM_OD_LO
        #define PDiode_DM_OD_HI           PIN_DM_OD_HI
        #define PDiode_DM_STRONG          PIN_DM_STRONG
        #define PDiode_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PDiode_MASK               PDiode__MASK
#define PDiode_SHIFT              PDiode__SHIFT
#define PDiode_WIDTH              1u

/* Interrupt constants */
#if defined(PDiode__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PDiode_SetInterruptMode() function.
     *  @{
     */
        #define PDiode_INTR_NONE      (uint16)(0x0000u)
        #define PDiode_INTR_RISING    (uint16)(0x0001u)
        #define PDiode_INTR_FALLING   (uint16)(0x0002u)
        #define PDiode_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PDiode_INTR_MASK      (0x01u) 
#endif /* (PDiode__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PDiode_PS                     (* (reg8 *) PDiode__PS)
/* Data Register */
#define PDiode_DR                     (* (reg8 *) PDiode__DR)
/* Port Number */
#define PDiode_PRT_NUM                (* (reg8 *) PDiode__PRT) 
/* Connect to Analog Globals */                                                  
#define PDiode_AG                     (* (reg8 *) PDiode__AG)                       
/* Analog MUX bux enable */
#define PDiode_AMUX                   (* (reg8 *) PDiode__AMUX) 
/* Bidirectional Enable */                                                        
#define PDiode_BIE                    (* (reg8 *) PDiode__BIE)
/* Bit-mask for Aliased Register Access */
#define PDiode_BIT_MASK               (* (reg8 *) PDiode__BIT_MASK)
/* Bypass Enable */
#define PDiode_BYP                    (* (reg8 *) PDiode__BYP)
/* Port wide control signals */                                                   
#define PDiode_CTL                    (* (reg8 *) PDiode__CTL)
/* Drive Modes */
#define PDiode_DM0                    (* (reg8 *) PDiode__DM0) 
#define PDiode_DM1                    (* (reg8 *) PDiode__DM1)
#define PDiode_DM2                    (* (reg8 *) PDiode__DM2) 
/* Input Buffer Disable Override */
#define PDiode_INP_DIS                (* (reg8 *) PDiode__INP_DIS)
/* LCD Common or Segment Drive */
#define PDiode_LCD_COM_SEG            (* (reg8 *) PDiode__LCD_COM_SEG)
/* Enable Segment LCD */
#define PDiode_LCD_EN                 (* (reg8 *) PDiode__LCD_EN)
/* Slew Rate Control */
#define PDiode_SLW                    (* (reg8 *) PDiode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PDiode_PRTDSI__CAPS_SEL       (* (reg8 *) PDiode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PDiode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PDiode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PDiode_PRTDSI__OE_SEL0        (* (reg8 *) PDiode__PRTDSI__OE_SEL0) 
#define PDiode_PRTDSI__OE_SEL1        (* (reg8 *) PDiode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PDiode_PRTDSI__OUT_SEL0       (* (reg8 *) PDiode__PRTDSI__OUT_SEL0) 
#define PDiode_PRTDSI__OUT_SEL1       (* (reg8 *) PDiode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PDiode_PRTDSI__SYNC_OUT       (* (reg8 *) PDiode__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PDiode__SIO_CFG)
    #define PDiode_SIO_HYST_EN        (* (reg8 *) PDiode__SIO_HYST_EN)
    #define PDiode_SIO_REG_HIFREQ     (* (reg8 *) PDiode__SIO_REG_HIFREQ)
    #define PDiode_SIO_CFG            (* (reg8 *) PDiode__SIO_CFG)
    #define PDiode_SIO_DIFF           (* (reg8 *) PDiode__SIO_DIFF)
#endif /* (PDiode__SIO_CFG) */

/* Interrupt Registers */
#if defined(PDiode__INTSTAT)
    #define PDiode_INTSTAT            (* (reg8 *) PDiode__INTSTAT)
    #define PDiode_SNAP               (* (reg8 *) PDiode__SNAP)
    
	#define PDiode_0_INTTYPE_REG 		(* (reg8 *) PDiode__0__INTTYPE)
#endif /* (PDiode__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PDiode_H */


/* [] END OF FILE */
