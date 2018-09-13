/*******************************************************************************
* File Name: TEST.h  
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

#if !defined(CY_PINS_TEST_H) /* Pins TEST_H */
#define CY_PINS_TEST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TEST_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TEST_Write(uint8 value) ;
void    TEST_SetDriveMode(uint8 mode) ;
uint8   TEST_ReadDataReg(void) ;
uint8   TEST_Read(void) ;
uint8   TEST_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TEST_DRIVE_MODE_BITS        (3)
#define TEST_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TEST_DRIVE_MODE_BITS))

#define TEST_DM_ALG_HIZ         (0x00u)
#define TEST_DM_DIG_HIZ         (0x01u)
#define TEST_DM_RES_UP          (0x02u)
#define TEST_DM_RES_DWN         (0x03u)
#define TEST_DM_OD_LO           (0x04u)
#define TEST_DM_OD_HI           (0x05u)
#define TEST_DM_STRONG          (0x06u)
#define TEST_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define TEST_MASK               TEST__MASK
#define TEST_SHIFT              TEST__SHIFT
#define TEST_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TEST_PS                     (* (reg32 *) TEST__PS)
/* Port Configuration */
#define TEST_PC                     (* (reg32 *) TEST__PC)
/* Data Register */
#define TEST_DR                     (* (reg32 *) TEST__DR)
/* Input Buffer Disable Override */
#define TEST_INP_DIS                (* (reg32 *) TEST__PC2)


#if defined(TEST__INTSTAT)  /* Interrupt Registers */

    #define TEST_INTSTAT                (* (reg32 *) TEST__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define TEST_DRIVE_MODE_SHIFT       (0x00u)
#define TEST_DRIVE_MODE_MASK        (0x07u << TEST_DRIVE_MODE_SHIFT)


#endif /* End Pins TEST_H */


/* [] END OF FILE */
