/*******************************************************************************
* File Name: Echo0.h  
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

#if !defined(CY_PINS_Echo0_H) /* Pins Echo0_H */
#define CY_PINS_Echo0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Echo0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Echo0__PORT == 15 && ((Echo0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Echo0_Write(uint8 value);
void    Echo0_SetDriveMode(uint8 mode);
uint8   Echo0_ReadDataReg(void);
uint8   Echo0_Read(void);
void    Echo0_SetInterruptMode(uint16 position, uint16 mode);
uint8   Echo0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Echo0_SetDriveMode() function.
     *  @{
     */
        #define Echo0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Echo0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Echo0_DM_RES_UP          PIN_DM_RES_UP
        #define Echo0_DM_RES_DWN         PIN_DM_RES_DWN
        #define Echo0_DM_OD_LO           PIN_DM_OD_LO
        #define Echo0_DM_OD_HI           PIN_DM_OD_HI
        #define Echo0_DM_STRONG          PIN_DM_STRONG
        #define Echo0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Echo0_MASK               Echo0__MASK
#define Echo0_SHIFT              Echo0__SHIFT
#define Echo0_WIDTH              1u

/* Interrupt constants */
#if defined(Echo0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Echo0_SetInterruptMode() function.
     *  @{
     */
        #define Echo0_INTR_NONE      (uint16)(0x0000u)
        #define Echo0_INTR_RISING    (uint16)(0x0001u)
        #define Echo0_INTR_FALLING   (uint16)(0x0002u)
        #define Echo0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Echo0_INTR_MASK      (0x01u) 
#endif /* (Echo0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Echo0_PS                     (* (reg8 *) Echo0__PS)
/* Data Register */
#define Echo0_DR                     (* (reg8 *) Echo0__DR)
/* Port Number */
#define Echo0_PRT_NUM                (* (reg8 *) Echo0__PRT) 
/* Connect to Analog Globals */                                                  
#define Echo0_AG                     (* (reg8 *) Echo0__AG)                       
/* Analog MUX bux enable */
#define Echo0_AMUX                   (* (reg8 *) Echo0__AMUX) 
/* Bidirectional Enable */                                                        
#define Echo0_BIE                    (* (reg8 *) Echo0__BIE)
/* Bit-mask for Aliased Register Access */
#define Echo0_BIT_MASK               (* (reg8 *) Echo0__BIT_MASK)
/* Bypass Enable */
#define Echo0_BYP                    (* (reg8 *) Echo0__BYP)
/* Port wide control signals */                                                   
#define Echo0_CTL                    (* (reg8 *) Echo0__CTL)
/* Drive Modes */
#define Echo0_DM0                    (* (reg8 *) Echo0__DM0) 
#define Echo0_DM1                    (* (reg8 *) Echo0__DM1)
#define Echo0_DM2                    (* (reg8 *) Echo0__DM2) 
/* Input Buffer Disable Override */
#define Echo0_INP_DIS                (* (reg8 *) Echo0__INP_DIS)
/* LCD Common or Segment Drive */
#define Echo0_LCD_COM_SEG            (* (reg8 *) Echo0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Echo0_LCD_EN                 (* (reg8 *) Echo0__LCD_EN)
/* Slew Rate Control */
#define Echo0_SLW                    (* (reg8 *) Echo0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Echo0_PRTDSI__CAPS_SEL       (* (reg8 *) Echo0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Echo0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Echo0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Echo0_PRTDSI__OE_SEL0        (* (reg8 *) Echo0__PRTDSI__OE_SEL0) 
#define Echo0_PRTDSI__OE_SEL1        (* (reg8 *) Echo0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Echo0_PRTDSI__OUT_SEL0       (* (reg8 *) Echo0__PRTDSI__OUT_SEL0) 
#define Echo0_PRTDSI__OUT_SEL1       (* (reg8 *) Echo0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Echo0_PRTDSI__SYNC_OUT       (* (reg8 *) Echo0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Echo0__SIO_CFG)
    #define Echo0_SIO_HYST_EN        (* (reg8 *) Echo0__SIO_HYST_EN)
    #define Echo0_SIO_REG_HIFREQ     (* (reg8 *) Echo0__SIO_REG_HIFREQ)
    #define Echo0_SIO_CFG            (* (reg8 *) Echo0__SIO_CFG)
    #define Echo0_SIO_DIFF           (* (reg8 *) Echo0__SIO_DIFF)
#endif /* (Echo0__SIO_CFG) */

/* Interrupt Registers */
#if defined(Echo0__INTSTAT)
    #define Echo0_INTSTAT            (* (reg8 *) Echo0__INTSTAT)
    #define Echo0_SNAP               (* (reg8 *) Echo0__SNAP)
    
	#define Echo0_0_INTTYPE_REG 		(* (reg8 *) Echo0__0__INTTYPE)
#endif /* (Echo0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Echo0_H */


/* [] END OF FILE */
