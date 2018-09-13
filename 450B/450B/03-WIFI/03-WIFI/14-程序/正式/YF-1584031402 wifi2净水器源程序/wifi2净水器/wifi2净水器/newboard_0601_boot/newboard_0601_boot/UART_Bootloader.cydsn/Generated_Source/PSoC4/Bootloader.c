/*******************************************************************************
* File Name: Bootloader.c
* Version 1.30
*
*  Description:
*   Provides an API for the Bootloader component. The API includes functions
*   for starting boot loading operations, validating the application and
*   jumping to the application.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Bootloader_PVT.h"
#include "project.h"
#include <string.h> 


/*******************************************************************************
* The Checksum and SizeBytes are forcefully set in code. We then post process
* the hex file from the linker and inject their values then. When the hex file
* is loaded onto the device these two variables should have valid values.
* Because the compiler can do optimizations to remove the constant
* accesses, these should not be accessed directly. Instead, the variables
* CyBtldr_ChecksumAccess & CyBtldr_SizeBytesAccess should be used to get the
* proper values at runtime.
*******************************************************************************/
#if defined(__ARMCC_VERSION) || defined (__GNUC__)
    __attribute__((section (".bootloader"), used))
#elif defined (__ICCARM__)
    #pragma location=".bootloader"
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) */

#if defined(__ARMCC_VERSION) || defined (__GNUC__) || defined (__C51__)
           const uint8  CYCODE Bootloader_Checksum = 0u;
#elif defined (__ICCARM__)
    __root const uint8  CYCODE Bootloader_Checksum = 0u;
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) || defined (__C51__) */
const uint8  CYCODE *Bootloader_ChecksumAccess  = (const uint8  CYCODE *)(&Bootloader_Checksum);

#if defined(__ARMCC_VERSION) || defined (__GNUC__)
    __attribute__((section (".bootloader"), used))
#elif defined (__ICCARM__)
    #pragma location=".bootloader"
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) */

const uint32 CYCODE Bootloader_SizeBytes = 0xFFFFFFFFu;
const uint32 CYCODE *Bootloader_SizeBytesAccess = (const uint32 CYCODE *)(&Bootloader_SizeBytes);
 #define Bootloader_activeApp      (Bootloader_MD_BTLDB_ACTIVE_0)

CYBIT f_ack_1,f_delay;

/***************************************
*     Function Prototypes
***************************************/
                                  ;
uint8 dataBuffer_0[300],packetBuffer[300];
uint8 z_iicount, z_itotalcount;
                                    ;
extern void Open_UART_WIFI_ISR(void);
extern CY_ISR(UART_ISR_0_FUN);
static void     Bootloader_HostLink(void); 
                               

static void     Bootloader_LaunchApplication(void) CYSMALL \
                                    ;

#if(!CY_PSOC3)
    /* Implementation for the PSoC 3 resides in a Bootloader_psoc3.a51 file.  */
    static void     Bootloader_LaunchBootloadable(uint32 appAddr);
#endif  /* (!CY_PSOC3) */

CYBIT BUZfkg;
uint32  BuzzerDly;
uint8 gcWifiCommunState;
struct{
		unsigned handshake_ok:1;           //握手成功标志
		unsigned bootloadable_load_ok:1;
		unsigned gcReceComm2OK:1;
		unsigned gcReceComm1OK:1;
		unsigned u8E0Set:1;
		unsigned u8E1Set:1;
		unsigned u8E2Set:1;
		unsigned u8E3Set:1;
}WifiWorkFlag;


struct{
    unsigned send_data_load:1;            //启动发送标志
    unsigned flag_rev_end:1;              //接收完毕标志
    unsigned uart_ack:1;              //应答标志位
    unsigned flag_Uart_Work:1;         //Uart_Work标志位
}WifidatagramWorkFlag;
uint8 gcWIFICTL,giWIFICommand,giWIFIDATALength;
 typedef struct Buffer0
{
	uint8  	gcATReceData[WIFIBUFLEN];  // wifi 模块一次传输1440字节，这里有51芯片只有1280个xdata
	uint16 	gcATReceCount;
} Buffer2;
struct Buffer0    ATReceBuffer[1];
uint16		iUartSendLen;
uint16		iSendCounter;
uint16 iSendCounter,iUartSendLen;
uint8 *cpSendBufPtr;
CYBIT F_uart_0_tx;

