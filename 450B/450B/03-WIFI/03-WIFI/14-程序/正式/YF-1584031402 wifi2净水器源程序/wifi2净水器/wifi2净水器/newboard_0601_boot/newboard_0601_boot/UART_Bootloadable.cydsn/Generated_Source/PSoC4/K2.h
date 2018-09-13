/*******************************************************************************
* File Name: K2.h  
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

#if !defined(CY_PINS_K2_H) /* Pins K2_H */
#define CY_PINS_K2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "K2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    K2_Write(uint8 value) ;
void    K2_SetDriveMode(uint8 mode) ;
uint8   K2_ReadDataReg(void) ;
uint8   K2_Read(void) ;
uint8   K2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define K2_DRIVE_MODE_BITS        (3)
#define K2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - K2_DRIVE_MODE_BITS))

#define K2_DM_ALG_HIZ         (0x00u)
#define K2_DM_DIG_HIZ         (0x01u)
#define K2_DM_RES_UP          (0x02u)
#define K2_DM_RES_DWN         (0x03u)
#define K2_DM_OD_LO           (0x04u)
#define K2_DM_OD_HI           (0x05u)
#define K2_DM_STRONG          (0x06u)
#define K2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define K2_MASK               K2__MASK
#define K2_SHIFT              K2__SHIFT
#define K2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define K2_PS                     (* (reg32 *) K2__PS)
/* Port Configuration */
#define K2_PC                     (* (reg32 *) K2__PC)
/* Data Register */
#define K2_DR                     (* (reg32 *) K2__DR)
/* Input Buffer Disable Override */
#define K2_INP_DIS                (* (reg32 *) K2__PC2)


#if defined(K2__INTSTAT)  /* Interrupt Registers */

    #define K2_INTSTAT                (* (reg32 *) K2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define K2_DRIVE_MODE_SHIFT       (0x00u)
#define K2_DRIVE_MODE_MASK        (0x07u << K2_DRIVE_MODE_SHIFT)


#endif /* End Pins K2_H */


/* [] END OF FILE */
