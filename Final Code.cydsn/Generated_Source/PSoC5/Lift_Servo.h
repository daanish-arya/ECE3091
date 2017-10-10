/*******************************************************************************
* File Name: Lift_Servo.h  
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

#if !defined(CY_PINS_Lift_Servo_H) /* Pins Lift_Servo_H */
#define CY_PINS_Lift_Servo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Lift_Servo_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Lift_Servo__PORT == 15 && ((Lift_Servo__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Lift_Servo_Write(uint8 value);
void    Lift_Servo_SetDriveMode(uint8 mode);
uint8   Lift_Servo_ReadDataReg(void);
uint8   Lift_Servo_Read(void);
void    Lift_Servo_SetInterruptMode(uint16 position, uint16 mode);
uint8   Lift_Servo_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Lift_Servo_SetDriveMode() function.
     *  @{
     */
        #define Lift_Servo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Lift_Servo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Lift_Servo_DM_RES_UP          PIN_DM_RES_UP
        #define Lift_Servo_DM_RES_DWN         PIN_DM_RES_DWN
        #define Lift_Servo_DM_OD_LO           PIN_DM_OD_LO
        #define Lift_Servo_DM_OD_HI           PIN_DM_OD_HI
        #define Lift_Servo_DM_STRONG          PIN_DM_STRONG
        #define Lift_Servo_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Lift_Servo_MASK               Lift_Servo__MASK
#define Lift_Servo_SHIFT              Lift_Servo__SHIFT
#define Lift_Servo_WIDTH              1u

/* Interrupt constants */
#if defined(Lift_Servo__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Lift_Servo_SetInterruptMode() function.
     *  @{
     */
        #define Lift_Servo_INTR_NONE      (uint16)(0x0000u)
        #define Lift_Servo_INTR_RISING    (uint16)(0x0001u)
        #define Lift_Servo_INTR_FALLING   (uint16)(0x0002u)
        #define Lift_Servo_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Lift_Servo_INTR_MASK      (0x01u) 
#endif /* (Lift_Servo__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Lift_Servo_PS                     (* (reg8 *) Lift_Servo__PS)
/* Data Register */
#define Lift_Servo_DR                     (* (reg8 *) Lift_Servo__DR)
/* Port Number */
#define Lift_Servo_PRT_NUM                (* (reg8 *) Lift_Servo__PRT) 
/* Connect to Analog Globals */                                                  
#define Lift_Servo_AG                     (* (reg8 *) Lift_Servo__AG)                       
/* Analog MUX bux enable */
#define Lift_Servo_AMUX                   (* (reg8 *) Lift_Servo__AMUX) 
/* Bidirectional Enable */                                                        
#define Lift_Servo_BIE                    (* (reg8 *) Lift_Servo__BIE)
/* Bit-mask for Aliased Register Access */
#define Lift_Servo_BIT_MASK               (* (reg8 *) Lift_Servo__BIT_MASK)
/* Bypass Enable */
#define Lift_Servo_BYP                    (* (reg8 *) Lift_Servo__BYP)
/* Port wide control signals */                                                   
#define Lift_Servo_CTL                    (* (reg8 *) Lift_Servo__CTL)
/* Drive Modes */
#define Lift_Servo_DM0                    (* (reg8 *) Lift_Servo__DM0) 
#define Lift_Servo_DM1                    (* (reg8 *) Lift_Servo__DM1)
#define Lift_Servo_DM2                    (* (reg8 *) Lift_Servo__DM2) 
/* Input Buffer Disable Override */
#define Lift_Servo_INP_DIS                (* (reg8 *) Lift_Servo__INP_DIS)
/* LCD Common or Segment Drive */
#define Lift_Servo_LCD_COM_SEG            (* (reg8 *) Lift_Servo__LCD_COM_SEG)
/* Enable Segment LCD */
#define Lift_Servo_LCD_EN                 (* (reg8 *) Lift_Servo__LCD_EN)
/* Slew Rate Control */
#define Lift_Servo_SLW                    (* (reg8 *) Lift_Servo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Lift_Servo_PRTDSI__CAPS_SEL       (* (reg8 *) Lift_Servo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Lift_Servo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Lift_Servo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Lift_Servo_PRTDSI__OE_SEL0        (* (reg8 *) Lift_Servo__PRTDSI__OE_SEL0) 
#define Lift_Servo_PRTDSI__OE_SEL1        (* (reg8 *) Lift_Servo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Lift_Servo_PRTDSI__OUT_SEL0       (* (reg8 *) Lift_Servo__PRTDSI__OUT_SEL0) 
#define Lift_Servo_PRTDSI__OUT_SEL1       (* (reg8 *) Lift_Servo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Lift_Servo_PRTDSI__SYNC_OUT       (* (reg8 *) Lift_Servo__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Lift_Servo__SIO_CFG)
    #define Lift_Servo_SIO_HYST_EN        (* (reg8 *) Lift_Servo__SIO_HYST_EN)
    #define Lift_Servo_SIO_REG_HIFREQ     (* (reg8 *) Lift_Servo__SIO_REG_HIFREQ)
    #define Lift_Servo_SIO_CFG            (* (reg8 *) Lift_Servo__SIO_CFG)
    #define Lift_Servo_SIO_DIFF           (* (reg8 *) Lift_Servo__SIO_DIFF)
#endif /* (Lift_Servo__SIO_CFG) */

/* Interrupt Registers */
#if defined(Lift_Servo__INTSTAT)
    #define Lift_Servo_INTSTAT            (* (reg8 *) Lift_Servo__INTSTAT)
    #define Lift_Servo_SNAP               (* (reg8 *) Lift_Servo__SNAP)
    
	#define Lift_Servo_0_INTTYPE_REG 		(* (reg8 *) Lift_Servo__0__INTTYPE)
#endif /* (Lift_Servo__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Lift_Servo_H */


/* [] END OF FILE */