/* CRC 高位字节值表 */ 
const uint8 auchCRCHi[] = { 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40 
} ; 
/* CRC低位字节值表*/ 
const uint8 auchCRCLo[] = { 		
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 
0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 
0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 
0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 
0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 
0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 
0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 
0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 
0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 
0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 
0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 
0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 
0x43, 0x83, 0x41, 0x81, 0x80, 0x40 		   
} ;
/**
 * @brief      计算CRC16数据
 * @param     puchMsg:需要计算的数据指针
　*            usDataLen：数据长度
 * @return     返回CRC16结果
　* @details     
*/
uint16 crc16(uint8 *puchMsg, uint16 usDataLen) 
{ 
	uint8 uchCRCHi = 0xFF ; /* 高CRC字节初始化 */ 
	uint8 uchCRCLo = 0xFF ; /* 低CRC 字节初始化 */ 
	uint32 uIndex ; /* CRC循环中的索引 */ 
	while (usDataLen--) /* 传输消息缓冲区 */ 
	{ 
		uIndex = uchCRCHi ^ *puchMsg++ ; /* 计算CRC */ 
		uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ; 
		uchCRCLo = auchCRCLo[uIndex] ; 
	} 
	return (uchCRCHi << 8 | uchCRCLo);	
}
/*********************************************************************************************************
** 函数名称: void Comm_Uart_0_PrintHex8(uint8 value)
** 功能描述: 从串口发送数据
** 入口参数:	无
** 出口参数:	无
********************************************************************************************************/
void Comm_Uart_0_PrintHex8(uint8 value)
{
    while(UART_0_FIFO_SIZE == UART_0_GET_TX_FIFO_ENTRIES);
    UART_0_TX_FIFO_WR_REG = (uint8)(value);
}
/*********************************************************************************************************
** 函数名称: void UART_putchar(void)
** 功能描述: 从串口发送数据
** 入口参数:	无
** 出口参数:	无
********************************************************************************************************/
void Uart_0_Putchar(void)
{
    	if(F_uart_0_tx!=0)
		{
    if(iSendCounter!=(iUartSendLen+1))
		{
          Comm_Uart_0_PrintHex8(cpSendBufPtr[iSendCounter++]);
	    }
        }

}

/*********************************************************************************************************
** 函数名称: void UART_SendData(unsigned char	 *data_buf,unsigned char	 count)
** 功能描述: 从串口发送数据
** 入口参数: data_buf:发送数据缓冲区首地址
**			 count	:发送字节数
** 出口参数:	无
********************************************************************************************************/
void UART_SendData(uint8	 *data_buf,uint16 iCount)
{
	iUartSendLen = iCount-1;
	iSendCounter = 0;
	cpSendBufPtr = &data_buf[0];
}

/******************************************************************************
* 函 数 名: Sum_Make_Verify (uint8 *pBuf, uint len)
* 函数功能: 串口接收程序
* 入口参数: 无
* 返    回: 
*******************************************************************************/
uint8 Sum_Make_Verify (uint8 *PBuf, uint16 Len)
{
    uint8 Verify = 0;
    while (Len--)
    {
        Verify = Verify + (*PBuf);
        ++ PBuf;
    }
    return (~Verify + 1);
}
/*
*********************************************************************************************************
** 函数名称 ：SendDataToWifi()
** 函数功能 ：发送数据到WIFI模块                          
** 入口参数 ：cCtl：控制字类型 
  							0x00(主动发送指令要求对方回复) 
  							0x80(返回指令) 
  							0x40(主动发送无需对方回复)
              unsigned char  *DataBuf  数据缓存区            
              unsigned int   iLength   数据长度          
** 出口参数 ：无
*********************************************************************************************************
*/
void  SendDataToWifi(uint8 cCtl,
                      uint16 cCommand,
                     uint8 *DataBuf,
		     							uint16 iLength)
{
 
    uint16 xxxxx;
    static uint8 cBuf[255]; ////51 has only 256 data in soc
    memset(cBuf,0x00,WIFIBUFLEN);
    cBuf[0] = WIFI_SYN_0;        	     // SYNC0
    cBuf[1] = WIFI_SYN_1;        	     // SYNC1
    cBuf[2] = 0x01;   //MCU_PROTOCOL_VERSION 
    if(cCommand==0xccc5)
    {
        cBuf[3]=0;
        cBuf[4]=0x00;
    }
    else
    {
        cBuf[3]=z_itotalcount;
        cBuf[4]=z_iicount;
    }
    cBuf[5] = cCtl;   	 // Wctrl
    cBuf[6] =  (cCommand)>>8;//长度0
    cBuf[7] =(cCommand)&0x00ff;//长度1	  cBuf[8]=(iLength)>>8;//长度0
    cBuf[8] =(iLength)>>8;//长度0
    cBuf[9] =(iLength)&0x00ff;//长度1
    //cBuf[iLength+10]=0x44;
    
    if(iLength!=0)
    {
        memcpy(&cBuf[10],DataBuf,iLength);
           // xxxxx=crc16(cBuf,10+iLength);
        xxxxx=crc16(&cBuf[0],10+iLength);
        cBuf[iLength+10] =xxxxx>>8;
        cBuf[iLength+11] =xxxxx;
        //cBuf[iLength+10]=0x88;
    }
    else
    {
        xxxxx=crc16(&cBuf[0],10);
        cBuf[iLength+10] = xxxxx>>8;
        cBuf[iLength+11] = xxxxx;
        
    }
		WifidatagramWorkFlag.flag_Uart_Work=1; 
    CyGlobalIntDisable;                  //应答时间设置
    UART_SendData(cBuf,iLength+12);   ///The Last six 0x00 is PADDING
    CyGlobalIntEnable; 
}



