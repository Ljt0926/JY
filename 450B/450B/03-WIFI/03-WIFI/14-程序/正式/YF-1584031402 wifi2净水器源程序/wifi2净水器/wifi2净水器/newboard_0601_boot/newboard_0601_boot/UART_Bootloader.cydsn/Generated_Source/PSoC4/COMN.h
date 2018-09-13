/*******************************************************************************
* File Name: COMN.h  
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

#if !defined(CY_PINS_COMN_H) /* Pins COMN_H */
#define CY_PINS_COMN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "COMN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    COMN_Write(uint8 value) ;
void    COMN_SetDriveMode(uint8 mode) ;
uint8   COMN_ReadDataReg(void) ;
uint8   COMN_Read(void) ;
uint8   COMN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define COMN_DRIVE_MODE_BITS        (3)
#define COMN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - COMN_DRIVE_MODE_BITS))

#define COMN_DM_ALG_HIZ         (0x00u)
#define COMN_DM_DIG_HIZ         (0x01u)
#define COMN_DM_RES_UP          (0x02u)
#define COMN_DM_RES_DWN         (0x03u)
#define COMN_DM_OD_LO           (0x04u)
#define COMN_DM_OD_HI           (0x05u)
#define COMN_DM_STRONG          (0x06u)
#define COMN_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define COMN_MASK               COMN__MASK
#define COMN_SHIFT              COMN__SHIFT
#define COMN_WIDTH              7u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define COMN_PS                     (* (reg32 *) COMN__PS)
/* Port Configuration */
#define COMN_PC                     (* (reg32 *) COMN__PC)
/* Data Register */
#define COMN_DR                     (* (reg32 *) COMN__DR)
/* Input Buffer Disable Override */
#define COMN_INP_DIS                (* (reg32 *) COMN__PC2)


#if defined(COMN__INTSTAT)  /* Interrupt Registers */

    #define COMN_INTSTAT                (* (reg32 *) COMN__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define COMN_DRIVE_MODE_SHIFT       (0x00u)
#define COMN_DRIVE_MODE_MASK        (0x07u << COMN_DRIVE_MODE_SHIFT)


#endif /* End Pins COMN_H */


/* [] END OF FILE */
