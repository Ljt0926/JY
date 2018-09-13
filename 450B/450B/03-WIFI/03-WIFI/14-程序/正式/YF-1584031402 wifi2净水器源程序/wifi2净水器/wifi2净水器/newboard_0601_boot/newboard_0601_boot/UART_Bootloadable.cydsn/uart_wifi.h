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

#ifdef _UART_WIFI_
    #define MYWIFI   
#else
    #define MYWIFI extern
#endif

#ifndef _UARTWIFI_H
#define _UARTWIFI_H
//固件升级
#define  PRODUCT_FIRMWARE  1//固件没增加1版固件加一
/////com state
#define  WIFI_WAIT_SYN_0 0x00//数据包头FA
#define  WIFI_WAIT_SYN_1 0x01 // 2数据包头FB
#define  WIFI_PROTOCOL_JUDGE 0x02//3协议版本
#define  WIFI_TOTAL_FRAME_NUM 0x03//4总帧数量
#define  WIFI_FRAME_NUM 0x04//5帧序号
#define   WIFI_WAIT_CTL 0x05//控制字		 
#define   WIFI_COMMAND_1 0x06// 7数据长度1
#define   WIFI_COMMAND_2 0x07// 8数据长度2			 				  		
#define   WIFI_LENGTH1 0x08// 9数据长度1
#define   WIFI_LENGTH2 0x09// 10数据长度2
#define   WIFI_CHCK 0x0A// 11校验
#define   WIFI_RECEDATA 0x0B// 12数据内容
#define   WIFI_WAITPADDING 0x0C// 13接收6个 0

#define  TDSBOARD_WAIT_SYN_0 0x00//数据包头FA
#define  TDSBOARD_WAIT_SYN_1 0x01 // 2数据包头FB
#define  TDSBOARD_PROTOCOL_JUDGE 0x02//3协议版本
#define  TDSBOARD_TOTAL_FRAME_NUM 0x03//4总帧数量
#define  TDSBOARD_FRAME_NUM 0x04//5帧序号
#define   TDSBOARD_WAIT_CTL 0x05//控制字		 
#define   TDSBOARD_COMMAND_1 0x06// 7数据长度1
#define   TDSBOARD_COMMAND_2 0x07// 8数据长度2			 				  		
#define   TDSBOARD_LENGTH1 0x08// 9数据长度1
#define   TDSBOARD_LENGTH2 0x09// 10数据长度2
#define   TDSBOARD_CHCK 0x0A// 11校验
#define   TDSBOARD_RECEDATA 0x0B// 12数据内容
#define   TDSBOARD_WAITPADDING 0x0C// 13接收6个 0
//------------------------------------------
#define WIFI_SYN_0         0XFA 
#define WIFI_SYN_1         0XFB   
#define WIFI_PROTOCOL_VERSION  0X00   
#define WIFIBUFLEN			100 
//------------------------------------------
#define FIRMWARE_DATALEN			128 
#define FIRMWARE_DATALEN			128  
//------------------------------------------
#define TDSBUFLEN			30  
//------------------------------------------
#define TDSBOARD_SYN_0         0XFA 
#define TDSBOARD_SYN_1         0XFC   
#define TDSBOARD_PROTOCOL_VERSION  0X00   
//#define TDSBOARDBUFLEN			50  

/////////Data Type  
#define CTL_ACK_DATA  							0x00//(主动发送指令要求对方回复) 
#define ACK_DATA  							0x80//(返回指令) 
#define NOA_DATA  							0x40//(主动发送无需对方回复)		
////数据帧位置////////////////////////
#define SYN        		0	    //
#define CTL        		1	    //
#define LENL        		2	    //
#define LENH        		3	    //
#define CHK        			4	    //
#define CMD_DATA       	5	    //

//------------------------------

