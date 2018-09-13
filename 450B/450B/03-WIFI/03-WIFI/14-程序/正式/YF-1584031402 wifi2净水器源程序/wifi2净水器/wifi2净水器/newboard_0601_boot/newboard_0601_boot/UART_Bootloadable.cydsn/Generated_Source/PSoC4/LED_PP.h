/*******************************************************************************
* File Name: LED_PP.h  
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

#if !defined(CY_PINS_LED_PP_H) /* Pins LED_PP_H */
#define CY_PINS_LED_PP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_PP_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_PP_Write(uint8 value) ;
void    LED_PP_SetDriveMode(uint8 mode) ;
uint8   LED_PP_ReadDataReg(void) ;
uint8   LED_PP_Read(void) ;
uint8   LED_PP_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_PP_DRIVE_MODE_BITS        (3)
#define LED_PP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_PP_DRIVE_MODE_BITS))

#define LED_PP_DM_ALG_HIZ         (0x00u)
#define LED_PP_DM_DIG_HIZ         (0x01u)
#define LED_PP_DM_RES_UP          (0x02u)
#define LED_PP_DM_RES_DWN         (0x03u)
#define LED_PP_DM_OD_LO           (0x04u)
#define LED_PP_DM_OD_HI           (0x05u)
#define LED_PP_DM_STRONG          (0x06u)
#define LED_PP_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LED_PP_MASK               LED_PP__MASK
#define LED_PP_SHIFT              LED_PP__SHIFT
#define LED_PP_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_PP_PS                     (* (reg32 *) LED_PP__PS)
/* Port Configuration */
#define LED_PP_PC                     (* (reg32 *) LED_PP__PC)
/* Data Register */
#define LED_PP_DR                     (* (reg32 *) LED_PP__DR)
/* Input Buffer Disable Override */
#define LED_PP_INP_DIS                (* (reg32 *) LED_PP__PC2)


#if defined(LED_PP__INTSTAT)  /* Interrupt Registers */

    #define LED_PP_INTSTAT                (* (reg32 *) LED_PP__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LED_PP_DRIVE_MODE_SHIFT       (0x00u)
#define LED_PP_DRIVE_MODE_MASK        (0x07u << LED_PP_DRIVE_MODE_SHIFT)


#endif /* End Pins LED_PP_H */


/* [] END OF FILE */
