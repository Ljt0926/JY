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

#define _MAIN_
#include <project.h>
#include "uart_0.c"
#include "uart_1.c"
#include "config.h"

uint8 UartRx,BootloaderSign;
uint32 Dly,Dly1;
uint8 NbPressCnt,NBfig,NBPressCnt,NBPressStart,lXXZcnt_fig;//南北计数,缺水标志,
uint16 LvxinJishi[12];
uint8 BUZfkg,qushui_BUZcnt,BUZfkgtemp,BUZqueshuifkg,standkeyfig;
uint8 dismode,V24fig,V24dengdai;
uint8 V24Vcnt;
uint8 Ack_Timer;              //应答时间设置
uint8 TimeBase_Interrupt_CountOne,TimeBase_Interrupt_CountTwo;
uint16 TimeBase_Interrupt_CountThree;
CY_ISR(UART_ISR_0_FUN)
{
    uint32 resource = UART_0_GetRxInterruptSource();
     if(resource & UART_0_INTR_RX_NOT_EMPTY)
    {
        WorkFlag.uart_0_tx=0;     
	    LoadUARTData((uint8)(UART_0_UartGetByte()& 0xFF));	

        WorkFlag.uart_0_tx=1;       
      	UART_0_ClearRxInterruptSource(UART_0_INTR_RX_NOT_EMPTY);//清中断源 
    }
    
}
/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
********************************************************************************/
CY_ISR(UART_ISR_1_FUN)
{
    uint32 resource = UART_1_GetRxInterruptSource();
    if(resource & UART_1_INTR_RX_NOT_EMPTY)
    {
        WorkFlag.uart_1_tx=0;     
	    LoadTDSBoardData((uint8)(UART_1_UartGetByte()& 0xFF));
        WorkFlag.uart_1_tx=1;       
      	UART_1_ClearRxInterruptSource(UART_1_INTR_RX_NOT_EMPTY);//清中断源 
    }
}


CY_ISR(isr_wdt)
{
    /* Clear interrupts state */
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
    CyIntClearPending(9);
    CySoftwareReset();
}

CY_ISR(isr_lowpower_Interrupt)
{
	CySoftwareReset(); 
}
CY_ISR(V24ISR)
{
    V24_IN_ISR_Disable();
    while(V24dengdai==0)
	    {
	        if(V24V_Read()==1)
	        {
	           
	            V24Vcnt++;
	            if(V24Vcnt>100)
	            {  
	                V24dengdai=1; 
	                V24Vcnt=0;
	            }    
	        }    
	
	        else
	        {
	            V24Vcnt=0;
	             V24dengdai=0; 
	              V24_IN_ISR_Enable();
	              return;
	            
	        } 
	    }
		V24dengdai=0;
    Stop_All_Module();
    if(cleareepromArrayflag==1)
    	{
    		cleareepromArrayflag=0;
    		cleareepromArray();  
    	}
    else   
    	write1();
    clearwdt();    
    CyDelayUs(1000); 
   while(V24fig==0)
   {
       if(V24V_Read()==1)
            V24fig=0;
       else
            V24fig=1; 
    

   }

    V24fig=0; 
 CySoftwareReset();
}
/*******************************************************************************
*                       POWEROVER
********************************************************************************/
void Open_UART_WIFI_ISR(void)
{   
  UART_0_Init();
  UART_0_Enable();
  UART_0_Start();
  UART_0_SetCustomInterruptHandler(UART_ISR_0_FUN);  
}
/*******************************************************************************
*                       POWEROVER
********************************************************************************/
void Open_UART_TDS_ISR(void)
{   
  UART_1_Init();
  UART_1_Enable();
  UART_1_Start();
  UART_1_SetCustomInterruptHandler(UART_ISR_1_FUN);
}
/*******************************************************************************
*                       POWEROVER
********************************************************************************/
void Open_V24_IN_ISR(void)
{
    V24_IN_ISR_Disable();

    /* Set the ISR to point to the V24_IN_ISR Interrupt. */
    V24_IN_ISR_SetVector(V24ISR);

    /* Set the priority. */
    V24_IN_ISR_SetPriority(1);

    /* Enable it. */
    V24_IN_ISR_Enable();

}
/*******************************************************************************
*                       POWER brownout
********************************************************************************/
void Open_POWERLOW_ISR(void)
{
/* For all we know the interrupt is active. */
isr_lowpower_1_Disable();

/* Set the ISR to point to the isr_lowpower Interrupt. */
isr_lowpower_1_SetVector(isr_lowpower_Interrupt);

/* Set the priority. */
isr_lowpower_1_SetPriority(0);

/* Enable it. */
isr_lowpower_1_Enable();

}
void Open_Watchdog(void)
{
    CyIntSetVector(9, isr_wdt);
    CyIntEnable(9);
    CySysWdtUnlock(); /* Unlock WDT counter 0 for configuration */
    CySysWdtWriteMode(CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_INT); /* Generate interrupts on TC */
    CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0, 65535 );
    CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER0, 1); /* Enable WDT clear on match */
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK); /* Enable WDT counter 0 */
    CySysWdtLock(); /* Lock WDT counter 0's configuration */
}

int main()
{
  uint8 ij;
	CyDelay(1000);
	Eme2prom_Initial();
	read();
	read1();
	CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */            
	Caps_Initial();
	Timer_Initial();          
	Sys_Init();
	V24fig=0; 
	lvxin_panduan(); 
	Open_POWERLOW_ISR();       
	Open_UART_WIFI_ISR();       
	Open_UART_TDS_ISR();
	Open_Watchdog();
	CySysLvdEnable(CY_LVD_THRESHOLD_2_10_V); 
	for(ij=31;ij<128;ij++)
	  {    
	      array[ij]=0;               
	  }   
    while(1)
    {
        clearwdt();
        Wifi_Fun();
        clearwdt();
        Caps_Scan(); 
        Timer_Isr_Fun();
        clearwdt();
        Work_Fun(); 
        Buzzer_Fun(); 
        clearwdt();
        Uart_0_Putchar();
        clearwdt();
				if(WorkFlag.test==1)
					Sys_Flownum=2;
        Led_Pannel_Process(Sys_Flownum,Sys_Testsn,Sys_Settingsn);
        if(firmwave_updatecnt>10)
          {
						firmwave_updatecnt=0;
						clearwdt();
						Bootloadable_Load();
                           
          }
		  	if(TimeBase_Interrupt_CountOne>5)
		  		{
		              TimeBase_Interrupt_CountOne=0;
		  		}
		  	if (TimeBase_Interrupt_CountTwo>100) 
		  		{
		  			TimeBase_Interrupt_CountTwo=0;
		  			/* Get received character or zero if nothing has been received yet */
		  			if((PowerOnCnt00>60)&&(poweroverfig==0)) 
		  			  {                  
		  			    poweroverfig=1;  
		  			    Open_V24_IN_ISR();
		  			  } 
		  			Error_Send();	
		  		}
		  	if (TimeBase_Interrupt_CountThree>1000) 
		  		{
		              TimeBase_Interrupt_CountThree=0;
		  		}

    }

}

/* [] END OF FILE */
