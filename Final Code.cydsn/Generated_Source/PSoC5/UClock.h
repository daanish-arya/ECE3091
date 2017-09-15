/*******************************************************************************
* File Name: UClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_UClock_H)
#define CY_CLOCK_UClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void UClock_Start(void) ;
void UClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void UClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void UClock_StandbyPower(uint8 state) ;
void UClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 UClock_GetDividerRegister(void) ;
void UClock_SetModeRegister(uint8 modeBitMask) ;
void UClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 UClock_GetModeRegister(void) ;
void UClock_SetSourceRegister(uint8 clkSource) ;
uint8 UClock_GetSourceRegister(void) ;
#if defined(UClock__CFG3)
void UClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 UClock_GetPhaseRegister(void) ;
#endif /* defined(UClock__CFG3) */

#define UClock_Enable()                       UClock_Start()
#define UClock_Disable()                      UClock_Stop()
#define UClock_SetDivider(clkDivider)         UClock_SetDividerRegister(clkDivider, 1u)
#define UClock_SetDividerValue(clkDivider)    UClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define UClock_SetMode(clkMode)               UClock_SetModeRegister(clkMode)
#define UClock_SetSource(clkSource)           UClock_SetSourceRegister(clkSource)
#if defined(UClock__CFG3)
#define UClock_SetPhase(clkPhase)             UClock_SetPhaseRegister(clkPhase)
#define UClock_SetPhaseValue(clkPhase)        UClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(UClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define UClock_CLKEN              (* (reg8 *) UClock__PM_ACT_CFG)
#define UClock_CLKEN_PTR          ((reg8 *) UClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define UClock_CLKSTBY            (* (reg8 *) UClock__PM_STBY_CFG)
#define UClock_CLKSTBY_PTR        ((reg8 *) UClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define UClock_DIV_LSB            (* (reg8 *) UClock__CFG0)
#define UClock_DIV_LSB_PTR        ((reg8 *) UClock__CFG0)
#define UClock_DIV_PTR            ((reg16 *) UClock__CFG0)

/* Clock MSB divider configuration register. */
#define UClock_DIV_MSB            (* (reg8 *) UClock__CFG1)
#define UClock_DIV_MSB_PTR        ((reg8 *) UClock__CFG1)

/* Mode and source configuration register */
#define UClock_MOD_SRC            (* (reg8 *) UClock__CFG2)
#define UClock_MOD_SRC_PTR        ((reg8 *) UClock__CFG2)

#if defined(UClock__CFG3)
/* Analog clock phase configuration register */
#define UClock_PHASE              (* (reg8 *) UClock__CFG3)
#define UClock_PHASE_PTR          ((reg8 *) UClock__CFG3)
#endif /* defined(UClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define UClock_CLKEN_MASK         UClock__PM_ACT_MSK
#define UClock_CLKSTBY_MASK       UClock__PM_STBY_MSK

/* CFG2 field masks */
#define UClock_SRC_SEL_MSK        UClock__CFG2_SRC_SEL_MASK
#define UClock_MODE_MASK          (~(UClock_SRC_SEL_MSK))

#if defined(UClock__CFG3)
/* CFG3 phase mask */
#define UClock_PHASE_MASK         UClock__CFG3_PHASE_DLY_MASK
#endif /* defined(UClock__CFG3) */

#endif /* CY_CLOCK_UClock_H */


/* [] END OF FILE */
