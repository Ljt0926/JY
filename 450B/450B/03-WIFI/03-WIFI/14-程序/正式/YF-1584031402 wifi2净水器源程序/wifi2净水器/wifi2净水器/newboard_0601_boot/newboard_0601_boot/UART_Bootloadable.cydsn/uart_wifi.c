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
#define _UART_WIFI_
#include "config.h"

const uint8 Tab_tds_in_01[]={									//tds值补偿表
                            0,0,0,0,0,0,0,0,0,0,            						//00-09
                            0,0,0,0,0,0,0,0,0,0,            						//10-19
                            1,1,1,1,1,1,1,1,1,1,            						//20-29
                            2,2,2,2,2,3,3,3,3,3,            						//30-39
                            4,4,4,4,4,4,4,4,4,4,            						//40-49
                            5,5,6,6,6,7,7,8,8,8,            						//50-59
                            9,9,9,9,9,10,10,10,11,12,       						//60-69
                            13,13,13,14,14,14,15,15,16,16,  						//70-79
                            17,18,18,18,19,19,20,20,21,21,              //80-89
                            22,23,24,25,26,27,28,29,30,31,              //90-99
                            31,32,32,35,35,36,36,37,38,39,              //100-109
                            39,40,40,41,41,42,42,43,43,44,              //110-119
                            44,45,45,46,46,47,48,49,50,51,              //120-129
                            52,53,54,55,56,57,58,59,60,61,              //130-139
                            62,63,64,65,66,67,68,68,69,70,              //140-149
                            71,72,73,74,75,76,77,78,79,80,              //150-159
                            80,81,82,83,84,85,86,87,88,89,              //160-169
                            90,91,92,93,94,95,96,97,98,99,              //170-179
                            100,101,102,103,104,105,106,107,108,109,    //180-189
                            110,111,112,113,114,115,116,117,118,120,    //190-199
                            122,124,126,128,130,132,134,136,138,140,    //200-209
                            142,144,146,148,150,152,154,156,158,160,    //210-219
                            162,164,166,168,170,172,174,176,178,180,    //220-229
                            183,186,189,192,195,198,200,203,206,208,    //230-239   
                            210,213,216,219,222,225,228,231,234,237,    //240-249  
                            240,243,246,249,252,255                     //250-255
};//
//--------------------------------------------------------
const uint16 Tab_tds_in_02[]={               //tds值补偿表
                            260,264,268,272,                            //256-259
                            276,280,284,288,292,296,300,304,308,312,    //260-269
                            316,320,324,328,332,336,340,345,350,355,    //270-279
                            360,365,370,375,380,385,390,395,400,405,    //280-289   
                            410,415,420,425,430,435,440,445,450,455,    //290-299   
                            460,465,470,475,480,485,490,495,500,505,    //300-309   
                            510,515,520,525,530,535,540,545,550,555,    //310-319   
                            560,566,572,578,584,590,596,602,608,614,    //320-329
                            620,626,632,638,644,650,656,662,668,672     //330-339
};
//--------------------------------------------------------
const uint8 Tab_tds_out[]={                  //tds值补偿表
                            0,1,1,1,1,1,1,1,1,1,                        //00-09
                            1,1,1,1,1,1,1,1,1,1,                        //10-19
                            0,0,0,0,0,0,0,0,0,0,                        //20-29 
                            1,1,1,1,1,2,2,2,2,2,                        //30-39 
                            3,3,3,3,3,4,4,4,4,4,                        //40-49 
                            5,5,6,6,7,7,8,8,9,9,                         //50-59
                            10,10,11,11,12,12,13,13,14,14,              //60-69
                            15,15,16,16,17,18,19,20,21                  //70-79
};
//--------------------------------------------------------
uint16 Tds_Scan_In(uint16 ram_tds_in)
{ 
	uint16 ram_tds_in_remainder,ram_tds_in_disp;
	ram_tds_in_remainder=ram_tds_in%10;//进水
	ram_tds_in_disp=ram_tds_in/10;
	if(ram_tds_in_disp>=339)
	    ram_tds_in_disp=339;
	if(ram_tds_in_disp<20)
	    ram_tds_in_disp+=0; 
	else if((ram_tds_in_disp>=20)&&(ram_tds_in_disp<256))
	    ram_tds_in_disp=ram_tds_in_disp+Tab_tds_in_01[ram_tds_in_disp];     
	else if(ram_tds_in_disp>=256)
	    ram_tds_in_disp=ram_tds_in_disp+Tab_tds_in_02[ram_tds_in_disp-256]+ram_tds_in_remainder/3;//ram_tds_in_remainder/3为随机尾数
	if(ram_tds_in_disp>=995)
	    ram_tds_in_disp=999;
	return ram_tds_in_disp;
}
uint8 Tds_Scan_Out(uint16 ram_tds_out)
{
	uint16 ram_tds_out_disp;
	ram_tds_out_disp=ram_tds_out/10;//出水
	if(ram_tds_out_disp>=79)//
		ram_tds_out_disp=79;
	if(ram_tds_out_disp<20)
	  ram_tds_out_disp=ram_tds_out_disp-Tab_tds_out[ram_tds_out_disp];
	else if((ram_tds_out_disp>=20)&&(ram_tds_out_disp<30))
	  ram_tds_out_disp+=0;
	else if(ram_tds_out_disp>=30)
	  ram_tds_out_disp=ram_tds_out_disp+Tab_tds_out[ram_tds_out_disp];
	if(ram_tds_out_disp>=98)
		ram_tds_out_disp=99;
	return ram_tds_out_disp;
}
typedef struct Buffer0
{
	uint8  	gcATReceData[WIFIBUFLEN];  // wifi 模块一次传输1440字节，这里有51芯片只有1280个xdata
	uint16 	gcATReceCount;
} Buffer2;
struct Buffer0    ATReceBuffer[1];
typedef struct Buffer1
{
	uint8  	gcATReceTdsboardData[TDSBUFLEN];  // wifi 模块一次传输1440字节，这里有51芯片只有1280个xdata
  uint16  gcATReceTdsboardCount;
} Buffer1;
struct Buffer1    ATTdsReceBuffer[1];

