/*******************************************************************************
* File Name: COMN.c  
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
#include "COMN.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        COMN_PC =   (COMN_PC & \
                                (uint32)(~(uint32)(COMN_DRIVE_MODE_IND_MASK << (COMN_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (COMN_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: COMN_Write
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
void COMN_Write(uint8 value) 
{
    uint8 drVal = (uint8)(COMN_DR & (uint8)(~COMN_MASK));
    drVal = (drVal | ((uint8)(value << COMN_SHIFT) & COMN_MASK));
    COMN_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: COMN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  COMN_DM_STRONG     Strong Drive 
*  COMN_DM_OD_HI      Open Drain, Drives High 
*  COMN_DM_OD_LO      Open Drain, Drives Low 
*  COMN_DM_RES_UP     Resistive Pull Up 
*  COMN_DM_RES_DWN    Resistive Pull Down 
*  COMN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  COMN_DM_DIG_HIZ    High Impedance Digital 
*  COMN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void COMN_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(COMN__0__SHIFT, mode);
	SetP4PinDriveMode(COMN__1__SHIFT, mode);
	SetP4PinDriveMode(COMN__2__SHIFT, mode);
	SetP4PinDriveMode(COMN__3__SHIFT, mode);
	SetP4PinDriveMode(COMN__4__SHIFT, mode);
	SetP4PinDriveMode(COMN__5__SHIFT, mode);
	SetP4PinDriveMode(COMN__6__SHIFT, mode);
}


/*******************************************************************************
* Function Name: COMN_Read
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
*  Macro COMN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 COMN_Read(void) 
{
    return (uint8)((COMN_PS & COMN_MASK) >> COMN_SHIFT);
}


/*******************************************************************************
* Function Name: COMN_ReadDataReg
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
uint8 COMN_ReadDataReg(void) 
{
    return (uint8)((COMN_DR & COMN_MASK) >> COMN_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(COMN_INTSTAT) 

    /*******************************************************************************
    * Function Name: COMN_ClearInterrupt
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
    uint8 COMN_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(COMN_INTSTAT & COMN_MASK);
		COMN_INTSTAT = maskedStatus;
        return maskedStatus >> COMN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
