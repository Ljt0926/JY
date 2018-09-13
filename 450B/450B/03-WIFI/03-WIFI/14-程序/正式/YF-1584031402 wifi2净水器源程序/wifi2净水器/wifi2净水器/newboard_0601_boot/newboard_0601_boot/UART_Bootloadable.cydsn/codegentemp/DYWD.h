/*******************************************************************************
* File Name: DYWD.h  
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

#if !defined(CY_PINS_DYWD_H) /* Pins DYWD_H */
#define CY_PINS_DYWD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DYWD_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    DYWD_Write(uint8 value) ;
void    DYWD_SetDriveMode(uint8 mode) ;
uint8   DYWD_ReadDataReg(void) ;
uint8   DYWD_Read(void) ;
uint8   DYWD_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DYWD_DRIVE_MODE_BITS        (3)
#define DYWD_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DYWD_DRIVE_MODE_BITS))

#define DYWD_DM_ALG_HIZ         (0x00u)
#define DYWD_DM_DIG_HIZ         (0x01u)
#define DYWD_DM_RES_UP          (0x02u)
#define DYWD_DM_RES_DWN         (0x03u)
#define DYWD_DM_OD_LO           (0x04u)
#define DYWD_DM_OD_HI           (0x05u)
#define DYWD_DM_STRONG          (0x06u)
#define DYWD_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define DYWD_MASK               DYWD__MASK
#define DYWD_SHIFT              DYWD__SHIFT
#define DYWD_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DYWD_PS                     (* (reg32 *) DYWD__PS)
/* Port Configuration */
#define DYWD_PC                     (* (reg32 *) DYWD__PC)
/* Data Register */
#define DYWD_DR                     (* (reg32 *) DYWD__DR)
/* Input Buffer Disable Override */
#define DYWD_INP_DIS                (* (reg32 *) DYWD__PC2)


#if defined(DYWD__INTSTAT)  /* Interrupt Registers */

    #define DYWD_INTSTAT                (* (reg32 *) DYWD__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define DYWD_DRIVE_MODE_SHIFT       (0x00u)
#define DYWD_DRIVE_MODE_MASK        (0x07u << DYWD_DRIVE_MODE_SHIFT)


#endif /* End Pins DYWD_H */


/* [] END OF FILE */
