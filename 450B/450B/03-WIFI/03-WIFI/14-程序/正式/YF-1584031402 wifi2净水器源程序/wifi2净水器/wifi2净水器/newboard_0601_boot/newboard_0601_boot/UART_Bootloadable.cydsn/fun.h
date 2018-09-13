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
//#include "uart_wifi.h"
#ifdef _FUN_
    
    #define MYFUN
#else
    #define MYFUN extern
#endif

#ifndef _FUN_H
#define _FUN_H
    
/*******************************************************************************
*                       Buzzer
********************************************************************************/
MYFUN struct{
    unsigned start:1;
    unsigned en:1;
    unsigned :14;
}BuzzerFlag;
MYFUN uint8 BuzzerNum,BuzzerCnt,BuzzerDly,eefig;
    
MYFUN void Buzzer_Fun(void);  
MYFUN uint8 BUZfkg,qushui_BUZcnt,BUZfkgtemp,BUZqueshuifkg,standkeyfig; 
MYFUN CYBIT Power_Buzfkg;  
    
MYFUN uint8 liucheng1,liucheng2,liucheng3,liucheng4,standstar_fig,DYWDfig,DYWDfig1,DYWDcnt;    
MYFUN uint16 DYWDcnt1;
MYFUN CYBIT F_Loushui_counter,F_Ssync_Clock,F_Fsync_Clock;
MYFUN uint8 F_Ssync_Clock_Cnt,F_Fsync_Clock_Cnt;
MYFUN uint16 Loushui_counter;
MYFUN uint8	Sys_Flownum;
MYFUN uint8 Sys_Testsn;
MYFUN uint8 Sys_Settingsn;
MYFUN uint8 Test_Cnt;
/********************************************************************************\
    Timer ISR FUN
\********************************************************************************/
MYFUN void Timer_Isr_Fun(void);


/********************************************************************************\
    USER FUNCTION
\********************************************************************************/
#define TIMER5S   50  //50 * 100ms = 5S
#define TIMER8S   80  //80 * 100ms = 5S
#define TIMER10S   100  //100 * 100ms = 10S
#define TIMER15S   150  //100 * 100ms = 10S
#define TIMER1S   10  //10 * 100ms = 1S
#define TIMER2S   20  //20*100ms=2S 
#define TIMER500MS   5  //5 * 100ms = 500mS
//#define TIMER1MB   1200  //3000*100mS=5分钟 
#define TIMER5MB   3000  //3000*100mS=5分钟 
#define TIMER1H   36000 	//36000 * 100ms = 1hour
#define TIMER2H   72000 	// 72000 * 100mS = 120min
#define TIMER30S  300			//300*100ms=30S
#define TIMER1MB   600  	//600*100mS=1分钟 北方滤芯计时1分钟
#define TIMER1MN   720  	//                南方滤芯计时1分钟
#define TIMER3D  2592000	// 3*24*3600*10*100ms=3天
#define TIMER1M_jingshui  600 //净水1分钟
#define TIMER5M     			3000//3000*100ms=300S=5min
#define KEYSETTING  			(BtnData1 & (1 << BTN_SETTING))&&(!(BtnData2 & (1 << BTN_SETTING)))//短设定键
#define KEYLINK  					(BtnData1 & (1 << BTN_LINK))&&(!(BtnData2 & (1 << BTN_LINK)))//短link
#define KEYACTIVATION  		(BtnData1 & (1 << BTN_ACTIVATION))&&(!(BtnData2 & (1 << BTN_ACTIVATION)))//短激活按键
#define LOUSHUI_AD     		2500

#define KEYSETTINGFLAG  	(BtnData1 & (1 << BTN_SETTING))&&(BtnData2 & (1 << BTN_SETTING))//设定键		
#define KEYSETTINGFLAG0  	(BtnData1 & (1 << BTN_SETTING))&&(BtnData2 == 0)//设定键																								
#define KEYLINKFLAG  			(BtnData1 & (1 << BTN_LINK))&&(BtnData2 & (1 << BTN_LINK))
#define KEYACTIVATIONFLAG  		(BtnData1 & (1 << BTN_ACTIVATION))&&(BtnData2 & (1 << BTN_ACTIVATION))//短激活按键

