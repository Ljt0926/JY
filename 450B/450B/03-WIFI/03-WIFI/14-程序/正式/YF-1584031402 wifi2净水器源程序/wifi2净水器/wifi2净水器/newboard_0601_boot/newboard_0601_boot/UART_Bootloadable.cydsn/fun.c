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
#define _FUN_
#include "config.h"

uint8 Counter_Key;
/*******************************************************************************
*                       Buzzer
********************************************************************************/
void Buzzer_Fun(void)
{
    
	if(BUZfkg==1)//按键提示音
		{       
		    if(BuzzerDly<=2)
		        PWM_Start();
		    else
		    {
		        PWM_Stop();
		        BuzzerDly=0; 
		        BUZfkg=0;     
		    }
		}
	else if(BUZfkg==2)//上电缺水提示音 蜂鸣器响3次
		{ 
		BUZqueshuifkg=1;
		if(qushui_BUZcnt<3)
		{
		  if(BuzzerDly<5)
		      PWM_Start();
		  else if( BuzzerDly>=5 &&BuzzerDly<10)
		      PWM_Stop();
		  else if(BuzzerDly>=10) 
		  {   
		      qushui_BUZcnt++;
		      BuzzerDly=0;
		      //BUZfkg=0;
		      
		  }
		} 
		else
		{
		qushui_BUZcnt=0;
		BUZfkg=0;
		}   
		
		}  
	else if(BUZfkg==3)//滤芯寿命到期报警提示音  蜂鸣器2秒一次鸣叫15S  debug 叫3声
		{
			if(qushui_BUZcnt<7)//鸣叫7次14S
			{
			    if(BuzzerDly<20)
			        PWM_Start();
			    else if( BuzzerDly>=20 &&BuzzerDly<40)
			        PWM_Stop();
			    else if(BuzzerDly>=40) 
			    {   
			        qushui_BUZcnt++;
			        BuzzerDly=0;
			        //BUZfkg=0;
			        
			    }
			} 
        	else
        	{
        	    qushui_BUZcnt=0;
        	    BUZfkg=0;
        	}   
		}
}


