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
#define _MODULE_
#include "module.h"
#include "config.h"
#include "flash_wr_rd.h"

/*****************************************************************\
    Capsense
\*****************************************************************/
void Caps_Initial(void)
{
    CapSense_Start();	

    /* Initialize baselines */ 
    CapSense_InitializeAllBaselines();
        
}
    

void Caps_Scan(void)
{
    unsigned char kcnt;    
    /* Update all baselines */
    CapSense_UpdateEnabledBaselines();
    /* Start scanning all enabled sensors */
    CapSense_ScanEnabledWidgets();    
    /* Wait for scanning to complete */
    while(CapSense_IsBusy() != 0)
    {
    }
    kcnt = 0;
    BtnData2 = BtnData1;
    if(CapSense_CheckIsWidgetActive(BTN_ACTIVATION))  //判断 激活键
    {
        kcnt++;
        BtnData1 |= (0x01 << BTN_ACTIVATION);
    }else
    {
        BtnData1 &= ~(0x01 << BTN_ACTIVATION);
    }
    if(CapSense_CheckIsWidgetActive(BTN_SETTING))    //判断选择键
    {
        kcnt++;
        BtnData1 |= (0x01 << BTN_SETTING);
    }else
    {
        BtnData1 &= ~(0x01 << BTN_SETTING);
    }
    if(CapSense_CheckIsWidgetActive(BTN_LINK))    //判断南北键
    {
        kcnt++;
        BtnData1 |= (0x01 << BTN_LINK);
    }else
    {
        BtnData1 &= ~(0x01 << BTN_LINK);
    }
    
    
    
    
    
//   if(CapSense_CheckIsWidgetActive(BtnCnt))   
//    {
//        kcnt++;
//        BtnData1 |= (0x01 << BtnCnt);
//    }else
//    {
//        BtnData1 &= ~(0x01 << BtnCnt);
//    }
//    
//    BtnCnt++;
//    if(BtnCnt >= BTN_N)
//    {
//        BtnCnt = 0;
//    }
//    if((BtnData1&(0x01<<BTN_XZ)) && 
//       (!(BtnData2&(0x01<<BTN_XZ))))
//    {
//        DigitalBuf += 100;
//    }
}

/*
    EZI2C
*/
#if EZI2C_EN
void Ezi2c_Initial(void)
{
    /* Start EZI2C slave (SCB mode) */
    EZI2C_EzI2CSetBuffer1(EZI2C_SIZE, 0, ezI2CBuffer);
    EZI2C_Start();
}
#endif




/*******************************************************************************
*                       Timer
********************************************************************************/
CY_ISR(InterruptHandler)
{
	/* Clear Inerrupt */
   	Timer_ClearInterrupt(Timer_INTR_MASK_TC );
    
	/*100mS */
    //TestPort_Write(~TestPort_ReadDataReg());
    T10msSign = 1;
    
    
}

void Timer_Initial(void)
{
    /* Enable the Interrupt component connected to interrupt */
    CC_ISR_StartEx(InterruptHandler);

	/* Start the components */
    Timer_Start();
}

/*******************************************************************************
*                       EM_E2PROM
********************************************************************************/
void Eme2prom_Initial(void)
{
    //EEPROM_Start();   
}


void read(void)
{   
	u_char  i,j,k;
	memset(array,0x00,31);           
	for(i=0;i<44;i++)
	  {   
	      array[i]=Flash_Read_aByte_Sys(i);
	  }
	  
	for(i=0,j=0;i<24;(i=i+2))
	  {
	      Filter_Full_Data_Buf[j]|=array[i+1];
	      Filter_Full_Data_Buf[j]=(Filter_Full_Data_Buf[j]<<8);
	      Filter_Full_Data_Buf[j]|=array[i];
	      j++;
	  }
  for(k=0;k<6;k++)
    {
        if(Filter_Full_Data_Buf[k]>=Filter_Full_Data_Buf[k+6])
            Filter_Full_Data_Buf[k+6]=Filter_Full_Data_Buf[k];
        else
            Filter_Full_Data_Buf[k]=Filter_Full_Data_Buf[k+6];
    }
 	Firmware_Version=array[25];
 	Firmware_Versionbak=array[26];  
 	if(Firmware_Version>=Firmware_Versionbak)
     Firmware_Versionbak=Firmware_Version;
  else	
     Firmware_Version=Firmware_Versionbak;  		
}