//--------------------------------------
#define NPP_P25     		2400
#define NFC_P25     		2400
#define NRO1_P25     		16200
#define NRO2_P25     		16200
#define NRO3_P25     		16200
#define NBC_P25     		4050

#define NPP_P0     	    3200
#define NFC_P0     	    3200
#define NRO1_P0     		21600
#define NRO2_P0     		21600
#define NRO3_P0     		21600
#define NBC_P0     	    5400

//---------------------------------------
#define SPP_P25     		2880
#define SFC_P25     		2880
#define SRO1_P25     		19440
#define SRO2_P25     		19440
#define SRO3_P25     		19440
#define SBC_P25     		4860

#define SPP_P0     	    3840
#define SFC_P0     	    3840
#define SRO1_P0     		25920
#define SRO2_P0     		25920
#define SRO3_P0     		25920
#define SBC_P0    	    6480
//-----------------------------------------
#define ALARMSTA		0
#define TESTSTA			1
#define MAINMENUSTA	2
#define STANDBYSTA	3
#define LVXINGXZSTA	4

MYFUN CYBIT F_Filter_Reset_Data_Buf;
MYFUN CYBIT F_Keysetting_Cnt,F_SSettingPressCnt;//按键计时标志
MYFUN uint8 Keysetting_Cnt;//按键标志
MYFUN uint8 Reset_Cnt,Reset_Delay_Cnt;
MYFUN uint8 Firmware_Version,Firmware_Versionbak,Firmware_Update; //固件版本           
MYFUN uint32 PowerOnOneHourCnt,Pump_No_workingCnt;//上电计时,1分钟计时
MYFUN uint8 NbPressCnt,NBfig,NBPressCnt,NBPressStart,lXXZcnt_fig;//南北计数,缺水标志, 
MYFUN uint8 XzPressCnt,XzPressCnt,FSettingPressCnt,SSettingPressCnt,WifiPressCnt,chongxifig;//
MYFUN struct{
	unsigned xzpressstart:1;
	//unsigned wifipressstart:1;
}PressFlag;
MYFUN uint8 TimeBase_Interrupt_CountOne,TimeBase_Interrupt_CountTwo;
MYFUN uint16 TimeBase_Interrupt_CountThree;

MYFUN uint16 chongxicnt,NBstandcnt,LXXZstandcnt,onemincnt,NBmint,jingshuicnt,eroorcnt,standkeycnt;//净水量计数
MYFUN uint8 zijianstacnt;//自检状态计时  
MYFUN uint8 jixingnumber,onehourcnt,jishihour;//机型号码
MYFUN uint8 zijiandisplayfig,workstartfig,GYfig,GYcnt,gyfullcnt;//自检显示标志
MYFUN uint8 GYcnt1,GYfig1,waterfullfig;
MYFUN uint8 lvxinbaojingcnt;
MYFUN struct //结构体类型定义  
	{  
		unsigned Error_00:1; //0 位Bit1 取寄存器最低位0 位，以下顺序取1 位直到最高位  
		unsigned Error_01:1; //1  
		unsigned Error_02:1; //2  
		unsigned Error_03:1; //3  
		unsigned Error_04:1; //4  
		unsigned Error_05:1; //5  
		unsigned Error_06:1; //6  
		unsigned Error_07:1; //7  
		unsigned Error_08:1; //8 
        unsigned Error_09:1; //8  
	}ErrorFlag; //bit为具有所定义的结构体类型的变量 
	
MYFUN struct
	{
	  unsigned open_value_sendingcmp:1;//开龙头发送完成标志	
    unsigned close_value_sendingcmp:1;//开龙头发送完成标志
    unsigned poll_24H_value_sendingcmp:1;//24小时定时发送完成标志	
	}WorkFlag02;