/********************************************************************************\
    Timer ISR FUN
    //100ms
\********************************************************************************/
void Timer_Isr_Fun(void)
{	

    if(T10msSign)
        T10msSign = 0;
    else
        return;
    //***************************************系统主时钟
    TimeBase_Interrupt_CountOne++;
    TimeBase_Interrupt_CountTwo++;
    TimeBase_Interrupt_CountThree++;
    //****************************************高低压开关延时
    if(DYWDfig==1&&DYWD_Read() ==0)//从无水到有水低压微动接通3S 计时 
        DYWDcnt++;
    else
       DYWDcnt=0;
    if(DYWDfig1==1&&DYWD_Read() ==1)//从有水到无水低压微动接通3S 计时 
        DYWDcnt1++;
    else
       DYWDcnt1=0; 
    if(GYfig1==1&&GYWD_Read() ==1)//从到有水低压微动接通3S 计时 
        GYcnt1++;
    else
       GYcnt1=0;
    if(GYfig==1&&GYWD_Read() ==0)//从有水到无水低压微动接通3S 计时 
        GYcnt++;
    else
       GYcnt=0;
    //****************************************uart通信延时   
    if(Ack_Timer>0)//应答时间设定
    	Ack_Timer--; 
    if(Tds_Ack_Timer>0)//应答时间设定
    	Tds_Ack_Timer--; 
    if(Send_Interval_Counter>0)
    	Send_Interval_Counter--;
    Reset_Cnt++;
    if(Reset_Delay_Cnt<0xff)
        {
            Reset_Delay_Cnt++;
        }

    //**************************************检测程序
    if(fastjishifig==1)
        fastjishicnt++;
    else
        fastjishicnt=0; 
        
    if(fastfig==1)
    {
    	if(fastcnt<0xff)
        fastcnt++;
    }
    else
        fastcnt=0;
    
    if(WorkFlag.zijiansta&&zijianstacnt<255) //自检状态计时
        zijianstacnt++;
        
    //*****************************蜂鸣器报警
    if(BUZfkg==1||BUZfkg==2||BUZfkg==3)//蜂鸣器计时
        BuzzerDly++;  
    else
    {
        BuzzerDly=0;
        qushui_BUZcnt=0;
    }
    //***********************************系统计时
    if(PowerOnOneHourCnt < 360000)
    	PowerOnOneHourCnt++;
    if(Pump_No_workingCnt<TIMER3D)
    	Pump_No_workingCnt++;
    if(PowerOnCnt00<0xffff)
  		{
    		PowerOnCnt00++;
		    if(PowerOnCnt00>60000)//10min
		    	{
		    		PowerOnCnt00=0;
		    		if(PowerOnCnt01<144)//24hour
		    			PowerOnCnt01++;
		    		else
		    			{
		    				WorkFlag02.poll_24H_value_sendingcmp=1;
		    				PowerOnCnt01=0;
		    				PowerOnCnt00=0;
		    			}
		    	}
	  	}
	  if(firmwave_update_fig==1)
		  {
		  	if(firmwave_updatecnt<0xff)
		      firmwave_updatecnt++;
		  }
    else
        firmwave_updatecnt=0;
		if(Error_Data.bit.Error_00_flag==1)//连续制水2小时全屏闪烁
        eroorcnt++;
    else
        eroorcnt=0;
    if(F_Loushui_counter) 
		 	{
		 		Loushui_counter++;
		 	}
   	else
		 	{
		 		Loushui_counter=0;
		 	}
	 	//***********************************滤芯计时 
    if((WorkFlag.jishi==1)&&(WorkFlag.nowater==0))  //判断滤芯计时标志
    {
        if(fastjishifig==1)
        {
            if(LvxinJishi[0]<NPP_P0)
                LvxinJishi[0]+=100;
            if(LvxinJishi[1]<NFC_P0)
                LvxinJishi[1]+=100;
            if(LvxinJishi[2]<NRO1_P0)    
                LvxinJishi[2]+=100;
            if(LvxinJishi[3]<NRO1_P0)    
                LvxinJishi[3]+=100;
            if(LvxinJishi[4]<NRO1_P0)
                LvxinJishi[4]+=100;
            if(LvxinJishi[5]<NBC_P0)
                LvxinJishi[5]+=100;
        
        }   
        else
        {
             onemincnt++;
            if(onemincnt>=NBmint)
            {               
                onemincnt=0;  
                if(NBfig==1)
                {             
                    if(LvxinJishi[0]<NPP_P0)
                        LvxinJishi[0]++;
                    if(LvxinJishi[1]<NFC_P0)
                        LvxinJishi[1]++;
                    if(LvxinJishi[2]<NRO1_P0)    
                        LvxinJishi[2]++;
                    if(LvxinJishi[3]<NRO2_P0)    
                        LvxinJishi[3]++;
                    if(LvxinJishi[4]<NRO3_P0)
                        LvxinJishi[4]++;
                    if(LvxinJishi[5]<NBC_P0)
                        LvxinJishi[5]++;
                }
                else
                {
                    if(LvxinJishi[0]<SPP_P0)
                         LvxinJishi[0]++;
                    if(LvxinJishi[1]<SFC_P0)    
                        LvxinJishi[1]++;
                    if(LvxinJishi[2]<SRO1_P0)    
                        LvxinJishi[2]++;
                    if(LvxinJishi[3]<SRO2_P0)    
                        LvxinJishi[3]++;
                    if(LvxinJishi[4]<SRO3_P0)
                        LvxinJishi[4]++;
                    if(LvxinJishi[5]<SBC_P0)
                        LvxinJishi[5]++;
                } 
            }                   
			      if(jingshuicnt<65500)
			      	jingshuicnt++;//净水量计数器
			      if(jingshuicnt>TIMER1M_jingshui)//每60S 净水量加1
			      {
			      	if(jingshuiliang > 65500)
			  				{   
			      			jingshuiliang = 0;//65500;
			      			EEjingshuiliang=0;
			     				// write1();
			  				}
			          jingshuiliang++;
			          jingshuicnt=0;
			      }
        } 
        if(LianXuJiShi<80000)
        	LianXuJiShi++;
    }else
    {
        LianXuJiShi = 0;
    }
    //************************************按键计时
		NbPressCnt++;
		WifiPressCnt++;
		XzPressCnt++;
		FSettingPressCnt++;		
		if(F_Keysetting_Cnt==1)
			Keysetting_Cnt++;
		if(F_SSettingPressCnt==1)
			SSettingPressCnt++;
	
		if(lXXZcnt_fig)//滤芯状态计时
        LXXZstandcnt++;
    if(lXXZcnt_fig)
		  {
	      if(LXXZstandcnt<400)//滤芯状态计时
	        LXXZstandcnt++; 
		  }
    else
        LXXZstandcnt=0; 
         
    if(chongxifig==1)//冲洗状态且无故障就计时
        chongxicnt++;
        
    if(WorkFlag.quyuxzsta)//区域选择状态激活时开始计时
        NBstandcnt++;
		//************************************显示计时
		F_Ssync_Clock_Cnt++;
		F_Fsync_Clock_Cnt++;
		if(F_Ssync_Clock_Cnt>6)
			{
				F_Ssync_Clock_Cnt=0;
				F_Ssync_Clock=~F_Ssync_Clock;
			}
		if(F_Fsync_Clock_Cnt>3)
			{
				F_Fsync_Clock_Cnt=0;
				F_Fsync_Clock=~F_Fsync_Clock;
			}
    if(standkeyfig==1)//按键无动作计时
        standkeycnt++;
    else
        standkeycnt=0; 
     //*********************************测试程序
     Test_Cnt++;   
}
/********************************************************************************\
    USER FUNCTION
\********************************************************************************/
void stand(void)//待机判断
{
	  /* 判断有没有滤芯寿命到期，有滤芯寿命到期的则不进待机   */
  if(DisFlag_Filter.fflash_pp==1||DisFlag_Filter.fflash_fc==1||
  	DisFlag_Filter.fflash_ro1==1||DisFlag_Filter.fflash_ro2==1||
  	DisFlag_Filter.fflash_ro3==1||DisFlag_Filter.fflash_bc==1)
    {    
        standkeycnt=0;
				return;
    }    
   /* 3个按键无动作   */
  if((KEYLINK)==0&&(KEYSETTING)==0&&(KEYACTIVATION)==0)
    {
      standkeyfig=1;
    }
  if((KEYLINK)||(KEYSETTING)||(KEYACTIVATION))
    {
      standkeyfig=0;
      standkeycnt=0;
    } 
   /* 指示灯连续5分钟无闪烁且四个按键5分钟无动作,则进入待机状态   */
  if(standkeycnt>=TIMER5M)
    {
        standkeycnt=0;     	
 			  	Sys_Sta(STANDBYSTA);
 			  WorkFlag.activation=0;   
    }        
}
//void DisFlag_Pp(uint8 set)
//{
//	switch (set)
//	{
//		case 0:
//			DisFlag_Filter.sflash_pp=1;
//			DisFlag_Filter.fflash_pp=0;
//			DisFlag_Filter.on_pp=0;
//			DisFlag_Filter.off_pp=0;			 
//		break;
//		case 0:
//			DisFlag_Filter.sflash_pp=0;
//			DisFlag_Filter.fflash_pp=1;
//			DisFlag_Filter.on_pp=0;
//			DisFlag_Filter.off_pp=0;			 
//		break;
//		case 0:
//			DisFlag_Filter.sflash_pp=0;
//			DisFlag_Filter.fflash_pp=0;
//			DisFlag_Filter.on_pp=1;
//			DisFlag_Filter.off_pp=0;			 
//		break;
//		case 0:
//			DisFlag_Filter.sflash_pp=0;
//			DisFlag_Filter.fflash_pp=0;
//			DisFlag_Filter.on_pp=0;
//			DisFlag_Filter.off_pp=1;			 
//		break;
//		default:
//			
//	}
//}

void lvxin_clean (void)
{
	if(F_Filter_Reset_Data_Buf==1)
        {
        if(Reset_Delay_Cnt<TIMER5S)
        {
          F_Filter_Reset_Data_Buf=0;
        }

        if(Reset_Cnt>10)
        	{ 
                
        		F_Filter_Reset_Data_Buf=0;
        		Filter_Reset_Data.all=Filter_Reset_Data_Buf;
        		Change_Filter.all=Filter_Reset_Data_Buf;
        		if(Filter_Reset_Data.bit.flag_00) 
        			{
        				LvxinJishi[0] = 0;
        				LvxinJishi[0+6]=0;
        				Filter_Changed_Num[0]+=1;
        				Filter_Changed_Num[0+6]+=1;
        			}
        		if(Filter_Reset_Data.bit.flag_01) 
        			{
        				LvxinJishi[1] = 0;
        				LvxinJishi[1+6]=0;
        				Filter_Changed_Num[1]+=1;
        				Filter_Changed_Num[1+6]+=1;
        			}
        		if(Filter_Reset_Data.bit.flag_02) 
        			{
        				LvxinJishi[2] = 0;
        				LvxinJishi[2+6]=0;
        				Filter_Changed_Num[2]+=1;
        				Filter_Changed_Num[2+6]+=1;
        			}
        		if(Filter_Reset_Data.bit.flag_03) 
        			{
        				LvxinJishi[3] = 0;
        				LvxinJishi[3+6]=0;
        				Filter_Changed_Num[3]+=1;
        				Filter_Changed_Num[3+6]+=1;
        			}
        		if(Filter_Reset_Data.bit.flag_04) 
        			{
        				LvxinJishi[4] = 0;
        				LvxinJishi[4+6]=0;
        				Filter_Changed_Num[4]+=1;
        				Filter_Changed_Num[4+6]+=1;
        			}
        		if(Filter_Reset_Data.bit.flag_05) 
        			{
        				LvxinJishi[5] = 0;
        				LvxinJishi[5+6]=0;
        				Filter_Changed_Num[5]+=1;
        				Filter_Changed_Num[5+6]+=1;
        			}
        		Load_Command(HOST_FILTER_CHANGED_DATA);
                Reset_Delay_Cnt=0;
        	}

        }
    else
        {
            Reset_Cnt=0;
        }
}

