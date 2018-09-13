/*******************************************************************************
* File Name: K1.h  
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

#if !defined(CY_PINS_K1_H) /* Pins K1_H */
#define CY_PINS_K1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "K1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    K1_Write(uint8 value) ;
void    K1_SetDriveMode(uint8 mode) ;
uint8   K1_ReadDataReg(void) ;
uint8   K1_Read(void) ;
uint8   K1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define K1_DRIVE_MODE_BITS        (3)
#define K1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - K1_DRIVE_MODE_BITS))

#define K1_DM_ALG_HIZ         (0x00u)
#define K1_DM_DIG_HIZ         (0x01u)
#define K1_DM_RES_UP          (0x02u)
#define K1_DM_RES_DWN         (0x03u)
#define K1_DM_OD_LO           (0x04u)
#define K1_DM_OD_HI           (0x05u)
#define K1_DM_STRONG          (0x06u)
#define K1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define K1_MASK               K1__MASK
#define K1_SHIFT              K1__SHIFT
#define K1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define K1_PS                     (* (reg32 *) K1__PS)
/* Port Configuration */
#define K1_PC                     (* (reg32 *) K1__PC)
/* Data Register */
#define K1_DR                     (* (reg32 *) K1__DR)
/* Input Buffer Disable Override */
#define K1_INP_DIS                (* (reg32 *) K1__PC2)


#if defined(K1__INTSTAT)  /* Interrupt Registers */

    #define K1_INTSTAT                (* (reg32 *) K1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define K1_DRIVE_MODE_SHIFT       (0x00u)
#define K1_DRIVE_MODE_MASK        (0x07u << K1_DRIVE_MODE_SHIFT)


#endif /* End Pins K1_H */


/* [] END OF FILE */