MYFUN struct{
    unsigned error:1;
    unsigned nowater:1;     //缺水标志
    unsigned stopzs:1;      //停止制水标志
    unsigned jishi:1;       //滤芯计时标志
    unsigned quyuxzsta:1;       //寿命选择状态
    unsigned lvxingxzsta:1;         //滤芯选择状态
    unsigned settingsta:1;	
    unsigned activation:1;//激活标志状态	    	
    unsigned 	kuaijiansta:1;         //快检状态
    unsigned 	poweron:1;            // 开机标志
    unsigned	poweroff:1;            // 关机标志
    unsigned standbysta:1;          //待机状态
    unsigned fastfig:1;             //
    unsigned lxxz:1;         //滤芯选择
    unsigned lxfw:1;         //滤芯复位完成
    unsigned sdby:1;         //手动保养标志
    unsigned lxxzwf:1;       //滤芯选择复位同时标志
    unsigned wifiset:1;	
    unsigned zijiansta:1;//自检状态标志
    unsigned shoucibysta:1; //首次冲洗状态
    unsigned zidongbysta:1;//自动保养标志状态
    unsigned zhishui:1;//制水状态
    unsigned gyfull:1;//高压水满标志
    unsigned uart_0_tx:1;
    unsigned uart_1_tx:1;
    unsigned mainmenusta:1;
    unsigned teststa:1;
    unsigned test:1;
    unsigned alarmsta:1;
}WorkFlag;

MYFUN struct{		
		unsigned host_e0_data:1;                  //制水超时故障上报
		unsigned host_e1_data:1; 	 								//增压泵、进水电磁阀故障
		unsigned host_e2_data:1; 	 								//冲洗电磁阀异常
		unsigned host_e3_data:1; 	 								//温度传感器故障
		unsigned host_e4_data:1;									//流量传感器故障
		unsigned host_e5_data:1;									//原水TDS传感器故障
		unsigned host_e6_data:1;									//净水TDS传感器故障
		unsigned host_e7_data:1;									//TDS板通讯异常
		unsigned host_e8_data:1;									//龙头显示板通讯异常
		unsigned host_e9_data:1;									//漏水异常
}SendFlag;


MYFUN union //共用体类型定义  
{ 
	uint8 all; //定义all 为16 位无符号整型变量  
	struct //结构体类型定义  
	{  
		unsigned gaoya_flag:1; //0 位Bit1 取寄存器最低位0 位，以下顺序取1 位直到最高位  
		unsigned diya_flag:1; //1  
	}bit; //bit为具有所定义的结构体类型的变量  
}Switch_Data; //CtrlBit 为具有所定义的共用体类型的变量

MYFUN union //共用体类型定义  
{ 
	uint8 all; //定义all 为16 位无符号整型变量  
	struct //结构体类型定义  
	{  
		unsigned standby_mode:1; 			//制水完成后待机	
		unsigned working:1; 		// 工作中 
		unsigned worked:1; 		// 工作 			
		unsigned cleaning:1; 		//清洗
	}bit; //bit为具有所定义的结构体类型的变量  
}Work_State; //CtrlBit 为具有所定义的共用体类型的变量
//-------------故障
MYFUN union
{ 
	uint16 all; 
	struct 
	{  
		unsigned Error_00_flag:1;  
		unsigned Error_01_flag:1; 
		unsigned Error_02_flag:1; 
		unsigned Error_03_flag:1; //3  
		unsigned Error_04_flag:1; //4  
		unsigned Error_05_flag:1; //5  
		unsigned Error_06_flag:1; //6  
		unsigned Error_07_flag:1; //7  
		unsigned Error_08_flag:1; //8  
		unsigned Error_09_flag:1; //9          
	}bit;  
}Error_Data; 
MYFUN union   
{ 
	uint8 all;   
	struct 
	{  
		unsigned flag_00:1; //0 位Bit1 取寄存器最低位0 位，以下顺序取1 位直到最高位  
		unsigned flag_01:1; //1  
		unsigned flag_02:1; //2  
		unsigned flag_03:1; //3  
		unsigned flag_04:1; //4  
		unsigned flag_05:1; //5  
		unsigned flag_06:1; //6  
		unsigned flag_07:1; //7   
	}bit; //bit为具有所定义的结构体类型的变量  
}Change_Filter; //CtrlBit 为具有所定义的共用体类型的变量 