void lvxin_panduan(void)//滤芯百分比计算 函数
{
    if(NBfig==1)//如果是北方模式
	    {
	      if(LvxinJishi[0]<NPP_P25)
	      	{
	      		DisFlag_Filter.fflash_pp=0;
						DisFlag_Filter.sflash_pp=0;
						DisFlag_Filter.on_pp=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[0]<NPP_P0)
					{
	      		DisFlag_Filter.fflash_pp=0;
						DisFlag_Filter.sflash_pp=1;
						DisFlag_Filter.on_pp=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_pp=1;
						DisFlag_Filter.sflash_pp=0;
						DisFlag_Filter.on_pp=0; 
					}
//////////////////////////////////////////////////////					
	      if(LvxinJishi[1]<NFC_P25)
	      	{
	      		DisFlag_Filter.fflash_fc=0;
						DisFlag_Filter.sflash_fc=0;
						DisFlag_Filter.on_fc=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[1]<NFC_P0)
					{
	      		DisFlag_Filter.fflash_fc=0;
						DisFlag_Filter.sflash_fc=1;
						DisFlag_Filter.on_fc=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_fc=1;
						DisFlag_Filter.sflash_fc=0;
						DisFlag_Filter.on_fc=0; 
					}
/////////////////////////////////////////////////////////////					
	      if(LvxinJishi[2]<NRO1_P25)
	      	{
	      		DisFlag_Filter.fflash_ro1=0;
						DisFlag_Filter.sflash_ro1=0;
						DisFlag_Filter.on_ro1=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[2]<NRO1_P0)
					{
	      		DisFlag_Filter.fflash_ro1=0;
						DisFlag_Filter.sflash_ro1=1;
						DisFlag_Filter.on_ro1=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro1=1;
						DisFlag_Filter.sflash_ro1=0;
						DisFlag_Filter.on_ro1=0; 
					}
///////////////////////////////////////////////////////////					
	      if(LvxinJishi[3]<NRO2_P25)
	      	{
	      		DisFlag_Filter.fflash_ro2=0;
						DisFlag_Filter.sflash_ro2=0;
						DisFlag_Filter.on_ro2=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[3]<NRO2_P0)
					{
	      		DisFlag_Filter.fflash_ro2=0;
						DisFlag_Filter.sflash_ro2=1;
						DisFlag_Filter.on_ro2=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro2=1;
						DisFlag_Filter.sflash_ro2=0;
						DisFlag_Filter.on_ro2=0; 
					}
////////////////////////////////////////////////////////////					
	      if(LvxinJishi[4]<NRO3_P25)
	      	{
	      		DisFlag_Filter.fflash_ro3=0;
						DisFlag_Filter.sflash_ro3=0;
						DisFlag_Filter.on_ro3=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[4]<NRO3_P0)
					{
	      		DisFlag_Filter.fflash_ro3=0;
						DisFlag_Filter.sflash_ro3=1;
						DisFlag_Filter.on_ro3=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro3=1;
						DisFlag_Filter.sflash_ro3=0;
						DisFlag_Filter.on_ro3=0; 
					}
////////////////////////////////////////////////////////////////
	      if(LvxinJishi[5]<NBC_P25)
	      	{
	      		DisFlag_Filter.fflash_bc=0;
						DisFlag_Filter.sflash_bc=0;
						DisFlag_Filter.on_bc=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[5]<NBC_P0)
					{
	      		DisFlag_Filter.fflash_bc=0;
						DisFlag_Filter.sflash_bc=1;
						DisFlag_Filter.on_bc=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_bc=1;
						DisFlag_Filter.sflash_bc=0;
						DisFlag_Filter.on_bc=0;
					} 
	    }
    else//如果是南方模式
	    {
	      if(LvxinJishi[0]<SPP_P25)
	      	{
	      		DisFlag_Filter.fflash_pp=0;
						DisFlag_Filter.sflash_pp=0;
						DisFlag_Filter.on_pp=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[0]<SPP_P0)
					{
	      		DisFlag_Filter.fflash_pp=0;
						DisFlag_Filter.sflash_pp=1;
						DisFlag_Filter.on_pp=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_pp=1;
						DisFlag_Filter.sflash_pp=0;
						DisFlag_Filter.on_pp=0; 
					}
//////////////////////////////////////////////////////					
	      if(LvxinJishi[1]<SFC_P25)
	      	{
	      		DisFlag_Filter.fflash_fc=0;
						DisFlag_Filter.sflash_fc=0;
						DisFlag_Filter.on_fc=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[1]<SFC_P0)
					{
	      		DisFlag_Filter.fflash_fc=0;
						DisFlag_Filter.sflash_fc=1;
						DisFlag_Filter.on_fc=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_fc=1;
						DisFlag_Filter.sflash_fc=0;
						DisFlag_Filter.on_fc=0; 
					}
/////////////////////////////////////////////////////////////					
	      if(LvxinJishi[2]<SRO1_P25)
	      	{
	      		DisFlag_Filter.fflash_ro1=0;
						DisFlag_Filter.sflash_ro1=0;
						DisFlag_Filter.on_ro1=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[2]<SRO1_P0)
					{
	      		DisFlag_Filter.fflash_ro1=0;
						DisFlag_Filter.sflash_ro1=1;
						DisFlag_Filter.on_ro1=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro1=1;
						DisFlag_Filter.sflash_ro1=0;
						DisFlag_Filter.on_ro1=0; 
					}
///////////////////////////////////////////////////////////					
	      if(LvxinJishi[3]<SRO2_P25)
	      	{
	      		DisFlag_Filter.fflash_ro2=0;
						DisFlag_Filter.sflash_ro2=0;
						DisFlag_Filter.on_ro2=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[3]<SRO2_P0)
					{
	      		DisFlag_Filter.fflash_ro2=0;
						DisFlag_Filter.sflash_ro2=1;
						DisFlag_Filter.on_ro2=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro2=1;
						DisFlag_Filter.sflash_ro2=0;
						DisFlag_Filter.on_ro2=0; 
					}
////////////////////////////////////////////////////////////					
	      if(LvxinJishi[4]<SRO3_P25)
	      	{
	      		DisFlag_Filter.fflash_ro3=0;
						DisFlag_Filter.sflash_ro3=0;
						DisFlag_Filter.on_ro3=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[4]<SRO3_P0)
					{
	      		DisFlag_Filter.fflash_ro3=0;
						DisFlag_Filter.sflash_ro3=1;
						DisFlag_Filter.on_ro3=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro3=1;
						DisFlag_Filter.sflash_ro3=0;
						DisFlag_Filter.on_ro3=0; 
					}
////////////////////////////////////////////////////////////////
	      if(LvxinJishi[5]<SBC_P25)
	      	{
	      		DisFlag_Filter.fflash_bc=0;
						DisFlag_Filter.sflash_bc=0;
						DisFlag_Filter.on_bc=1; 
						BUZfkg=3;	
					}     	
				else if(LvxinJishi[5]<SBC_P0)
					{
	      		DisFlag_Filter.fflash_bc=0;
						DisFlag_Filter.sflash_bc=1;
						DisFlag_Filter.on_bc=0; 
						BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_bc=1;
						DisFlag_Filter.sflash_bc=0;
						DisFlag_Filter.on_bc=0;
					} 
	    }

}
void lvxin_panduan_Nobeep(void)//滤芯百分比计算 函数
{
    if(NBfig==1)//如果是北方模式
	    {
	      if(LvxinJishi[0]<NPP_P25)
	      	{
	      		DisFlag_Filter.fflash_pp=0;
						DisFlag_Filter.sflash_pp=0;
						DisFlag_Filter.on_pp=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[0]<NPP_P0)
					{
	      		DisFlag_Filter.fflash_pp=0;
						DisFlag_Filter.sflash_pp=1;
						DisFlag_Filter.on_pp=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_pp=1;
						DisFlag_Filter.sflash_pp=0;
						DisFlag_Filter.on_pp=0; 
					}
//////////////////////////////////////////////////////					
	      if(LvxinJishi[1]<NFC_P25)
	      	{
	      		DisFlag_Filter.fflash_fc=0;
						DisFlag_Filter.sflash_fc=0;
						DisFlag_Filter.on_fc=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[1]<NFC_P0)
					{
	      		DisFlag_Filter.fflash_fc=0;
						DisFlag_Filter.sflash_fc=1;
						DisFlag_Filter.on_fc=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_fc=1;
						DisFlag_Filter.sflash_fc=0;
						DisFlag_Filter.on_fc=0; 
					}
/////////////////////////////////////////////////////////////					
	      if(LvxinJishi[2]<NRO1_P25)
	      	{
	      		DisFlag_Filter.fflash_ro1=0;
						DisFlag_Filter.sflash_ro1=0;
						DisFlag_Filter.on_ro1=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[2]<NRO1_P0)
					{
	      		DisFlag_Filter.fflash_ro1=0;
						DisFlag_Filter.sflash_ro1=1;
						DisFlag_Filter.on_ro1=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro1=1;
						DisFlag_Filter.sflash_ro1=0;
						DisFlag_Filter.on_ro1=0; 
					}
///////////////////////////////////////////////////////////					
	      if(LvxinJishi[3]<NRO2_P25)
	      	{
	      		DisFlag_Filter.fflash_ro2=0;
						DisFlag_Filter.sflash_ro2=0;
						DisFlag_Filter.on_ro2=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[3]<NRO2_P0)
					{
	      		DisFlag_Filter.fflash_ro2=0;
						DisFlag_Filter.sflash_ro2=1;
						DisFlag_Filter.on_ro2=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro2=1;
						DisFlag_Filter.sflash_ro2=0;
						DisFlag_Filter.on_ro2=0; 
					}
////////////////////////////////////////////////////////////					
	      if(LvxinJishi[4]<NRO3_P25)
	      	{
	      		DisFlag_Filter.fflash_ro3=0;
						DisFlag_Filter.sflash_ro3=0;
						DisFlag_Filter.on_ro3=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[4]<NRO3_P0)
					{
	      		DisFlag_Filter.fflash_ro3=0;
						DisFlag_Filter.sflash_ro3=1;
						DisFlag_Filter.on_ro3=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro3=1;
						DisFlag_Filter.sflash_ro3=0;
						DisFlag_Filter.on_ro3=0; 
					}
////////////////////////////////////////////////////////////////
	      if(LvxinJishi[5]<NBC_P25)
	      	{
	      		DisFlag_Filter.fflash_bc=0;
						DisFlag_Filter.sflash_bc=0;
						DisFlag_Filter.on_bc=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[5]<NBC_P0)
					{
	      		DisFlag_Filter.fflash_bc=0;
						DisFlag_Filter.sflash_bc=1;
						DisFlag_Filter.on_bc=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_bc=1;
						DisFlag_Filter.sflash_bc=0;
						DisFlag_Filter.on_bc=0;
					} 
	    }
    else//如果是南方模式
	    {
	      if(LvxinJishi[0]<SPP_P25)
	      	{
	      		DisFlag_Filter.fflash_pp=0;
						DisFlag_Filter.sflash_pp=0;
						DisFlag_Filter.on_pp=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[0]<SPP_P0)
					{
	      		DisFlag_Filter.fflash_pp=0;
						DisFlag_Filter.sflash_pp=1;
						DisFlag_Filter.on_pp=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_pp=1;
						DisFlag_Filter.sflash_pp=0;
						DisFlag_Filter.on_pp=0; 
					}
//////////////////////////////////////////////////////					
	      if(LvxinJishi[1]<SFC_P25)
	      	{
	      		DisFlag_Filter.fflash_fc=0;
						DisFlag_Filter.sflash_fc=0;
						DisFlag_Filter.on_fc=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[1]<SFC_P0)
					{
	      		DisFlag_Filter.fflash_fc=0;
						DisFlag_Filter.sflash_fc=1;
						DisFlag_Filter.on_fc=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_fc=1;
						DisFlag_Filter.sflash_fc=0;
						DisFlag_Filter.on_fc=0; 
					}
/////////////////////////////////////////////////////////////					
	      if(LvxinJishi[2]<SRO1_P25)
	      	{
	      		DisFlag_Filter.fflash_ro1=0;
						DisFlag_Filter.sflash_ro1=0;
						DisFlag_Filter.on_ro1=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[2]<SRO1_P0)
					{
	      		DisFlag_Filter.fflash_ro1=0;
						DisFlag_Filter.sflash_ro1=1;
						DisFlag_Filter.on_ro1=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro1=1;
						DisFlag_Filter.sflash_ro1=0;
						DisFlag_Filter.on_ro1=0; 
					}
///////////////////////////////////////////////////////////					
	      if(LvxinJishi[3]<SRO2_P25)
	      	{
	      		DisFlag_Filter.fflash_ro2=0;
						DisFlag_Filter.sflash_ro2=0;
						DisFlag_Filter.on_ro2=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[3]<SRO2_P0)
					{
	      		DisFlag_Filter.fflash_ro2=0;
						DisFlag_Filter.sflash_ro2=1;
						DisFlag_Filter.on_ro2=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro2=1;
						DisFlag_Filter.sflash_ro2=0;
						DisFlag_Filter.on_ro2=0; 
					}
////////////////////////////////////////////////////////////					
	      if(LvxinJishi[4]<SRO3_P25)
	      	{
	      		DisFlag_Filter.fflash_ro3=0;
						DisFlag_Filter.sflash_ro3=0;
						DisFlag_Filter.on_ro3=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[4]<SRO3_P0)
					{
	      		DisFlag_Filter.fflash_ro3=0;
						DisFlag_Filter.sflash_ro3=1;
						DisFlag_Filter.on_ro3=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_ro3=1;
						DisFlag_Filter.sflash_ro3=0;
						DisFlag_Filter.on_ro3=0; 
					}
////////////////////////////////////////////////////////////////
	      if(LvxinJishi[5]<SBC_P25)
	      	{
	      		DisFlag_Filter.fflash_bc=0;
						DisFlag_Filter.sflash_bc=0;
						DisFlag_Filter.on_bc=1; 
						//BUZfkg=3;	
					}     	
				else if(LvxinJishi[5]<SBC_P0)
					{
	      		DisFlag_Filter.fflash_bc=0;
						DisFlag_Filter.sflash_bc=1;
						DisFlag_Filter.on_bc=0; 
						//BUZfkg=3;		
					}
	      else 
	      	{
	      		DisFlag_Filter.fflash_bc=1;
						DisFlag_Filter.sflash_bc=0;
						DisFlag_Filter.on_bc=0;
					} 
	    }

}

