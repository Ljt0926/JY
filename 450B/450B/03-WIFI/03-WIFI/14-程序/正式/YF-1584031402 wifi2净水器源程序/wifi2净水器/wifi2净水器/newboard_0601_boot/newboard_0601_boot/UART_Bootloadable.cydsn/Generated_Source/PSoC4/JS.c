/*******************************************************************************
* File Name: JS.c  
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
#include "JS.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        JS_PC =   (JS_PC & \
                                (uint32)(~(uint32)(JS_DRIVE_MODE_IND_MASK << (JS_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (JS_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: JS_Write
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
void JS_Write(uint8 value) 
{
    uint8 drVal = (uint8)(JS_DR & (uint8)(~JS_MASK));
    drVal = (drVal | ((uint8)(value << JS_SHIFT) & JS_MASK));
    JS_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: JS_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  JS_DM_STRONG     Strong Drive 
*  JS_DM_OD_HI      Open Drain, Drives High 
*  JS_DM_OD_LO      Open Drain, Drives Low 
*  JS_DM_RES_UP     Resistive Pull Up 
*  JS_DM_RES_DWN    Resistive Pull Down 
*  JS_DM_RES_UPDWN  Resistive Pull Up/Down 
*  JS_DM_DIG_HIZ    High Impedance Digital 
*  JS_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void JS_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(JS__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: JS_Read
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
*  Macro JS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 JS_Read(void) 
{
    return (uint8)((JS_PS & JS_MASK) >> JS_SHIFT);
}


/*******************************************************************************
* Function Name: JS_ReadDataReg
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
uint8 JS_ReadDataReg(void) 
{
    return (uint8)((JS_DR & JS_MASK) >> JS_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(JS_INTSTAT) 

    /*******************************************************************************
    * Function Name: JS_ClearInterrupt
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
    uint8 JS_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(JS_INTSTAT & JS_MASK);
		JS_INTSTAT = maskedStatus;
        return maskedStatus >> JS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
