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

#ifdef _MODULE_
    #define MYMOD
#else
    #define MYMOD extern
#endif


#ifndef _MODULE_H
#define _MODULE_H
 
    
    /*****************************************************************\
    Capsense
    \*****************************************************************/
    #define BTN_N   3       //Capsens Butten Number
    #define BTN_ACTIVATION    0
    #define BTN_SETTING      	1
    #define BTN_LINK      		2

    
    MYMOD unsigned char BtnData1,BtnData2,BtnData;
    MYMOD unsigned char BtnCnt,eepfig;
    
    
    MYMOD struct{
        unsigned sk1:1;
        unsigned sk2:1;
        unsigned sk3:1;
        unsigned sk4:1;
        unsigned ADfig:1;
        
        unsigned :12;
    }BtnFlag;
    
     
    
    
    
    MYMOD void Caps_Initial(void);
    MYMOD void Caps_Scan(void);
    
    /*
            EzI2C
    */
    
    
    
    /*******************************************************************************
    *                       Timer
    ********************************************************************************/
    MYMOD uint8 T10msSign;
    
    MYMOD void Timer_Initial(void);
    
    
    /*
             EzI2C
    */
    //#define EZI2C_EN 
    #if EZI2C_EN
    /* EZI2C buffer */
    #define EZI2C_SIZE 5
    MYMOD uint8 ezI2CBuffer[EZI2C_SIZE];
    #endif
    
   

    
    /*******************************************************************************
    *                       ADC
    ********************************************************************************/
     MYMOD  void POWEROVER_Initial(void);
    
    
    
    
    #define V24V_CH           0x00u
    #define BM_CH             0x01u
    
    MYMOD uint32 AdcReady;
    MYMOD uint16 AdcData[2],AdcBuf[2];
                 
    MYMOD uint32 AdcTemp[2];
    
    MYMOD void ADC_Initial(void);
    
    
    
    /*******************************************************************************
    *                       EM_E2PROM
    ********************************************************************************/
    #define E2PROM_NUM  8
   
    MYMOD uint8 array[128];
    MYMOD uint8 array_0[128];
    
    


    

    
    
    
   
    MYMOD    void Eme2prom_Initial(void);
    
    
    MYMOD    void read(void);
    MYMOD    void read1(void);
    MYMOD    void write(void);
    MYMOD    void write1(void);
    MYMOD    void clean_ram(void);
    
    MYMOD    void cleareepromArray(void);
    
    MYMOD void Stop_All_Module(void);
    
    MYMOD    void clearwdt(void);
    
#endif

/* [] END OF FILE */
