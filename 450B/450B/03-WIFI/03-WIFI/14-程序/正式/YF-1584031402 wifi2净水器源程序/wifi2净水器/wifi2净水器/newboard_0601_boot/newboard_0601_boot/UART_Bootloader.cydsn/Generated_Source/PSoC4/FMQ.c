/*******************************************************************************
* File Name: FMQ.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "FMQ.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        FMQ_PC =   (FMQ_PC & \
                                (uint32)(~(uint32)(FMQ_DRIVE_MODE_IND_MASK << (FMQ_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (FMQ_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: FMQ_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void FMQ_Write(uint8 value) 
{
    uint8 drVal = (uint8)(FMQ_DR & (uint8)(~FMQ_MASK));
    drVal = (drVal | ((uint8)(value << FMQ_SHIFT) & FMQ_MASK));
    FMQ_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: FMQ_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  FMQ_DM_STRONG     Strong Drive 
*  FMQ_DM_OD_HI      Open Drain, Drives High 
*  FMQ_DM_OD_LO      Open Drain, Drives Low 
*  FMQ_DM_RES_UP     Resistive Pull Up 
*  FMQ_DM_RES_DWN    Resistive Pull Down 
*  FMQ_DM_RES_UPDWN  Resistive Pull Up/Down 
*  FMQ_DM_DIG_HIZ    High Impedance Digital 
*  FMQ_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void FMQ_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(FMQ__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: FMQ_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro FMQ_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 FMQ_Read(void) 
{
    return (uint8)((FMQ_PS & FMQ_MASK) >> FMQ_SHIFT);
}


/*******************************************************************************
* Function Name: FMQ_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 FMQ_ReadDataReg(void) 
{
    return (uint8)((FMQ_DR & FMQ_MASK) >> FMQ_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(FMQ_INTSTAT) 

    /*******************************************************************************
    * Function Name: FMQ_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 FMQ_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(FMQ_INTSTAT & FMQ_MASK);
		FMQ_INTSTAT = maskedStatus;
        return maskedStatus >> FMQ_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
