/*******************************************************************************
* File Name: V24V.c  
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
#include "V24V.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        V24V_PC =   (V24V_PC & \
                                (uint32)(~(uint32)(V24V_DRIVE_MODE_IND_MASK << (V24V_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (V24V_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: V24V_Write
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
void V24V_Write(uint8 value) 
{
    uint8 drVal = (uint8)(V24V_DR & (uint8)(~V24V_MASK));
    drVal = (drVal | ((uint8)(value << V24V_SHIFT) & V24V_MASK));
    V24V_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: V24V_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  V24V_DM_STRONG     Strong Drive 
*  V24V_DM_OD_HI      Open Drain, Drives High 
*  V24V_DM_OD_LO      Open Drain, Drives Low 
*  V24V_DM_RES_UP     Resistive Pull Up 
*  V24V_DM_RES_DWN    Resistive Pull Down 
*  V24V_DM_RES_UPDWN  Resistive Pull Up/Down 
*  V24V_DM_DIG_HIZ    High Impedance Digital 
*  V24V_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void V24V_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(V24V__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: V24V_Read
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
*  Macro V24V_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 V24V_Read(void) 
{
    return (uint8)((V24V_PS & V24V_MASK) >> V24V_SHIFT);
}


/*******************************************************************************
* Function Name: V24V_ReadDataReg
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
uint8 V24V_ReadDataReg(void) 
{
    return (uint8)((V24V_DR & V24V_MASK) >> V24V_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(V24V_INTSTAT) 

    /*******************************************************************************
    * Function Name: V24V_ClearInterrupt
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
    uint8 V24V_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(V24V_INTSTAT & V24V_MASK);
		V24V_INTSTAT = maskedStatus;
        return maskedStatus >> V24V_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
