/*******************************************************************************
* File Name: WIFIPOWER.h  
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

#if !defined(CY_PINS_WIFIPOWER_H) /* Pins WIFIPOWER_H */
#define CY_PINS_WIFIPOWER_H

#include "cytypes.h"
#include "cyfitter.h"
#include "WIFIPOWER_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    WIFIPOWER_Write(uint8 value) ;
void    WIFIPOWER_SetDriveMode(uint8 mode) ;
uint8   WIFIPOWER_ReadDataReg(void) ;
uint8   WIFIPOWER_Read(void) ;
uint8   WIFIPOWER_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define WIFIPOWER_DRIVE_MODE_BITS        (3)
#define WIFIPOWER_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - WIFIPOWER_DRIVE_MODE_BITS))

#define WIFIPOWER_DM_ALG_HIZ         (0x00u)
#define WIFIPOWER_DM_DIG_HIZ         (0x01u)
#define WIFIPOWER_DM_RES_UP          (0x02u)
#define WIFIPOWER_DM_RES_DWN         (0x03u)
#define WIFIPOWER_DM_OD_LO           (0x04u)
#define WIFIPOWER_DM_OD_HI           (0x05u)
#define WIFIPOWER_DM_STRONG          (0x06u)
#define WIFIPOWER_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define WIFIPOWER_MASK               WIFIPOWER__MASK
#define WIFIPOWER_SHIFT              WIFIPOWER__SHIFT
#define WIFIPOWER_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WIFIPOWER_PS                     (* (reg32 *) WIFIPOWER__PS)
/* Port Configuration */
#define WIFIPOWER_PC                     (* (reg32 *) WIFIPOWER__PC)
/* Data Register */
#define WIFIPOWER_DR                     (* (reg32 *) WIFIPOWER__DR)
/* Input Buffer Disable Override */
#define WIFIPOWER_INP_DIS                (* (reg32 *) WIFIPOWER__PC2)


#if defined(WIFIPOWER__INTSTAT)  /* Interrupt Registers */

    #define WIFIPOWER_INTSTAT                (* (reg32 *) WIFIPOWER__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define WIFIPOWER_DRIVE_MODE_SHIFT       (0x00u)
#define WIFIPOWER_DRIVE_MODE_MASK        (0x07u << WIFIPOWER_DRIVE_MODE_SHIFT)


#endif /* End Pins WIFIPOWER_H */


/* [] END OF FILE */
