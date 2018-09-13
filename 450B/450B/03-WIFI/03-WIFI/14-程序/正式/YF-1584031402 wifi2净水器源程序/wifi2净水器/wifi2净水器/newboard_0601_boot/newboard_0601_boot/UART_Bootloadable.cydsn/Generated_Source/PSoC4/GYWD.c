/*******************************************************************************
* File Name: GYWD.c  
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
#include "GYWD.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        GYWD_PC =   (GYWD_PC & \
                                (uint32)(~(uint32)(GYWD_DRIVE_MODE_IND_MASK << (GYWD_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (GYWD_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: GYWD_Write
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
void GYWD_Write(uint8 value) 
{
    uint8 drVal = (uint8)(GYWD_DR & (uint8)(~GYWD_MASK));
    drVal = (drVal | ((uint8)(value << GYWD_SHIFT) & GYWD_MASK));
    GYWD_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: GYWD_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  GYWD_DM_STRONG     Strong Drive 
*  GYWD_DM_OD_HI      Open Drain, Drives High 
*  GYWD_DM_OD_LO      Open Drain, Drives Low 
*  GYWD_DM_RES_UP     Resistive Pull Up 
*  GYWD_DM_RES_DWN    Resistive Pull Down 
*  GYWD_DM_RES_UPDWN  Resistive Pull Up/Down 
*  GYWD_DM_DIG_HIZ    High Impedance Digital 
*  GYWD_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void GYWD_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(GYWD__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: GYWD_Read
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
*  Macro GYWD_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 GYWD_Read(void) 
{
    return (uint8)((GYWD_PS & GYWD_MASK) >> GYWD_SHIFT);
}


/*******************************************************************************
* Function Name: GYWD_ReadDataReg
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
uint8 GYWD_ReadDataReg(void) 
{
    return (uint8)((GYWD_DR & GYWD_MASK) >> GYWD_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(GYWD_INTSTAT) 

    /*******************************************************************************
    * Function Name: GYWD_ClearInterrupt
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
    uint8 GYWD_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(GYWD_INTSTAT & GYWD_MASK);
		GYWD_INTSTAT = maskedStatus;
        return maskedStatus >> GYWD_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
