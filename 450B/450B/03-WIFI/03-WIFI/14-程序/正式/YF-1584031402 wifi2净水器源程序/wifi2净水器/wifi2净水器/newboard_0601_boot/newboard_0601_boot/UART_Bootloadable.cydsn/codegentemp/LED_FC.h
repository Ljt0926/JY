/*******************************************************************************
* File Name: LED_FC.h  
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

#if !defined(CY_PINS_LED_FC_H) /* Pins LED_FC_H */
#define CY_PINS_LED_FC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_FC_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_FC_Write(uint8 value) ;
void    LED_FC_SetDriveMode(uint8 mode) ;
uint8   LED_FC_ReadDataReg(void) ;
uint8   LED_FC_Read(void) ;
uint8   LED_FC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_FC_DRIVE_MODE_BITS        (3)
#define LED_FC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_FC_DRIVE_MODE_BITS))

#define LED_FC_DM_ALG_HIZ         (0x00u)
#define LED_FC_DM_DIG_HIZ         (0x01u)
#define LED_FC_DM_RES_UP          (0x02u)
#define LED_FC_DM_RES_DWN         (0x03u)
#define LED_FC_DM_OD_LO           (0x04u)
#define LED_FC_DM_OD_HI           (0x05u)
#define LED_FC_DM_STRONG          (0x06u)
#define LED_FC_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LED_FC_MASK               LED_FC__MASK
#define LED_FC_SHIFT              LED_FC__SHIFT
#define LED_FC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_FC_PS                     (* (reg32 *) LED_FC__PS)
/* Port Configuration */
#define LED_FC_PC                     (* (reg32 *) LED_FC__PC)
/* Data Register */
#define LED_FC_DR                     (* (reg32 *) LED_FC__DR)
/* Input Buffer Disable Override */
#define LED_FC_INP_DIS                (* (reg32 *) LED_FC__PC2)


#if defined(LED_FC__INTSTAT)  /* Interrupt Registers */

    #define LED_FC_INTSTAT                (* (reg32 *) LED_FC__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LED_FC_DRIVE_MODE_SHIFT       (0x00u)
#define LED_FC_DRIVE_MODE_MASK        (0x07u << LED_FC_DRIVE_MODE_SHIFT)


#endif /* End Pins LED_FC_H */


/* [] END OF FILE */
