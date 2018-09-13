/*******************************************************************************
* File Name: TDSPOWER.h  
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

#if !defined(CY_PINS_TDSPOWER_H) /* Pins TDSPOWER_H */
#define CY_PINS_TDSPOWER_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TDSPOWER_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TDSPOWER_Write(uint8 value) ;
void    TDSPOWER_SetDriveMode(uint8 mode) ;
uint8   TDSPOWER_ReadDataReg(void) ;
uint8   TDSPOWER_Read(void) ;
uint8   TDSPOWER_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TDSPOWER_DRIVE_MODE_BITS        (3)
#define TDSPOWER_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TDSPOWER_DRIVE_MODE_BITS))

#define TDSPOWER_DM_ALG_HIZ         (0x00u)
#define TDSPOWER_DM_DIG_HIZ         (0x01u)
#define TDSPOWER_DM_RES_UP          (0x02u)
#define TDSPOWER_DM_RES_DWN         (0x03u)
#define TDSPOWER_DM_OD_LO           (0x04u)
#define TDSPOWER_DM_OD_HI           (0x05u)
#define TDSPOWER_DM_STRONG          (0x06u)
#define TDSPOWER_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define TDSPOWER_MASK               TDSPOWER__MASK
#define TDSPOWER_SHIFT              TDSPOWER__SHIFT
#define TDSPOWER_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TDSPOWER_PS                     (* (reg32 *) TDSPOWER__PS)
/* Port Configuration */
#define TDSPOWER_PC                     (* (reg32 *) TDSPOWER__PC)
/* Data Register */
#define TDSPOWER_DR                     (* (reg32 *) TDSPOWER__DR)
/* Input Buffer Disable Override */
#define TDSPOWER_INP_DIS                (* (reg32 *) TDSPOWER__PC2)


#if defined(TDSPOWER__INTSTAT)  /* Interrupt Registers */

    #define TDSPOWER_INTSTAT                (* (reg32 *) TDSPOWER__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define TDSPOWER_DRIVE_MODE_SHIFT       (0x00u)
#define TDSPOWER_DRIVE_MODE_MASK        (0x07u << TDSPOWER_DRIVE_MODE_SHIFT)


#endif /* End Pins TDSPOWER_H */


/* [] END OF FILE */
