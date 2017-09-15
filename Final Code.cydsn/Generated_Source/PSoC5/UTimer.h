/*******************************************************************************
* File Name: UTimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_UTimer_H)
#define CY_Timer_v2_60_UTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 UTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define UTimer_Resolution                 16u
#define UTimer_UsingFixedFunction         1u
#define UTimer_UsingHWCaptureCounter      0u
#define UTimer_SoftwareCaptureMode        0u
#define UTimer_SoftwareTriggerMode        0u
#define UTimer_UsingHWEnable              1u
#define UTimer_EnableTriggerMode          0u
#define UTimer_InterruptOnCaptureCount    0u
#define UTimer_RunModeUsed                0u
#define UTimer_ControlRegRemoved          0u

#if defined(UTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define UTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (UTimer_UsingFixedFunction)
    #define UTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define UTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End UTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!UTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (UTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!UTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}UTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    UTimer_Start(void) ;
void    UTimer_Stop(void) ;

void    UTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   UTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define UTimer_GetInterruptSource() UTimer_ReadStatusRegister()

#if(!UTimer_UDB_CONTROL_REG_REMOVED)
    uint8   UTimer_ReadControlRegister(void) ;
    void    UTimer_WriteControlRegister(uint8 control) ;
#endif /* (!UTimer_UDB_CONTROL_REG_REMOVED) */

uint16  UTimer_ReadPeriod(void) ;
void    UTimer_WritePeriod(uint16 period) ;
uint16  UTimer_ReadCounter(void) ;
void    UTimer_WriteCounter(uint16 counter) ;
uint16  UTimer_ReadCapture(void) ;
void    UTimer_SoftwareCapture(void) ;

#if(!UTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (UTimer_SoftwareCaptureMode)
        void    UTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!UTimer_UsingFixedFunction) */

    #if (UTimer_SoftwareTriggerMode)
        void    UTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (UTimer_SoftwareTriggerMode) */

    #if (UTimer_EnableTriggerMode)
        void    UTimer_EnableTrigger(void) ;
        void    UTimer_DisableTrigger(void) ;
    #endif /* (UTimer_EnableTriggerMode) */


    #if(UTimer_InterruptOnCaptureCount)
        void    UTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (UTimer_InterruptOnCaptureCount) */

    #if (UTimer_UsingHWCaptureCounter)
        void    UTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   UTimer_ReadCaptureCount(void) ;
    #endif /* (UTimer_UsingHWCaptureCounter) */

    void UTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void UTimer_Init(void)          ;
void UTimer_Enable(void)        ;
void UTimer_SaveConfig(void)    ;
void UTimer_RestoreConfig(void) ;
void UTimer_Sleep(void)         ;
void UTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define UTimer__B_TIMER__CM_NONE 0
#define UTimer__B_TIMER__CM_RISINGEDGE 1
#define UTimer__B_TIMER__CM_FALLINGEDGE 2
#define UTimer__B_TIMER__CM_EITHEREDGE 3
#define UTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define UTimer__B_TIMER__TM_NONE 0x00u
#define UTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define UTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define UTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define UTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define UTimer_INIT_PERIOD             65535u
#define UTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << UTimer_CTRL_CAP_MODE_SHIFT))
#define UTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << UTimer_CTRL_TRIG_MODE_SHIFT))
#if (UTimer_UsingFixedFunction)
    #define UTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << UTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << UTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define UTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << UTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << UTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << UTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (UTimer_UsingFixedFunction) */
