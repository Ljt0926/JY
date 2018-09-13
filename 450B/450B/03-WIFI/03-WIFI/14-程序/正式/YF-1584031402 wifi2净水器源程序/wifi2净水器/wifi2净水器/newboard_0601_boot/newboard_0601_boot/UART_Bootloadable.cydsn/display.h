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

#ifdef _DISPLAY_ 
    #define MYDIS   
#else
    #define MYDIS extern
#endif

#ifndef _DISPLAY_H
#define _DISPLAY_H
/***************************************************************\
system_define
\***************************************************************/
#define  DISSTANDBY 	Sys_Flownum=0
#define  DISMAINMENU 	Sys_Flownum=1
#define  DISTEST 			Sys_Flownum=2
#define  DISSETTING 	Sys_Flownum=3
#define  DISALLON 	  Sys_Flownum=4
#define  DISALARM 	  Sys_Flownum=5

/****************************************************************\
system_temp
\******************************************************************/

MYDIS unsigned int LData;
MYDIS unsigned int KData;
MYDIS unsigned int HData;
MYDIS unsigned int JData;
/*****************************************************************\
    LED Pannel Display
\*****************************************************************/
    MYDIS struct{
    	  unsigned on_pp:1;
        unsigned on_fc:1;
        unsigned on_ro1:1;
        unsigned on_ro2:1;
        unsigned on_ro3:1;
        unsigned on_bc:1;
        	
    	  unsigned off_pp:1;
        unsigned off_fc:1;
        unsigned off_ro1:1;
        unsigned off_ro2:1;
        unsigned off_ro3:1;
        unsigned off_bc:1;
	
        unsigned sflash_pp:1;
        unsigned sflash_fc:1;
        unsigned sflash_ro1:1;
        unsigned sflash_ro2:1;
        unsigned sflash_ro3:1;
        unsigned sflash_bc:1;
        	
        unsigned fflash_pp:1;
        unsigned fflash_fc:1;
        unsigned fflash_ro1:1;
        unsigned fflash_ro2:1;
        unsigned fflash_ro3:1;
        unsigned fflash_bc:1;
    }DisFlag_Filter;
    
    MYDIS struct{
				unsigned on_wifi:1;
				unsigned off_wifi:1;	
				unsigned sflash_wifi:1;		
				unsigned fflash_wifi:1;		
    }DisFlag_Wifi; 
    MYDIS struct{
				unsigned on_wifi:1;	
				unsigned on_setting:1;		
    }DisFlag_Keyshow;    
    MYDIS unsigned char LedPannelCnt;    
    /*****************************************************************\
    \*****************************************************************/
    MYDIS void Led_Pannel_Shutdown(void);
    MYDIS void Led_Pannel_Display(void); 
    MYDIS void Led_Pannel_Test(uint8 sn);
    MYDIS void Led_Pannel_Filter_Setting(uint8 sn);
    MYDIS void Led_Pannel_Process(uint8 flownum,uint8 testsn,uint8 settingsn);
 
   
#endif

/* [] END OF FILE */
