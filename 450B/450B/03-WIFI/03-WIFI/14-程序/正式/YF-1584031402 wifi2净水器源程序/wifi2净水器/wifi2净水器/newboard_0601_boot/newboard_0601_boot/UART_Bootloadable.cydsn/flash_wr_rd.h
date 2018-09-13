/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#ifdef _FLASH_WR_RD_
    #define MYFLASH 
#else
    #define MYFLASH extern
#endif

#ifndef _FLASH_WR_RD_H
#define _FLASH_WR_RD_H
    
    uint8 FlashDataBuf[128];
    
//    /* Requires custom linker flags to define the section. Add custom linker flags
//     * by right-clicking on the project, select "Build Settings", then under:
//     * ARM GCC -> Linker -> Command Line enter the desired custom flags.
//     * Add the following text (remove quotation marks):
//     * "-Wl,--section-start=.array_flash_loc=0x3200"
//     * Replace 0x3200 with your own location. Make sure it's at the start of a row. */
//    #define FLASH_LOCATION __attribute__ ((section(".array_flash_loc")))
    
      #define FLASH_DATA_BASE_ROW_NUM 254                 //255 ROW 
    #define FLASH_DATA_BASE_ROW_NUM_SYS 253                 //255 ROW        
       
    #define FLASH_DATA_BASE_ROW_START_ADDRESS 0x7800 + 0x700    //255 ROW start address is 0x7878 
    #define FLASH_DATA_BASE_ROW_START_ADDRESS_SYS 0x7800 + 0x680    //255 ROW start address is 0x7878 
  
    

    MYFLASH void Flash_Write_aRow_Data(uint8 databuf[]);
    MYFLASH uint8 Flash_Read_aByte(uint8 offsetadr);
    MYFLASH void Flash_Write_aRow_Data_Sys(uint8 databuf[]);
    MYFLASH uint8 Flash_Read_aByte_Sys(uint8 offsetadr);
    
#endif
/* [] END OF FILE */
