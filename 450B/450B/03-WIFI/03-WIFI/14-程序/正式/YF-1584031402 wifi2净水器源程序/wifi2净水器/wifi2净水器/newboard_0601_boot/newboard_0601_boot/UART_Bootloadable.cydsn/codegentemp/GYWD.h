/*******************************************************************************
* File Name: GYWD.h  
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

#if !defined(CY_PINS_GYWD_H) /* Pins GYWD_H */
#define CY_PINS_GYWD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GYWD_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GYWD_Write(uint8 value) ;
void    GYWD_SetDriveMode(uint8 mode) ;
uint8   GYWD_ReadDataReg(void) ;
uint8   GYWD_Read(void) ;
uint8   GYWD_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GYWD_DRIVE_MODE_BITS        (3)
#define GYWD_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GYWD_DRIVE_MODE_BITS))

#define GYWD_DM_ALG_HIZ         (0x00u)
#define GYWD_DM_DIG_HIZ         (0x01u)
#define GYWD_DM_RES_UP          (0x02u)
#define GYWD_DM_RES_DWN         (0x03u)
#define GYWD_DM_OD_LO           (0x04u)
#define GYWD_DM_OD_HI           (0x05u)
#define GYWD_DM_STRONG          (0x06u)
#define GYWD_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define GYWD_MASK               GYWD__MASK
#define GYWD_SHIFT              GYWD__SHIFT
#define GYWD_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GYWD_PS                     (* (reg32 *) GYWD__PS)
/* Port Configuration */
#define GYWD_PC                     (* (reg32 *) GYWD__PC)
/* Data Register */
#define GYWD_DR                     (* (reg32 *) GYWD__DR)
/* Input Buffer Disable Override */
#define GYWD_INP_DIS                (* (reg32 *) GYWD__PC2)


#if defined(GYWD__INTSTAT)  /* Interrupt Registers */

    #define GYWD_INTSTAT                (* (reg32 *) GYWD__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define GYWD_DRIVE_MODE_SHIFT       (0x00u)
#define GYWD_DRIVE_MODE_MASK        (0x07u << GYWD_DRIVE_MODE_SHIFT)


#endif /* End Pins GYWD_H */


/* [] END OF FILE */