#define WORKING_STATE_REPORT 			0x00B2 // 工作状态上报指令
//wifi模块系统指令
#define WIFI_SENDDINGSTATE_DATA 					0xCCD0 //WiFi模块上报状态信息
#define WIFI_FIRMWARE_HANDSHAKE_DATA 			0xCCD1 //固件升级握手指令
#define WIFI_FIRMWARE_UPDATE_DATA 				0xCCD2 //固件升级数据包指令
#define WIFI_DECT_DATA 										0xCCD6 //检测设备
//MCU系统指令
#define MCU_CLEARALLUSERBOUND_DATA   	0x6001 //	清除所有用户绑定
#define MCU_HANDSHAKE_DATA   					0xCCC0 //发送握手信号HANDSHAKE_DATA
#define MCU_POWERONSMARTLINK_DATA 		0xCCC2 //启动Smarklink
#define MCU_FIRMWARE_UPDATE 					0xCCC5 // 固件升级指令
//--------------设备上报
#define HOST_STATE_DATA 0x9000 //设备发出工作状态指令
#define HOST_FILTER_CHANGED_DATA 		0x9001	//设备发出滤芯使用次数（n级）
#define HOST_FILTER_USED_TIME_DATA 	0x9002	//设备发出滤芯使用时间（n级）
#define HOST_E0_DATA 	0x90F0 								//制水超时故障上报
#define HOST_E1_DATA 	0x90F1 								//增压泵、进水电磁阀故障
#define HOST_E2_DATA 	0x90F2 								//冲洗电磁阀异常
#define HOST_E3_DATA 	0x90F3 								//温度传感器故障
#define HOST_E4_DATA	0x90F4								//流量传感器故障
#define HOST_E5_DATA	0x90F5								//原水TDS传感器故障
#define HOST_E6_DATA	0x90F6								//净水TDS传感器故障
#define HOST_E7_DATA	0x90F7												//TDS板通讯异常
#define HOST_E8_DATA	0x90F8									//龙头显示板通讯异常
#define HOST_E9_DATA	0x90F9									//龙头显示板通讯异常

//-----app、服务器控制指令
#define APP_HOST_STATE 											0x00B2			//APP查询设备工作状态指令	APP查询设备工作状态指令
#define APP_SEARCH_FILTER_MANAGE_NUM 				0x00B1	//查询本机滤芯管理方案号	查询本机滤芯管理方案号
#define APP_DOWNLOAD_FILTER_RESET_DATA			0x00A4	//下载新的滤芯滤芯复位数据到主机上
#define APP_DOWNLOAD_FILTER_MANAGE_NUM  		0x00A2	//下载新的滤芯管理方案号到主机上	下载新的滤芯管理方案号到主机上
#define APP_DOWNLOAD_NB_STA  		            0x00A3	//下载新的滤芯管理方案号到主机上	下载新的滤芯管理方案号到主机上
#define APP_POWERON  												0x00A0	//远程关机功能	远程关机功能
#define APP_POWEROFF 												0x00A1	//远程关机功能	远程关机功能
#define APP_FILTER_CHANGED_DATA 						0x00B5 //查询本机滤芯使用次数（n级）
#define APP_ERROR_DATA 											0x00B4 //查询本机故障信息
#define APP_FILTER_USED_TIME_DATA 					0x00B3 //查询本机滤芯使用时间（n级）


//设备发出工作状态指令

#define DATA_FRAME_NUM_EQUE_0  0x00
#define DATA_FRAME_EQUE_0 0x00
//#define NULL         0x00


// 消息类型，模块到主机 属于消息
#define SCANNET_END					0x40	// 扫描网络结果消息
#define LINKNET_END					0x00	// 网络已连接消息 
#define E0_REPORT_END				0x00	// E0成功发送
#define E1_REPORT_END				0x00	// E0成功发送
#define E2_REPORT_END				0x00	// E0成功发送
#define E3_REPORT_END				0x00	// E0成功发送
#define E4_REPORT_END				0x00	// E0成功发送
#define E5_REPORT_END				0x00	// E0成功发送
#define E6_REPORT_END				0x00	// E0成功发送
#define E7_REPORT_END				0x00	// E0成功发送
#define E8_REPORT_END				0x00	// E0成功发送






#define SMARTLINKNET_END    0x00	// SMART成功消息 
#define CLOSENET_END				0x42	// 网络已断开消息
#define SETNETPARA_END     	0x43	// 设置参数结果消息
#define QUERYNETPARA_END   	0x44	// 查询参数结果消息
#define RESTWIFI_END       	0x45	// 初始化完成消息
#define TCPLINK_END        	0x46	// TCP连接状态消息



