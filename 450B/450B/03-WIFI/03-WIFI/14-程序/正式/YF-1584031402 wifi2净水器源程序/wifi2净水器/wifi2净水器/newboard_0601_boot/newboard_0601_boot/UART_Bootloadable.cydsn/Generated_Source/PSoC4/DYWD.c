/*******************************************************************************
* File Name: DYWD.c  
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
#include "DYWD.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        DYWD_PC =   (DYWD_PC & \
                                (uint32)(~(uint32)(DYWD_DRIVE_MODE_IND_MASK << (DYWD_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (DYWD_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: DYWD_Write
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
void DYWD_Write(uint8 value) 
{
    uint8 drVal = (uint8)(DYWD_DR & (uint8)(~DYWD_MASK));
    drVal = (drVal | ((uint8)(value << DYWD_SHIFT) & DYWD_MASK));
    DYWD_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: DYWD_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DYWD_DM_STRONG     Strong Drive 
*  DYWD_DM_OD_HI      Open Drain, Drives High 
*  DYWD_DM_OD_LO      Open Drain, Drives Low 
*  DYWD_DM_RES_UP     Resistive Pull Up 
*  DYWD_DM_RES_DWN    Resistive Pull Down 
*  DYWD_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DYWD_DM_DIG_HIZ    High Impedance Digital 
*  DYWD_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DYWD_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(DYWD__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: DYWD_Read
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
*  Macro DYWD_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DYWD_Read(void) 
{
    return (uint8)((DYWD_PS & DYWD_MASK) >> DYWD_SHIFT);
}


/*******************************************************************************
* Function Name: DYWD_ReadDataReg
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
uint8 DYWD_ReadDataReg(void) 
{
    return (uint8)((DYWD_DR & DYWD_MASK) >> DYWD_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DYWD_INTSTAT) 

    /*******************************************************************************
    * Function Name: DYWD_ClearInterrupt
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
    uint8 DYWD_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(DYWD_INTSTAT & DYWD_MASK);
		DYWD_INTSTAT = maskedStatus;
        return maskedStatus >> DYWD_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
