/*******************************************************************************
* File Name: FMQ.h  
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

#if !defined(CY_PINS_FMQ_H) /* Pins FMQ_H */
#define CY_PINS_FMQ_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FMQ_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    FMQ_Write(uint8 value) ;
void    FMQ_SetDriveMode(uint8 mode) ;
uint8   FMQ_ReadDataReg(void) ;
uint8   FMQ_Read(void) ;
uint8   FMQ_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define FMQ_DRIVE_MODE_BITS        (3)
#define FMQ_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FMQ_DRIVE_MODE_BITS))

#define FMQ_DM_ALG_HIZ         (0x00u)
#define FMQ_DM_DIG_HIZ         (0x01u)
#define FMQ_DM_RES_UP          (0x02u)
#define FMQ_DM_RES_DWN         (0x03u)
#define FMQ_DM_OD_LO           (0x04u)
#define FMQ_DM_OD_HI           (0x05u)
#define FMQ_DM_STRONG          (0x06u)
#define FMQ_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define FMQ_MASK               FMQ__MASK
#define FMQ_SHIFT              FMQ__SHIFT
#define FMQ_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FMQ_PS                     (* (reg32 *) FMQ__PS)
/* Port Configuration */
#define FMQ_PC                     (* (reg32 *) FMQ__PC)
/* Data Register */
#define FMQ_DR                     (* (reg32 *) FMQ__DR)
/* Input Buffer Disable Override */
#define FMQ_INP_DIS                (* (reg32 *) FMQ__PC2)


#if defined(FMQ__INTSTAT)  /* Interrupt Registers */

    #define FMQ_INTSTAT                (* (reg32 *) FMQ__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define FMQ_DRIVE_MODE_SHIFT       (0x00u)
#define FMQ_DRIVE_MODE_MASK        (0x07u << FMQ_DRIVE_MODE_SHIFT)


#endif /* End Pins FMQ_H */


/* [] END OF FILE */