/*
	========================================================================
* 函 数 名: LodaUARTData(   IN unsigned char  UartData)
* 函数功能: 串口发送程序
* 入口参数: UartData
* 返    回: 
	========================================================================
*/
void LoadUARTData(uint8  UartData)
{
	switch (gcWifiCommunState)
		{
			 case WIFI_WAIT_SYN_0:		                 // 1数据包头FA
			   		if(UartData==WIFI_SYN_0)
  			   		gcWifiCommunState = WIFI_WAIT_SYN_1;
  			  	    ATReceBuffer[0].gcATReceData[0]= UartData;
			  		break;
			 case WIFI_WAIT_SYN_1:		                // 2数据包头FB
			   		if(UartData==WIFI_SYN_1)
  			   		gcWifiCommunState = WIFI_PROTOCOL_JUDGE;
  			  	    ATReceBuffer[0].gcATReceData[1]= UartData;
			  		break;
			 case WIFI_PROTOCOL_JUDGE:                //3协议版本
			 			if(UartData==0x01)
  			   		gcWifiCommunState = WIFI_TOTAL_FRAME_NUM;
  			  	ATReceBuffer[0].gcATReceData[2]= UartData;
			  		break;
			 case WIFI_TOTAL_FRAME_NUM:               //4总帧数量
			 			gcWifiCommunState = WIFI_FRAME_NUM;

  			  	ATReceBuffer[0].gcATReceData[3]= UartData;
			  		break;		
			 case WIFI_FRAME_NUM:                    //5帧序号
			 			gcWifiCommunState = WIFI_WAIT_CTL;

  			  	ATReceBuffer[0].gcATReceData[4]= UartData;
			  		break;		
			 case WIFI_WAIT_CTL:	               // 6控制字
			    	gcWIFICTL = UartData;
						gcWifiCommunState = WIFI_COMMAND_1;
  			  	ATReceBuffer[0].gcATReceData[5]= UartData;
			 			break;		 
			 case WIFI_COMMAND_1:	           // 7指令1
			    	giWIFICommand = UartData;
						gcWifiCommunState = WIFI_COMMAND_2;
  			  	ATReceBuffer[0].gcATReceData[6]= UartData;
			 			break;
			 case WIFI_COMMAND_2:			  // 8指令2
			    	giWIFICommand = (giWIFICommand<<8)+UartData;
      				  gcWifiCommunState = WIFI_LENGTH1;     
  			  	ATReceBuffer[0].gcATReceData[7]= UartData;
			 			break;			 					  		
			 case WIFI_LENGTH1:	           // 9数据长度1
			    	giWIFIDATALength = UartData;
						gcWifiCommunState = WIFI_LENGTH2;
  			  	ATReceBuffer[0].gcATReceData[8]= UartData;
			 			break;
			 case WIFI_LENGTH2:			  // 10数据长度2
			    	giWIFIDATALength = (giWIFIDATALength<<8)+UartData;
    				if(giWIFIDATALength>0)   // 
      				{
      				  gcWifiCommunState = WIFI_RECEDATA;
      				} 
    				else
      				{
      				   gcWifiCommunState = WIFI_CHCK00; 
      				}
  			  	ATReceBuffer[0].gcATReceData[9]= UartData;
			 			break;
    	case WIFI_CHCK00:	  // 11校验 
    				if (ATReceBuffer[0].gcATReceCount<=(WIFIBUFLEN-10-1)) 
    					{
  			    		ATReceBuffer[0].gcATReceData[10+ATReceBuffer[0].gcATReceCount]= UartData; 
	      				gcWifiCommunState = WIFI_CHCK01;
    					}  
                        
			 			break;
        case WIFI_CHCK01:	  // 11校验 
    				if (ATReceBuffer[0].gcATReceCount<=(WIFIBUFLEN-10-1)) 
    					{
  			    		ATReceBuffer[0].gcATReceData[11+ATReceBuffer[0].gcATReceCount]= UartData; 
  			    		ATReceBuffer[0].gcATReceCount = 0;
	      				gcWifiCommunState = WIFI_WAIT_SYN_0;
	      				WifiWorkFlag.gcReceComm1OK = 1;  // 数据成功接收完毕 
    					}         						
			 			break;                
		case WIFI_RECEDATA:  // 12数据内容
    				if (ATReceBuffer[0].gcATReceCount<(WIFIBUFLEN-10-1)) 
    					{
  			    		ATReceBuffer[0].gcATReceData[10+ATReceBuffer[0].gcATReceCount]= UartData;
  			    		ATReceBuffer[0].gcATReceCount++;    						
    					}

    				if(ATReceBuffer[0].gcATReceCount == giWIFIDATALength)
    				{
    				  	gcWifiCommunState = WIFI_CHCK00;
    				}
    			 	break;
		default:
			 	gcWifiCommunState = WIFI_WAIT_SYN_0;	
		}
}
/*******************************************************************************
*                       Buzzer
********************************************************************************/
void Buzzer_Fun(void)
{
    
	if(BUZfkg==1)//按键提示音
		{       
		    if(BuzzerDly>1000000)
            {
		        PWM_Start();

            }
		    if(BuzzerDly>1005000)
		    {
                BuzzerDly=0;
		        PWM_Stop();
		        BuzzerDly=0; 
		       // BUZfkg=0;     
		    }
            BuzzerDly++;
		}

    
}




