/*******************************************************************************
* File Name: LED_BC.h  
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

#if !defined(CY_PINS_LED_BC_H) /* Pins LED_BC_H */
#define CY_PINS_LED_BC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_BC_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_BC_Write(uint8 value) ;
void    LED_BC_SetDriveMode(uint8 mode) ;
uint8   LED_BC_ReadDataReg(void) ;
uint8   LED_BC_Read(void) ;
uint8   LED_BC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_BC_DRIVE_MODE_BITS        (3)
#define LED_BC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_BC_DRIVE_MODE_BITS))

#define LED_BC_DM_ALG_HIZ         (0x00u)
#define LED_BC_DM_DIG_HIZ         (0x01u)
#define LED_BC_DM_RES_UP          (0x02u)
#define LED_BC_DM_RES_DWN         (0x03u)
#define LED_BC_DM_OD_LO           (0x04u)
#define LED_BC_DM_OD_HI           (0x05u)
#define LED_BC_DM_STRONG          (0x06u)
#define LED_BC_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LED_BC_MASK               LED_BC__MASK
#define LED_BC_SHIFT              LED_BC__SHIFT
#define LED_BC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_BC_PS                     (* (reg32 *) LED_BC__PS)
/* Port Configuration */
#define LED_BC_PC                     (* (reg32 *) LED_BC__PC)
/* Data Register */
#define LED_BC_DR                     (* (reg32 *) LED_BC__DR)
/* Input Buffer Disable Override */
#define LED_BC_INP_DIS                (* (reg32 *) LED_BC__PC2)


#if defined(LED_BC__INTSTAT)  /* Interrupt Registers */

    #define LED_BC_INTSTAT                (* (reg32 *) LED_BC__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LED_BC_DRIVE_MODE_SHIFT       (0x00u)
#define LED_BC_DRIVE_MODE_MASK        (0x07u << LED_BC_DRIVE_MODE_SHIFT)


#endif /* End Pins LED_BC_H */


/* [] END OF FILE */