void write(void)
{
    u_char m,n;
	  memset(array,0x00,31);        
    for(m=0,n=0;m<24;(m=m+2))
	    {
	        array[m]=Filter_Full_Data_Buf[n];//取出n号滤芯计时的低八位
	        array[m+1]=(Filter_Full_Data_Buf[n]>>8);//取出n号滤芯计时的高八位     
	        n++;
	    }
	  array[25]=Firmware_Version;
	  array[26]=Firmware_Version;
	  array[27]=Firmware_Update; 
    Flash_Write_aRow_Data_Sys(array);

}
void read1(void)
{
    u_char  i,j,k;
	  memset(array,0x00,31);           
    for(i=0;i<44;i++)
    {   
        array[i]=Flash_Read_aByte(i);
    }
    
    for(i=4,j=0;i<28;(i=i+2))
    {
        LvxinJishi[j]|=array[i+1];
        LvxinJishi[j]=(LvxinJishi[j]<<8);
        LvxinJishi[j]|=array[i];
        j++;
    }
    for(i=31,j=0;i<43;i++)
    {
        Filter_Changed_Num[j]|=array[i];
        j++;
    }
    jingshuiliang|=array[3];
    jingshuiliang=(jingshuiliang<<8);
    jingshuiliang|=array[2];
    
    EEjingshuiliang|=array[29];
    EEjingshuiliang=(EEjingshuiliang<<8);
    EEjingshuiliang|=array[28];
    
    NBfig=array[0];
    
    gyfullcnt=array[1];
    EEgyfullcnt=array[30];
    
    if(gyfullcnt>=EEgyfullcnt)
        EEgyfullcnt=gyfullcnt;
    else
        gyfullcnt=EEgyfullcnt;
    
    if(jingshuiliang>=EEjingshuiliang)
        EEjingshuiliang=jingshuiliang;
    else
        jingshuiliang=EEjingshuiliang;
    for(k=0;k<6;k++)
	    {
	        if(LvxinJishi[k]>=LvxinJishi[k+6])
	            LvxinJishi[k+6]=LvxinJishi[k];
	        else
	            LvxinJishi[k]=LvxinJishi[k+6];
	    }
	  for(k=0;k<6;k++)
	    {
	        if(Filter_Changed_Num[k]>=Filter_Changed_Num[k+6])
	            Filter_Changed_Num[k+6]=Filter_Changed_Num[k];
	        else
	            Filter_Changed_Num[k]=Filter_Changed_Num[k+6];
	    }

}
void write1(void)
{
    u_char m,n;
	  memset(array,0x00,43);        
    for(m=4,n=0;m<28;(m=m+2))
	    {
	        array[m]=LvxinJishi[n];//取出n号滤芯计时的低八位
	        array[m+1]=(LvxinJishi[n]>>8);//取出n号滤芯计时的高八位     
	        n++;
	    
	    }
    array[2]=jingshuiliang;
    array[3]=(jingshuiliang>>8);
    array[28]=EEjingshuiliang;
    array[29]=(EEjingshuiliang>>8);
    
    array[0]=NBfig;
    array[1]=gyfullcnt;
    array[30]=EEgyfullcnt;
    memcpy(&array[31],Filter_Changed_Num,12);
    Flash_Write_aRow_Data(array);

}
void clean_ram(void)
{
    u_char n;      
    for(n=0;n<44;n++)
    {
        array[n]=0;
    }     
    for(n=0;n<12;n++)
    {
       LvxinJishi[n]=0;   
    }
    for(n=0;n<12;n++)
    {
        Filter_Changed_Num[n]=0;
    }
    gyfullcnt=0;
    NBfig=1;
    jingshuiliang=0;
  	EEgyfullcnt=0;
  	EEjingshuiliang=0;
}

void Stop_All_Module(void)
{
		K2_Write(0);
		K1_Write(0);
		FMQ_Write(0);
    CapSense_Stop();
    Timer_Stop();
    PWM_Stop();
    Led_Pannel_Shutdown();
    UART_0_Stop();
    UART_1_Stop();    

}

void cleareepromArray(void)
{
    
    for(n=0;n<31;n++)
    {
        array[n]=0;
    }
     
    
    for(n=0;n<12;n++)
    {
       LvxinJishi[n]=0;
    
    
    }
    
    gyfullcnt=0;
    NBfig=1;//1为北
    jingshuiliang=0;
    array[0]=NBfig;
    
    
    
    
    
   Flash_Write_aRow_Data(array);      

}
/*******************************************************************************
                     WDT
********************************************************************************/
void clearwdt(void)
{
      CySysWdtUnlock();        
      CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
      CySysWdtLock();


}


/* [] END OF FILE */
