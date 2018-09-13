/*******************************************************************************
* File Name: TDSPOWER.c  
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
#include "TDSPOWER.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TDSPOWER_PC =   (TDSPOWER_PC & \
                                (uint32)(~(uint32)(TDSPOWER_DRIVE_MODE_IND_MASK << (TDSPOWER_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TDSPOWER_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TDSPOWER_Write
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
void TDSPOWER_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TDSPOWER_DR & (uint8)(~TDSPOWER_MASK));
    drVal = (drVal | ((uint8)(value << TDSPOWER_SHIFT) & TDSPOWER_MASK));
    TDSPOWER_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TDSPOWER_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TDSPOWER_DM_STRONG     Strong Drive 
*  TDSPOWER_DM_OD_HI      Open Drain, Drives High 
*  TDSPOWER_DM_OD_LO      Open Drain, Drives Low 
*  TDSPOWER_DM_RES_UP     Resistive Pull Up 
*  TDSPOWER_DM_RES_DWN    Resistive Pull Down 
*  TDSPOWER_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TDSPOWER_DM_DIG_HIZ    High Impedance Digital 
*  TDSPOWER_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TDSPOWER_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TDSPOWER__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TDSPOWER_Read
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
*  Macro TDSPOWER_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TDSPOWER_Read(void) 
{
    return (uint8)((TDSPOWER_PS & TDSPOWER_MASK) >> TDSPOWER_SHIFT);
}


/*******************************************************************************
* Function Name: TDSPOWER_ReadDataReg
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
uint8 TDSPOWER_ReadDataReg(void) 
{
    return (uint8)((TDSPOWER_DR & TDSPOWER_MASK) >> TDSPOWER_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TDSPOWER_INTSTAT) 

    /*******************************************************************************
    * Function Name: TDSPOWER_ClearInterrupt
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
    uint8 TDSPOWER_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TDSPOWER_INTSTAT & TDSPOWER_MASK);
		TDSPOWER_INTSTAT = maskedStatus;
        return maskedStatus >> TDSPOWER_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
