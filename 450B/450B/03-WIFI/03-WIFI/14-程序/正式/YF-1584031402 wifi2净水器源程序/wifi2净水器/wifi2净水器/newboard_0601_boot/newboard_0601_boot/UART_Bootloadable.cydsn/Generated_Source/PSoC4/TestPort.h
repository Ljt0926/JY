/*******************************************************************************
* File Name: TestPort.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TestPort_H) /* Pins TestPort_H */
#define CY_PINS_TestPort_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TestPort_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TestPort_Write(uint8 value) ;
void    TestPort_SetDriveMode(uint8 mode) ;
uint8   TestPort_ReadDataReg(void) ;
uint8   TestPort_Read(void) ;
uint8   TestPort_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TestPort_DRIVE_MODE_BITS        (3)
#define TestPort_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TestPort_DRIVE_MODE_BITS))

#define TestPort_DM_ALG_HIZ         (0x00u)
#define TestPort_DM_DIG_HIZ         (0x01u)
#define TestPort_DM_RES_UP          (0x02u)
#define TestPort_DM_RES_DWN         (0x03u)
#define TestPort_DM_OD_LO           (0x04u)
#define TestPort_DM_OD_HI           (0x05u)
#define TestPort_DM_STRONG          (0x06u)
#define TestPort_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define TestPort_MASK               TestPort__MASK
#define TestPort_SHIFT              TestPort__SHIFT
#define TestPort_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TestPort_PS                     (* (reg32 *) TestPort__PS)
/* Port Configuration */
#define TestPort_PC                     (* (reg32 *) TestPort__PC)
/* Data Register */
#define TestPort_DR                     (* (reg32 *) TestPort__DR)
/* Input Buffer Disable Override */
#define TestPort_INP_DIS                (* (reg32 *) TestPort__PC2)


#if defined(TestPort__INTSTAT)  /* Interrupt Registers */

    #define TestPort_INTSTAT                (* (reg32 *) TestPort__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define TestPort_DRIVE_MODE_SHIFT       (0x00u)
#define TestPort_DRIVE_MODE_MASK        (0x07u << TestPort_DRIVE_MODE_SHIFT)


#endif /* End Pins TestPort_H */


/* [] END OF FILE */