#define UTimer_INIT_CAPTURE_COUNT      (2u)
#define UTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << UTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (UTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define UTimer_STATUS         (*(reg8 *) UTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define UTimer_STATUS_MASK    (*(reg8 *) UTimer_TimerHW__SR0 )
    #define UTimer_CONTROL        (*(reg8 *) UTimer_TimerHW__CFG0)
    #define UTimer_CONTROL2       (*(reg8 *) UTimer_TimerHW__CFG1)
    #define UTimer_CONTROL2_PTR   ( (reg8 *) UTimer_TimerHW__CFG1)
    #define UTimer_RT1            (*(reg8 *) UTimer_TimerHW__RT1)
    #define UTimer_RT1_PTR        ( (reg8 *) UTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define UTimer_CONTROL3       (*(reg8 *) UTimer_TimerHW__CFG2)
        #define UTimer_CONTROL3_PTR   ( (reg8 *) UTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define UTimer_GLOBAL_ENABLE  (*(reg8 *) UTimer_TimerHW__PM_ACT_CFG)
    #define UTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) UTimer_TimerHW__PM_STBY_CFG)

    #define UTimer_CAPTURE_LSB         (* (reg16 *) UTimer_TimerHW__CAP0 )
    #define UTimer_CAPTURE_LSB_PTR       ((reg16 *) UTimer_TimerHW__CAP0 )
    #define UTimer_PERIOD_LSB          (* (reg16 *) UTimer_TimerHW__PER0 )
    #define UTimer_PERIOD_LSB_PTR        ((reg16 *) UTimer_TimerHW__PER0 )
    #define UTimer_COUNTER_LSB         (* (reg16 *) UTimer_TimerHW__CNT_CMP0 )
    #define UTimer_COUNTER_LSB_PTR       ((reg16 *) UTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define UTimer_BLOCK_EN_MASK                     UTimer_TimerHW__PM_ACT_MSK
    #define UTimer_BLOCK_STBY_EN_MASK                UTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define UTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define UTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define UTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define UTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define UTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define UTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << UTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define UTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define UTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << UTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define UTimer_CTRL_MODE_SHIFT                 0x01u
        #define UTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << UTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define UTimer_CTRL_RCOD_SHIFT        0x02u
        #define UTimer_CTRL_ENBL_SHIFT        0x00u
        #define UTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define UTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << UTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define UTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << UTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define UTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << UTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define UTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << UTimer_CTRL_RCOD_SHIFT))
        #define UTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << UTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define UTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define UTimer_RT1_MASK                        ((uint8)((uint8)0x03u << UTimer_RT1_SHIFT))
    #define UTimer_SYNC                            ((uint8)((uint8)0x03u << UTimer_RT1_SHIFT))
    #define UTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define UTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << UTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define UTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << UTimer_SYNCDSI_SHIFT))

    #define UTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << UTimer_CTRL_MODE_SHIFT))
    #define UTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << UTimer_CTRL_MODE_SHIFT))
    #define UTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << UTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define UTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define UTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define UTimer_STATUS_TC_INT_MASK_SHIFT        (UTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define UTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (UTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define UTimer_STATUS_TC                       ((uint8)((uint8)0x01u << UTimer_STATUS_TC_SHIFT))
    #define UTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << UTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define UTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << UTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define UTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << UTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define UTimer_STATUS              (* (reg8 *) UTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define UTimer_STATUS_MASK         (* (reg8 *) UTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define UTimer_STATUS_AUX_CTRL     (* (reg8 *) UTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define UTimer_CONTROL             (* (reg8 *) UTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(UTimer_Resolution <= 8u) /* 8-bit Timer */
        #define UTimer_CAPTURE_LSB         (* (reg8 *) UTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define UTimer_CAPTURE_LSB_PTR       ((reg8 *) UTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define UTimer_PERIOD_LSB          (* (reg8 *) UTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define UTimer_PERIOD_LSB_PTR        ((reg8 *) UTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define UTimer_COUNTER_LSB         (* (reg8 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define UTimer_COUNTER_LSB_PTR       ((reg8 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(UTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define UTimer_CAPTURE_LSB         (* (reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define UTimer_CAPTURE_LSB_PTR       ((reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define UTimer_PERIOD_LSB          (* (reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define UTimer_PERIOD_LSB_PTR        ((reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define UTimer_COUNTER_LSB         (* (reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define UTimer_COUNTER_LSB_PTR       ((reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define UTimer_CAPTURE_LSB         (* (reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define UTimer_CAPTURE_LSB_PTR       ((reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define UTimer_PERIOD_LSB          (* (reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define UTimer_PERIOD_LSB_PTR        ((reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define UTimer_COUNTER_LSB         (* (reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define UTimer_COUNTER_LSB_PTR       ((reg16 *) UTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(UTimer_Resolution <= 24u)/* 24-bit Timer */
        #define UTimer_CAPTURE_LSB         (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define UTimer_CAPTURE_LSB_PTR       ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define UTimer_PERIOD_LSB          (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define UTimer_PERIOD_LSB_PTR        ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define UTimer_COUNTER_LSB         (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define UTimer_COUNTER_LSB_PTR       ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define UTimer_CAPTURE_LSB         (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define UTimer_CAPTURE_LSB_PTR       ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define UTimer_PERIOD_LSB          (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define UTimer_PERIOD_LSB_PTR        ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define UTimer_COUNTER_LSB         (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define UTimer_COUNTER_LSB_PTR       ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define UTimer_CAPTURE_LSB         (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define UTimer_CAPTURE_LSB_PTR       ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define UTimer_PERIOD_LSB          (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define UTimer_PERIOD_LSB_PTR        ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define UTimer_COUNTER_LSB         (* (reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define UTimer_COUNTER_LSB_PTR       ((reg32 *) UTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define UTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) UTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (UTimer_UsingHWCaptureCounter)
        #define UTimer_CAP_COUNT              (*(reg8 *) UTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define UTimer_CAP_COUNT_PTR          ( (reg8 *) UTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define UTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) UTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define UTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) UTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (UTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define UTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define UTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define UTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define UTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define UTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define UTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << UTimer_CTRL_INTCNT_SHIFT))
    #define UTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << UTimer_CTRL_TRIG_MODE_SHIFT))
    #define UTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << UTimer_CTRL_TRIG_EN_SHIFT))
    #define UTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << UTimer_CTRL_CAP_MODE_SHIFT))
    #define UTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << UTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define UTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define UTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define UTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define UTimer_STATUS_TC_INT_MASK_SHIFT       UTimer_STATUS_TC_SHIFT
    #define UTimer_STATUS_CAPTURE_INT_MASK_SHIFT  UTimer_STATUS_CAPTURE_SHIFT
    #define UTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define UTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define UTimer_STATUS_FIFOFULL_INT_MASK_SHIFT UTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define UTimer_STATUS_TC                      ((uint8)((uint8)0x01u << UTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define UTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << UTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << UTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << UTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define UTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << UTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define UTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << UTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << UTimer_STATUS_FIFOFULL_SHIFT))

    #define UTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define UTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define UTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define UTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define UTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define UTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_UTimer_H */


/* [] END OF FILE */
