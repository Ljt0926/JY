/*******************************************************************************
* File Name: CX.c  
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
#include "CX.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        CX_PC =   (CX_PC & \
                                (uint32)(~(uint32)(CX_DRIVE_MODE_IND_MASK << (CX_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (CX_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: CX_Write
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
void CX_Write(uint8 value) 
{
    uint8 drVal = (uint8)(CX_DR & (uint8)(~CX_MASK));
    drVal = (drVal | ((uint8)(value << CX_SHIFT) & CX_MASK));
    CX_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: CX_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  CX_DM_STRONG     Strong Drive 
*  CX_DM_OD_HI      Open Drain, Drives High 
*  CX_DM_OD_LO      Open Drain, Drives Low 
*  CX_DM_RES_UP     Resistive Pull Up 
*  CX_DM_RES_DWN    Resistive Pull Down 
*  CX_DM_RES_UPDWN  Resistive Pull Up/Down 
*  CX_DM_DIG_HIZ    High Impedance Digital 
*  CX_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void CX_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(CX__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: CX_Read
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
*  Macro CX_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 CX_Read(void) 
{
    return (uint8)((CX_PS & CX_MASK) >> CX_SHIFT);
}


/*******************************************************************************
* Function Name: CX_ReadDataReg
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
uint8 CX_ReadDataReg(void) 
{
    return (uint8)((CX_DR & CX_MASK) >> CX_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(CX_INTSTAT) 

    /*******************************************************************************
    * Function Name: CX_ClearInterrupt
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
    uint8 CX_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(CX_INTSTAT & CX_MASK);
		CX_INTSTAT = maskedStatus;
        return maskedStatus >> CX_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
