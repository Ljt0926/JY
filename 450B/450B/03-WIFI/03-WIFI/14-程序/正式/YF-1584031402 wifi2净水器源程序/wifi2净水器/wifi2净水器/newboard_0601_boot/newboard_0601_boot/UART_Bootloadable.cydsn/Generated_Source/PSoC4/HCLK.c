/*******************************************************************************
* File Name: HCLK.c  
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
#include "HCLK.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        HCLK_PC =   (HCLK_PC & \
                                (uint32)(~(uint32)(HCLK_DRIVE_MODE_IND_MASK << (HCLK_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (HCLK_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: HCLK_Write
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
void HCLK_Write(uint8 value) 
{
    uint8 drVal = (uint8)(HCLK_DR & (uint8)(~HCLK_MASK));
    drVal = (drVal | ((uint8)(value << HCLK_SHIFT) & HCLK_MASK));
    HCLK_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: HCLK_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  HCLK_DM_STRONG     Strong Drive 
*  HCLK_DM_OD_HI      Open Drain, Drives High 
*  HCLK_DM_OD_LO      Open Drain, Drives Low 
*  HCLK_DM_RES_UP     Resistive Pull Up 
*  HCLK_DM_RES_DWN    Resistive Pull Down 
*  HCLK_DM_RES_UPDWN  Resistive Pull Up/Down 
*  HCLK_DM_DIG_HIZ    High Impedance Digital 
*  HCLK_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void HCLK_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(HCLK__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: HCLK_Read
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
*  Macro HCLK_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 HCLK_Read(void) 
{
    return (uint8)((HCLK_PS & HCLK_MASK) >> HCLK_SHIFT);
}


/*******************************************************************************
* Function Name: HCLK_ReadDataReg
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
uint8 HCLK_ReadDataReg(void) 
{
    return (uint8)((HCLK_DR & HCLK_MASK) >> HCLK_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(HCLK_INTSTAT) 

    /*******************************************************************************
    * Function Name: HCLK_ClearInterrupt
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
    uint8 HCLK_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(HCLK_INTSTAT & HCLK_MASK);
		HCLK_INTSTAT = maskedStatus;
        return maskedStatus >> HCLK_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