void Test(void)
{
	if(PowerOnCnt00<TIMER10S)
		{
			if(TEST_Read()==1) 
			{  		
				Test_Cnt=0;	
			} 
			else	if(Test_Cnt>10)
			  	{
			  		WorkFlag.teststa=1;
			  		WorkFlag.test=1;
			  		Sys_Sta(TESTSTA);
			  	}		
		}
}

  

void Alarm_Judge(void)

{
    //LianXuJiShi=TIMER2H+1;
 //   Loushui_counter=1100;
	if(LianXuJiShi>=TIMER2H)//连续工作超过120分钟报警 *****************************************************************
		{ 
			ErrorFlag.Error_00=1;
			Error_Data.bit.Error_00_flag=1;
		} 
	
	if(Value_Loushui_Ad<LOUSHUI_AD)//漏水判断
		{
			F_Loushui_counter=1;
		}
	else
		{
			F_Loushui_counter=0;
		}
	if(Loushui_counter>TIMER15S)
		{
			ErrorFlag.Error_09=1;
			Error_Data.bit.Error_09_flag=1;
		} 
	if(DYWD_Read()==1)//为1时无水//判断是否有自来水************************************************
		{
		    if(DYWDfig1)//从有水到无水低压开关有3S 的延时,低压开关断开有3S的延时
		    {
		        if(DYWDcnt1>30*20*5)
		//            if(DYWDcnt1>30)
		        {   
		           DYWDfig1=0;
		           DYWDcnt1=0;
		         }    
		    }        
		    else
		    {
		        //无水，
		        DYWDfig=1;
		        WorkFlag.nowater = 1;
						Switch_Data.bit.diya_flag=1;   
		    }            
		      
		
		}
	else    //有水
		{ 
		    if(DYWDfig==1)//标志等于1,则是无水到有水,低压开关延时3S 接通
		    {
		        if(DYWDcnt>30)
		        {
		            DYWDfig=0;
		            DYWDcnt=0;                
		        }
		        
		    }
		    else
		    {
		        DYWDfig1=1;
		        WorkFlag.nowater = 0;   
		        Switch_Data.bit.diya_flag=0;     
		    }      
		}                 
	if(GYWD_Read()==1) ///为1判断压力罐是否水满************************************************
		{  
		    if(GYfig1==1)
		    {
		        if(GYcnt1>5)
		        {
		            GYcnt1=0;
		            GYfig1=0;
		        }
		    
		    }
		    else
		    {
		        shuibumanfig=0;
		        WorkFlag.gyfull = 1;//高开开关判断水满了
		      	Work_State.all=0x04; 				// 制水完成 	
		
		        GYfig=1;
		        waterfullfig=0;
		        Switch_Data.bit.gaoya_flag=0;
		        
		    }    
		 
		} 
	else//水不满
		{      
		   if(GYfig==1)//从水满到到不满有1S延时
		    {
		        if(GYcnt>10)
		        {
		            GYfig=0;
		            GYcnt=0;
		        }    
		    }        
		    else
		    {
		        WorkFlag.gyfull =0;
		        Switch_Data.bit.gaoya_flag=1;
		        Work_State.all=0x02; 			// 制水中 
		        GYfig1=1;
		        if(waterfullfig==0)
		        {
		            if(gyfullcnt<254)
		            
		            gyfullcnt++;
		            waterfullfig=1;
		        }
		        if(shuibumanfig==0&&(
	                DisFlag_Filter.fflash_pp==1||DisFlag_Filter.fflash_fc==1||
	  	            DisFlag_Filter.fflash_ro1==1||DisFlag_Filter.fflash_ro2==1||
	  	            DisFlag_Filter.fflash_ro3==1||DisFlag_Filter.fflash_bc==1)
	                &&lvxinbaojingcnt<2)
		        {
		            lvxinbaojingcnt++;
		            BUZfkg=3;
		            shuibumanfig=1;
		        }
		        
		        
		    }
		    
		 
		}        
          
}
   

