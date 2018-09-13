/*******************************************************************************
* File Name: UART_0_SPI_UART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_0_PVT.h"
#include "UART_0_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(UART_0_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 UART_0_rxBufferHead;
    volatile uint32 UART_0_rxBufferTail;
    volatile uint8  UART_0_rxBufferOverflow;
#endif /* (UART_0_INTERNAL_RX_SW_BUFFER_CONST) */

#if(UART_0_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 UART_0_txBufferHead;
    volatile uint32 UART_0_txBufferTail;
#endif /* (UART_0_INTERNAL_TX_SW_BUFFER_CONST) */

#if(UART_0_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 UART_0_rxBufferInternal[UART_0_RX_BUFFER_SIZE];
#endif /* (UART_0_INTERNAL_RX_SW_BUFFER) */

#if(UART_0_INTERNAL_TX_SW_BUFFER)
    volatile uint8 UART_0_txBufferInternal[UART_0_TX_BUFFER_SIZE];
#endif /* (UART_0_INTERNAL_TX_SW_BUFFER) */


#if(UART_0_RX_DIRECTION)

    /*******************************************************************************
    * Function Name: UART_0_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into UART_0_SpiInit for description.
    *
    *******************************************************************************/
    uint32 UART_0_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

        #if(UART_0_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (UART_0_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(UART_0_CHECK_RX_SW_BUFFER)
        {
            if(UART_0_rxBufferHead != UART_0_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (UART_0_rxBufferTail + 1u);

                if(UART_0_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = UART_0_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                UART_0_rxBufferTail = locTail;
            }
        }
        #else
        {
            rxData = UART_0_RX_FIFO_RD_REG; /* Read data from RX FIFO */
        }
        #endif

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UART_0_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 UART_0_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
        #if(UART_0_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locHead;
        #endif /* (UART_0_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(UART_0_CHECK_RX_SW_BUFFER)
        {
            locHead = UART_0_rxBufferHead;

            if(locHead >= UART_0_rxBufferTail)
            {
                size = (locHead - UART_0_rxBufferTail);
            }
            else
            {
                size = (locHead + (UART_0_RX_BUFFER_SIZE - UART_0_rxBufferTail));
            }
        }
        #else
        {
            size = UART_0_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: UART_0_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_0_SpiUartClearRxBuffer(void)
    {
        #if(UART_0_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (UART_0_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(UART_0_CHECK_RX_SW_BUFFER)
        {
            intSourceMask = UART_0_SpiUartDisableIntRx();

            UART_0_CLEAR_RX_FIFO;

            /* Flush RX software buffer */
            UART_0_rxBufferHead     = UART_0_rxBufferTail;
            UART_0_rxBufferOverflow = 0u;

            /* End RX transfer */
            UART_0_ClearRxInterruptSource(UART_0_INTR_RX_ALL);

            UART_0_SpiUartEnableIntRx(intSourceMask);
        }
        #else
        {
            UART_0_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (UART_0_RX_DIRECTION) */


#if(UART_0_TX_DIRECTION)

    /*******************************************************************************
    * Function Name: UART_0_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_0_SpiUartWriteTxData(uint32 txData)
    {
        #if(UART_0_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locHead;
            uint32 intSourceMask;
        #endif /* (UART_0_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(UART_0_CHECK_TX_SW_BUFFER)
        {
            /* Head index to put data */
            locHead = (UART_0_txBufferHead + 1u);

            /* Adjust TX software buffer index */
            if(UART_0_TX_BUFFER_SIZE == locHead)
            {
                locHead = 0u;
            }

            while(locHead == UART_0_txBufferTail)
            {
                /* Wait for space in TX software buffer */
            }

            /* TX software buffer has at least one room */

            if((UART_0_txBufferHead == UART_0_txBufferTail) &&
               (UART_0_SPI_UART_FIFO_SIZE != UART_0_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                UART_0_TX_FIFO_WR_REG = txData;
            }
            /* Put data in TX software buffer */
            else
            {
                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                UART_0_ClearTxInterruptSource(UART_0_INTR_TX_NOT_FULL);

                UART_0_PutWordInTxBuffer(locHead, txData);

                UART_0_txBufferHead = locHead;

                /* Enable interrupt to transmit */
                intSourceMask  = UART_0_INTR_TX_NOT_FULL;
                intSourceMask |= UART_0_GetTxInterruptMode();
                UART_0_SpiUartEnableIntTx(intSourceMask);
            }
        }
        #else
        {
            while(UART_0_SPI_UART_FIFO_SIZE == UART_0_GET_TX_FIFO_ENTRIES)
            {
                /* Block while TX FIFO is FULL */
            }

            UART_0_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: UART_0_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_0_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for(i=0u; i < count; i++)
        {
            UART_0_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: UART_0_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 UART_0_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
        #if(UART_0_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (UART_0_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(UART_0_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = UART_0_txBufferTail;

            if(UART_0_txBufferHead >= locTail)
            {
                size = (UART_0_txBufferHead - locTail);
            }
            else
            {
                size = (UART_0_txBufferHead + (UART_0_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = UART_0_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: UART_0_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_0_SpiUartClearTxBuffer(void)
    {
        #if(UART_0_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (UART_0_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(UART_0_CHECK_TX_SW_BUFFER)
        {
            intSourceMask = UART_0_SpiUartDisableIntTx();

            UART_0_CLEAR_TX_FIFO;

            /* Flush TX software buffer */
            UART_0_txBufferHead = UART_0_txBufferTail;

            /* End TX transfer if it is in progress */
            intSourceMask &= (uint32) ~UART_0_INTR_TX_NOT_FULL;

            UART_0_SpiUartEnableIntTx(intSourceMask);
        }
        #else
        {
            UART_0_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (UART_0_TX_DIRECTION) */


/*******************************************************************************
* Function Name: UART_0_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 UART_0_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = UART_0_GetRxInterruptMode();

    UART_0_SetRxInterruptMode(UART_0_NO_INTR_SOURCES);

    return(intSource);
}


/*******************************************************************************
* Function Name: UART_0_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 UART_0_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = UART_0_GetTxInterruptMode();

    UART_0_SetTxInterruptMode(UART_0_NO_INTR_SOURCES);

    return(intSourceMask);
}


#if(UART_0_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: UART_0_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_0_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if(UART_0_ONE_BYTE_WIDTH == UART_0_rxDataBits)
        {
            UART_0_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            UART_0_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            UART_0_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: UART_0_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 UART_0_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if(UART_0_ONE_BYTE_WIDTH == UART_0_rxDataBits)
        {
            value = UART_0_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) UART_0_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)UART_0_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }


    /*******************************************************************************
    * Function Name: UART_0_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_0_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if(UART_0_ONE_BYTE_WIDTH == UART_0_txDataBits)
        {
            UART_0_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            UART_0_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            UART_0_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: UART_0_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 UART_0_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if(UART_0_ONE_BYTE_WIDTH == UART_0_txDataBits)
        {
            value = (uint32) UART_0_txBuffer[idx];
        }
        else
        {
            value  = (uint32) UART_0_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) UART_0_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }

#endif /* (UART_0_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
