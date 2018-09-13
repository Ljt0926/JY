/*******************************************************************************
* File Name: HSDA.h  
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

#if !defined(CY_PINS_HSDA_H) /* Pins HSDA_H */
#define CY_PINS_HSDA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HSDA_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    HSDA_Write(uint8 value) ;
void    HSDA_SetDriveMode(uint8 mode) ;
uint8   HSDA_ReadDataReg(void) ;
uint8   HSDA_Read(void) ;
uint8   HSDA_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HSDA_DRIVE_MODE_BITS        (3)
#define HSDA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HSDA_DRIVE_MODE_BITS))

#define HSDA_DM_ALG_HIZ         (0x00u)
#define HSDA_DM_DIG_HIZ         (0x01u)
#define HSDA_DM_RES_UP          (0x02u)
#define HSDA_DM_RES_DWN         (0x03u)
#define HSDA_DM_OD_LO           (0x04u)
#define HSDA_DM_OD_HI           (0x05u)
#define HSDA_DM_STRONG          (0x06u)
#define HSDA_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define HSDA_MASK               HSDA__MASK
#define HSDA_SHIFT              HSDA__SHIFT
#define HSDA_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HSDA_PS                     (* (reg32 *) HSDA__PS)
/* Port Configuration */
#define HSDA_PC                     (* (reg32 *) HSDA__PC)
/* Data Register */
#define HSDA_DR                     (* (reg32 *) HSDA__DR)
/* Input Buffer Disable Override */
#define HSDA_INP_DIS                (* (reg32 *) HSDA__PC2)


#if defined(HSDA__INTSTAT)  /* Interrupt Registers */

    #define HSDA_INTSTAT                (* (reg32 *) HSDA__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define HSDA_DRIVE_MODE_SHIFT       (0x00u)
#define HSDA_DRIVE_MODE_MASK        (0x07u << HSDA_DRIVE_MODE_SHIFT)


#endif /* End Pins HSDA_H */


/* [] END OF FILE */