/*******************************************************************************
* Function Name: Bootloader_Calc8BitSum
********************************************************************************
*
* Summary:
*  This computes the 8 bit sum for the provided number of bytes contained in
*  FLASH (if baseAddr equals CY_FLASH_BASE) or EEPROM (if baseAddr equals
*  CY_EEPROM_BASE).
*
* Parameters:
* baseAddr:
*   CY_FLASH_BASE
*   CY_EEPROM_BASE - applicable only for PSoC 3 / PSoC 5LP devices.
*
*  start:
*     The starting address to start summing data for
*  size:
*     The number of bytes to read and compute the sum for
*
* Returns:
*   8 bit sum for the provided data
*
*******************************************************************************/
uint8 Bootloader_Calc8BitSum(uint32 baseAddr, uint32 start, uint32 size) \
                CYSMALL 
{
    uint8 CYDATA sum = 0u;
    CYASSERT(baseAddr == CY_FLASH_BASE);


    while (size > 0u)
    {
        size--;
        sum += (*((uint8  *)(baseAddr + start + size)));
    }

    return(sum);
}


/*******************************************************************************
* Function Name: Bootloader_Start
********************************************************************************
* Summary:
*  This function is called in order to execute the following algorithm:
*
*  - Identify the active bootloadable application (applicable only to
*    the Multi-application bootloader)
*
*  - Validate the bootloader application (design-time configurable, Bootloader
*    application validation option of the component customizer)
*
*  - Validate the active bootloadable application. If active bootloadable
*    application is not valid, and the other bootloadable application (inactive)
*    is valid, the last one is started.
*
*  - Run a communication subroutine (design-time configurable, Wait for command
*    option of the component customizer)
*
*  - Schedule the bootloadable and reset the device
*
* Parameters:
*  None
*
* Return:
*  This method will never return. It will either load a new application and
*  reset the device or jump directly to the existing application. The CPU is
*  halted, if validation failed when "Bootloader application validation" option
*  is enabled.
*  PSoC 3/PSoC 5: The CPU is halted if Flash initialization fails.
*
* Side Effects:
*  If Bootloader application validation option is enabled and this method
*  determines that the bootloader application itself is corrupt, this method
*  will not return, instead it will simply hang the application.
*
*******************************************************************************/
void Bootloader_Start(void) CYSMALL 
{
    cystatus validApp  = CYRET_BAD_DATA;
    if (CYRET_SUCCESS == Bootloader_ValidateBootloadable(Bootloader_MD_BTLDB_ACTIVE_0))
    {
        validApp = CYRET_SUCCESS;
    }

    /***********************************************************************
    * If the active bootloadable application is invalid or a bootloader
    * application is scheduled - do the following:
    *  - schedule the bootloader application to be run after software reset
    *  - Go to the communication subroutine. The HostLink() will wait for
    *    the commands forever.
    ***********************************************************************/
    if ((Bootloader_GET_RUN_TYPE == Bootloader_START_BTLDR) ||
        (CYRET_SUCCESS != validApp))
        {
                //BUZfkg=1;
            Bootloader_SET_RUN_TYPE(0u);

            Bootloader_HostLink();
        }
    /* Schedule bootloadable application and perform software reset */

    Bootloader_LaunchApplication();
}


/*******************************************************************************
* Function Name: Bootloader_LaunchApplication
********************************************************************************
*
* Summary:
*  Schedules bootloadable application and resets device
*
* Parameters:
*  None
*
* Returns:
*  This method will never return.
*
*******************************************************************************/
static void Bootloader_LaunchApplication(void) CYSMALL 
{
    /* Schedule Bootloadable to start after reset */
    Bootloader_SET_RUN_TYPE(Bootloader_START_APP);

    CySoftwareReset();
}


/*******************************************************************************
* Function Name: Bootloader_Exit
********************************************************************************
*
* Summary:
*  Schedules the specified application and performs software reset to launch
*  a specified application.
*
*  If the specified application is not valid, the Bootloader (the result of the
*  ValidateBootloadable() function execution returns other than CYRET_SUCCESS,
*  the bootloader application is launched.
*
* Parameters:
*  appId: application to be started:
*  Bootloader_EXIT_TO_BTLDR   - Bootloader application will be started on
*                                     software reset.
*  Bootloader_EXIT_TO_BTLDB,
*  Bootloader_EXIT_TO_BTLDB_1 - Bootloadable application # 1 will be
*                                     started on software reset.
*  Bootloader_EXIT_TO_BTLDB_2 - Bootloadable application # 2 will be
*                                     started on software reset. Available only
*                                     if Multi-Application option is enabled in
*                                     the component customizer.
* Returns:
*  This function never returns.
*
*******************************************************************************/
void Bootloader_Exit(uint8 appId) CYSMALL 
{
    if(Bootloader_EXIT_TO_BTLDR == appId)
    {
        Bootloader_SET_RUN_TYPE(0x0u);
    }
    else
    {
        if(CYRET_SUCCESS == Bootloader_ValidateBootloadable(appId))
        {
            /* Set active application in metadata */
            uint8 CYDATA idx;
            for(idx = 0u; idx < Bootloader_MAX_NUM_OF_BTLDB; idx++)
            {
                Bootloader_SetFlashByte((uint32) Bootloader_MD_BTLDB_ACTIVE_OFFSET(idx),
                                              (uint8 )(idx == appId));
            }


            Bootloader_SET_RUN_TYPE(Bootloader_SCHEDULE_BTLDB);
        }
        else
        {
            Bootloader_SET_RUN_TYPE(0u);
        }
    }

    CySoftwareReset();
}