struct{
    unsigned send_data_load:1;            //启动发送标志
    unsigned flag_rev_end:1;              //接收完毕标志
    unsigned uart_ack:1;              //应答标志位
    unsigned flag_Uart_Work:1;         //Uart_Work标志位
}WifidatagramWorkFlag;
uint8	Work_State_Num_H,Work_State_Num_L;
uint8	Cmd_Function_Num;
uint16 Cmd_Function,Cmd_Function_Buf[8];     //设置8组缓冲区

uint16 Error_Data_Buf[9];
uint8	gcWifiCommunState;   	// 通讯接收状态
uint8	gctdsboardCommunState;   	// 通讯接收状态
uint8 Frame_Num;//总帧数量
uint16 giWIFICommand;//wifi控制命令
uint16 giWIFIDATALength;//wifi数据长度
uint8 gcWIFICTL;//wifi控制字
uint16 giTDSBOARDCommand;//wifi控制命令
uint16 giTDSBOARDDATALength;//wifi数据长度
uint8 gcTDSBOARDCTL;//wifi控制字
uint16		iUartSendLen;
uint16		iSendCounter;
uint16 iSendCounter,iUartSendLen;
uint8 *cpSendBufPtr;
uint8	Send_Interval_Counter;//发送时间间隔20ms 
/******************************************************************************
* 函 数 名: uint8 Sum_Verify (uint8 *PBuf, uint16 Len)
* 函数功能: 串口接收程序
* 入口参数: 无
* 返    回: 
*******************************************************************************/
CYBIT Sum_Verify (uint8 *PBuf, uint16 Len)
{
    uint8 Verify = 0;
    while (Len--)
    {
        Verify = Verify + (*PBuf);
        PBuf ++;
    }
    return (Verify == 0);                                //如果verify为0 返回1 否则返回0
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
			 			if(UartData==WIFI_PROTOCOL_VERSION)
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
      				   gcWifiCommunState = WIFI_CHCK; 
      				}
  			  	ATReceBuffer[0].gcATReceData[9]= UartData;
			 			break;
    	case WIFI_CHCK:	  // 11校验 
    				if (ATReceBuffer[0].gcATReceCount<=(WIFIBUFLEN-10-1)) 
    					{
  			    		ATReceBuffer[0].gcATReceData[10+ATReceBuffer[0].gcATReceCount]= UartData; 
  			    		ATReceBuffer[0].gcATReceCount = 0;
	      				gcWifiCommunState = WIFI_WAIT_SYN_0;
	      				WifiWorkFlag.gcReceComm1OK = 1;  // 数据成功接收完毕 
                        TestPort_Write(1); 
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
    				  	gcWifiCommunState = WIFI_CHCK;
    				}
    			 	break;
		default:
			 	gcWifiCommunState = WIFI_WAIT_SYN_0;	
		}
}
/*
	========================================================================
* 函 数 名: LodaUARTData(   IN unsigned char  UartData)
* 函数功能: 串口发送程序
* 入口参数: UartData
* 返    回: 
	========================================================================
*/
void LoadTDSBoardData(uint8  UartData)
{
	switch (gctdsboardCommunState)
		{
			 case TDSBOARD_WAIT_SYN_0:		                 // 1数据包头FA
			   		if(UartData==TDSBOARD_SYN_0)
                    {
  			   		    gctdsboardCommunState = TDSBOARD_WAIT_SYN_1;
                        ATTdsReceBuffer[0].gcATReceTdsboardData[0]= UartData;
                    }
                    else
                        gctdsboardCommunState = TDSBOARD_WAIT_SYN_0;
			  		break;
			 case TDSBOARD_WAIT_SYN_1:		                // 2数据包头FB
			   		if(UartData==TDSBOARD_SYN_1)
                    {
  			   		gctdsboardCommunState = TDSBOARD_PROTOCOL_JUDGE;
  			  	    ATTdsReceBuffer[0].gcATReceTdsboardData[1]= UartData;
                    }
                    else
                        gctdsboardCommunState = TDSBOARD_WAIT_SYN_0;
			  		break;
			 case TDSBOARD_PROTOCOL_JUDGE:                //3协议版本
			 			if(UartData==TDSBOARD_PROTOCOL_VERSION)
  			   		gctdsboardCommunState = TDSBOARD_TOTAL_FRAME_NUM;
  			  	ATTdsReceBuffer[0].gcATReceTdsboardData[2]= UartData;
			  		break;
			 case TDSBOARD_TOTAL_FRAME_NUM:               //4总帧数量
			 			gctdsboardCommunState = TDSBOARD_FRAME_NUM;
  			  	ATTdsReceBuffer[0].gcATReceTdsboardData[3]= UartData;
			  		break;		
			 case TDSBOARD_FRAME_NUM:                    //5帧序号
			 			gctdsboardCommunState = TDSBOARD_WAIT_CTL;
  			  	ATTdsReceBuffer[0].gcATReceTdsboardData[4]= UartData;
			  		break;		
			 case TDSBOARD_WAIT_CTL:	               // 6控制字
			    	gcTDSBOARDCTL = UartData;
						gctdsboardCommunState = TDSBOARD_COMMAND_1;
  			  	ATTdsReceBuffer[0].gcATReceTdsboardData[5]= UartData;
			 			break;		 
			 case TDSBOARD_COMMAND_1:	           // 7指令1
			    	giTDSBOARDCommand = UartData;
						gctdsboardCommunState = TDSBOARD_COMMAND_2;
  			  	ATTdsReceBuffer[0].gcATReceTdsboardData[6]= UartData;
			 			break;
			 case TDSBOARD_COMMAND_2:			  // 8指令2
			    	giTDSBOARDCommand = (giTDSBOARDCommand<<8)+UartData;
      				  gctdsboardCommunState = TDSBOARD_LENGTH1;     
  			  	ATTdsReceBuffer[0].gcATReceTdsboardData[7]= UartData;
			 			break;			 					  		
			 case TDSBOARD_LENGTH1:	           // 9数据长度1
			    	giTDSBOARDDATALength = UartData;
						gctdsboardCommunState = TDSBOARD_LENGTH2;
  			  	ATTdsReceBuffer[0].gcATReceTdsboardData[8]= UartData;
			 			break;
			 case TDSBOARD_LENGTH2:			  // 10数据长度2
			    	giTDSBOARDDATALength = (giTDSBOARDDATALength<<8)+UartData;
    				if(giTDSBOARDDATALength>0)   // 
      				{
      				  gctdsboardCommunState = TDSBOARD_RECEDATA;
      				} 
    				else
      				{
      				   gctdsboardCommunState = TDSBOARD_CHCK; 
      				}
  			  	ATTdsReceBuffer[0].gcATReceTdsboardData[9]= UartData;
			 			break;
    	case TDSBOARD_CHCK:	  // 11校验 
		    		if (ATTdsReceBuffer[0].gcATReceTdsboardCount<=TDSBUFLEN-10-1) 
		    			{
		   			    ATTdsReceBuffer[0].gcATReceTdsboardData[10+ATTdsReceBuffer[0].gcATReceTdsboardCount]= UartData;
		      			ATTdsReceBuffer[0].gcATReceTdsboardCount = 0;
		      			gctdsboardCommunState = TDSBOARD_WAIT_SYN_0;
		      			WifiWorkFlag.gcReceComm2OK = 1;  // 数据成功接收完毕   				
		    			} 
                     else
                        {
                           gctdsboardCommunState = TDSBOARD_WAIT_SYN_0; 
                        }
			 			break;
		case TDSBOARD_RECEDATA:  // 12数据内容
					  if (ATTdsReceBuffer[0].gcATReceTdsboardCount<TDSBUFLEN-10-1) 
		    			{
    			 			ATTdsReceBuffer[0].gcATReceTdsboardData[10+ATTdsReceBuffer[0].gcATReceTdsboardCount]= UartData;
    			    	ATTdsReceBuffer[0].gcATReceTdsboardCount++;
                         if(ATTdsReceBuffer[0].gcATReceTdsboardCount == giTDSBOARDDATALength)
    				        {
    				  	        gctdsboardCommunState = TDSBOARD_CHCK;
    				        }
    			  	    }
                        else
                        {
                           gctdsboardCommunState = TDSBOARD_WAIT_SYN_0; 
                        }
    			 	break;
		default:
			 	gctdsboardCommunState = TDSBOARD_WAIT_SYN_0;	
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
	WifidatagramWorkFlag.flag_Uart_Work = 1;                 //置正在通信标志

	iUartSendLen = iCount-1;
	iSendCounter = 0;
//  UART_UartPutChar(data_buf[0]);
	cpSendBufPtr = &data_buf[0];
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
** 函数名称: void Comm_Uart_1_PrintHex8(uint8 value)
** 功能描述: 从串口发送数据
** 入口参数:	无
** 出口参数:	无
********************************************************************************************************/
void Comm_Uart_1_PrintHex8(uint8 value)
{
    while(UART_1_FIFO_SIZE == UART_1_GET_TX_FIFO_ENTRIES);
    UART_1_TX_FIFO_WR_REG = (uint8)(value);
}
/*********************************************************************************************************
** 函数名称: void UART_putchar(void)
** 功能描述: 从串口发送数据
** 入口参数:	无
** 出口参数:	无
********************************************************************************************************/
void Uart_0_Putchar(void)
{
	if(WorkFlag.uart_0_tx!=0)
		{
			if(iSendCounter!=(iUartSendLen+1))
			{
          Comm_Uart_0_PrintHex8(cpSendBufPtr[iSendCounter++]);
	    }

	    WifidatagramWorkFlag.flag_Uart_Work = 0;                 //置正在通信标志
	  }
 
}
/*********************************************************************************************************
** 函数名称: void UART_putchar(void)
** 功能描述: 从串口发送数据
** 入口参数:	无
** 出口参数:	无
********************************************************************************************************/
void Uart_1_Putchar(void)
{
    if(WorkFlag.uart_1_tx!=0)  //接收非空
        {
//        	while(iSendCounter!=(iUartSendLen+1))
//						{
// 							Comm_Uart_1_PrintHex8(cpSendBufPtr[iSendCounter++]);
//        		}
        }
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
 
    //uint32 xxxxx;
    static uint8 cBuf[WIFIBUFLEN]; ////51 has only 256 data in soc


    memset(cBuf,0x00,WIFIBUFLEN);
    cBuf[0] = WIFI_SYN_0;        	     // SYNC0
    cBuf[1] = WIFI_SYN_1;        	     // SYNC1
    cBuf[2] = WIFI_PROTOCOL_VERSION;   //MCU_PROTOCOL_VERSION       
    cBuf[3] = DATA_FRAME_EQUE_0;   //FRAME_EQUE_0       
    cBuf[4]= DATA_FRAME_NUM_EQUE_0;//帧需要
    cBuf[5] = cCtl;   	 // Wctrl
    cBuf[6]=(cCommand)>>8;//长度0
    cBuf[7]=(cCommand)&0x00ff;//长度1	  cBuf[8]=(iLength)>>8;//长度0
    cBuf[8]=(iLength)>>8;//长度0
    cBuf[9]=(iLength)&0x00ff;//长度1
    //cBuf[iLength+10]=0x44;
    if(cCtl==0x00)
    {
    	WifidatagramWorkFlag.uart_ack=1;
    	Ack_Timer = 70; 
    	Send_Interval_Counter=10;  
    }
    if(cCtl==0x80)
    {
    	Cmd_Function_Num=0;	
    	WifidatagramWorkFlag.uart_ack=0;

    }
    if(iLength!=0)
    {
        memcpy(&cBuf[10],DataBuf,iLength);
        cBuf[iLength+10] = Sum_Make_Verify(&cBuf[0],10+iLength);
        //cBuf[iLength+10]=0x88;
    }
    else
    {
        cBuf[iLength+10] = Sum_Make_Verify(&cBuf[0],10);	
        
    }
		WifidatagramWorkFlag.flag_Uart_Work=1; 
    CyGlobalIntDisable;                  //应答时间设置
    UART_SendData(cBuf,iLength+11);   ///The Last six 0x00 is PADDING
    CyGlobalIntEnable;
    TestPort_Write(0); 
}


/*
	========================================================================
** 函数名称 ：JoinWIFI()
** 函数功能 ：连接WIFI模块                          
** 入口参数 ：
		    cIdx: The group Number
		    AckFlag:  1 Need wifi model send ack, 0 is not         
** 出口参数 ：无
	========================================================================
*/
void Mcu_Handshake_Data(void)
{
   uint8 cBuf[6];
   cBuf[0]=0x20;  ////13t450b
   cBuf[1]=0x01;
   cBuf[2]=0x00;  ////Command
   cBuf[3]=PRODUCT_FIRMWARE;
   cBuf[4]=0x00;  ////Command
   cBuf[5]=0x80;   
   SendDataToWifi(CTL_ACK_DATA,MCU_HANDSHAKE_DATA,cBuf,6);
}
/*
	========================================================================
** 函数名称 APP_HOST_STATE()
** 函数功能 ：连接WIFI模块                          
** 入口参数 ：         
** 出口参数 ：无
	========================================================================
*/
void App_Host_State(void)
{
    uint8 cBuf[16];
    cBuf[0]=0x00;  
    cBuf[1]=0x00;//ok
    cBuf[2]=Work_State.all; //01待机 02制水中 03制水完成 04 冲洗
    cBuf[3]=0x06; 	//滤芯级数	1	U8 (总级数)
    cBuf[4]=Error_Counter;   
    cBuf[5]=LianXuJiShi/600;  //工作状态	1	U8 见注2
    cBuf[6]=jingshuiliang>>8; //总净水量	2	U16(现在总净水量)
    cBuf[7]=jingshuiliang; 
    cBuf[8]=(Value_Tds0>>8); //TDS(原水)	2	U16(实际TDS值)
    cBuf[9]=Value_Tds0;
    cBuf[10]=(Value_Tds1_bak>>8); //TDS(净水)	2	U16(实际TDS值)
    cBuf[11]=Value_Tds1_bak; 
    cBuf[12]=Value_T; //温度	1	U8(实际温度值 
    cBuf[13]=(Value_Loushui_Ad>>8); //漏水	2	U16(实际AD值)
    cBuf[14]=Value_Loushui_Ad; 
    cBuf[15]=Switch_Data.all; //高、低压开关状态	1	U8 见注    
    SendDataToWifi(ACK_DATA,APP_HOST_STATE,cBuf,16);
}
void App_Filter_Changed_Data(void)
{
	uint8 cBuf[9];
	cBuf[0]=0x00;  
	cBuf[1]=0x00;//ok
	cBuf[2]=Change_Filter.all;
	cBuf[3]=Filter_Changed_Num[0]; 
	cBuf[4]=Filter_Changed_Num[1]; 	
	cBuf[5]=Filter_Changed_Num[2];   
	cBuf[6]=Filter_Changed_Num[3];  
	cBuf[7]=Filter_Changed_Num[4]; 
	cBuf[8]=Filter_Changed_Num[5]; 
	SendDataToWifi(ACK_DATA,APP_FILTER_CHANGED_DATA,cBuf,9);
}

void App_Error_Data(void)
{
	uint8 cBuf[21];
	cBuf[0]=0x00;  
	cBuf[1]=0x00;//ok
	cBuf[2]=Error_Counter;
	memcpy(&cBuf[3],Error_Data_Buf,Error_Counter*2);	
	SendDataToWifi(ACK_DATA,APP_ERROR_DATA,cBuf,Error_Counter*2+3);
}
//void App_Error_Data(void)
//{
//	uint8 cBuf[21];
//	cBuf[0]=0x00;  
//	cBuf[1]=0x00;//ok
//	cBuf[2]=0x00;;
//	SendDataToWifi(ACK_DATA,APP_ERROR_DATA,cBuf,3);
//}
void App_Filter_Used_Time_Data(void)
{
	uint8 cBuf[15];
	cBuf[0]=0x00;  
	cBuf[1]=0x00;//ok
	cBuf[2]=0x06;  	//滤芯级数
	cBuf[3]=(LvxinJishi[0]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[4]=LvxinJishi[0];
	cBuf[5]=(LvxinJishi[1]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[6]=LvxinJishi[1];
	cBuf[7]=(LvxinJishi[2]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[8]=LvxinJishi[2];
	cBuf[9]=(LvxinJishi[3]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[10]=LvxinJishi[3]; 
	cBuf[11]=(LvxinJishi[4]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[12]=LvxinJishi[4]; 
	cBuf[13]=(LvxinJishi[5]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[14]=LvxinJishi[5]; 
	SendDataToWifi(ACK_DATA,APP_FILTER_CHANGED_DATA,cBuf,15);
}
void App_Download_Nb_Sta(void)
{
	uint8 cBuf[2];
	cBuf[0]=0x00;  
	cBuf[1]=0x00;//ok
	SendDataToWifi(ACK_DATA,APP_DOWNLOAD_NB_STA,cBuf,2);
}
void Wifi_Senddingstate_Data(void)
{
	uint8 cBuf[2];
	cBuf[0]=0x00;
	cBuf[1]=0x00;
	SendDataToWifi(ACK_DATA,WIFI_SENDDINGSTATE_DATA,cBuf,2);
}
void Wifi_Firmware_Handshake_Data(void)
{
	uint8 cBuf[4];
	cBuf[0]=0x00;
	if(Firmware_Update==0xfe)
		cBuf[1]=0x00;
	else
		cBuf[1]=0x05;		
	cBuf[2]=0x00;
	cBuf[3]=FIRMWARE_DATALEN;
	SendDataToWifi(ACK_DATA,WIFI_FIRMWARE_HANDSHAKE_DATA,cBuf,4);
}
void Wifi_Dect_Data(void)
{
	uint8 cBuf[2];
	cBuf[0]=0x00;
	cBuf[1]=0x00;
	SendDataToWifi(ACK_DATA,WIFI_DECT_DATA,cBuf,2);
}
void Wifi_Firmware_Update_Data(void)
{	
	uint8 cBuf[2];
	cBuf[0]=0x00;
	cBuf[1]=0x00;
	SendDataToWifi(ACK_DATA,WIFI_FIRMWARE_UPDATE_DATA,cBuf,2);
}
/*
	========================================================================
** 函数名称 APP_HOST_STATE()
** 函数功能 ：连接WIFI模块                          
** 入口参数 ：         
** 出口参数 ：无
	========================================================================
*/
void App_Search_Filter_Manage_Num(void)
{
	uint8 cBuf[3];
	cBuf[0]=0x00;  
	cBuf[1]=0x00;//ok
	cBuf[2]=NBfig;
	SendDataToWifi(ACK_DATA,APP_SEARCH_FILTER_MANAGE_NUM,cBuf,3);
}

/*
	========================================================================
** 函数名称 App_Download_Filter_Manage_Num()
** 函数功能 ：连接WIFI模块                          
** 入口参数 ：         
** 出口参数 ：无
	========================================================================
*/
void App_Download_Filter_Manage_Num(void)
{
	uint8 cBuf[2];
	cBuf[0]=0x00;
	cBuf[1]=0x00;
	SendDataToWifi(ACK_DATA,APP_DOWNLOAD_FILTER_MANAGE_NUM,cBuf,2);
}
/*
	========================================================================
** 函数名称 App_Download_Filter_Manage_Num()
** 函数功能 ：连接WIFI模块                          
** 入口参数 ：         
** 出口参数 ：无
	========================================================================
*/
void App_Download_Filter_Reset_Data(void)
{
	uint8 cBuf[2];
	cBuf[0]=0x00;
	cBuf[1]=0x00;
	SendDataToWifi(ACK_DATA,APP_DOWNLOAD_FILTER_RESET_DATA,cBuf,2);
}
/*
	========================================================================
** 函数名称 App_Poweron()
** 函数功能 ：连接WIFI模块                          
** 入口参数 ：         
** 出口参数 ：无
	========================================================================
*/
void App_Poweron(void)
{
		uint8 cBuf[2];
		cBuf[0]=0x00;
		cBuf[1]=0x00;
		SendDataToWifi(ACK_DATA,APP_POWERON,cBuf,2);
}
/*
	========================================================================
** 函数名称 App_Poweroff()
** 函数功能 ：连接WIFI模块                          
** 入口参数 ：         
** 出口参数 ：无
	========================================================================
*/
void App_Poweroff(void)
{
		uint8 cBuf[2];
		cBuf[0]=0x00;
		cBuf[1]=0x00;
		SendDataToWifi(ACK_DATA,APP_POWEROFF,cBuf,2);
}
/*
	========================================================================
** 函数名称 ：Mcu_Poweronsmartlink_Data()
** 函数功能 ：Mcu_Poweronsmartlink_Data                          
** 入口参数 ：
        
** 出口参数 ：无
	========================================================================
*/
void Mcu_Poweronsmartlink_Data(void)
{
   SendDataToWifi(CTL_ACK_DATA,MCU_POWERONSMARTLINK_DATA,0,0);
}
/*
	========================================================================
** 函数名称 Clean_All_User_Bound()
** 函数功能 ：连接WIFI模块                          
** 入口参数 ：        
** 出口参数 ：无
	========================================================================
*/
void Clean_All_User_Bound(void)
{
   SendDataToWifi(CTL_ACK_DATA,MCU_CLEARALLUSERBOUND_DATA,0,0);
}
void Mcu_Firmware_Update(void)
{
	  uint8 cBuf[2];
  	cBuf[0] = 0x00;				 //
  	cBuf[1] = FIRMWARE_DATALEN;				 //固件数据长度
  	SendDataToWifi(CTL_ACK_DATA,MCU_FIRMWARE_UPDATE,cBuf,2);	
}

void Host_State_Data(void)
{
		uint8 cBuf[14];
		cBuf[0]=Error_Counter;
		cBuf[1]=Work_State.all; //01待机 02制水中 03制水完成 04 冲洗
		cBuf[2]=LianXuJiShi/600;  //工作状态	1	U8 见注2  
		cBuf[3]=0x06; 	//滤芯级数	1	U8 (总级数)
		cBuf[4]=(jingshuiliang>>8); //总净水量	2	U16(现在总净水量)
		cBuf[5]=jingshuiliang; 
		cBuf[6]=(Value_Tds0>>8); //TDS(原水)	2	U16(实际TDS值)
		cBuf[7]=Value_Tds0;
		cBuf[8]=(Value_Tds1_bak>>8); //TDS(净水)	2	U16(实际TDS值)
		cBuf[9]=Value_Tds1_bak; 
		cBuf[10]=Value_T; //温度	1	U8(实际温度值 
		cBuf[11]=(Value_Loushui_Ad>>8); //漏水	2	U16(实际AD值)
		cBuf[12]=Value_Loushui_Ad; 
		cBuf[13]=Switch_Data.all; //高、低压开关状态	1	U8 见注    
		SendDataToWifi(CTL_ACK_DATA,HOST_STATE_DATA,cBuf,14);
}

void Host_Filter_Changed_Data(void)
{
	uint8 cBuf[8];
	cBuf[0]=0x06;  	//滤芯级数
	cBuf[1]=Change_Filter.all;  	
	cBuf[2]=Filter_Changed_Num[0]; 
	cBuf[3]=Filter_Changed_Num[1]; 	
	cBuf[4]=Filter_Changed_Num[2];   
	cBuf[5]=Filter_Changed_Num[3];  
	cBuf[6]=Filter_Changed_Num[4]; 
	cBuf[7]=Filter_Changed_Num[5]; 
	SendDataToWifi(CTL_ACK_DATA,HOST_FILTER_CHANGED_DATA,cBuf,8);
}
void Host_Filter_Used_Time_Data(void)
{
	uint8 cBuf[14];
	cBuf[0]=0x06;  	//滤芯级数
	cBuf[1]=(LvxinJishi[0]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[2]=LvxinJishi[0];
	cBuf[3]=(LvxinJishi[1]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[4]=LvxinJishi[1];
	cBuf[5]=(LvxinJishi[2]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[6]=LvxinJishi[2];
	cBuf[7]=(LvxinJishi[3]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[8]=LvxinJishi[3]; 
	cBuf[9]=(LvxinJishi[4]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[10]=LvxinJishi[4]; 
	cBuf[11]=(LvxinJishi[5]>>8);  	//滤芯数据0	2	U16(实际滤芯使用时间值)
	cBuf[12]=LvxinJishi[5]; 
	SendDataToWifi(CTL_ACK_DATA,HOST_FILTER_USED_TIME_DATA,cBuf,13);
}

void Host_E0_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E0_DATA,0,0);		
}
void Host_E1_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E1_DATA,0,0);		
}
void Host_E2_Data (void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E2_DATA,0,0);		
}
void Host_E3_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E3_DATA,0,0);		
}
void Host_E4_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E4_DATA,0,0);		
}
void Host_E5_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E5_DATA,0,0);		
}
void Host_E6_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E6_DATA,0,0);		
}
void Host_E7_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E7_DATA,0,0);		
}
void Host_E8_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E8_DATA,0,0);		
}
void Host_E9_Data(void)
{
	 SendDataToWifi(CTL_ACK_DATA,HOST_E9_DATA,0,0);		
}
void Load_Command(uint16 icommand)
{ 
	if(Cmd_Function_Num<5) 
	{
		Cmd_Function_Buf[Cmd_Function_Num] = icommand;	
		Cmd_Function_Num++;
	}

}
void Load_Error(uint16 icommand)
{ 
	if(Error_Counter<8) 
	{
		Error_Data_Buf[Error_Counter] = icommand;	
		Error_Counter++;
	}
}
/******************************************************************************
* 函 数 名: Uart_Exception_Handl(void)
* 函数功能: 完成超时重发等异常处理
* 入口参数: 无
* 返    回: 
*******************************************************************************/
void Uart_Exception_Handl(void)
{
	if(WifidatagramWorkFlag.uart_ack)
		{
		  if(Ack_Timer==0)
				{
				 	WifidatagramWorkFlag.send_data_load= 1;
				}
		} 
}
/******************************************************************************
* 函 数 名: Send_Uart(void)
* 函数功能: 串口发送程序
* 入口参数: 无
* 返    回: 
*******************************************************************************/
void Send_To_WifiUart(void)
{
  uint8 i; 
	if((!WifidatagramWorkFlag.uart_ack)&&(!WifidatagramWorkFlag.flag_Uart_Work)&&(Send_Interval_Counter==0))
		{
			 if(Cmd_Function_Num>0)
	  		 { 
	  		   Cmd_Function = Cmd_Function_Buf[0];
	  			 Cmd_Function_Num--;
	  			 if(Cmd_Function_Num>0)
	  			 {
	  				 for(i=0;i<=Cmd_Function_Num;i++)
	  				 {
	  				     Cmd_Function_Buf[i] = Cmd_Function_Buf[i+1];	
	  				 }
	  			 }
	  			 WifidatagramWorkFlag.send_data_load = 1;		 	     
	  		 }
		}
 	if(WifidatagramWorkFlag.send_data_load)
	 {
	   WifidatagramWorkFlag.send_data_load = 0;
		 switch(Cmd_Function)
		 {
			//发送握手信号
			case	MCU_HANDSHAKE_DATA:
				    Mcu_Handshake_Data();
				    break;
			//启动Smarklink
			case	MCU_POWERONSMARTLINK_DATA:	 				     
				    Mcu_Poweronsmartlink_Data();	     
			 	    break;
			case	MCU_FIRMWARE_UPDATE:  //设备要求固件升级
						Mcu_Firmware_Update();
			 			break;	 	
			case	HOST_STATE_DATA:
						Host_State_Data();	
						break;		
			case	HOST_FILTER_CHANGED_DATA:
						Host_Filter_Changed_Data();	
						break;	
			case	HOST_FILTER_USED_TIME_DATA:
						Host_Filter_Used_Time_Data();	
						break;
			case	MCU_CLEARALLUSERBOUND_DATA:
						Clean_All_User_Bound();
						break;	
			case HOST_E0_DATA:
			  	Host_E0_Data();			      
				  break;
			case HOST_E9_DATA:
			  	Host_E9_Data();			      
				  break;
			default:			 		 
				   break;
		 }		 		  
	 } 		 					
}







