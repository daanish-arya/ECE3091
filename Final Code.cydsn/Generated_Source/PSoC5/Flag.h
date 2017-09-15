/*******************************************************************************
* File Name: Flag.h  
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

#if !defined(CY_PINS_Flag_H) /* Pins Flag_H */
#define CY_PINS_Flag_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Flag_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Flag__PORT == 15 && ((Flag__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Flag_Write(uint8 value);
void    Flag_SetDriveMode(uint8 mode);
uint8   Flag_ReadDataReg(void);
uint8   Flag_Read(void);
void    Flag_SetInterruptMode(uint16 position, uint16 mode);
uint8   Flag_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Flag_SetDriveMode() function.
     *  @{
     */
        #define Flag_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Flag_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Flag_DM_RES_UP          PIN_DM_RES_UP
        #define Flag_DM_RES_DWN         PIN_DM_RES_DWN
        #define Flag_DM_OD_LO           PIN_DM_OD_LO
        #define Flag_DM_OD_HI           PIN_DM_OD_HI
        #define Flag_DM_STRONG          PIN_DM_STRONG
        #define Flag_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Flag_MASK               Flag__MASK
#define Flag_SHIFT              Flag__SHIFT
#define Flag_WIDTH              1u

/* Interrupt constants */
#if defined(Flag__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Flag_SetInterruptMode() function.
     *  @{
     */
        #define Flag_INTR_NONE      (uint16)(0x0000u)
        #define Flag_INTR_RISING    (uint16)(0x0001u)
        #define Flag_INTR_FALLING   (uint16)(0x0002u)
        #define Flag_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Flag_INTR_MASK      (0x01u) 
#endif /* (Flag__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Flag_PS                     (* (reg8 *) Flag__PS)
/* Data Register */
#define Flag_DR                     (* (reg8 *) Flag__DR)
/* Port Number */
#define Flag_PRT_NUM                (* (reg8 *) Flag__PRT) 
/* Connect to Analog Globals */                                                  
#define Flag_AG                     (* (reg8 *) Flag__AG)                       
/* Analog MUX bux enable */
#define Flag_AMUX                   (* (reg8 *) Flag__AMUX) 
/* Bidirectional Enable */                                                        
#define Flag_BIE                    (* (reg8 *) Flag__BIE)
/* Bit-mask for Aliased Register Access */
#define Flag_BIT_MASK               (* (reg8 *) Flag__BIT_MASK)
/* Bypass Enable */
#define Flag_BYP                    (* (reg8 *) Flag__BYP)
/* Port wide control signals */                                                   
#define Flag_CTL                    (* (reg8 *) Flag__CTL)
/* Drive Modes */
#define Flag_DM0                    (* (reg8 *) Flag__DM0) 
#define Flag_DM1                    (* (reg8 *) Flag__DM1)
#define Flag_DM2                    (* (reg8 *) Flag__DM2) 
/* Input Buffer Disable Override */
#define Flag_INP_DIS                (* (reg8 *) Flag__INP_DIS)
/* LCD Common or Segment Drive */
#define Flag_LCD_COM_SEG            (* (reg8 *) Flag__LCD_COM_SEG)
/* Enable Segment LCD */
#define Flag_LCD_EN                 (* (reg8 *) Flag__LCD_EN)
/* Slew Rate Control */
#define Flag_SLW                    (* (reg8 *) Flag__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Flag_PRTDSI__CAPS_SEL       (* (reg8 *) Flag__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Flag_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Flag__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Flag_PRTDSI__OE_SEL0        (* (reg8 *) Flag__PRTDSI__OE_SEL0) 
#define Flag_PRTDSI__OE_SEL1        (* (reg8 *) Flag__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Flag_PRTDSI__OUT_SEL0       (* (reg8 *) Flag__PRTDSI__OUT_SEL0) 
#define Flag_PRTDSI__OUT_SEL1       (* (reg8 *) Flag__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Flag_PRTDSI__SYNC_OUT       (* (reg8 *) Flag__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Flag__SIO_CFG)
    #define Flag_SIO_HYST_EN        (* (reg8 *) Flag__SIO_HYST_EN)
    #define Flag_SIO_REG_HIFREQ     (* (reg8 *) Flag__SIO_REG_HIFREQ)
    #define Flag_SIO_CFG            (* (reg8 *) Flag__SIO_CFG)
    #define Flag_SIO_DIFF           (* (reg8 *) Flag__SIO_DIFF)
#endif /* (Flag__SIO_CFG) */

/* Interrupt Registers */
#if defined(Flag__INTSTAT)
    #define Flag_INTSTAT            (* (reg8 *) Flag__INTSTAT)
    #define Flag_SNAP               (* (reg8 *) Flag__SNAP)
    
	#define Flag_0_INTTYPE_REG 		(* (reg8 *) Flag__0__INTTYPE)
#endif /* (Flag__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Flag_H */


/* [] END OF FILE */