/*******************************************************************************
* Function Name: CyBtldr_CheckLaunch
********************************************************************************
*
* Summary:
*  This routine checks if the bootloader or the bootloadable application has to
*  be run.  If the application has to be run, it will start executing.
*  If the bootloader is to be run, it will return, so the bootloader can
*  continue starting up.
*
* Parameters:
*  None
*
* Returns:
*  It will not return if it determines that the bootloadable application should
*  be run.
*
*******************************************************************************/
void CyBtldr_CheckLaunch(void) CYSMALL 
{

#if(CY_PSOC4)

    /*******************************************************************************
    * Set cyBtldrRunType to zero in case of non-software reset occurred. This means
    * that bootloader application is scheduled - that is initial clean state. The
    * value of cyBtldrRunType is valid only in case of software reset.
    *******************************************************************************/
    if (0u == (Bootloader_RES_CAUSE_REG & Bootloader_RES_CAUSE_RESET_SOFT))
    {
        cyBtldrRunType = 0u;
    }

#endif /* (CY_PSOC4) */


    if (Bootloader_GET_RUN_TYPE == Bootloader_START_APP)
    {
        Bootloader_SET_RUN_TYPE(0u);

        /*******************************************************************************
        * Indicates that we have told ourselves to jump to the application since we have
        * already told ourselves to jump, we do not do any expensive verification of the
        * application. We just check to make sure that the value at CY_APP_ADDR_ADDRESS
        * is something other than 0.
        *******************************************************************************/
        if(0u != Bootloader_GetMetadata(Bootloader_GET_BTLDB_ADDR, Bootloader_activeApp))
        {
            /* Never return from this method */
            Bootloader_LaunchBootloadable(Bootloader_GetMetadata(Bootloader_GET_BTLDB_ADDR,
                                                                             Bootloader_activeApp));
        }
    }
}


/* Moves argument appAddr (RO) into PC, moving execution to appAddr */
#if defined (__ARMCC_VERSION)

    __asm static void Bootloader_LaunchBootloadable(uint32 appAddr)
    {
        BX  R0
        ALIGN
    }

#elif defined(__GNUC__)

    __attribute__((noinline)) /* Workaround for GCC toolchain bug with inlining */
    __attribute__((naked))
    static void Bootloader_LaunchBootloadable(uint32 appAddr)
    {
        __asm volatile("    BX  R0\n");
    }

#elif defined (__ICCARM__)

    static void Bootloader_LaunchBootloadable(uint32 appAddr)
    {
        __asm volatile("    BX  R0\n");
    }

#endif  /* (__ARMCC_VERSION) */


/*******************************************************************************
* Function Name: Bootloader_ValidateBootloadable
********************************************************************************
* Summary:
*  Performs the bootloadable application validation by calculating the
*  application image checksum and comparing it with the checksum value stored
*  in the Bootloadable Application Checksum field of the metadata section.
*
*  If the Fast bootloadable application validation option is enabled in the
*  component customizer and bootloadable application successfully passes
*  validation, the Bootloadable Application Verification Status field of the
*  metadata section is updated. Refer to the Metadata Layout section for the
*  details.
*
*  If the Fast bootloadable application validation option is enabled and
*  Bootloadable Application Verification Status field of the metadata section
*  claims that bootloadable application is valid, the function returns
*  CYRET_SUCCESS without further checksum calculation.
*
* Parameters:
*  appId:
*  The number of the bootloadable application should be 0 for the normal
*  bootloader and 0 or 1 for the Multi-Application bootloader.
*
* Returns:
*  Returns CYRET_SUCCESS if the specified bootloadable application is valid.
*
*******************************************************************************/
cystatus Bootloader_ValidateBootloadable(uint8 appId) CYSMALL \

    {
        uint32 CYDATA idx;

        uint32 CYDATA end   = Bootloader_FIRST_APP_BYTE(appId) +
                                Bootloader_GetMetadata(Bootloader_GET_BTLDB_LENGTH,
                                                       appId);

        CYBIT         valid = 0u; /* Assume bad flash image */
        uint8  CYDATA calcedChecksum = 0u;
        /* Calculate checksum of bootloadable image */
        for(idx = Bootloader_FIRST_APP_BYTE(appId); idx < end; ++idx)
        {
            uint8 CYDATA curByte = Bootloader_GET_CODE_BYTE(idx);

            if((curByte != 0u) && (curByte != 0xFFu))
            {
                valid = 1u;
            }

            calcedChecksum += curByte;
        }
        calcedChecksum = ( uint8 )1u + ( uint8 )(~calcedChecksum);
        if((calcedChecksum != Bootloader_GetMetadata(Bootloader_GET_BTLDB_CHECKSUM, appId)) ||
           (0u == valid))
        {
            return(CYRET_BAD_DATA);
        }
        return(CYRET_SUCCESS);
}
CY_ISR(UART_ISR_0_FUN)
{
    uint32 resource = UART_0_GetRxInterruptSource();
     if(resource & UART_0_INTR_RX_NOT_EMPTY)
    {  
                F_uart_0_tx=0;   
	    LoadUARTData((uint8)(UART_0_UartGetByte()& 0xFF));
                F_uart_0_tx=1;   
      	UART_0_ClearRxInterruptSource(UART_0_INTR_RX_NOT_EMPTY);//清中断源 
    }
    
}