/******************************************************************************
* 函 数 名: void Process_From_Wifi_Ctl_Ack_Data(void)
* 函数功能: app、服务器控制数据
* 入口参数: 无
* 返    回: 
*******************************************************************************/
void Process_From_Wifi_Ctl_Ack_Data(void)
{
	 if((WifiWorkFlag.gcReceComm1OK)&&(giWIFIDATALength<=(WIFIBUFLEN-10-1))) 
	 {
	   WifiWorkFlag.gcReceComm1OK =0;
		 if(ATReceBuffer[0].gcATReceData[10+giWIFIDATALength]==Sum_Make_Verify (&ATReceBuffer[0].gcATReceData[0], giWIFIDATALength+10))
		 {

			 switch(giWIFICommand)
			 {
			 	case 	WIFI_SENDDINGSTATE_DATA:			
			 				SmarkLink_State = ATReceBuffer[0].gcATReceData[10];         //获取当前状态
              if((WIFI_SENDDINGSTATE_DATA_LINK_SERVER==SmarkLink_State)&&(Power_Buzfkg==0))	
              	{
              		Power_Buzfkg=1;								
                	BUZfkg=1;
                }
			 				Wifi_Senddingstate_Data();  		 				  					  					  					  					  					  					  				  					  					  				      
					  	break;
				case 	WIFI_FIRMWARE_UPDATE_DATA:	
							Wifi_Firmware_Update_Data(); 
							break;
				case 	WIFI_DECT_DATA:
							Wifi_Dect_Data();  	
							break;		
				case 	WIFI_FIRMWARE_HANDSHAKE_DATA:
							if(ATReceBuffer[0].gcATReceData[10]>Firmware_Version);         //获取当前状态
								{
									Firmware_Version=ATReceBuffer[0].gcATReceData[10];
									Firmware_Update=0xfe;
								}
							CyGlobalIntDisable;
			 				write();
			 				write1();  
			 				CyGlobalIntEnable;								
							Wifi_Firmware_Handshake_Data();
							firmwave_update_fig=1;

							break; 									
			 	case  APP_HOST_STATE://APP查询设备工作状态指令	APP查询设备工作状态指令
			 				App_Host_State(); 
			 		 		break;	
				case  APP_FILTER_CHANGED_DATA: 						//0x00B2 //查询本机滤芯使用次数（n级）
							App_Filter_Changed_Data(); 
			 		 		break;
				case  APP_ERROR_DATA: 											//0x00B4 //查询本机故障信息
							App_Error_Data(); 
			 		 		break;
				case  APP_FILTER_USED_TIME_DATA: 					//0x00B3 //查询本机滤芯使用时间（n级）		 		
			 				App_Filter_Used_Time_Data();
			 		 		break;
			 	case  APP_SEARCH_FILTER_MANAGE_NUM:	//查询本机滤芯管理方案号
			 				App_Search_Filter_Manage_Num(); 	
			 		 		break;
			 	case  APP_DOWNLOAD_FILTER_MANAGE_NUM:	//下载本机滤芯管理方案号
			 				Filter_Full_Data_Buf[0]= ATReceBuffer[0].gcATReceData[11]; 
			 				Filter_Full_Data_Buf[0]= (Filter_Full_Data_Buf[0]<<8)+ATReceBuffer[0].gcATReceData[12];
			 				Filter_Full_Data_Buf[1]= ATReceBuffer[0].gcATReceData[13]; 
			 				Filter_Full_Data_Buf[1]= (Filter_Full_Data_Buf[1]<<8)+ATReceBuffer[0].gcATReceData[14];
			 				Filter_Full_Data_Buf[2]= ATReceBuffer[0].gcATReceData[15]; 
			 				Filter_Full_Data_Buf[2]= (Filter_Full_Data_Buf[2]<<8)+ATReceBuffer[0].gcATReceData[16];
			 				Filter_Full_Data_Buf[3]= ATReceBuffer[0].gcATReceData[17]; 
			 				Filter_Full_Data_Buf[3]= (Filter_Full_Data_Buf[3]<<8)+ATReceBuffer[0].gcATReceData[18]; 
			 				Filter_Full_Data_Buf[4]= ATReceBuffer[0].gcATReceData[19]; 
			 				Filter_Full_Data_Buf[4]= (Filter_Full_Data_Buf[4]<<8)+ATReceBuffer[0].gcATReceData[20]; 
			 				Filter_Full_Data_Buf[5]= ATReceBuffer[0].gcATReceData[21]; 
			 				Filter_Full_Data_Buf[5]= (Filter_Full_Data_Buf[5]<<8)+ATReceBuffer[0].gcATReceData[22];
							CyGlobalIntDisable;
			 				write(); 
			 				CyGlobalIntEnable;
			 				App_Download_Filter_Manage_Num(); 		 				 		
			 		 		break;
			 	case  APP_DOWNLOAD_FILTER_RESET_DATA:	//下载本机滤芯管理方案号
                            BUZfkg=1;

			 				Filter_Reset_Data_Buf= ATReceBuffer[0].gcATReceData[10];
			 				F_Filter_Reset_Data_Buf=1; 
			 				App_Download_Filter_Reset_Data(); 		 				 		
			 		 		break;	 		
			 	case  APP_DOWNLOAD_NB_STA:	//远程开机功能
			 				if(ATReceBuffer[0].gcATReceData[10]==1)
			 					NBfig=1;//1为北
			 				else
			 					NBfig=0;//0为南			 					
			 		 		App_Download_Nb_Sta();			 		 
			 		 		break;
			 	case  APP_POWERON:	//远程开机功能
			 				WorkFlag.poweroff=0;
			 				WorkFlag.poweron=1;
			 				App_Poweron(); 
			 		 		break;
			 	case  APP_POWEROFF:	//远程关机功能	
			 				WorkFlag.poweroff=1;
			 				WorkFlag.poweron=0;
							App_Poweroff();
			 		 		break;
				 default:				 				 				 
					break;
				 
			 } 
		 }
		}		 					
}
/******************************************************************************
* 函 数 名: void Process_From_Wifi_Noa_Data(void)
* 函数功能: app、服务器控制数据
* 入口参数: 无
* 返    回: 
*******************************************************************************/
void Process_From_Wifi_Noa_Data(void)
{
	 if((WifiWorkFlag.gcReceComm1OK)&&(giWIFIDATALength<=(WIFIBUFLEN-10-1)))
	 {
	   WifiWorkFlag.gcReceComm1OK =0;
		 if(ATReceBuffer[0].gcATReceData[10+giWIFIDATALength]==Sum_Make_Verify (&ATReceBuffer[0].gcATReceData[0], giWIFIDATALength+10))
		 {
			 switch(giWIFICommand)
			 {
			 		case 	WIFI_SENDDINGSTATE_DATA:				      
					    	SmarkLink_State = ATReceBuffer[0].gcATReceData[10];         //获取当前状态
                if((WIFI_SENDDINGSTATE_DATA_LINK_SERVER==SmarkLink_State)&&(Power_Buzfkg==0))						
                {
              		Power_Buzfkg=1;								
                	BUZfkg=1;
                }
					  		break;
				 	default:				 				 				 
								break;
				 
			 } 
		 }
	 }		 					
}
/******************************************************************************
* 函 数 名: void Process_From_Wifi_Ack_Data(void)
* 函数功能: wifi应答数据
* 入口参数: 无
* 返    回: 
*******************************************************************************/
void Process_From_Wifi_Ack_Data(void)
{
	 if((WifiWorkFlag.gcReceComm1OK)&&(giWIFIDATALength<=(WIFIBUFLEN-10-1)))
	 {
	   WifiWorkFlag.gcReceComm1OK =0;
		 if(ATReceBuffer[0].gcATReceData[10+giWIFIDATALength]==Sum_Make_Verify (&ATReceBuffer[0].gcATReceData[0], giWIFIDATALength+10))
		 {
			 switch(giWIFICommand)
			 {
         case MCU_HANDSHAKE_DATA:		
                {
							 		if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == LINKNET_END))
								  	{
									  	WifidatagramWorkFlag.uart_ack = 0;
                                        SmarkLink_State=ATReceBuffer[0].gcATReceData[12];
									  	//BUZfkg=1;
								  	}				      
								  break;
                }
			   case MCU_CLEARALLUSERBOUND_DATA:			 
				 		if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == LINKNET_END))
	  					{
	  						WifidatagramWorkFlag.uart_ack = 0;
	  					}
					  break;				 
		 
				 case MCU_POWERONSMARTLINK_DATA:				 
				 		if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == LINKNET_END))
					  {
						  WifidatagramWorkFlag.uart_ack = 0;
						 	
					  }			      
					  break;
				case	HOST_STATE_DATA: 
						if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == LINKNET_END))
					  {
						  WifidatagramWorkFlag.uart_ack = 0;
					  }				      
					  break;
				 case MCU_FIRMWARE_UPDATE:	 
				 		if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == LINKNET_END))
					  {
						  WifidatagramWorkFlag.uart_ack = 0;
					  }				      
					  break;
				case	HOST_FILTER_CHANGED_DATA:
						if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == E0_REPORT_END))
					  {
						  WifidatagramWorkFlag.uart_ack = 0;
					  }				      
					  break;
				case	HOST_FILTER_USED_TIME_DATA:
						if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == E0_REPORT_END))
					  {
						  WifidatagramWorkFlag.uart_ack = 0;
					  }				      
					  break;
				 case HOST_E0_DATA:
				 
				 		if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == E0_REPORT_END))
					  {
						  WifidatagramWorkFlag.uart_ack = 0;
					  }				      
					  break;
				case HOST_E9_DATA:
				 
				 		if((ATReceBuffer[0].gcATReceData[10] == 0x00)  && (ATReceBuffer[0].gcATReceData[11] == E0_REPORT_END))
					  {
						  WifidatagramWorkFlag.uart_ack = 0;
					  }				      
					  break;
				 default:
				 		break;
				 
			 } 
		 }
	 }		 					
}
/******************************************************************************
* 函 数 名: void ProcessUARTData(void)
* 函数功能: 机器上报数据
* 入口参数: 无
* 返    回: 
*******************************************************************************/
void Process_From_Tdsboard_Data(void)
{
	 if((WifiWorkFlag.gcReceComm2OK)&&(giTDSBOARDDATALength<(TDSBUFLEN-10-1)))
		 {
		   WifiWorkFlag.gcReceComm2OK =0;
		     //
			 if(ATTdsReceBuffer[0].gcATReceTdsboardData[10+giTDSBOARDDATALength]==Sum_Make_Verify (&ATTdsReceBuffer[0].gcATReceTdsboardData[0], giTDSBOARDDATALength+10))
			 {
		                      Tds_Ack_Timer=30;
				 switch(giTDSBOARDCommand)
				 {
					 case 0x1000:		      
//					  	Value_Tds0=ATTdsReceBuffer[0].gcATReceTdsboardData[10];
//					  	Value_Tds0=(Value_Tds0<<8)+ATTdsReceBuffer[0].gcATReceTdsboardData[11];
//					  	Value_Tds1=ATTdsReceBuffer[0].gcATReceTdsboardData[12];
//					  	Value_Tds1=(Value_Tds1<<8)+ATTdsReceBuffer[0].gcATReceTdsboardData[13];
					  	Value_Loushui_Ad=ATTdsReceBuffer[0].gcATReceTdsboardData[14];
					  	Value_Loushui_Ad=(Value_Loushui_Ad<<8)+ATTdsReceBuffer[0].gcATReceTdsboardData[15];
					  	Value_T=ATTdsReceBuffer[0].gcATReceTdsboardData[16];
					  	Value_Flow=ATTdsReceBuffer[0].gcATReceTdsboardData[17];
					  	Value_Flow=(Value_Flow<<8)+ATTdsReceBuffer[0].gcATReceTdsboardData[18];	
              Value_Tds0_Tmp=ATTdsReceBuffer[0].gcATReceTdsboardData[19];
					  	Value_Tds0_Tmp=(Value_Tds0_Tmp<<8)+ATTdsReceBuffer[0].gcATReceTdsboardData[20];	
              Value_Tds1_Tmp=ATTdsReceBuffer[0].gcATReceTdsboardData[21];
					  	Value_Tds1_Tmp=(Value_Tds1_Tmp<<8)+ATTdsReceBuffer[0].gcATReceTdsboardData[22];	
              Value_Tds0=Tds_Scan_In(Value_Tds0_Tmp);//原水
              Value_Tds1=Tds_Scan_Out(Value_Tds1_Tmp);
						  break;
					 default:				 					 
						break;
				 } 
			 }
		 }		
   if(Tds_Ack_Timer==0)
    {
        Tds_Ack_Timer=30;
         memset(ATTdsReceBuffer[0].gcATReceTdsboardData,0x00,TDSBUFLEN);
        gctdsboardCommunState=0;
        giTDSBOARDCommand=0;
        giTDSBOARDDATALength=0;
        WifiWorkFlag.gcReceComm2OK=0;
        ATTdsReceBuffer[0].gcATReceTdsboardCount=0; 
        Open_UART_TDS_ISR();
    }
}
void Error_Send(void)
{

	if((ErrorFlag.Error_09==1)&&(SendFlag.host_e9_data==0))//漏水
		{
			SendFlag.host_e9_data=1;
			Load_Error(HOST_E9_DATA);
			Load_Command(HOST_E9_DATA);
		}		
	if((ErrorFlag.Error_00==1)&&(SendFlag.host_e0_data==0))//制水超时故障上报
		{
			SendFlag.host_e0_data=1;
			Load_Error(HOST_E0_DATA);
			Load_Command(HOST_E0_DATA);
		}
}
/*
*********************************************************************************************************
** 函数名称 ：ProcessWIFIData()
** 函数功能 ：WIFI数据帧处理                        
** 入口参数 ：无
** 出口参数 ：无
*********************************************************************************************************
*/
void Process_From_Wifi_Data(void)
{
    //uint8 i;//数据缓冲区判断，主要判断哪些代码需要发送	
  //Rev_Uart();		
	if((gcWIFICTL & ACK_DATA) == ACK_DATA) 				// 返回指令
		{	
			Process_From_Wifi_Ack_Data();
		}
	if((gcWIFICTL & NOA_DATA) == NOA_DATA) // 主动发送无需对方回复
		{  	
			Process_From_Wifi_Noa_Data();
		}
	if((gcWIFICTL & CTL_ACK_DATA) == CTL_ACK_DATA) // 主动发送需对方回复
		{  	
			Process_From_Wifi_Ctl_Ack_Data();
		}
}
/******************************************************************************/
/* [] END OF FILE */
