/*******************************************************************************
* File Name: JS.h  
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

#if !defined(CY_PINS_JS_H) /* Pins JS_H */
#define CY_PINS_JS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "JS_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    JS_Write(uint8 value) ;
void    JS_SetDriveMode(uint8 mode) ;
uint8   JS_ReadDataReg(void) ;
uint8   JS_Read(void) ;
uint8   JS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define JS_DRIVE_MODE_BITS        (3)
#define JS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - JS_DRIVE_MODE_BITS))

#define JS_DM_ALG_HIZ         (0x00u)
#define JS_DM_DIG_HIZ         (0x01u)
#define JS_DM_RES_UP          (0x02u)
#define JS_DM_RES_DWN         (0x03u)
#define JS_DM_OD_LO           (0x04u)
#define JS_DM_OD_HI           (0x05u)
#define JS_DM_STRONG          (0x06u)
#define JS_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define JS_MASK               JS__MASK
#define JS_SHIFT              JS__SHIFT
#define JS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define JS_PS                     (* (reg32 *) JS__PS)
/* Port Configuration */
#define JS_PC                     (* (reg32 *) JS__PC)
/* Data Register */
#define JS_DR                     (* (reg32 *) JS__DR)
/* Input Buffer Disable Override */
#define JS_INP_DIS                (* (reg32 *) JS__PC2)


#if defined(JS__INTSTAT)  /* Interrupt Registers */

    #define JS_INTSTAT                (* (reg32 *) JS__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define JS_DRIVE_MODE_SHIFT       (0x00u)
#define JS_DRIVE_MODE_MASK        (0x07u << JS_DRIVE_MODE_SHIFT)


#endif /* End Pins JS_H */


/* [] END OF FILE */
