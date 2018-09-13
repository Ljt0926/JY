/*******************************************************************************
* File Name: CX.h  
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

#if !defined(CY_PINS_CX_H) /* Pins CX_H */
#define CY_PINS_CX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CX_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    CX_Write(uint8 value) ;
void    CX_SetDriveMode(uint8 mode) ;
uint8   CX_ReadDataReg(void) ;
uint8   CX_Read(void) ;
uint8   CX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CX_DRIVE_MODE_BITS        (3)
#define CX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CX_DRIVE_MODE_BITS))

#define CX_DM_ALG_HIZ         (0x00u)
#define CX_DM_DIG_HIZ         (0x01u)
#define CX_DM_RES_UP          (0x02u)
#define CX_DM_RES_DWN         (0x03u)
#define CX_DM_OD_LO           (0x04u)
#define CX_DM_OD_HI           (0x05u)
#define CX_DM_STRONG          (0x06u)
#define CX_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define CX_MASK               CX__MASK
#define CX_SHIFT              CX__SHIFT
#define CX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CX_PS                     (* (reg32 *) CX__PS)
/* Port Configuration */
#define CX_PC                     (* (reg32 *) CX__PC)
/* Data Register */
#define CX_DR                     (* (reg32 *) CX__DR)
/* Input Buffer Disable Override */
#define CX_INP_DIS                (* (reg32 *) CX__PC2)


#if defined(CX__INTSTAT)  /* Interrupt Registers */

    #define CX_INTSTAT                (* (reg32 *) CX__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define CX_DRIVE_MODE_SHIFT       (0x00u)
#define CX_DRIVE_MODE_MASK        (0x07u << CX_DRIVE_MODE_SHIFT)


#endif /* End Pins CX_H */


/* [] END OF FILE */
