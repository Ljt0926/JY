/*******************************************************************************
* File Name: HCLK.h  
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

#if !defined(CY_PINS_HCLK_H) /* Pins HCLK_H */
#define CY_PINS_HCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HCLK_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    HCLK_Write(uint8 value) ;
void    HCLK_SetDriveMode(uint8 mode) ;
uint8   HCLK_ReadDataReg(void) ;
uint8   HCLK_Read(void) ;
uint8   HCLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HCLK_DRIVE_MODE_BITS        (3)
#define HCLK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HCLK_DRIVE_MODE_BITS))

#define HCLK_DM_ALG_HIZ         (0x00u)
#define HCLK_DM_DIG_HIZ         (0x01u)
#define HCLK_DM_RES_UP          (0x02u)
#define HCLK_DM_RES_DWN         (0x03u)
#define HCLK_DM_OD_LO           (0x04u)
#define HCLK_DM_OD_HI           (0x05u)
#define HCLK_DM_STRONG          (0x06u)
#define HCLK_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define HCLK_MASK               HCLK__MASK
#define HCLK_SHIFT              HCLK__SHIFT
#define HCLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HCLK_PS                     (* (reg32 *) HCLK__PS)
/* Port Configuration */
#define HCLK_PC                     (* (reg32 *) HCLK__PC)
/* Data Register */
#define HCLK_DR                     (* (reg32 *) HCLK__DR)
/* Input Buffer Disable Override */
#define HCLK_INP_DIS                (* (reg32 *) HCLK__PC2)


#if defined(HCLK__INTSTAT)  /* Interrupt Registers */

    #define HCLK_INTSTAT                (* (reg32 *) HCLK__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define HCLK_DRIVE_MODE_SHIFT       (0x00u)
#define HCLK_DRIVE_MODE_MASK        (0x07u << HCLK_DRIVE_MODE_SHIFT)


#endif /* End Pins HCLK_H */


/* [] END OF FILE */
