/*******************************************************************************
* File Name: BootloaderStart.h  
* Version 2.5
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

#if !defined(CY_PINS_BootloaderStart_H) /* Pins BootloaderStart_H */
#define CY_PINS_BootloaderStart_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BootloaderStart_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    BootloaderStart_Write(uint8 value) ;
void    BootloaderStart_SetDriveMode(uint8 mode) ;
uint8   BootloaderStart_ReadDataReg(void) ;
uint8   BootloaderStart_Read(void) ;
uint8   BootloaderStart_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BootloaderStart_DRIVE_MODE_BITS        (3)
#define BootloaderStart_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BootloaderStart_DRIVE_MODE_BITS))
#define BootloaderStart_DRIVE_MODE_SHIFT       (0x00u)
#define BootloaderStart_DRIVE_MODE_MASK        (0x07u << BootloaderStart_DRIVE_MODE_SHIFT)

#define BootloaderStart_DM_ALG_HIZ         (0x00u << BootloaderStart_DRIVE_MODE_SHIFT)
#define BootloaderStart_DM_DIG_HIZ         (0x01u << BootloaderStart_DRIVE_MODE_SHIFT)
#define BootloaderStart_DM_RES_UP          (0x02u << BootloaderStart_DRIVE_MODE_SHIFT)
#define BootloaderStart_DM_RES_DWN         (0x03u << BootloaderStart_DRIVE_MODE_SHIFT)
#define BootloaderStart_DM_OD_LO           (0x04u << BootloaderStart_DRIVE_MODE_SHIFT)
#define BootloaderStart_DM_OD_HI           (0x05u << BootloaderStart_DRIVE_MODE_SHIFT)
#define BootloaderStart_DM_STRONG          (0x06u << BootloaderStart_DRIVE_MODE_SHIFT)
#define BootloaderStart_DM_RES_UPDWN       (0x07u << BootloaderStart_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define BootloaderStart_MASK               BootloaderStart__MASK
#define BootloaderStart_SHIFT              BootloaderStart__SHIFT
#define BootloaderStart_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BootloaderStart_PS                     (* (reg32 *) BootloaderStart__PS)
/* Port Configuration */
#define BootloaderStart_PC                     (* (reg32 *) BootloaderStart__PC)
/* Data Register */
#define BootloaderStart_DR                     (* (reg32 *) BootloaderStart__DR)
/* Input Buffer Disable Override */
#define BootloaderStart_INP_DIS                (* (reg32 *) BootloaderStart__PC2)


#if defined(BootloaderStart__INTSTAT)  /* Interrupt Registers */

    #define BootloaderStart_INTSTAT                (* (reg32 *) BootloaderStart__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins BootloaderStart_H */


/* [] END OF FILE */