void jixing(void)//判断机型函数
{
    //jixingnumber=Read_jixingnumber() ;读机型号 
    switch(jixingnumber)
    {
			case 0:
			Led_Pannel_Filter_Setting(0);
			break;
			case 1:
			Led_Pannel_Filter_Setting(1);
			break;
			case 2:
			Led_Pannel_Filter_Setting(2);
			break;
			case 3:
			Led_Pannel_Filter_Setting(3);
			break;
			case 4:
			Led_Pannel_Filter_Setting(4);
			break;
			case 5:
			Led_Pannel_Filter_Setting(5);
			break;
			default:
			break;
    } 
}   
void Sys_Sta(uint8 sn)
{
	switch (sn)
	{
		case 0:
			WorkFlag.alarmsta=1;
			WorkFlag.teststa=0;
			WorkFlag.mainmenusta=0;
			WorkFlag.standbysta=0;
			WorkFlag.lvxingxzsta=0;
		break;
		case 1:
			WorkFlag.alarmsta=0;
			WorkFlag.teststa=1;
			WorkFlag.mainmenusta=0;
			WorkFlag.standbysta=0;
			WorkFlag.lvxingxzsta=0;
		break;
		case 2:
			WorkFlag.alarmsta=0;
			WorkFlag.teststa=0;
			WorkFlag.mainmenusta=1;
			WorkFlag.standbysta=0;
			WorkFlag.lvxingxzsta=0;
		break;
		case 3:
			WorkFlag.alarmsta=0;
			WorkFlag.teststa=0;
			WorkFlag.mainmenusta=0;
			WorkFlag.standbysta=1;
			WorkFlag.lvxingxzsta=0;
		break;
		case 4:
			WorkFlag.alarmsta=0;
			WorkFlag.teststa=0;
			WorkFlag.mainmenusta=0;
			WorkFlag.standbysta=0;
			WorkFlag.lvxingxzsta=1;
		break;
		default:
    break;
			
	}
}
void Key_Return(void)
{
	if(PressFlag.xzpressstart == 0)
		{  
			PressFlag.xzpressstart = 1;
				Sys_Sta(MAINMENUSTA);                    	                    	                      
			return;
		}
}
void Key_Test(void)
{
			  //短按激活键
	if(KEYACTIVATION)
		{
			BUZfkg=1;
			Sys_Testsn=0;
		}
		
	if(KEYLINK)
		{
			BUZfkg=1;
			Sys_Testsn=1;
		}
	if(KEYSETTING)
		{
			BUZfkg=1;
			Sys_Testsn=2;
		}
	if(DYWD_Read()==0)
		{
			BUZfkg=1;
     	K1_Write(1);   //打开进水电磁阀 ，
		}
	if(GYWD_Read()==0)
		{
			BUZfkg=1;
			K2_Write(1);    //打开冲洗电磁阀
		}
}
void key(void)
{  
		if(WorkFlag.lvxingxzsta==1) 
			{
				DISSETTING;
			}
		else if (WorkFlag.standbysta==1) 
			{
				DISSTANDBY;
			}
		else if (WorkFlag.mainmenusta==1) 
			{
				DISMAINMENU;
			}
		else if (WorkFlag.teststa==1) 
			{
				DISTEST;
			}
		else if(WorkFlag.alarmsta==1)
			{
				DISALARM;
			}
	  //短按激活键
    if(KEYACTIVATION)
	    {
				BUZfkg=1;
	      WorkFlag.activation = 1;
	      	Sys_Sta(MAINMENUSTA); 
	    }
	  if(WorkFlag.activation==1) 
		  {
			  //判断是否wifilink按下
			  if(KEYLINKFLAG)
			    {
			      if(WifiPressCnt >TIMER1S)
			      	{
			      		WifiPressCnt = 0;  		
			      		Load_Command(MCU_POWERONSMARTLINK_DATA);
			      		BUZfkg=1;
			      	}
			    } 
				else
			    {
			       WifiPressCnt = 0;
			    }
			  //滤芯选择状态
			  if(WorkFlag.lvxingxzsta)
			  //if(WorkFlag.lvxingxzsta)
			    {
			    	if(WorkFlag.settingsta==0)
				    	{
					      if(KEYSETTINGFLAG)
					        {
					        	 	Sys_Sta(LVXINGXZSTA);
					            LXXZstandcnt=0;
					            lXXZcnt_fig=0;
					        }
					      else
					        {     
					            lXXZcnt_fig=1; //此段程序为在滤芯选择状态下30秒内部操作则退去滤芯选择状态
					            if(LXXZstandcnt>=300)
					            {
												lXXZcnt_fig=0;
                                                PressFlag.xzpressstart =0;
												Key_Return();
		
					            }   
					        }  
					        //短按，滤芯选择
					      if(KEYSETTINGFLAG)
									{
		
											if(SSettingPressCnt > TIMER5S)
												{
													BUZfkg=1;  
													F_SSettingPressCnt=1;
													F_Keysetting_Cnt=0;
													SSettingPressCnt=0;
													WorkFlag.lxfw = 1;
													LvxinJishi[LvXinNum] = 0;
													LvxinJishi[LvXinNum+6]=0;
													Filter_Changed_Num[LvXinNum]+=1;
													Filter_Changed_Num[LvXinNum+6]+=1;
													Load_Command(HOST_FILTER_CHANGED_DATA);
													lXXZcnt_fig=0;
														Sys_Sta(MAINMENUSTA);                    
													LvXinNum = 0;		                    	                      
													return;	
												}
											else
												{
													F_Keysetting_Cnt=1;
													F_SSettingPressCnt=1;
													Keysetting_Cnt=0;
												}
											
									}
								else if(Keysetting_Cnt>1)
									{
										BUZfkg=1;
										Keysetting_Cnt=0;
										F_Keysetting_Cnt=0;
                                        F_SSettingPressCnt=0;
										SSettingPressCnt=0;
					            LvXinNum++;         
					            if(LvXinNum >= 6)
					                LvXinNum = 0; 
					            WorkFlag.lxfw = 1;
						          switch(LvXinNum)
						            {
					                case 0:
															Sys_Settingsn=0;
															Change_Filter.all=1;                    
					                    break;
					                case 1:
															Sys_Settingsn=1;
					                    Change_Filter.all=2;   
					                    break;
					                case 2:
															Sys_Settingsn=2;
					                    Change_Filter.all=4;  
					                    break;
					                case 3:
															Sys_Settingsn=3;
					                    Change_Filter.all=8; 
					                    break;
					                case 4:
															Sys_Settingsn=4;
					                    Change_Filter.all=0x10; 
					                    break;
					                case 5:
															Sys_Settingsn=5;
					                    Change_Filter.all=0x20; 
					                    break;
					                default:
					                    Change_Filter.all=0x00; 
					                    break;
						            }
		                   return;
									}	
							}
			    } 
				//长按选择键2S

				if(KEYSETTINGFLAG)
				  {
			      if((XzPressCnt > 1)&&(WorkFlag.lvxingxzsta==0)&&(WorkFlag.lxfw==0))
			      {
              BUZfkg=1; 
              Sys_Sta(LVXINGXZSTA);
              WorkFlag.settingsta=1;
              LvXinNum=0;
              Sys_Settingsn=0;
              Change_Filter.all=1; 
              return;
			      }
				  }	      
				else
					{
						WorkFlag.settingsta=0;
						WorkFlag.lxfw=0;
					    XzPressCnt = 0;
					}
 
		  }
		  //上电10S内同时按下选择键和复位键，持续到10S后进入快检模式
	  else
	  	{
	  	if(PowerOnCnt00 <TIMER5MB)
		      {        
						CyDelayUs(1);  
						if(KEYSETTINGFLAG&&KEYLINKFLAG)         
						{
						    fastfig=1;          
						}    
						else
						{
						     WorkFlag.lxxzwf = 0;
						     fastfig=0;       
						}
		          
		      }
		  if(fastcnt>=TIMER5S) 
				{
					fastfig=0;
					faststa=1;
					BUZfkg=1; 
					Load_Command(MCU_CLEARALLUSERBOUND_DATA);
				}
 
		  }
            if(fastjishifig==1)
    {
        if((KEYSETTING)==1||(KEYLINK)==1||(fastjishicnt>=TIMER5M))
        {   
            
            BUZfkg=1;
            fastjishifig=0;
            cleareepromArrayflag=0;
            
            clean_ram();
        }    
    }
 }
