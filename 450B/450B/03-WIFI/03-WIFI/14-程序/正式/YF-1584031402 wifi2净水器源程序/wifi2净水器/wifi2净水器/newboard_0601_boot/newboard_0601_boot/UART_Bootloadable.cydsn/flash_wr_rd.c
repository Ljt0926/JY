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
#define _FLASH_WR_RD_
#include "flash_wr_rd.h"
#include <project.h>

void Flash_Write_aRow_Data(uint8 databuf[])
{
    //uint32 flashWriteResult;
    /* Configure the Flash Writes for the current clock frequency */
    CySysFlashSetWaitCycles(48);           
    /* Write the SRAM array into flash */
    CySysFlashWriteRow(FLASH_DATA_BASE_ROW_NUM, databuf);
}
void Flash_Write_aRow_Data_Sys(uint8 databuf[])
{
    //uint32 flashWriteResult;
    /* Configure the Flash Writes for the current clock frequency */
    CySysFlashSetWaitCycles(48);      
    /* Write the SRAM array into flash */
    CySysFlashWriteRow(FLASH_DATA_BASE_ROW_NUM_SYS, databuf);
}
uint8 Flash_Read_aByte(uint8 offsetadr)
{
    uint8 *pp;
    uint8 redata;
    pp = FLASH_DATA_BASE_ROW_START_ADDRESS + offsetadr;   
    redata = *pp;  
    return(redata);
}
uint8 Flash_Read_aByte_Sys(uint8 offsetadr)
{
    uint8 *pp;
    uint8 redata;
    pp = FLASH_DATA_BASE_ROW_START_ADDRESS_SYS + offsetadr;   
    redata = *pp;  
    return(redata);
}
/* [] END OF FILE */
