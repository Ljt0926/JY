/*******************************************************************************
* File Name: UART_0_PM.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_0.h"
#include "UART_0_PVT.h"

#if(UART_0_SCB_MODE_I2C_INC)
    #include "UART_0_I2C_PVT.h"
#endif /* (UART_0_SCB_MODE_I2C_INC) */

#if(UART_0_SCB_MODE_EZI2C_INC)
    #include "UART_0_EZI2C_PVT.h"
#endif /* (UART_0_SCB_MODE_EZI2C_INC) */

#if(UART_0_SCB_MODE_SPI_INC || UART_0_SCB_MODE_UART_INC)
    #include "UART_0_SPI_UART_PVT.h"
#endif /* (UART_0_SCB_MODE_SPI_INC || UART_0_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_0_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_0_SCB_MODE_I2C_CONST_CFG   && (!UART_0_I2C_WAKE_ENABLE_CONST))   || \
   (UART_0_SCB_MODE_EZI2C_CONST_CFG && (!UART_0_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_0_SCB_MODE_SPI_CONST_CFG   && (!UART_0_SPI_WAKE_ENABLE_CONST))   || \
   (UART_0_SCB_MODE_UART_CONST_CFG  && (!UART_0_UART_WAKE_ENABLE_CONST)))

    UART_0_BACKUP_STRUCT UART_0_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_0_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_0_Sleep(void)
{
#if(UART_0_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_0_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_0_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_0_I2CSaveConfig();
        }
        else if(UART_0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_0_EzI2CSaveConfig();
        }
    #if(!UART_0_CY_SCBIP_V1)
        else if(UART_0_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_0_SpiSaveConfig();
        }
        else if(UART_0_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_0_UartSaveConfig();
        }
    #endif /* (!UART_0_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_0_backup.enableState = (uint8) UART_0_GET_CTRL_ENABLED;

        if(0u != UART_0_backup.enableState)
        {
            UART_0_Stop();
        }
    }

#else

    #if (UART_0_SCB_MODE_I2C_CONST_CFG && UART_0_I2C_WAKE_ENABLE_CONST)
        UART_0_I2CSaveConfig();

    #elif (UART_0_SCB_MODE_EZI2C_CONST_CFG && UART_0_EZI2C_WAKE_ENABLE_CONST)
        UART_0_EzI2CSaveConfig();

    #elif (UART_0_SCB_MODE_SPI_CONST_CFG && UART_0_SPI_WAKE_ENABLE_CONST)
        UART_0_SpiSaveConfig();

    #elif (UART_0_SCB_MODE_UART_CONST_CFG && UART_0_UART_WAKE_ENABLE_CONST)
        UART_0_UartSaveConfig();

    #else

        UART_0_backup.enableState = (uint8) UART_0_GET_CTRL_ENABLED;

        if(0u != UART_0_backup.enableState)
        {
            UART_0_Stop();
        }

    #endif /* defined (UART_0_SCB_MODE_I2C_CONST_CFG) && (UART_0_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_0_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_0_Wakeup(void)
{
#if(UART_0_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_0_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_0_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_0_I2CRestoreConfig();
        }
        else if(UART_0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_0_EzI2CRestoreConfig();
        }
    #if(!UART_0_CY_SCBIP_V1)
        else if(UART_0_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_0_SpiRestoreConfig();
        }
        else if(UART_0_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_0_UartRestoreConfig();
        }
    #endif /* (!UART_0_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_0_backup.enableState)
        {
            UART_0_Enable();
        }
    }

#else

    #if (UART_0_SCB_MODE_I2C_CONST_CFG  && UART_0_I2C_WAKE_ENABLE_CONST)
        UART_0_I2CRestoreConfig();

    #elif (UART_0_SCB_MODE_EZI2C_CONST_CFG && UART_0_EZI2C_WAKE_ENABLE_CONST)
        UART_0_EzI2CRestoreConfig();

    #elif (UART_0_SCB_MODE_SPI_CONST_CFG && UART_0_SPI_WAKE_ENABLE_CONST)
        UART_0_SpiRestoreConfig();

    #elif (UART_0_SCB_MODE_UART_CONST_CFG && UART_0_UART_WAKE_ENABLE_CONST)
        UART_0_UartRestoreConfig();

    #else

        if(0u != UART_0_backup.enableState)
        {
            UART_0_Enable();
        }

    #endif /* (UART_0_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