void Work_Fun_Init(void)
{  
    LvXinNum= 0;
    NBmint=TIMER1MB;//默认为为北方计时
    Sys_Sta(STANDBYSTA);
}
void Sys_Init(void)
{  
    zijiandisplayfig=0;//上电首先进入自检
    WorkFlag.zijiansta=1;
    WorkFlag.shoucibysta=1;
    WorkFlag.nowater = 1;
    WorkFlag.uart_0_tx=1;
  	WorkFlag.poweroff=0;
  	WorkFlag.poweron=0;	
  	Tds_Ack_Timer=30;
    Load_Command(MCU_HANDSHAKE_DATA);
		SP_N=288;
		HP_N=384;
		JP_N=2592;
		KP_N=2592;
		LP_N=2592;
		MP_N=648;

		if((Filter_Full_Data_Buf[0]>2)&&(Filter_Full_Data_Buf[3]>100))
			{

		    SP_N=((Filter_Full_Data_Buf[0]*12)/100);
		    HP_N=((Filter_Full_Data_Buf[1]*12)/100);
		    JP_N=((Filter_Full_Data_Buf[2]*12)/100);
		    KP_N=((Filter_Full_Data_Buf[3]*12)/100);
		    LP_N=((Filter_Full_Data_Buf[4]*12)/100);
		    MP_N=((Filter_Full_Data_Buf[5]*12)/100);
				
			}
		  
}

