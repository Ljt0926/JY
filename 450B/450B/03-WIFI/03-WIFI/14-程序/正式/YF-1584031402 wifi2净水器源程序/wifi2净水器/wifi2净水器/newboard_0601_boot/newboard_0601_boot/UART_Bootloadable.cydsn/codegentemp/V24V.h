/*******************************************************************************
* File Name: V24V.h  
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

#if !defined(CY_PINS_V24V_H) /* Pins V24V_H */
#define CY_PINS_V24V_H

#include "cytypes.h"
#include "cyfitter.h"
#include "V24V_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    V24V_Write(uint8 value) ;
void    V24V_SetDriveMode(uint8 mode) ;
uint8   V24V_ReadDataReg(void) ;
uint8   V24V_Read(void) ;
uint8   V24V_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define V24V_DRIVE_MODE_BITS        (3)
#define V24V_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - V24V_DRIVE_MODE_BITS))

#define V24V_DM_ALG_HIZ         (0x00u)
#define V24V_DM_DIG_HIZ         (0x01u)
#define V24V_DM_RES_UP          (0x02u)
#define V24V_DM_RES_DWN         (0x03u)
#define V24V_DM_OD_LO           (0x04u)
#define V24V_DM_OD_HI           (0x05u)
#define V24V_DM_STRONG          (0x06u)
#define V24V_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define V24V_MASK               V24V__MASK
#define V24V_SHIFT              V24V__SHIFT
#define V24V_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V24V_PS                     (* (reg32 *) V24V__PS)
/* Port Configuration */
#define V24V_PC                     (* (reg32 *) V24V__PC)
/* Data Register */
#define V24V_DR                     (* (reg32 *) V24V__DR)
/* Input Buffer Disable Override */
#define V24V_INP_DIS                (* (reg32 *) V24V__PC2)


#if defined(V24V__INTSTAT)  /* Interrupt Registers */

    #define V24V_INTSTAT                (* (reg32 *) V24V__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define V24V_DRIVE_MODE_SHIFT       (0x00u)
#define V24V_DRIVE_MODE_MASK        (0x07u << V24V_DRIVE_MODE_SHIFT)


#endif /* End Pins V24V_H */


/* [] END OF FILE */
