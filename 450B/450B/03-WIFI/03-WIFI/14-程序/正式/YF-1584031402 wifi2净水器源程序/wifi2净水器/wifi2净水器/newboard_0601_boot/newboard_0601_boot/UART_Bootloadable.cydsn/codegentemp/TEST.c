/*******************************************************************************
* File Name: TEST.c  
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
#include "TEST.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TEST_PC =   (TEST_PC & \
                                (uint32)(~(uint32)(TEST_DRIVE_MODE_IND_MASK << (TEST_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TEST_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TEST_Write
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
void TEST_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TEST_DR & (uint8)(~TEST_MASK));
    drVal = (drVal | ((uint8)(value << TEST_SHIFT) & TEST_MASK));
    TEST_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TEST_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TEST_DM_STRONG     Strong Drive 
*  TEST_DM_OD_HI      Open Drain, Drives High 
*  TEST_DM_OD_LO      Open Drain, Drives Low 
*  TEST_DM_RES_UP     Resistive Pull Up 
*  TEST_DM_RES_DWN    Resistive Pull Down 
*  TEST_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TEST_DM_DIG_HIZ    High Impedance Digital 
*  TEST_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TEST_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TEST__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TEST_Read
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
*  Macro TEST_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TEST_Read(void) 
{
    return (uint8)((TEST_PS & TEST_MASK) >> TEST_SHIFT);
}


/*******************************************************************************
* Function Name: TEST_ReadDataReg
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
uint8 TEST_ReadDataReg(void) 
{
    return (uint8)((TEST_DR & TEST_MASK) >> TEST_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TEST_INTSTAT) 

    /*******************************************************************************
    * Function Name: TEST_ClearInterrupt
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
    uint8 TEST_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TEST_INTSTAT & TEST_MASK);
		TEST_INTSTAT = maskedStatus;
        return maskedStatus >> TEST_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
