/*******************************************************************************
* File Name: LED_FC.c  
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
#include "LED_FC.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        LED_FC_PC =   (LED_FC_PC & \
                                (uint32)(~(uint32)(LED_FC_DRIVE_MODE_IND_MASK << (LED_FC_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (LED_FC_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: LED_FC_Write
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
void LED_FC_Write(uint8 value) 
{
    uint8 drVal = (uint8)(LED_FC_DR & (uint8)(~LED_FC_MASK));
    drVal = (drVal | ((uint8)(value << LED_FC_SHIFT) & LED_FC_MASK));
    LED_FC_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: LED_FC_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LED_FC_DM_STRONG     Strong Drive 
*  LED_FC_DM_OD_HI      Open Drain, Drives High 
*  LED_FC_DM_OD_LO      Open Drain, Drives Low 
*  LED_FC_DM_RES_UP     Resistive Pull Up 
*  LED_FC_DM_RES_DWN    Resistive Pull Down 
*  LED_FC_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LED_FC_DM_DIG_HIZ    High Impedance Digital 
*  LED_FC_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LED_FC_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(LED_FC__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: LED_FC_Read
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
*  Macro LED_FC_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LED_FC_Read(void) 
{
    return (uint8)((LED_FC_PS & LED_FC_MASK) >> LED_FC_SHIFT);
}


/*******************************************************************************
* Function Name: LED_FC_ReadDataReg
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
uint8 LED_FC_ReadDataReg(void) 
{
    return (uint8)((LED_FC_DR & LED_FC_MASK) >> LED_FC_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LED_FC_INTSTAT) 

    /*******************************************************************************
    * Function Name: LED_FC_ClearInterrupt
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
    uint8 LED_FC_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(LED_FC_INTSTAT & LED_FC_MASK);
		LED_FC_INTSTAT = maskedStatus;
        return maskedStatus >> LED_FC_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