MYFUN union   
{ 
	uint8 all;   
	struct 
	{  
		unsigned flag_00:1; //0 位Bit1 取寄存器最低位0 位，以下顺序取1 位直到最高位  
		unsigned flag_01:1; //1  
		unsigned flag_02:1; //2  
		unsigned flag_03:1; //3  
		unsigned flag_04:1; //4  
		unsigned flag_05:1; //5    
	}bit; //bit为具有所定义的结构体类型的变量  
}Filter_Reset_Data; //CtrlBit 为具有所定义的共用体类型的变量 

MYFUN uint16 jingshuiliang,EEjingshuiliang;
MYFUN uint32 LianXuJiShi;  //
MYFUN uint16 LvxinJishi[12];
//MYFUN uint16 tempLvxinJishi[7];


MYFUN uint16 SP_N,HP_N,JP_N,KP_N,LP_N,MP_N;
MYFUN uint8 Tds_Ack_Timer;
MYFUN uint16 Filter_Full_Data_Buf[12];
MYFUN uint8 Filter_Reset_Data_Buf;
MYFUN uint8 Filter_Changed_Num[12];
MYFUN uint8 faststa,fastfig,fastcnt,n,fastjishifig,yanshidisfig,  firmwave_update_fig  ;
MYFUN uint16 fastjishicnt;
MYFUN uint8 firmwave_updatecnt;
MYFUN uint8 EEgyfullcnt;
MYFUN uint8 LvXinNum;
MYFUN uint8 cleareepromArrayflag;

MYFUN uint16 StandByCnt;    //待机
MYFUN uint16 PowerOnCnt00;     //开机计时
MYFUN uint8 PowerOnCnt01; 
MYFUN uint16  V24cnt;
MYFUN uint8  poweroverfig;       
MYFUN uint8  jserrorcnt,jserrorcntfig;
MYFUN uint8 shuibumanfig;
//-------------wifiuart
MYFUN uint16 Value_Tds0;
MYFUN uint16 Value_Tds1;
MYFUN uint16 Value_Tds1_bak;
MYFUN uint16 Value_Loushui_Ad;
MYFUN uint8 Value_T;
MYFUN uint16 Value_Flow;
//---------------------
MYFUN uint8 Error_Counter;//故障数量统计
MYFUN uint8 Filter_Manage_Num;
MYFUN uint8 SmarkLink_State;
//------------------------------------
MYFUN void Read_E2prom();
MYFUN void Lvxin_Detect(void);
MYFUN void Key_Deal(void);
MYFUN void Work_Fun_Init(void);
MYFUN void Work_Fun(void);
MYFUN void stand(void);
MYFUN void LXPercent(void);
MYFUN void error_alm(void);
MYFUN void jixing(void);
MYFUN void key(void);
MYFUN void delay_500ms(void);
MYFUN void Alarm_Judge(void);
MYFUN void lvxin_panduan(void);
MYFUN void lvxin_panduan_Nobeep(void);
MYFUN void Open_UART_TDS_ISR(void);
MYFUN void Open_UART_WIFI_ISR(void);
MYFUN void Comm_Uart_1_PrintHex8(uint8 value);
MYFUN void Load_Error(uint16 icommand);
MYFUN void Sys_Init(void);
MYFUN void Wifi_Fun(void);

MYFUN void Sys_Sta(uint8 sn);
#endif

/* [] END OF FILE */
