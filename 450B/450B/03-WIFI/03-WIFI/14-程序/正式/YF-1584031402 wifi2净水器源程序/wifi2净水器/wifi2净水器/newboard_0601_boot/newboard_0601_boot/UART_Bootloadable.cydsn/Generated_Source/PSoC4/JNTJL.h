/*******************************************************************************
* File Name: JNTJL.h  
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

#if !defined(CY_PINS_JNTJL_H) /* Pins JNTJL_H */
#define CY_PINS_JNTJL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "JNTJL_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    JNTJL_Write(uint8 value) ;
void    JNTJL_SetDriveMode(uint8 mode) ;
uint8   JNTJL_ReadDataReg(void) ;
uint8   JNTJL_Read(void) ;
uint8   JNTJL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define JNTJL_DRIVE_MODE_BITS        (3)
#define JNTJL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - JNTJL_DRIVE_MODE_BITS))

#define JNTJL_DM_ALG_HIZ         (0x00u)
#define JNTJL_DM_DIG_HIZ         (0x01u)
#define JNTJL_DM_RES_UP          (0x02u)
#define JNTJL_DM_RES_DWN         (0x03u)
#define JNTJL_DM_OD_LO           (0x04u)
#define JNTJL_DM_OD_HI           (0x05u)
#define JNTJL_DM_STRONG          (0x06u)
#define JNTJL_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define JNTJL_MASK               JNTJL__MASK
#define JNTJL_SHIFT              JNTJL__SHIFT
#define JNTJL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define JNTJL_PS                     (* (reg32 *) JNTJL__PS)
/* Port Configuration */
#define JNTJL_PC                     (* (reg32 *) JNTJL__PC)
/* Data Register */
#define JNTJL_DR                     (* (reg32 *) JNTJL__DR)
/* Input Buffer Disable Override */
#define JNTJL_INP_DIS                (* (reg32 *) JNTJL__PC2)


#if defined(JNTJL__INTSTAT)  /* Interrupt Registers */

    #define JNTJL_INTSTAT                (* (reg32 *) JNTJL__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define JNTJL_DRIVE_MODE_SHIFT       (0x00u)
#define JNTJL_DRIVE_MODE_MASK        (0x07u << JNTJL_DRIVE_MODE_SHIFT)


#endif /* End Pins JNTJL_H */


/* [] END OF FILE */