void Wifi_Fun(void)
{
	switch(SmarkLink_State)
		{
			case 	WIFI_SENDDINGSTATE_DATA_NO_LINK_ROUTER://：无法连接路由器	
						DisFlag_Wifi.on_wifi=0;
						DisFlag_Wifi.off_wifi=1;						      
						DisFlag_Wifi.sflash_wifi=0;
						DisFlag_Wifi.fflash_wifi=0;	 			      	  					  					  					  					  					  				  					  					  				      
			  		break;
			case 	WIFI_SENDDINGSTATE_DATA_NO_LINK_SERVER://01：无法连接服务器	 
						DisFlag_Wifi.on_wifi=0;
						DisFlag_Wifi.off_wifi=1;						      
						DisFlag_Wifi.sflash_wifi=0;
						DisFlag_Wifi.fflash_wifi=0;	 			      		  				  					  					  					  					  					  					  				  					  					  				      
			  		break;
			case 	WIFI_SENDDINGSTATE_DATA_LINK_ROUTER:	//：已经路由器（指示灯常亮）		      
						DisFlag_Wifi.on_wifi=1;
						DisFlag_Wifi.off_wifi=0;						      
						DisFlag_Wifi.sflash_wifi=0;
						DisFlag_Wifi.fflash_wifi=0;		  	  					  					  					  					  					  					  				  					  					  				      
			  		break;
			case 	WIFI_SENDDINGSTATE_DATA_LINK_SERVER:		//03：已连接服务器（指示灯常亮）		
						DisFlag_Wifi.on_wifi=1;
						DisFlag_Wifi.off_wifi=0;						      
						DisFlag_Wifi.sflash_wifi=0;
						DisFlag_Wifi.fflash_wifi=0;						  				  				  					  					  					  					  					  					  				  					  					  				      
			  		break;
			case 	WIFI_SENDDINGSTATE_DATA_LINK_SMART_SETTING:		//已进入SmartLink等待App配置(指示灯可急闪)		      
						DisFlag_Wifi.on_wifi=0;
						DisFlag_Wifi.off_wifi=0;						      
						DisFlag_Wifi.sflash_wifi=0;
						DisFlag_Wifi.fflash_wifi=1;					     				  				  					  					  					  					  					  					  				  					  					  				      
			  		break;
			case 	WIFI_SENDDINGSTATE_DATA_LINK_SMART_SETTING_WAITTING:	//05：正在进SmartLink 配置中(指示灯慢闪)			      
						DisFlag_Wifi.on_wifi=0;
						DisFlag_Wifi.off_wifi=0;						      
						DisFlag_Wifi.sflash_wifi=1;
						DisFlag_Wifi.fflash_wifi=0;	 
			  		break;
			case 	WIFI_SENDDINGSTATE_DATA_SMART_SETTING_FAIL:	//06：SmartLink 配置失败 			 
						DisFlag_Wifi.on_wifi=0;
						DisFlag_Wifi.off_wifi=1;						      
						DisFlag_Wifi.sflash_wifi=0;
						DisFlag_Wifi.fflash_wifi=0;	      
			  		break;
			case 	WIFI_SENDDINGSTATE_DATA_SMART_SETTING_OK:	//07：SmartLink配置成功（指示灯常亮同上02状态）	
						DisFlag_Wifi.on_wifi=0;
						DisFlag_Wifi.off_wifi=0;						      
						DisFlag_Wifi.sflash_wifi=0;
						DisFlag_Wifi.fflash_wifi=1;	 			      			     				  				  					  					  					  					  					  					  				  					  					  				      
			  		break;
			case 	WIFI_SENDDINGSTATE_DATA_SOFTAP:	//08：SoftAP状态	
						break;	
			default:	 
						break;
		}					
}
void Work_Fun(void)
{  
		Test();
		if(WorkFlag.test==1)
			{
				Process_From_Wifi_Data();  
				Process_From_Tdsboard_Data(); 
				Uart_Exception_Handl();
				Send_To_WifiUart();  
				//Sys_Sta(TESTSTA);
				Key_Test();
				lvxin_clean ();
				return;
			}
    if((Error_Data.bit.Error_00_flag)||(Error_Data.bit.Error_09_flag))//连续工作2小时报警程序
		  {       
		     PWM_Start();//蜂鸣器长鸣
		     DISALARM; /*所有显示灯1HZ闪烁*/
		  }
    else
        {
            stand();//待机状态检测
            key();//按键检测程序 
        }
    lvxin_panduan_Nobeep();//滤芯寿命百分比
    Alarm_Judge();
    Process_From_Wifi_Data();  
    Process_From_Tdsboard_Data(); 
    Uart_Exception_Handl();
 		Send_To_WifiUart();   

 		lvxin_clean ();  

    if(WorkFlag02.poll_24H_value_sendingcmp==1)  
    	{
    		 WorkFlag02.poll_24H_value_sendingcmp=0;
    		 Load_Command(HOST_FILTER_USED_TIME_DATA);
    		 Load_Command(HOST_STATE_DATA);
    	}  
		if((WorkFlag.poweroff==1)&&(WorkFlag.poweron==0))//关机状态************************************************************
      {
          DISSTANDBY;       //待机状态所有指示灯全灭
          K1_Write(0);
    			K2_Write(0);
    			return;
      }        
   	else if((WorkFlag.poweroff==0)&&(WorkFlag.poweron==1))//开机状态************************************************************
      {
				WorkFlag.poweron=0;
      }   
    else if(faststa)//快检模式************************************************
    	{
        BUZfkg=1;
        fastcnt=0;
        fastjishifig=1;
        cleareepromArrayflag=1;
        clean_ram();
        faststa=0;
        return;   
    
    	}      
    else if(WorkFlag.zijiansta) //开机上电自检模式************************************************
    	{       
        if(zijianstacnt>10&&zijianstacnt<13)
        {
            BUZfkg=1;
            jixing();//机型判断及显示程序
        }
            
            
        else if(zijianstacnt>15&&zijianstacnt<18)  
        {
          switch(jixingnumber)
				    {          
				        case 0:
							Sys_Settingsn=0;
    				        break;
				        case 1:
							Sys_Settingsn=1;
    				        break;
				        case 2:
							Sys_Settingsn=2;
    				        break;
				        case 3:
							Sys_Settingsn=3;
    				        break;
				        case 4:
							Sys_Settingsn=4;
    				        break;
				        break;
				    } 
        }
   
        else if(zijianstacnt>18&&zijianstacnt<28)
        {        
            DISALLON;
              
        }
        else if(zijianstacnt>28&&zijianstacnt<30)
        {
            zijiandisplayfig=1;//机型和全屏检测后,可以开始正常的显示
            Work_Fun_Init();//正常显示开始给LED显示初始化
        }    
        if(zijianstacnt>30&&zijianstacnt<33)//如果无故障报警,30mS后退出自检状态
        {    
            
            if(WorkFlag.nowater==1)
                BUZfkg=2;
        }  
        if(zijianstacnt>33&&WorkFlag.nowater==0)
        {
            WorkFlag.zijiansta=0;
            zijianstacnt=0;
        }          
    	}
    else if(WorkFlag.nowater==1)//缺水状态,停止工作************************************************
			{ 
			
			    workstartfig=0;//停止工作
			    K1_Write(0);//关掉进水阀
			    K2_Write(0);//关掉冲洗阀
					WorkFlag.jishi=0;
			    chongxifig=0;//冲洗有故障时冲洗计时标志清0  
			}
    else if((Error_Data.bit.Error_00_flag==1)||(Error_Data.bit.Error_09_flag==1))//故障状态,停止工作************************************************
		  {               
		      workstartfig=0;//停止工作 
		      K1_Write(0);//关掉进水阀
		      K2_Write(0);//关掉冲洗阀
		      WorkFlag.jishi=0;        
		      chongxifig=0;//冲洗有故障时冲洗计时标志清0 
		  }
    else if(WorkFlag.shoucibysta==1)//若果是首次上电,且无故障则进入首次冲洗状态************************************************
	    {
	       //故障排可以开始冲洗//有自来水,且压力罐水不满开始首次冲洗                                               
				chongxifig=1;//进入上电首次冲洗,则冲洗计时开始
				if(chongxicnt<600)//60S自动60*100ms=30S
				{   
				    K1_Write(1);//打开进水阀
				    K2_Write(1);//打开冲洗阀
				    Work_State.all=0x01; 			//清洗
				}    
				else
				{
				    WorkFlag.shoucibysta=0;//首次上电冲洗完成后退出冲洗状态
				    chongxifig=0;
				    chongxicnt=0;       //冲洗计时器清0
				    K1_Write(0);
				    K2_Write(0);        //首次冲洗完成关闭进水和冲洗阀
				  
				}
	    }           
    else
    {
        workstartfig=1;//故障排可以开始正常工作      
    }
   if(workstartfig)   //自检模式无故障后开始正常工作模式*****************
    {   
        if(gyfullcnt>=50&&WorkFlag.gyfull==1)//如果压力罐水满50次则自动冲洗debug
        	{                                      
            WorkFlag.zidongbysta=1;      
        	}
 				if (Pump_No_workingCnt>=TIMER3D) 
 					{
            WorkFlag.zidongbysta=1;   						
 					} 
 				else
 					Pump_No_workingCnt=0;   
        if(WorkFlag.standbysta)//待机状态************************************************************
        {
          	Work_State.all=0x01; 	//制水完成后待机
            DISSTANDBY;      //待机状态所有指示灯全灭
            if((KEYACTIVATION)==1)//在待机状下点按任意键蜂鸣器有响应
                BUZfkg=1;
            if(WorkFlag.gyfull==0)//待机的时候如果压力罐水不满则退出待机
            {
                standkeycnt=0;
                WorkFlag.standbysta=0;  
            
            }  
	
            
        
        }          
        else if(WorkFlag.zidongbysta)//自动保养模式*****************************
            
        {                 
            chongxifig=1;//进入自动保养状态 冲洗计时标志开始                                    
            if(chongxicnt < 600) //600 * 100ms = 60S
            {
               Work_State.all=0x08; 			//清洗
               K2_Write(1);    //打开冲洗电磁阀
               K1_Write(1);   //打开进水电磁阀 ，
            }
            else
            {
                WorkFlag.zidongbysta = 0;
                //WorkFlag.worksta = 1;
                chongxifig = 0;//手动保养结束清标志位
                chongxicnt=0;
                if(gyfullcnt>=4)//zhm
                gyfullcnt=0;
                K2_Write(0); 
                 
            }                           
            if(WorkFlag.gyfull==0)//如果在自动冲洗的时候检测高压开关闭合,则退出自动冲洗状态
            {
                
                WorkFlag.zidongbysta = 0;
                K2_Write(0); 
            
            
            
            }                                    
        }    
//        else if(WorkFlag.gyfull==0&&WorkFlag.nowater==0)//制水模式,压力罐水不满时候*****************************
        else if(WorkFlag.gyfull==0)//制水模式,压力罐水不满时候*****************************
        {
            
            K1_Write(1);            //打开进水电子阀
            K2_Write(0); 
            WorkFlag02.close_value_sendingcmp=1;
            WorkFlag.jishi = 1;     //开始寿命计数    
            if(WorkFlag02.open_value_sendingcmp==1)//开龙头发送完成标志	
            	{
            		WorkFlag02.open_value_sendingcmp=0;
            		Load_Command(HOST_FILTER_USED_TIME_DATA);
            		Load_Command(HOST_STATE_DATA);
            	}
            if(LianXuJiShi>500)
   			    Value_Tds1_bak=Value_Tds1;
        }  
        else if(WorkFlag.gyfull==1) //压力罐水满)
        {
            K1_Write(0); //进水电磁阀关闭 

            WorkFlag02.open_value_sendingcmp=1;
            WorkFlag.jishi = 0; //制水计时标志置0
            if(WorkFlag02.close_value_sendingcmp==1)//开龙头发送完成标志 
            	{
            		WorkFlag02.close_value_sendingcmp=0;
            		Load_Command(HOST_FILTER_USED_TIME_DATA);
            		Load_Command(HOST_STATE_DATA);
            	}
        }            
    }             
}

/* [] END OF FILE */