/*******************************************************************************
* Function Name: Bootloader_HostLink
********************************************************************************
*
* Summary:
*  Causes the bootloader to attempt to read data being transmitted by the
*  host application.  If data is sent from the host, this establishes the
*  communication interface to process all requests.
*
* Parameters:
*  timeOut:
*   The amount of time to listen for data before giving up. Timeout is
*   measured in 10s of ms.  Use 0 for an infinite wait.
*
* Return:
*   None
*
*******************************************************************************/
static void Bootloader_HostLink(void) 
{


    uint8     CYDATA ackCode;
    uint16   CYDATA pktChecksum;
    uint8     dataBuffer  [Bootloader_SIZEOF_COMMAND_BUFFER];
   // uint8 dataBuffer_0[300],packetBuffer[300];
    uint16 iCommand;
    uint16 row,numberRead;
    uint8     timeOut=20,iicount,itotalcount;
    uint16 tmp;
    uint32 count=0,count00;
    CYBIT F_send,readStat;  ;

    /* Initialize communications channel. */
    UART_0_Init();
    UART_0_Enable();
    UART_0_Start();
    UART_0_SetCustomInterruptHandler(UART_ISR_0_FUN);  
    UART_0_SpiUartClearRxBuffer();
    UART_0_SpiUartClearTxBuffer();
    //Open_UART_WIFI_ISR();
    /* Enable global interrupts */
    CyGlobalIntEnable;
    F_uart_0_tx=1;

    F_send=0;
    CyDelay(100);
    while(1)
    {
        Buzzer_Fun();
        Uart_0_Putchar();
        BUZfkg=1;
        /* The command may be sent along with the last block of data, to program the row. */

        if(count>0)
        {
           count--;
        }
        else
        {
            F_send=0;
        }
        if(f_delay==1)
        {
           count00++;
        }
        else
        {
            count00=0;
        }
        if(count00>50000)
        {
               Bootloader_LaunchApplication();
             if(CYRET_SUCCESS == Bootloader_ValidateBootloadable(Bootloader_activeApp))
        {

                                                                         Bootloader_SET_RUN_TYPE(Bootloader_SCHEDULE_BTLDB);
            CySoftwareReset();
        }
        }
        if((F_send==0)&&(f_ack_1==0))
        {
            F_send=1;
            dataBuffer_0[0x00] 	= 0x00u;
			dataBuffer_0[0x01] 	= 0x80u;
			SendDataToWifi(	0x00,0xCCC5,&dataBuffer_0[0],0x02);
            count=100000;
        }
        else if((WifiWorkFlag.gcReceComm1OK==1)&&(giWIFIDATALength<=(WIFIBUFLEN-10-1))) 
        {
            BUZfkg=1;
            WifiWorkFlag.gcReceComm1OK=0;
            pktChecksum = ATReceBuffer[0].gcATReceData[giWIFIDATALength+10];
            pktChecksum = (pktChecksum<<8)+ATReceBuffer[0].gcATReceData[giWIFIDATALength+11];
            tmp= crc16(&ATReceBuffer[0].gcATReceData[0], giWIFIDATALength+10);
           if(pktChecksum == tmp)
            {
                itotalcount=ATReceBuffer[0].gcATReceData[3];
                iicount=ATReceBuffer[0].gcATReceData[4];
                z_iicount=iicount; 
                z_itotalcount=itotalcount;
                iCommand=ATReceBuffer[0].gcATReceData[Bootloader_CMD_ADDR];
                iCommand=(iCommand<<8u)+ATReceBuffer[0].gcATReceData[Bootloader_CMD_ADDR+1];
                switch(iCommand)
                {
                case 0xccc5:
                {
                   //BUZfkg=1;
                    f_ack_1=0xff;
                    break;
                }
                case Bootloader_COMMAND_PROGRAM:
                {
                    (void) memcpy(&dataBuffer[0],&ATReceBuffer[0].gcATReceData[10],128);
                    if((iicount==itotalcount)&&(iicount>5))
                        {
                             /* Get FLASH/EEPROM row number inside of the array */
                            row = 255;
                            ackCode = (CYRET_SUCCESS != CySysFlashWriteRow((uint32) row, dataBuffer)) \
                            ? Bootloader_ERR_ROW : CYRET_SUCCESS;   


                            dataBuffer_0[0x00] 	= 0x00u;
                            dataBuffer_0[0x01] 	= 0x00u;
                            SendDataToWifi(	0x00,Bootloader_COMMAND_PROGRAM,&dataBuffer_0[0],0x02);

f_delay=1;
                        }
                    else
                        {
                             /* Get FLASH/EEPROM row number inside of the array */
                            row = iicount+Bootloader_DATAOFFSET;
                            ackCode = (CYRET_SUCCESS != CySysFlashWriteRow((uint32) row, dataBuffer)) \
                            ? Bootloader_ERR_ROW : CYRET_SUCCESS;   
                            dataBuffer_0[0x03] 	= ATReceBuffer[0].gcATReceData[3];
                            dataBuffer_0[0x04] 	= iicount;
                            dataBuffer_0[0x00] 	= 0x00u;
                            dataBuffer_0[0x01] 	= 0x00u;
                            SendDataToWifi(	0x00,Bootloader_COMMAND_PROGRAM,&dataBuffer_0[0],0x02);
                            
                        }    
                 }
                default:
                break;
                }

            }
		}
//        if((count00>5000)&&(f_delay==1))
//        {
//
//        }
    }
}
//static void Bootloader_HostLink(void) 
//{
//
//
//    uint8     CYDATA ackCode;
//    uint16   CYDATA pktChecksum;
//    uint8     dataBuffer  [Bootloader_SIZEOF_COMMAND_BUFFER];
//    uint16 iCommand;
//    /* Initialize communications channel. */
//    CyBtldrCommStart();
//    /* Enable global interrupts */
//    CyGlobalIntEnable;
//    while(1)
//    {
//        Buzzer_Fun();
//        Uart_0_Putchar();
//    	 if((WifiWorkFlag.gcReceComm1OK)&&(giWIFIDATALength<=(WIFIBUFLEN-10-1))) 
//    	 {
//                WifiWorkFlag.gcReceComm1OK=0;
//                pktChecksum = ATReceBuffer[0].gcATReceData[Bootloader_CHK_ADDR(giWIFIDATALength+Bootloader_DATA_ADDR)]<<8/
//                +ATReceBuffer[0].gcATReceData[Bootloader_CHK_ADDR(giWIFIDATALength+Bootloader_DATA_ADDR+1)];
//                if(pktChecksum != crc16(&ATReceBuffer[0].gcATReceData[0], giWIFIDATALength+10))
//                {
//                    ATReceBuffer[0].gcATReceData[Bootloader_DATA_ADDR] 		= 0x00u;
//                    ATReceBuffer[0].gcATReceData[Bootloader_DATA_ADDR+1] 	= 0x01u;
//                    SendDataToWifi(	0x80,
//                    								Bootloader_COMMAND_PROGRAM,
//                    									&ATReceBuffer[0].gcATReceData[0],
//                    													0x02);
//                }
//                else
//                {
//                    BUZfkg=1;
//                    iCommand=ATReceBuffer[0].gcATReceData[Bootloader_CMD_ADDR+1]<<8u;
//                    iCommand=ATReceBuffer[0].gcATReceData[Bootloader_CMD_ADDR];
//                    switch(iCommand)
//                    {
//                    /***************************************************************************
//                    *   Program / Erase row
//                    ***************************************************************************/
//                    case Bootloader_COMMAND_PROGRAM:
//
//
//                            /* The command may be sent along with the last block of data, to program the row. */
//                        (void) memcpy(&dataBuffer[0],
//                                      &ATReceBuffer[0].gcATReceData[Bootloader_DATA_ADDR],
//                                      (uint16) giWIFIDATALength);
//            	        uint16 row;
//
//                        /* Get FLASH/EEPROM row number inside of the array */
//                        row = ATReceBuffer[0].gcATReceData[4]+Bootloader_DATAOFFSET;
//                        ackCode = (CYRET_SUCCESS != CySysFlashWriteRow((uint32) row, dataBuffer)) \
//                            ? Bootloader_ERR_ROW : CYRET_SUCCESS;
//                        ATReceBuffer[0].gcATReceData[Bootloader_DATA_ADDR] 		= 0x00u;
//                    		ATReceBuffer[0].gcATReceData[Bootloader_DATA_ADDR+1] 	= 0x00u;
//                        SendDataToWifi(	0x80,
//                  						Bootloader_COMMAND_PROGRAM,
//                 						&ATReceBuffer[0].gcATReceData[0],
//	     								0x02);
//                        if((ATReceBuffer[0].gcATReceData[3]==ATReceBuffer[0].gcATReceData[4])&&(ATReceBuffer[0].gcATReceData[3]>10))
//                    	{
//                    		 if(CYRET_SUCCESS == Bootloader_ValidateBootloadable(Bootloader_activeApp))
//                            {
//                                Bootloader_SET_RUN_TYPE(Bootloader_SCHEDULE_BTLDB);
//                                CySoftwareReset();
//                            }
//                    	}
//            	                    
//
//                        
//
//                        break;
//                    /***************************************************************************
//                    *   Unsupported command
//                    ***************************************************************************/
//                    default:
//                        break;
//                    }
//                } 
//          }  
//       
//
//
//    }
//}





