/*******************************************************************************
* File Name: Phase_R_A.h  
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

#if !defined(CY_PINS_Phase_R_A_H) /* Pins Phase_R_A_H */
#define CY_PINS_Phase_R_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Phase_R_A_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Phase_R_A__PORT == 15 && ((Phase_R_A__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Phase_R_A_Write(uint8 value);
void    Phase_R_A_SetDriveMode(uint8 mode);
uint8   Phase_R_A_ReadDataReg(void);
uint8   Phase_R_A_Read(void);
void    Phase_R_A_SetInterruptMode(uint16 position, uint16 mode);
uint8   Phase_R_A_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Phase_R_A_SetDriveMode() function.
     *  @{
     */
        #define Phase_R_A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Phase_R_A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Phase_R_A_DM_RES_UP          PIN_DM_RES_UP
        #define Phase_R_A_DM_RES_DWN         PIN_DM_RES_DWN
        #define Phase_R_A_DM_OD_LO           PIN_DM_OD_LO
        #define Phase_R_A_DM_OD_HI           PIN_DM_OD_HI
        #define Phase_R_A_DM_STRONG          PIN_DM_STRONG
        #define Phase_R_A_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Phase_R_A_MASK               Phase_R_A__MASK
#define Phase_R_A_SHIFT              Phase_R_A__SHIFT
#define Phase_R_A_WIDTH              1u

/* Interrupt constants */
#if defined(Phase_R_A__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Phase_R_A_SetInterruptMode() function.
     *  @{
     */
        #define Phase_R_A_INTR_NONE      (uint16)(0x0000u)
        #define Phase_R_A_INTR_RISING    (uint16)(0x0001u)
        #define Phase_R_A_INTR_FALLING   (uint16)(0x0002u)
        #define Phase_R_A_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Phase_R_A_INTR_MASK      (0x01u) 
#endif /* (Phase_R_A__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Phase_R_A_PS                     (* (reg8 *) Phase_R_A__PS)
/* Data Register */
#define Phase_R_A_DR                     (* (reg8 *) Phase_R_A__DR)
/* Port Number */
#define Phase_R_A_PRT_NUM                (* (reg8 *) Phase_R_A__PRT) 
/* Connect to Analog Globals */                                                  
#define Phase_R_A_AG                     (* (reg8 *) Phase_R_A__AG)                       
/* Analog MUX bux enable */
#define Phase_R_A_AMUX                   (* (reg8 *) Phase_R_A__AMUX) 
/* Bidirectional Enable */                                                        
#define Phase_R_A_BIE                    (* (reg8 *) Phase_R_A__BIE)
/* Bit-mask for Aliased Register Access */
#define Phase_R_A_BIT_MASK               (* (reg8 *) Phase_R_A__BIT_MASK)
/* Bypass Enable */
#define Phase_R_A_BYP                    (* (reg8 *) Phase_R_A__BYP)
/* Port wide control signals */                                                   
#define Phase_R_A_CTL                    (* (reg8 *) Phase_R_A__CTL)
/* Drive Modes */
#define Phase_R_A_DM0                    (* (reg8 *) Phase_R_A__DM0) 
#define Phase_R_A_DM1                    (* (reg8 *) Phase_R_A__DM1)
#define Phase_R_A_DM2                    (* (reg8 *) Phase_R_A__DM2) 
/* Input Buffer Disable Override */
#define Phase_R_A_INP_DIS                (* (reg8 *) Phase_R_A__INP_DIS)
/* LCD Common or Segment Drive */
#define Phase_R_A_LCD_COM_SEG            (* (reg8 *) Phase_R_A__LCD_COM_SEG)
/* Enable Segment LCD */
#define Phase_R_A_LCD_EN                 (* (reg8 *) Phase_R_A__LCD_EN)
/* Slew Rate Control */
#define Phase_R_A_SLW                    (* (reg8 *) Phase_R_A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Phase_R_A_PRTDSI__CAPS_SEL       (* (reg8 *) Phase_R_A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Phase_R_A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Phase_R_A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Phase_R_A_PRTDSI__OE_SEL0        (* (reg8 *) Phase_R_A__PRTDSI__OE_SEL0) 
#define Phase_R_A_PRTDSI__OE_SEL1        (* (reg8 *) Phase_R_A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Phase_R_A_PRTDSI__OUT_SEL0       (* (reg8 *) Phase_R_A__PRTDSI__OUT_SEL0) 
#define Phase_R_A_PRTDSI__OUT_SEL1       (* (reg8 *) Phase_R_A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Phase_R_A_PRTDSI__SYNC_OUT       (* (reg8 *) Phase_R_A__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Phase_R_A__SIO_CFG)
    #define Phase_R_A_SIO_HYST_EN        (* (reg8 *) Phase_R_A__SIO_HYST_EN)
    #define Phase_R_A_SIO_REG_HIFREQ     (* (reg8 *) Phase_R_A__SIO_REG_HIFREQ)
    #define Phase_R_A_SIO_CFG            (* (reg8 *) Phase_R_A__SIO_CFG)
    #define Phase_R_A_SIO_DIFF           (* (reg8 *) Phase_R_A__SIO_DIFF)
#endif /* (Phase_R_A__SIO_CFG) */

/* Interrupt Registers */
#if defined(Phase_R_A__INTSTAT)
    #define Phase_R_A_INTSTAT            (* (reg8 *) Phase_R_A__INTSTAT)
    #define Phase_R_A_SNAP               (* (reg8 *) Phase_R_A__SNAP)
    
	#define Phase_R_A_0_INTTYPE_REG 		(* (reg8 *) Phase_R_A__0__INTTYPE)
#endif /* (Phase_R_A__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Phase_R_A_H */


/* [] END OF FILE */