#define WIFI_SENDDINGSTATE_DATA_NO_LINK_ROUTER 0x00//：无法连接路由器
#define WIFI_SENDDINGSTATE_DATA_NO_LINK_SERVER 0x01//01：无法连接服务器
#define WIFI_SENDDINGSTATE_DATA_LINK_ROUTER 0x02//：已经路由器（指示灯常亮）
#define WIFI_SENDDINGSTATE_DATA_LINK_SERVER 0x03//03：已连接服务器（指示灯常亮）
#define WIFI_SENDDINGSTATE_DATA_LINK_SMART_SETTING 0x04//04：已进入SmartLink等待App配置(指示灯可急闪) 
#define WIFI_SENDDINGSTATE_DATA_LINK_SMART_SETTING_WAITTING 0x05//05：正在进SmartLink 配置中(指示灯慢闪)
#define WIFI_SENDDINGSTATE_DATA_SMART_SETTING_FAIL 0x06//06：SmartLink 配置失败
#define WIFI_SENDDINGSTATE_DATA_SMART_SETTING_OK 0x07//07：SmartLink配置成功（指示灯常亮同上02状态）
#define WIFI_SENDDINGSTATE_DATA_SOFTAP 0x08//08：SoftAP状态


MYWIFI struct{
		unsigned handshake_ok:1;           //握手成功标志
		unsigned gcReceComm2OK:1;
		unsigned gcReceComm1OK:1;
		unsigned u8E0Set:1;
		unsigned u8E1Set:1;
		unsigned u8E2Set:1;
		unsigned u8E3Set:1;
}WifiWorkFlag;
MYWIFI uint16 *TDScheck1;
MYWIFI uint16 *TDScheck2;
MYWIFI uint16 *TDScheck3;
MYWIFI unsigned int *TDScheck4; 
MYWIFI uint8 u8LinkState,u8SmartLinkState;
MYWIFI uint8 Ack_Timer;              //应答时间设置 
MYWIFI uint8 Work_State_Num_H;     //当前工作状态功能号高位
MYWIFI uint8 Work_State_Num_L;     //当前工作状态功能号低位
MYWIFI uint8		*cpSendBufPtr;
MYWIFI uint16 Value_Tds0;
MYWIFI uint16 Value_Tds1;
MYWIFI uint16 Value_Tds0_Tmp;
MYWIFI uint16 Value_Tds1_Tmp;
MYWIFI uint16 Value_Loushui_Ad;
MYWIFI uint8 	Value_T;
MYWIFI uint16 Value_Flow;

MYWIFI uint8	Send_Interval_Counter;//发送时间间隔20ms 

MYWIFI void Send_To_WifiUart(void);
MYWIFI void Mcu_Handshake_Data(void);
MYWIFI void Smartlink_Fun(void);
MYWIFI void Process_From_Wifi_Data(void);
MYWIFI void Uart_Exception_Handl(void);
MYWIFI void Process_From_Wifi_Ack_Data(void);
MYWIFI void Process_From_Wifi_Noa_Data(void);
MYWIFI void Process_From_Wifi_Ctl_Ack_Data(void);
MYWIFI CYBIT Sum_Verify (uint8 *PBuf, uint16 Len);
MYWIFI void LoadUARTData(uint8  UartData);
MYWIFI void LoadTDSBoardData(uint8  UartData);
MYWIFI void ProcessWIFIData(void);

MYWIFI void ScanNetWork(uint8 cChannel,uint8  AckFlag);
MYWIFI void Wifi_Firmware_Handshake_Data(void);
MYWIFI void Uart_0_Putchar(void);
MYWIFI void Uart_1_Putchar(void);
MYWIFI void Clean_All_User_Bound(void);
MYWIFI void Mcu_Handshake_Data(void);
MYWIFI void Mcu_Poweronsmartlink_Data(void);
MYWIFI void Handshave_Fun(void);
MYWIFI void LoadUARTData(uint8  UartData);
MYWIFI void UART_SendData(uint8	 *data_buf,uint16 iCount);
MYWIFI void WifiLink(void);
MYWIFI void WifiSmartLink(void);
MYWIFI void Load_Command(uint16 icommand);
MYWIFI void Process_From_Tdsboard_Data(void);
MYWIFI void Error_Send(void);
MYWIFI uint16 find_position(uint16 a, const uint16 *p,uint16 num,uint16 chang_temp);


/* [] END OF FILE */

    
#endif

/* [] END OF FILE */