/*******************************************************************************
* Function Name: Bootloader_SetFlashByte
********************************************************************************
*
* Summary:
*  Writes a byte to the specified Flash memory location.
*
* Parameters:
*  address:
*      The address in Flash memory where data will be written
*
*  runType:
*      Byte to be written
*
* Return:
*  None
*
*******************************************************************************/
void Bootloader_SetFlashByte(uint32 address, uint8 runType) 
{
    uint32 flsAddr = address - CYDEV_FLASH_BASE;
    uint8  rowData[CYDEV_FLS_ROW_SIZE];
    uint16 rowNum = ( uint16 )(flsAddr / CYDEV_FLS_ROW_SIZE);
    uint32 baseAddr = address - (address % CYDEV_FLS_ROW_SIZE);
    uint16 idx;

    for(idx = 0u; idx < CYDEV_FLS_ROW_SIZE; idx++)
    {
        rowData[idx] = Bootloader_GET_CODE_BYTE(baseAddr + idx);
    }

    rowData[address % CYDEV_FLS_ROW_SIZE] = runType;
    (void) CySysFlashWriteRow((uint32) rowNum, rowData);



}


/*******************************************************************************
* Function Name: Bootloader_GetMetadata
********************************************************************************
*
* Summary:
*  Returns the value of the specified field of the metadata section.
*
* Parameters:
*  field:
*   The field to get data from:
*   Bootloader_GET_BTLDB_CHECKSUM    - Bootloadable Application Checksum
*   Bootloader_GET_BTLDB_ADDR        - Bootloadable Application Start
*                                            Routine Address
*   Bootloader_GET_BTLDR_LAST_ROW    - Bootloader Last Flash Row
*   Bootloader_GET_BTLDB_LENGTH      - Bootloadable Application Length
*   Bootloader_GET_BTLDB_ACTIVE      - Active Bootloadable Application
*   Bootloader_GET_BTLDB_STATUS      - Bootloadable Application
*                                            Verification Status
*   Bootloader_GET_BTLDR_APP_VERSION - Bootloader Application Version
*   Bootloader_GET_BTLDB_APP_VERSION - Bootloadable Application Version
*   Bootloader_GET_BTLDB_APP_ID      - Bootloadable Application ID
*   Bootloader_GET_BTLDB_APP_CUST_ID - Bootloadable Application Custom ID
*
*  appId:
*   Number of the bootlodable application. Should be 0 for the normal
*   bootloader and 0 or 1 for the Multi-Application bootloader.
*
* Return:
*  The value of the specified field of the specified application.
*
*******************************************************************************/
uint32 Bootloader_GetMetadata(uint8 field, uint8 appId)
{
    uint32 fieldPtr;
    uint8  fieldSize = 2u;
    uint32 result = 0u;

    switch (field)
    {
    case Bootloader_GET_BTLDB_CHECKSUM:
        fieldPtr  = Bootloader_MD_BTLDB_CHECKSUM_OFFSET(appId);
        fieldSize = 1u;
        break;

    case Bootloader_GET_BTLDB_ADDR:
        fieldPtr  = Bootloader_MD_BTLDB_ADDR_OFFSET(appId);
    #if(!CY_PSOC3)
        fieldSize = 4u;
    #endif  /* (!CY_PSOC3) */
        break;

    case Bootloader_GET_BTLDR_LAST_ROW:
        fieldPtr  = Bootloader_MD_BTLDR_LAST_ROW_OFFSET(appId);
        break;

    case Bootloader_GET_BTLDB_LENGTH:
        fieldPtr  = Bootloader_MD_BTLDB_LENGTH_OFFSET(appId);
    #if(!CY_PSOC3)
        fieldSize = 4u;
    #endif  /* (!CY_PSOC3) */
        break;

    case Bootloader_GET_BTLDB_ACTIVE:
        fieldPtr  = Bootloader_MD_BTLDB_ACTIVE_OFFSET(appId);
        fieldSize = 1u;
        break;

    case Bootloader_GET_BTLDB_STATUS:
        fieldPtr  = Bootloader_MD_BTLDB_VERIFIED_OFFSET(appId);
        fieldSize = 1u;
        break;

    case Bootloader_GET_BTLDB_APP_VERSION:
        fieldPtr  = Bootloader_MD_BTLDB_APP_VERSION_OFFSET(appId);
        break;

    case Bootloader_GET_BTLDR_APP_VERSION:
        fieldPtr  = Bootloader_MD_BTLDR_APP_VERSION_OFFSET(appId);
        break;

    case Bootloader_GET_BTLDB_APP_ID:
        fieldPtr  = Bootloader_MD_BTLDB_APP_ID_OFFSET(appId);
        break;

    case Bootloader_GET_BTLDB_APP_CUST_ID:
        fieldPtr  = Bootloader_MD_BTLDB_APP_CUST_ID_OFFSET(appId);
        fieldSize = 4u;
        break;

    default:
        /* Should never be here */
        CYASSERT(0u != 0u);
        fieldPtr  = 0u;
        break;
    }


    if (1u == fieldSize)
    {
        result =  (uint32) CY_GET_XTND_REG8((volatile uint8 *)fieldPtr);
    }

    /* PSoC 4 and PSoC 5: Little-endian */

        if (2u == fieldSize)
        {
            result =  (uint32) CY_GET_XTND_REG8((volatile uint8 *) (fieldPtr     ));
            result |= (uint32) CY_GET_XTND_REG8((volatile uint8 *) (fieldPtr + 1u)) <<  8u;
        }

        if (4u == fieldSize)
        {
            result =  (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr     ));
            result |= (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr + 1u)) <<  8u;
            result |= (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr + 2u)) << 16u;
            result |= (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr + 3u)) << 24u;
        }

    

    return (result);
}


/* [] END OF FILE */
