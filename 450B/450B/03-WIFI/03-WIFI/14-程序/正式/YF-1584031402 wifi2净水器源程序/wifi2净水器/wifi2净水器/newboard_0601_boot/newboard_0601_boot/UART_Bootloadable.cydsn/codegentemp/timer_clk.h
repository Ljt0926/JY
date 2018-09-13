/*******************************************************************************
* File Name: timer_clk.h
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

#if !defined(CY_CLOCK_timer_clk_H)
#define CY_CLOCK_timer_clk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void timer_clk_StartEx(uint32 alignClkDiv);
#define timer_clk_Start() \
    timer_clk_StartEx(timer_clk__PA_DIV_ID)

#else

void timer_clk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void timer_clk_Stop(void);

void timer_clk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 timer_clk_GetDividerRegister(void);
uint8  timer_clk_GetFractionalDividerRegister(void);

#define timer_clk_Enable()                         timer_clk_Start()
#define timer_clk_Disable()                        timer_clk_Stop()
#define timer_clk_SetDividerRegister(clkDivider, reset)  \
    timer_clk_SetFractionalDividerRegister((clkDivider), 0u)
#define timer_clk_SetDivider(clkDivider)           timer_clk_SetDividerRegister((clkDivider), 1u)
#define timer_clk_SetDividerValue(clkDivider)      timer_clk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define timer_clk_DIV_ID     timer_clk__DIV_ID

#define timer_clk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define timer_clk_CTRL_REG   (*(reg32 *)timer_clk__CTRL_REGISTER)
#define timer_clk_DIV_REG    (*(reg32 *)timer_clk__DIV_REGISTER)

#define timer_clk_CMD_DIV_SHIFT          (0u)
#define timer_clk_CMD_PA_DIV_SHIFT       (8u)
#define timer_clk_CMD_DISABLE_SHIFT      (30u)
#define timer_clk_CMD_ENABLE_SHIFT       (31u)

#define timer_clk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << timer_clk_CMD_DISABLE_SHIFT))
#define timer_clk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << timer_clk_CMD_ENABLE_SHIFT))

#define timer_clk_DIV_FRAC_MASK  (0x000000F8u)
#define timer_clk_DIV_FRAC_SHIFT (3u)
#define timer_clk_DIV_INT_MASK   (0xFFFFFF00u)
#define timer_clk_DIV_INT_SHIFT  (8u)

#else 

#define timer_clk_DIV_REG        (*(reg32 *)timer_clk__REGISTER)
#define timer_clk_ENABLE_REG     timer_clk_DIV_REG
#define timer_clk_DIV_FRAC_MASK  timer_clk__FRAC_MASK
#define timer_clk_DIV_FRAC_SHIFT (16u)
#define timer_clk_DIV_INT_MASK   timer_clk__DIVIDER_MASK
#define timer_clk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_timer_clk_H) */

/* [] END OF FILE */
