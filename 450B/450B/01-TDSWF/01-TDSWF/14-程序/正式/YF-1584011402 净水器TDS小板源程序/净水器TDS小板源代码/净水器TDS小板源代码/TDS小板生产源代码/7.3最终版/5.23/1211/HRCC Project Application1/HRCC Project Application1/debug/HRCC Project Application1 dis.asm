;The Num of Instruction(Size):814. The Max Address(Begin with 0):814 

                MCU  HR7P170

A    equ    0
R    equ    1
HRAM_0X2  equ  0X2
HRAM_0X3  equ  0X3
HRAM_0X30  equ  0X30
HRAM_0X31  equ  0X31
HRAM_0X32  equ  0X32
HRAM_0X33  equ  0X33
HRAM_0X3E  equ  0X3e
HRAM_0X4  equ  0X4
HRAM_0X5  equ  0X5
HRAM_0X80  equ  0X80
HRAM_0X81  equ  0X81
HRAM_0X82  equ  0X82
HRAM_0X83  equ  0X83
HRAM_0X84  equ  0X84
HRAM_0X86  equ  0X86
HRAM_0X87  equ  0X87
HRAM_0X88  equ  0X88
HRAM_0X89  equ  0X89
HRAM_0X9B  equ  0X9b
HRAM_0X9F  equ  0X9f
HRAM_0XAC  equ  0Xac
HRAM_0XDC  equ  0Xdc
HRAM_0XE3  equ  0Xe3

                ORG             0X00
HADR_0X0:
:0X0  60c5                      CALL            HADR_0XC5
:0X1  6086                      CALL            HADR_0X86
:0X2  6800                      GOTO            HADR_0X0
                                ORG             0X4
:0X4  c180                      PUSH
:0X5  e787                      CLR             HRAM_0X87
:0X6  e783                      CLR             HRAM_0X83
:0X7  5081                      MOV             HRAM_0X81,      A
:0X8  e600                      MOVA            (SAVED_FSR)&7f                        ;(SAVED_FSR)&7f: Bank 0    Addr: 0    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X9  5082                      MOV             HRAM_0X82,      A
:0Xa  e601                      MOVA            (SAVED_FSR+1)&7f                      ;(SAVED_FSR+1)&7f: Bank 0    Addr: 1    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0Xb  7834                      MOVRA           CSEG_PTR                              ;CSEG_PTR: Bank 0    Addr: 52     
:0Xc  2036                      MOVAR           CSEG_PTR+2                            ;CSEG_PTR+2: Bank 0    Addr: 54     
:0Xd  7835                      MOVRA           CSEG_PTR+1                            ;CSEG_PTR+1: Bank 0    Addr: 53     
:0Xe  2037                      MOVAR           CSEG_PTR+3                            ;CSEG_PTR+3: Bank 0    Addr: 55     
:0Xf  503f                      MOV             (MUL_TEMP)&7f,  A                     ;(MUL_TEMP)&7f: Bank 0    Addr: 63     
:0X10  e641                     MOVA            (MUL_TEMP+2)&7f                      ;(MUL_TEMP+2)&7f: Bank 0    Addr: 65     
:0X11  5040                     MOV             (MUL_TEMP+1)&7f,                A    ;(MUL_TEMP+1)&7f: Bank 0    Addr: 64     
:0X12  e642                     MOVA            (MUL_TEMP+3)&7f                      ;(MUL_TEMP+3)&7f: Bank 0    Addr: 66     
:0X13  5030                     MOV             0X30,           A
:0X14  e602                     MOVA            0X2
:0X15  5031                     MOV             0X31,           A
:0X16  e603                     MOVA            0X3
:0X17  5032                     MOV             0X32,           A
:0X18  e604                     MOVA            0X4
:0X19  5033                     MOV             0X33,           A
:0X1a  e605                     MOVA            0X5
;//*****************************************************************************
;//                              中断服务程序
;//*****************************************************************************
;void isr(void) interrupt//125us 中断
;{
;
;	//按键中断
;
;	if(KIF)
:0X1b  909b                     JBS             HRAM_0X9B,      0
:0X1c  6829                     GOTO            HADR_0X29
;	{
;		if(PB5)//up   //x=4~7,用哪个则x=哪个数值。
:0X1d  95ac                     JBS             HRAM_0XAC,      5
:0X1e  6821                     GOTO            HADR_0X21
;		{
;			up_pluse_f=1;
:0X1f  a23e                     BSS             ((_up_pluse_f)>>3)&7f,          2    ;((_up_pluse_f)>>3)&7f: Bank 0    Addr: 62     
;		}
:0X20  6828                     GOTO            HADR_0X28
HADR_0X21:
;		else	//down
:0X21  923e                     JBS             HRAM_0X3E,      2
:0X22  6828                     GOTO            HADR_0X28
;			{
;				up_pluse_f=0;
:0X23  aa3e                     BCC             ((_up_pluse_f)>>3)&7f,          2    ;((_up_pluse_f)>>3)&7f: Bank 0    Addr: 62     
;				pulse_num_r++;//脉冲个数
:0X24  ea01                     SECTION         0X1
:0X25  5503                     INC             (_pulse_num_r)&7f,              R    ;(_pulse_num_r)&7f: Bank 0    Addr: 3     
:0X26  9a84                     JBC             HRAM_0X84,      2
:0X27  5504                     INC             (_pulse_num_r+1)&7f,            R    ;(_pulse_num_r+1)&7f: Bank 0    Addr: 4     
HADR_0X28:
;			}
;		}
:0X28  a89b                     BCC             (_KIF)>>3,      0                    ;(_KIF)>>3: Bank 511    Addr: 65435    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
HADR_0X29:
;
;
;
;
;
;
;
;
;//*******************************定时器T8N中断
;    //if(T8NIE&&T8NIF)		
;    //{	
;
;
;		
;
;		//for(rxi=0;rxi<10;rxi++)
;		//{
;			//if(PA0)//判断口线电平
;			//{
;				//Ture_r++;
;			//}
;		//}
;		//if(Ture_r>=8)//高电平
;		//{
;			//Ture_f=1;
;		//}
;		//else//低电平
;		//{
;			//if(Ture_f)
;			//{
;	   			//Ture_f=0;
;				//pulse_num_r++;
;			//}
;		//}
;
;		//if(++time_1s_r>=10000)
;		//{
;			//time_1s_r=0;
;			//frequency_r=pulse_num_r;//程序中直接调用frequency_r使用。
;			//TDS_temp[1]=pulse_num_r;
;			//pulse_num_r=pulse_num_r>>8;
;			//TDS_temp[0]=pulse_num_r;
;				//pulse_num_r=0;
;		//}
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;	    //t1=PA0;				      //进入T8N定时器中断
;		//if(t0==t1)
;		//{
;			//if(TDS_cnt<65535)
;			//TDS_cnt++;	
;		//}
;		//else if(t0!=t1)
;		//{
;			//flag=1;
;			//t0=t1;
;			//TDS_period1=TDS_cnt;
;			//TDS_cnt=0;
;
;		//}
;		//PA1 = ~PA1;	   //输出端口取反
;		/*T_old=T_new;
;		T_new=PA0;
;		if(T_old==0&&T_new==1)
;		{
;				T_upcnt++;
;
;		}
;
;		T2_old=T2_new;
;		T2_new=PA1;
;		if(T2_old==0&&T2_new==1)
;		{
;		
;			T2_upcnt++;
;		
;		
;		}
;		if(T2_upcnt==1)
;		{
;			if(TDS2_cnt<65535)
;			TDS2_cnt++;
;		
;		}
;		else if(T2_upcnt==2)
;		{
;			TDS2_period1=TDS2_cnt;
;			T2_upcnt=0;
;			TDS2_cnt=0;
;			flag2=1;
;
;		}
;
;		
;            
;
;		if(T_upcnt==1)
;		{
;			if(TDS_cnt<65535)
;			TDS_cnt++;
;		
;		}
;		else if(T_upcnt==2)
;		{
;			TDS_period1=TDS_cnt;
;			T_upcnt=0;
;			TDS_cnt=0;
;			flag=1;
;		}*/
;        //T8NIF = 0;      //清T8N中断标志
;       //T8N = T8N + 223;	//重载T8N初值，加上进入中断时间
;				 ////T8N = T8N + 230;
;    //}
;    //else
;    //{
;        //T8NIF = 0;
;    //}
;//*******************************时基定时器T8P1中断
;	if(T8P1IF)
:0X29  929b                     JBS             HRAM_0X9B,      2
:0X2a  6866                     GOTO            HADR_0X66
;	{
;		T8P1IF=0;
:0X2b  aa9b                     BCC             (_T8P1IF)>>3,   2                    ;(_T8P1IF)>>3: Bank 511    Addr: 65435    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;		//PA1 = ~PA1;	   //输出端口取反
;		 
;		if(T8N>=0x7f)
:0X2c  e57f                     MOVI            0X7F
:0X2d  eebb                     SUB             _T8N,           A                    ;_T8N: Bank 511    Addr: 65467    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X2e  9084                     JBS             HRAM_0X84,      0
:0X2f  683c                     GOTO            HADR_0X3C
;		{
;			test_f=test_f+T8N;
:0X30  50bb                     MOV             _T8N,           A                    ;_T8N: Bank 511    Addr: 65467    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X31  203c                     MOVAR           _isrDATA                             ;_isrDATA: Bank 0    Addr: 60    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X32  ea00                     SECTION         0X0
:0X33  e73d                     CLR             (_isrDATA+1)&7f                      ;(_isrDATA+1)&7f: Bank 0    Addr: 61    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X34  783c                     MOVRA           _isrDATA                             ;_isrDATA: Bank 0    Addr: 60    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X35  ea02                     SECTION         0X2
:0X36  5e04                     ADD             (_test_f)&7f,   A                    ;(_test_f)&7f: Bank 0    Addr: 4     
:0X37  2104                     MOVAR           _test_f                              ;_test_f: Bank 2    Addr: 260     
:0X38  783d                     MOVRA           _isrDATA+1                           ;_isrDATA+1: Bank 0    Addr: 61    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X39  1405                     ADDC            (_test_f+1)&7f, A                    ;(_test_f+1)&7f: Bank 0    Addr: 5     
:0X3a  2105                     MOVAR           _test_f+1                            ;_test_f+1: Bank 2    Addr: 261     
;			T8N=0;
:0X3b  e7bb                     CLR             _T8N                                 ;_T8N: Bank 511    Addr: 65467    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
HADR_0X3C:
;		}
:0X3c  ea02                     SECTION         0X2
:0X3d  5506                     INC             (_test_cnt)&7f, R                    ;(_test_cnt)&7f: Bank 0    Addr: 6     
:0X3e  9a84                     JBC             HRAM_0X84,      2
:0X3f  5507                     INC             (_test_cnt+1)&7f,               R    ;(_test_cnt+1)&7f: Bank 0    Addr: 7     
;		if(test_cnt>=1000)
:0X40  e503                     MOVI            0X3
:0X41  ee07                     SUB             (_test_cnt+1)&7f,               A    ;(_test_cnt+1)&7f: Bank 0    Addr: 7     
:0X42  9284                     JBS             HRAM_0X84,      2
:0X43  6846                     GOTO            HADR_0X46
:0X44  e5e8                     MOVI            0XE8
:0X45  ee06                     SUB             (_test_cnt)&7f, A                    ;(_test_cnt)&7f: Bank 0    Addr: 6     
HADR_0X46:
:0X46  9084                     JBS             HRAM_0X84,      0
:0X47  6866                     GOTO            HADR_0X66
;		{
;			test_f=test_f+T8N;
:0X48  50bb                     MOV             _T8N,           A                    ;_T8N: Bank 511    Addr: 65467    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X49  203c                     MOVAR           _isrDATA                             ;_isrDATA: Bank 0    Addr: 60    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X4a  ea00                     SECTION         0X0
:0X4b  e73d                     CLR             (_isrDATA+1)&7f                      ;(_isrDATA+1)&7f: Bank 0    Addr: 61    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X4c  783c                     MOVRA           _isrDATA                             ;_isrDATA: Bank 0    Addr: 60    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X4d  ea02                     SECTION         0X2
:0X4e  5e04                     ADD             (_test_f)&7f,   A                    ;(_test_f)&7f: Bank 0    Addr: 4     
:0X4f  2104                     MOVAR           _test_f                              ;_test_f: Bank 2    Addr: 260     
:0X50  783d                     MOVRA           _isrDATA+1                           ;_isrDATA+1: Bank 0    Addr: 61    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X51  1405                     ADDC            (_test_f+1)&7f, A                    ;(_test_f+1)&7f: Bank 0    Addr: 5     
:0X52  2105                     MOVAR           _test_f+1                            ;_test_f+1: Bank 2    Addr: 261     
;			TDS1_frequency=test_f;
:0X53  7904                     MOVRA           _test_f                              ;_test_f: Bank 2    Addr: 260     
:0X54  2188                     MOVAR           _TDS1_frequency                      ;_TDS1_frequency: Bank 3    Addr: 392     
:0X55  7905                     MOVRA           _test_f+1                            ;_test_f+1: Bank 2    Addr: 261     
:0X56  2189                     MOVAR           _TDS1_frequency+1                    ;_TDS1_frequency+1: Bank 3    Addr: 393     
;			//TDS_temp[1]=test_f;
;			//test_f=test_f>>8;
;			//TDS_temp[0]=test_f;
;
;			//frequency_r=pulse_num_r;//程序中直接调用frequency_r使用。
;			TDS2_frequency=pulse_num_r;//程序中直接调用frequency_r使用。
:0X57  7883                     MOVRA           _pulse_num_r                         ;_pulse_num_r: Bank 1    Addr: 131     
:0X58  218a                     MOVAR           _TDS2_frequency                      ;_TDS2_frequency: Bank 3    Addr: 394     
:0X59  7884                     MOVRA           _pulse_num_r+1                       ;_pulse_num_r+1: Bank 1    Addr: 132     
:0X5a  218b                     MOVAR           _TDS2_frequency+1                    ;_TDS2_frequency+1: Bank 3    Addr: 395     
;			pulse_num_r=0;
:0X5b  ea01                     SECTION         0X1
:0X5c  e703                     CLR             (_pulse_num_r)&7f                    ;(_pulse_num_r)&7f: Bank 0    Addr: 3     
:0X5d  e704                     CLR             (_pulse_num_r+1)&7f                  ;(_pulse_num_r+1)&7f: Bank 0    Addr: 4     
;			T8N=0;
:0X5e  e7bb                     CLR             _T8N                                 ;_T8N: Bank 511    Addr: 65467    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;			test_f=0;
:0X5f  ea02                     SECTION         0X2
:0X60  e704                     CLR             (_test_f)&7f                         ;(_test_f)&7f: Bank 0    Addr: 4     
:0X61  e705                     CLR             (_test_f+1)&7f                       ;(_test_f+1)&7f: Bank 0    Addr: 5     
;			test_cnt=0;
:0X62  e706                     CLR             (_test_cnt)&7f                       ;(_test_cnt)&7f: Bank 0    Addr: 6     
:0X63  e707                     CLR             (_test_cnt+1)&7f                     ;(_test_cnt+1)&7f: Bank 0    Addr: 7     
;
;			flag=1;
:0X64  ea00                     SECTION         0X0
:0X65  a33e                     BSS             ((_flag)>>3)&7f,                3    ;((_flag)>>3)&7f: Bank 0    Addr: 62     
HADR_0X66:
;
;
;
;		}
;		
;	}
:0X66  939b                     JBS             HRAM_0X9B,      3
:0X67  686a                     GOTO            HADR_0X6A
;	{
;		T8P2IF=0;
:0X68  ab9b                     BCC             (_T8P2IF)>>3,   3                    ;(_T8P2IF)>>3: Bank 511    Addr: 65435    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	//PA1 = ~PA1;	   //输出端口取反
;		
;	
;		PA5=~PA5;
:0X69  2daa                     BTT             (_PA5)>>3,      5                    ;(_PA5)>>3: Bank 511    Addr: 65450    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
HADR_0X6A:
;		
;	}
;	
;//*******************************串口通讯中断
;	
;  /*if(RXIE&&RXIF)   
;	{  
;		RXIF = 0;  //清接收中断标志位
;		RecData = RXB;  //读取接收字节
;		ProcessUARTData(RecData);
;		
;	}  */           
;
;
;
;
;}
:0X6a  ea00                     SECTION         0X0
:0X6b  686c                     GOTO            HADR_0X6C
HADR_0X6C:
:0X6c  ffff                     NOP
:0X6d  ffff                     NOP
:0X6e  5002                     MOV             HRAM_0X2,       A
:0X6f  e630                     MOVA            HRAM_0X30
:0X70  5003                     MOV             HRAM_0X3,       A
:0X71  e631                     MOVA            HRAM_0X31
:0X72  5004                     MOV             HRAM_0X4,       A
:0X73  e632                     MOVA            HRAM_0X32
:0X74  5005                     MOV             HRAM_0X5,       A
:0X75  e633                     MOVA            HRAM_0X33
:0X76  5037                     MOV             (CSEG_PTR+3)&7f,                A    ;(CSEG_PTR+3)&7f: Bank 0    Addr: 55     
:0X77  e635                     MOVA            (CSEG_PTR+1)&7f                      ;(CSEG_PTR+1)&7f: Bank 0    Addr: 53     
:0X78  5036                     MOV             (CSEG_PTR+2)&7f,                A    ;(CSEG_PTR+2)&7f: Bank 0    Addr: 54     
:0X79  e634                     MOVA            (CSEG_PTR)&7f                        ;(CSEG_PTR)&7f: Bank 0    Addr: 52     
:0X7a  5041                     MOV             (MUL_TEMP+2)&7f,                A    ;(MUL_TEMP+2)&7f: Bank 0    Addr: 65     
:0X7b  e63f                     MOVA            (MUL_TEMP)&7f                        ;(MUL_TEMP)&7f: Bank 0    Addr: 63     
:0X7c  e688                     MOVA            HRAM_0X88
:0X7d  5042                     MOV             (MUL_TEMP+3)&7f,                A    ;(MUL_TEMP+3)&7f: Bank 0    Addr: 66     
:0X7e  e640                     MOVA            (MUL_TEMP+1)&7f                      ;(MUL_TEMP+1)&7f: Bank 0    Addr: 64     
:0X7f  e689                     MOVA            HRAM_0X89
:0X80  5001                     MOV             (SAVED_FSR+1)&7f,               A    ;(SAVED_FSR+1)&7f: Bank 0    Addr: 1    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X81  e682                     MOVA            HRAM_0X82
:0X82  5000                     MOV             (SAVED_FSR)&7f, A                    ;(SAVED_FSR)&7f: Bank 0    Addr: 0    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X83  e681                     MOVA            HRAM_0X81
:0X84  c181                     POP
:0X85  c189                     RETIE
HADR_0X86:
;void main() 
;{
;
;     delay(1500);
:0X86  e783                     CLR             HRAM_0X83
:0X87  e5dc                     MOVI            0XDC
:0X88  2038                     MOVAR           _delayDATA                           ;_delayDATA: Bank 0    Addr: 56     
:0X89  e505                     MOVI            0X5
:0X8a  2039                     MOVAR           _delayDATA+1                         ;_delayDATA+1: Bank 0    Addr: 57     
:0X8b  ec00                     PAGE            (_delay)>>11
:0X8c  60ec                     CALL            HADR_0XEC
:0X8d  ec00                     PAGE            (_25)>>11
;	Iint();
:0X8e  ec00                     PAGE            (_Iint)>>11
:0X8f  61d4                     CALL            HADR_0X1D4
:0X90  ec00                     PAGE            (_26)>>11
;	 frequency_sum_flag=1;
:0X91  a43e                     BSS             ((_frequency_sum_flag)>>3)&7f,  4    ;((_frequency_sum_flag)>>3)&7f: Bank 0    Addr: 62     
;	 //Send_Buf[0]=0x55;
;	  //Send_Buf[1]=0x78;
;	  putchar_step=0;
:0X92  ea03                     SECTION         0X3
:0X93  e715                     CLR             (_putchar_step)&7f                   ;(_putchar_step)&7f: Bank 0    Addr: 21     
;	  temp_p=0;
:0X94  ea00                     SECTION         0X0
:0X95  e706                     CLR             (_temp_p)&7f                         ;(_temp_p)&7f: Bank 0    Addr: 6     
:0X96  e707                     CLR             (_temp_p+1)&7f                       ;(_temp_p+1)&7f: Bank 0    Addr: 7     
;	  POWERSTART_cnt=0;
:0X97  ea03                     SECTION         0X3
:0X98  e707                     CLR             (_POWERSTART_cnt)&7f                 ;(_POWERSTART_cnt)&7f: Bank 0    Addr: 7     
;	  giWIFICommand=0x2000;	
:0X99  e500                     MOVI            0X0
:0X9a  2196                     MOVAR           _giWIFICommand                       ;_giWIFICommand: Bank 3    Addr: 406     
:0X9b  e520                     MOVI            0X20
:0X9c  2197                     MOVAR           _giWIFICommand+1                     ;_giWIFICommand+1: Bank 3    Addr: 407     
;			
;	 
;	
;	  a=11;
:0X9d  e50b                     MOVI            0XB
:0X9e  218e                     MOVAR           _a                                   ;_a: Bank 3    Addr: 398     
;	  b=612;
:0X9f  e564                     MOVI            0X64
:0Xa0  218f                     MOVAR           _b                                   ;_b: Bank 3    Addr: 399     
:0Xa1  e502                     MOVI            0X2
:0Xa2  2190                     MOVAR           _b+1                                 ;_b+1: Bank 3    Addr: 400     
;	   RCEN=1;
:0Xa3  a1a9                     BSS             (_RCEN)>>3,     1                    ;(_RCEN)>>3: Bank 511    Addr: 65449    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	   WDTC=0xff;
:0Xa4  e5ff                     MOVI            0XFF
:0Xa5  e6a7                     MOVA            _WDTC                                ;_WDTC: Bank 511    Addr: 65447    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	    
;
;	 
;	   callwdt();
:0Xa6  c18b                     CWDT
HADR_0XA7:
;
;
;	while(1)
:0Xa7  acac                     BCC             (_PB4)>>3,      4                    ;(_PB4)>>3: Bank 511    Addr: 65452    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;		 
;			ADC();
:0Xa8  ec00                     PAGE            (_ADC)>>11
:0Xa9  ea00                     SECTION         0X0
:0Xaa  61ea                     CALL            HADR_0X1EA
:0Xab  ec00                     PAGE            (_27)>>11
;		
;			TDS_DEL();
:0Xac  ec00                     PAGE            (_TDS_DEL)>>11
:0Xad  6251                     CALL            HADR_0X251
:0Xae  ec00                     PAGE            (_28)>>11
;			Timer();
:0Xaf  ec00                     PAGE            (_Timer)>>11
:0Xb0  630a                     CALL            HADR_0X30A
:0Xb1  ec00                     PAGE            (_29)>>11
;		//if(giWIFICommand==0x2000)	 
;			//UART();
;		if(POWERSTART_cnt>8)
:0Xb2  7987                     MOVRA           _POWERSTART_cnt                      ;_POWERSTART_cnt: Bank 3    Addr: 391     
:0Xb3  ce08                     SUBI            0X8
:0Xb4  9884                     JBC             HRAM_0X84,      0
:0Xb5  68b9                     GOTO            HADR_0XB9
;			UART_putchar();
:0Xb6  ec00                     PAGE            (_UART_putchar)>>11
:0Xb7  62ba                     CALL            HADR_0X2BA
:0Xb8  ec00                     PAGE            (_2a)>>11
HADR_0XB9:
;		 callwdt();
:0Xb9  c18b                     CWDT
;		
;	}
:0Xba  68a7                     GOTO            HADR_0XA7
HADR_0XBB:
:0Xbb  5f86                     ADD             HRAM_0X86,      R
:0Xbc  e402                     RETIA           0X2
:0Xbd  e480                     RETIA           SECTION1IG__5_23_1211_HRCC_Project_Application1_HRCC_Project_Application1_sample_c488_i
:0Xbe  e402                     RETIA           0X2
:0Xbf  e400                     RETIA           0X0
:0Xc0  e400                     RETIA           0X0
:0Xc1  e482                     RETIA           SECTION1IG__5_23_1211_HRCC_Project_Application1_HRCC_Project_Application1_sample_c491_i
:0Xc2  e401                     RETIA           0X1
:0Xc3  e400                     RETIA           0X0
:0Xc4  e400                     RETIA           0X0
HADR_0XC5:
:0Xc5  e783                     CLR             HRAM_0X83
:0Xc6  e500                     MOVI            (#_CINIT)>>8
:0Xc7  e687                     MOVA            HRAM_0X87
:0Xc8  e500                     MOVI            0X0
:0Xc9  e630                     MOVA            ?_TMP                                ;?_TMP: Bank 0    Addr: 48     
:0Xca  5030                     MOV             ?_TMP,          A                    ;?_TMP: Bank 0    Addr: 48     
:0Xcb  ec00                     PAGE            (#_CINIT)>>11
:0Xcc  60bb                     CALL            HADR_0XBB
:0Xcd  e631                     MOVA            ?_TMP+1                              ;?_TMP+1: Bank 0    Addr: 49     
:0Xce  5131                     MOV             ?_TMP+1,        R                    ;?_TMP+1: Bank 0    Addr: 49     
:0Xcf  9a84                     JBC             HRAM_0X84,      2
:0Xd0  c183                     RET
HADR_0XD1:
:0Xd1  5530                     INC             ?_TMP,          R                    ;?_TMP: Bank 0    Addr: 48     
:0Xd2  5030                     MOV             ?_TMP,          A                    ;?_TMP: Bank 0    Addr: 48     
:0Xd3  ec00                     PAGE            (#_CINIT)>>11
:0Xd4  60bb                     CALL            HADR_0XBB
:0Xd5  e632                     MOVA            ?_TMP+2                              ;?_TMP+2: Bank 0    Addr: 50     
:0Xd6  5530                     INC             ?_TMP,          R                    ;?_TMP: Bank 0    Addr: 48     
:0Xd7  5030                     MOV             ?_TMP,          A                    ;?_TMP: Bank 0    Addr: 48     
:0Xd8  ec00                     PAGE            (#_CINIT)>>11
:0Xd9  60bb                     CALL            HADR_0XBB
:0Xda  e633                     MOVA            ?_TMP+3                              ;?_TMP+3: Bank 0    Addr: 51     
:0Xdb  60df                     CALL            HADR_0XDF
:0Xdc  5731                     JDEC            HRAM_0X31,      R
:0Xdd  68d1                     GOTO            HADR_0XD1
:0Xde  c183                     RET
HADR_0XDF:
:0Xdf  5032                     MOV             ?_TMP+2,        A                    ;?_TMP+2: Bank 0    Addr: 50     
:0Xe0  e681                     MOVA            HRAM_0X81
:0Xe1  e500                     MOVI            0X0
:0Xe2  e682                     MOVA            HRAM_0X82
:0Xe3  5530                     INC             ?_TMP,          R                    ;?_TMP: Bank 0    Addr: 48     
:0Xe4  5030                     MOV             ?_TMP,          A                    ;?_TMP: Bank 0    Addr: 48     
:0Xe5  ec00                     PAGE            (#_CINIT)>>11
:0Xe6  60bb                     CALL            HADR_0XBB
:0Xe7  e680                     MOVA            HRAM_0X80
:0Xe8  5532                     INC             ?_TMP+2,        R                    ;?_TMP+2: Bank 0    Addr: 50     
:0Xe9  5733                     JDEC            HRAM_0X33,      R
:0Xea  68df                     GOTO            HADR_0XDF
:0Xeb  c183                     RET
HADR_0XEC:
;
;#include <hic.h>
;
;#define Len 10/*TDS频率计数存储数组长度*/
;#define CHCEK_len  4
;#define frequency_sum_len 9/*TDS频率计数存储数组存储的数组次数*/
;#define uint8        unsigned char
;#define uint16        unsigned int
;#define	CYBIT		sbit
;
;
;#define callwdt()	__Asm CWDT
;
;sbit Timer2ms_flag;
;section3  unsigned int Timer1S_cnt;
;section3  unsigned int test1S_cnt;
;sbit Timer1S_flag;
;sbit TimeOn_flag;
;sbit T_old;
;sbit T_new;
;sbit T2_old;
;sbit T2_new;
;sbit T_timeOn_flag;
;sbit up_pluse_f;
;CYBIT POWER_flag;
;section2 unsigned char i;
;section2 unsigned char T_upcnt;
;sbit flag;
;sbit flag2;
;section3 unsigned int TDS_cnt;
;section3 unsigned int ADCRH1; //AD转换结果
;section3 unsigned char ADcnt;
;section3 unsigned int ADsum;
;section2 unsigned int ADture;
;section3 unsigned int ADCRH1_WD; //AD转换结果
;section3 unsigned char ADcnt_WD;
;section3 unsigned int ADsum_WD;
;section2 unsigned int ADture_WD;
;
;
;section2 unsigned int test_f;
;section2 unsigned int test_ftemp;
;section2 unsigned int test_cnt;
;
;//long  TDS_sum;
;
;//**********************************计时相关
;section3  uint8 POWERSTART_cnt;
;
;uint16 watch_TDS(unsigned int fey);
;
;//*******************************频率相关
;section3 unsigned int TDS_ture;
;section3 unsigned char frequency_cnt;
;section3 unsigned char TDS_temp[2];
;section3 unsigned int TDS1_frequency;
;section3 unsigned int TDS2_frequency;
;section3 unsigned int TDSfrequency_temp;
;section3 unsigned int TDSfrequency_temp_yushu;
;section3  unsigned int TDS1_sum;
;section3  unsigned int TDS2_sum;
;section3  unsigned int TDS1_ture;
;section3  unsigned int TDS2_ture;
;section2  unsigned int uartsendcnt;
;section2 unsigned char frequency_sum_cnt;
;
;section3 uint8 a;
;section3	uint16 b;
;//unsigned int TDS_period1;
;//section3 unsigned int TDS_period2;
;//section3 unsigned int TDS2_period1;
;//section3 unsigned int TDS2_cnt;
;//section3 unsigned int TDS2_period2;
;section3 uint16 TDS_IN_ture;
;section3 uint16 TDS_OUT_ture;
;section3 uint8 T2_upcnt;
;section3  uint8 TDSchcek_num;
;section3 uint8 CHECK_step;
;section1 uint8 CHECK_buff[2]={0x00,0x00};
;sbit frequency_sum_flag;
;
;section1 unsigned char rxi,Ture_r=0;
;section1 unsigned int pulse_num_r,frequency_r,time_1s_r;
;sbit Ture_f;
;section2 unsigned int temp_frequency[Len];
;//************************************第1个表
;const unsigned int TDS_data1[98]={36,38,40,43,45,47,50,52,54,56,59,61,63,66,68,70,73,75,77,79,82,84,86,89,91,93,96,98,100,102,105,107,109,111,114,116,118,121,123,125,127,130,132,134,136,139,141,143,146,148,150,152,155,157,159,161,164,166,168,170,173,175,177,179,182,184,186,188,191,193,195,197,199,202,204,206,208,211,213,215,217,220,222,224,226,228,231,233,235,237,239,242,244,246,248,250,253,255};
;const unsigned int  TDS_data2[333]={257,259,261,264,266,268,270,272,275,277,279,281,283,286,288,290,292,294,297,299,301,303,305,307,310,312,314,316,318,320,323,325,327,329,331,333,336,338,340,342,344,346,348,351,353,355,357,359,361,364,366,368,370,372,374,376,378,381,383,385,387,389,391,393,396,398,400,402,404,406,408,410,412,415,417,419,421,423,425,427,429,431,434,436,438,440,442,444,446,448,450,452,455,457,459,461,463,465,467,469,471,473,475,477,480,482,484,486,488,490,492,494,496,498,500,502,504,506,508,511,513,515,517,519,521,523,525,527,529,531,533,535,537,539,541,543,545,547,549,551,554,556,558,560,562,564,566,568,570,572,574,576,578,580,582,584,586,588,590,592,594,596,598,600,602,604,606,608,610,612,614,616,618,620,622,624,626,628,630,632,634,636,638,640
;                                     ,642,644,646,648,650,652,654,656,658,660,662,664,665,667,669,671,673,675,677,679,681,683,685,687,689,691,693,695,697,699,701,703,705,707,708,710,712,714,716,718,720,722,724,726,728,730,732,734,735,737,739,741,743,745,747,749,751,753,755,757,758,760,762,764,766,768,770,772,774,776,777,779,781,783,785,787,789,791,793,795,796,798,800,802,804,806,808,810,811,813,815,817,819,821,823,825,826,828,830,832,834,836,838,839,841,843,845,847,849,851,852,854,856,858,860,862,863,865,867,869,871,873,874,876,878,880,882,884,885,887,889,891,893,895,896,898,900,902,904,905,907,909,911,913,915,916,918,920,922};
;const unsigned int  TDS_data3[267]={924,925,927,929,931,933,934,936,938,940,942,943,945,947,949,950,952,954,956,958,959,961,963,965,966,968,970,972,974,975,977,979,981,982,984,986,988,989,991,993,995,996,998,1000,1002,1003,1005,1007,1009,1010,1012,1014,1016,1017,1019,1021,1023,1024,1026,1028,1030,1031,1033,1035,1036,1038,1040,1042,1043,1045,1047,1048,1050,1052,1054,1055,1057,1059,1060,1062,1064,1066,1067,1069,1071,1072,1074,1076,1077,1079,1081,1083,1084,1086,1088,1089,1091,1093,1094,1096,1098,1099,1101,1103,1104,1106,1108,1109,1111,1113,1114,1116,1118,1119,1121,1123,1124,1126,1128,1129,1131,1133,1134,1136,1138,1139,1141,1143,1144,1146,1148,1149,1151,1153,1154,1156,1157,1159,1161,1162,1164,1166,1167,1169,1171,1172,1174,1175,1177,1179,1180,1182,1184,1185,1187,1188,1190,1192,1193,1195,1196,1198,1200,1201,1203,1204,1206,1208,1209,1211,1212,1214,1216,1217,1219,1220,1222,1224,1225,1227,1228,1230,1232,1233,1235,1236,1238,1239,1241,1243,1244,1246,1247,1249,1250,1252,1254,1255,1257,1258,1260,1261,1263,1265,1266,1268,1269,1271,1272,1274,1275,1277,1279,1280,1282,1283,1285,1286,1288,1289,1291,1292,1294,1295,1297,1299,1300,1302,1303,1305,1306,1308,1309,1311,1312,1314,1315,1317,1318,1320,1321,1323,1324,1326,1327,1329,1330,1332,1333,1335,1336,1338,1339,1341,1342,1344,1345,1347,1348,1350,1351,1353,1354,1356,1357,1359,1360};
;const unsigned int  TDS_data4[302]={1362,1363,1365,1366,1368,1369,1371,1372,1374,1375,1377,1378,1380,1381,1382,1384,1385,1387,1388,1390,1391,1393,1394,1396,1397,1398,1400,1401,1403,1404,1406,1407,1409,1410,1411,1413,1414,1416,1417,1419,1420,1422,1423,1424,1426,1427,1429,1430,1432,1433,1434,1436,1437,1439,1440,1441,1443,1444,1446,1447,1449,1450,1451,1453,1454,1456,1457,1458,1460,1461,1463,1464,1465,1467,1468,1470,1471,1472,1474,1475,1476,1478,1479,1481,1482,1483,1485,1486,1488,1489,1490,1492,1493,1494,1496,1497,1498,1500,1501,1503,1504,1505,1507,1508,1509,1511,1512,1513,1515,1516,1517,1519,1520,1522,1523,1524,1526,1527,1528,1530,1531,1532,1534,1535,1536,1538,1539,1540,1542,1543,1544,1546,1547,1548,1550,1551,1552,1553,1555,1556,1557,1559,1560,1561,1563,1564,1565,1567,1568,1569,1570,1572,1573,1574,1576,1577,1578,1580,1581,1582,1583,1585,1586,1587,1589,1590,1591,1592,1594,1595,1596,1598,1599,1600,1601,1603,1604,1605,1606,1608,1609,1610,1612,1613,1614,1615,1617,1618,1619,1620,1622,1623,1624,1625,1627,1628,1629,1630,1632,1633,1634,1635,1637,1638,1639,1640,1641,1643,1644,1645,1646,1648,1649,1650,1651,1653,1654,1655,1656,1657,1659,
; 
;                                1660,1661,1662,1664,1665,1666,1667,1668,1670,1671,1672,1673,1674,1676,1677,1678,1679,1680,1682,1683,1684,1685,1686,1688,1689,1690,1691,1692,1693,1695,1696,1697,1698,1699,1701,1702,1703,1704,1705,1706,1708,1709,1710,1711,1712,1713,1715,1716,1717,1718,1719,1720,1721,1723,1724,1725,1726,1727,1728,1730,1731,1732,1733,1734,1735,1736,1738,1739,1740,1741,1742,1743,1744,1745,1747,1748,1749,1750,1751,1752,1753 };
; const unsigned int *temp_p;
;  const unsigned int *TDScheck1;
;   const unsigned int *TDScheck2;
;    const unsigned int *TDScheck3;
;	 const unsigned int *TDScheck4;                                   
;//************************************第5个表
;const unsigned int TDS_data5[98]={47,50,54,57,61,64,68,71,75,78,82,85,89,92,96,99,103,106,110,113,117,120,124,127,131,134,138,141,144,148,151,155,158,162,165,169,172,175,179,182,186,189,193,196,199,203,206,210,213,216,220,223,226,230,233,237,240,243,247,250,253,257,260,263,267,270,274,277,280,284,287,290,294,297,300,303,307,310,313,317,320,323,327,330,333,337,340,343,346,350,353,356,359,363,366,369,373,376};
;const unsigned int TDS_data6[333]={379,382,386,389,392,395,399,402,405,408,411,415,418,421,424,428,431,434,437,440,444,447,450,453,456,459,463,466,469,472,475,479,482,485,488,491,494,497,501,504,507,510,513,516,519,523,526,529,532,535,538,541,544,548,551,554,557,560,563,566,569,572,575,578,581,585,588,591,594,597,600,603,606,609,612,615,618,621,624,627,630,633,636,639,642,645,648,651,654,657,660,663,666,669,672,675,678,681,684,687,690,693,696,699,702,705,708,711,714,717,720,723,726,729,732,735,738,740,743,746,749,752,755,758,761,764,767,770,772,775,778,781,784,787,790,793,796,798,801,804,807,810,813,816,818,821,824,827,830,833,835,838,841,844,847,850,852,855,858,861,864,866,869,872,875,878,880,883,886,889,892,894,897,900,903,905,908,911,914,916,919,922,925,927,930,933,936,938,941,944,947,949,952,955,957,960,963,966,968,971,974,976,979,982,984,987,990,992,995,998,1000,1003,1006,1008,1011,1014,1016,1019,1022,1024,1027,1030,1032,1035,1037,1040,1043,1045,1048,1051,1053,1056,1058,1061,1064,1066,1069,1071,1074,1076,1079,1082,1084,1087,1089,1092,1095,1097,1100,1102,1105,1107,1110,1112,1115,1117,1120,1123,1125,1128,1130,1133,1135,1138,1140,1143,1145,1148,1150,1153,1155,1158,1160,1163,1165
;                                    ,1168,1170,1173,1175,1178,1180,1183,1185,1187,1190,1192,1195,1197,1200,1202,1205,1207,1209,1212,1214,1217,1219,1222,1224,1226,1229,1231,1234,1236,1239,1241,1243,1246,1248,1250,1253,1255,1258,1260,1262,1265,1267,1270,1272,1274,1277,1279,1281,1284,1286,1288,1291,1293,1295,1298,1300,1302,1305};
;const unsigned int TDS_data7[267]={1307,1309,1312,1314,1316,1319,1321,1323,1325,1328,1330,1332,1335,1337,1339,1341,1344,1346,1348,1351,1353,1355,1357,1360,1362,1364,1366,1369,1371,1373,1375,1378,1380,1382,1384,1386,1389,1391,1393,1395,1398,1400,1402,1404,1406,1409,1411,1413,1415,1417,1420,1422,1424,1426,1428,1430,1433,1435,1437,1439,1441,1443,1445,1448,1450,1452,1454,1456,1458,1460,1463,1465,1467,1469,1471,1473,1475,1477,1479,1482,1484,1486,1488,1490,1492,1494,1496,1498,1500,1502,1504,1507,1509,1511,1513,1515,1517,1519,1521,1523,1525,1527,1529,1531,1533,1535,1537,1539,1541,1543,1545,1547,1549,1551,1553,1555,1557,1559,1561,1563,1565,1567,1569,1571,1573,1575,1577,1579,1581,1583,1585,1587,1589,1591,1593,1595,1597,1599,1601,1602,1604,1606,1608,1610,1612,1614,1616,1618,1620,1622,1624,1625,1627,1629,1631,1633,1635,1637,1639,1641,1642,1644,1646,1648,1650,1652,1654,1655,1657,1659,1661,1663,1665,1667,1668,1670,1672,1674,1676,1677,1679,1681,1683,1685,1687,1688,1690,1692,1694,1696,1697,1699,1701,1703,1704,1706,1708,1710,1712,1713,1715,1717,1719,1720,1722,1724,1726,1727,1729,1731,1733,1734,1736,1738,1739,1741,1743,1745,1746,1748,1750,1751,1753,1755,1757,1758,1760,1762,1763,1765,1767,1768,1770,1772,1773,1775,1777,1778,1780,1782,1783,1785,1787,1788,1790,1791,1793,1795,1796,1798,1800,1801,1803,1804,1806,1808,1809,1811,1812,1814,1816,1817,1819,1820,1822,1824,1825};
;const unsigned int TDS_data8[302]={1827,1828,1830,1831,1833,1835,1836,1838,1839,1841,1842,1844,1845,1847,1848,1850,1852,1853,1855,1856,1858,1859,1861,1862,1864,1865,1867,1868,1870,1871,1873,1874,1876,1877,1879,1880,1882,1883,1884,1886,1887,1889,1890,1892,1893,1895,1896,1898,1899,1900,1902,1903,1905,1906,1908,1909,1910,1912,1913,1915,1916,1917,1919,1920,1922,1923,1924,1926,1927,1929,1930,1931,1933,1934,1935,1937,1938,1940,1941,1942,1944,1945,1946,1948,1949,1950,1952,1953,1954,1956,1957,1958,1960,1961,1962,1964,1965,1966,1967,1969,1970,1971,1973,1974,1975,1976,1978,1979,1980,1982,1983,1984,1985,1987,1988,1989,1990,1992,1993,1994,1995,1997,1998,1999,2000,2001,2003,2004,2005,2006,2008,2009,2010,2011,2012,2014,2015,2016,2017,2018,2019,2021,2022,2023,2024,2025,2027,2028,2029,2030,2031,2032,2033,2035,2036,2037,2038,2039,2040,2041,2043,2044,2045,2046,2047,2048,2049,2050,2051,2053,2054,2055,2056,2057,2058,2059,2060,2061,2062,2063,2064,2066,2067,2068,2069,2070,
;	                                 2071,2072,2073,2074,2075,2076,2077,2078,2079,2080,2081,2082,2083,2084,2085,2086,2087,2088,2089,2090,2091,2092,2093,2094,2095,2096,2097,2098,2099,2100,2101,2102,2103,2104,2105,2106,2107,2108,2109,2110,2111,2112,2113,2113,2114,2115,2116,2117,2118,2119,2120,2121,2122,2123,2124,2124,2125,2126,2127,2128,2129,2130,2131,2132,2132,2133,2134,2135,2136,2137,2138,2138,2139,2140,2141,2142,2143,2144,2144,2145,2146,2147,2148,2149,2149,2150,2151,2152,2153,2153,2154,2155,2156,2157,2157,2158,2159,2160,2160,2161,2162,2163,2164,2164,2165,2166,2167,2167,2168,2169,2170,2170,2171,2172,2173,2173};
;	
;//************************************第七个表
;const unsigned int TDS_data9[98]={52,57,61,65,69,73,77,81,85,90,94,98,102,106,110,114,118,122,126,130,134,139,143,147,151,155,159,163,167,171,175,179,183,187,191,195,199,203,207,211,215,219,223,227,231,235,239,243,247,251,255,259,263,267,271,274,278,282,286,290,294,298,302,306,310,314,318,321,325,329,333,337,341,345,349,353,356,360,364,368,372,376,380,383,387,391,395,399,403,406,410,414,418,422,425,429,433,437};	
;const unsigned int TDS_data10[332]={441,444,448,452,456,459,463,467,471,474,478,482,486,489,493,497,501,504,508,512,515,519,523,527,530,534,538,541,545,549,552,556,560,563,567,571,574,578,582,585,589,593,596,600,604,607,611,614,618,622,625,629,632,636,640,643,647,650,654,657,661,665,668,672,675,679,682,686,689,693,697,700,704,707,711,714,718,721,725,728,732,735,739,742,746,749,753,756,760,763,766,770,773,777,780,784,787,791,794,797,801,804,808,811,815,818,821,825,828,832,835,838,842,845,848,852,855,859,862,865,869,872,875,879,882,885,889,892,895,899,902,905,909,912,915,918,922,925,928,932,935,938,941,945,948,951,955,958,961,964,968,971,974,977,981,984,987,990,993,997,1000,1003,1006,1009,1013,1016,1019,1022,1025,1029,1032,1035,1038,1041,1044,1048,1051,1054,1057,1060,1063,1066,1070,1073,1076,1079,1082,1085,1088,1091,1094,1098,1101,1104,1107,1110,1113,1116,1119,1122,1125,1128,1131,1134,1137,1141,1144,1147,1150,1153,1156,1159,1162,1165,1168,1171,1174,1177,1180,1183,1186,1189,1192,1195,1198,1201,1204,1207,1210,1213,1216,1218,1221,1224,1227,1230,1233,1236,1239,1242,1245,1248,1251,1254,1257,1259,1262,1265,1268,1271,1274,1277,1280,1283,1285,1288,1291,1294,1297,1300,1303,1305,1308,1311,1314,1317,1320,1322,1325,1328,1331,
;                                    1334,1336,1339,1342,1345,1348,1350,1353,1356,1359,1362,1364,1367,1370,1373,1375,1378,1381,1384,1386,1389,1392,1395,1397,1400,1403,1405
;									,1408,1411,1414,1416,1419,1422,1424,1427,1430,1432,1435,1438,1440,1443,1446,1448,1451,1454,1456,1459,1462,1464,1467,1470,
;									1472,1475,1477,1480,1483,1485,14881490,1493,1496,1498};	
;const unsigned int TDS_data11[267]={1501,1503,1506,1509,1511,1514,1516,1519,1521,1524,1527,1529,1532,1534,1537,1539,1542,1544,1547,1549,1552,1554,1557,1559,1562,1564,1567,1569,1572,1574,1577,1579,1582,1584,1587,1589,1592,1594,1596,1599,1601,1604,1606,1609,1611,1614,1616,1618,1621,1623,1626,1628,1630,1633,1635,1638,1640,1642,1645,1647,1649,1652,1654,1657,1659,1661,1664,1666,1668,1671,1673,1675,1678,1680,1682,1685,1687,1689,1692,1694,1696,1698,1701,1703,1705,1708,1710,1712,1714,1717,1719,1721,1723,1726,1728,1730,1732,1735,1737,1739,1741,1744,1746,1748,1750,1752,1755,1757,1759,1761,1763,1766,1768,1770,1772,1774,1776,1779,1781,1783,1785,1787,1789,1792,1794,1796,1798,1800,1802,1804,1806,1809,1811,1813,1815,1817,1819,1821,1823,1825,1827,1830,1832,1834,1836,1838,1840,1842,1844,1846,1848,1850,1852,1854,1856,1858,1860,1862,1864,1866,1868,1870,1872,1874,1876,1878,1880,1882,1884,1886,1888,1890,1892
;                                     ,1894,1896,1898,1900,1902,1904,1906,1908,1910,1912,1914,1916,1917,1919,1921,1923,1925,1927,1929,1931,1933,1935,1936,1938,1940,1942,1944,1946,1948,1950,1951,1953,1955,1957,1959,1961,1962,1964,1966,1968,1970,1972,1973,1975,1977,1979,1981,1982,1984,1986,1988,1990,1991,1993,1995,1997,1998,2000,2002,2004,2005,2007,2009,2011,2012,2014,2016,2018,2019,2021,2023,2024,2026,2028,2029,2031,2033,2035,2036,2038,2040,2041,2043,2045,2046,2048,2050,2051,2053,2055,2056,2058,2059,2061};
; const unsigned int TDS_data12[302]={2063,2064,2066,2068,2069,2071,2072,2074,2076,2077,2079,2080,2082,2083,2085,2087,2088,2090,2091,2093,2094,2096,2098,2099,2101,2102,2104,2105,2107,2108,2110,2111,2113,2114,2116,2117,2119,2120,2122,2123,2125,2126,2128,2129,2131,2132,2134,2135,2136,2138,2139,2141,2142,2144,2145,2147,2148,2149,2151,2152,2154,2155,2156,2158,2159,2161,2162,2163,2165,2166,2168,2169,2170,2172,2173,2174,2176,2177,2178,2180,2181,2182,2184,2185,2186,2188,2189,2190,2192,2193,2194,2196,2197,2198,2199,2201,2202,2203,2205,2206,2207,2208,2210,2211,2212,2213,2215,2216,2217,2218,2219,2221,2222,2223,2224,2226,2227,2228,2229,2230,2232,2233,2234,2235,2236,2238,2239,2240,2241,2242,2243,2244,2246,2247,2248,2249,2250,2251,2252,2254,2255,2256,2257,2258,2259,2260,2261,2262,2264,2265,2266,2267,2268,2269,2270,2271,2272,2273,2274,2275,2276,2277,2278,2280,2281,2282,2283,2284,2285,2286,2287,2288,2289,2290,2291,2292,2293,2294,2295,2296,2297,2298,2299,2300,2300,2301,2302,2303,2304,2305,2306,2307,2308,2309,2310,2311,2312,2313,2314,2314,2315,2316,2317,2318,2319,2320,2321,2322,2323,2323,2324,2325,2326,2327,2328,2329,2329,2330,2331,2332,2333,2334,2334,2335,2336,2337,2338,2338,2339,2340,2341,2342,2342,2343,2344,2345,2346,2346,2347,2348,2349,2349,2350,2351,2352,2352,2353,2354,2355,2355,2356,2357,2358,2358,2359,2360,2360,2361,2362,2362,2363,2364,2365,2365,2366,2367,2367,2368,2369,2369,2370,2370,2371,2372,2372,2373,2374,2374,2375,2376,2376,2377,2377,2378,2379,2379,2380,2380,2381,2382,2382,2383,2383,2384,2384,2385,2386,2386,2387,2387,2388,2388};   
;//************************************第9个表 
; const unsigned int TDS_data13[98]={61,66,71,76,81,86,91,96,101,106,111,116,121,126,131,136,141,146,151,156,161,166,171,176,181,185,190,195,200,205,210,215,220,225,230,234,239,244,249,254,259,264,269,273,278,283,288,293,297,302,307,312,317,322,326,331,336,341,345,350,355,360,364,369,374,379,383,388,393,398,402,407,412,416,421,426,430,435,440,444,449,454,458,463,468,472,477,482,486,491,495,500,505,509,514,518,523,528};
; const unsigned int TDS_data14[333]={532,537,541,546,550,555,560,564,569,573,578,582,587,591,596,600,605,609,614,618,623,627,632,636,641,645,650,654,658,663,667,672,676,681,685,689,694,698,703,707,711,716,720,725,729,733,738,742,746,751,755,759,764,768,772,777,781,785,789,794,798,802,807,811,815,819,824,828,832,836,841,845,849,853,858,862,866,870,874,879,883,887,891,895,900,904,908,912,916,920,925,929,933,937,941,945,949,953,958,962,966,970,974,978,982,986,990,994,998,1002,1006,1010,1014,1019,1023,1027,1031,1035,1039,1043,1047,1051,1055,1059,1063,1067,1071,1075,1078,1082,1086,1090,1094,1098,1102,1106,1110,1114,1118,1122,1126,1130,1133,1137,1141,1145,1149,1153,1157,1161,1164,1168,1172,1176,1180,1184,1187,1191,1195,1199,1203,1207,1210,1214,1218,1222,1226,1229,1233,1237,1241,1244,1248,1252,1256,1259,1263,1267,1271,1274,1278,1282,1285,1289,1293,1296,1300,1304,1307,1311,1315,1318,1322,1326,1329,1333,1337,1340,1344,1348,1351,1355,1358,1362,1366,1369,1373,1376,1380,1384,1387,1391,1394,1398,1401,1405,1408,1412,1415,1419,1423,1426,1430,1433,1437,1440,1444,1447,1451,1454,1457,1461,1464,1468,1471,1475,1478
;                                      ,1482,1485,1489,1492,1495,1499,1502,1506,1509,1512,1516,1519,1523,1526,1529,1533,1536,1539,1543,1546,1549,1553,1556,1559,1563,1566,1569,1573,1576,1579,1583,1586,1589,1592,1596,1599,1602
;									  ,1606,1609,1612,1615,1619,1622,1625,1628,1631,1635,1638,1641,1644,1648,1651,1654,1657,1660,1663,1667,1670,1673,1676,1679,1682,1686,1689,1692,1695,1698,1701,1704,
;									  1707,1710,1714,1717,1720,1723,1726,1729,1732,1735,1738,1741,1744,1747,1750,1753,1756,1759,1763,1766,1769,1772,1775,1778,1781,1784,1787};
; const unsigned int TDS_data15[267]={1790,1792,1795,1798,1801,1804,1807,1810,1813,1816,1819,1822,1825,1828,1831,1834,1837,1839,1842,1845,1848,1851,1854,1857,1860,1862,1865,1868,1871,1874,1877,1879,1882,1885,1888,1891,1894,1896,1899,1902,1905,1908,1910,1913,1916,1919,1921,1924,1927,1930,1932,1935,1938,1941,1943,1946,1949,1951,1954,1957,1959,1962,1965,1967,1970,1973,1975,1978,1981,1983,1986,1989,1991,1994,1997,1999,2002,2004,2007,2010,2012,2015,2017,2020,2023,2025,2028,2030,2033,2035,2038,2040,2043,2046,2048,2051,2053,2056,2058,2061,2063,2066,2068,2071,2073,2076,
;                                     2078,2080,2083,2085,2088,2090,2093,2095,2098,2100,2102,2105,2107,2110,2112,2115,2117,2119,2122,2124,2126,2129,2131,2134,2136,2138,2141,2143,2145,2148,2150,2152,2155,2157,2159,2161,2164,2166,2168,2171,2173,2175,2177,2180,2182,2184,2186,2189,2191,2193,2195,2198,2200,2202,2204,2206,2209,2211,2213,2215,2217,2220,2222,2224,2226,2228,2230,2233,2235,2237,2239,2241,2243,2245,2247,2250,2252,2254,2256,2258,2260,2262,2264,2266,2268,2270,2272,2275,2277,2279,2281,2283,2285,2287,2289,2291,2293,2295,2297,2299,2301,2303,2305,2307,2309,2311,2313,2315,2317,2318,2320,2322,2324,2326,2328,2330,2332,2334,2336,2338,2340,2341,2343,2345,2347,2349,2351,2353,2355,2356,2358,2360,2362,
;									 2364,2366,2367,2369,2371,2373,2375,2376,2378,2380,2382,2384,2385,2387,2389,2391,2392,2394,2396,2398,2399,2401,2403,2405,2406,2408,2410,2411};
;const unsigned int TDS_data16[302]={2413,2415,2416,2418,2420,2422,2423,2425,2427,2428,2430,2431,2433,2435,2436,2438,2440,2441,2443,2444,2446,2448,2449,2451,2452,2454,2456,2457,2459,2460,2462,2463,2465,2466,2468,2469,2471,2473,2474,2476,2477,2479,2480,2482,2483,2485,2486,2487,2489,2490,2492,2493,2495,2496,2498,2499,2500,2502,2503,2505,2506,2508,2509,2510,2512,2513,2515,2516,2517,2519,2520,2521,2523,2524,2525,2527,2528,2529,2531,2532,2533,2535,2536,2537,2539,2540,2541,2542,2544,2545,2546,2547,2549,2550,2551,2552,2554,2555,2556,2557,2559,2560,2561,2562,2563,2565,2566,2567,2568,2569,2570,2572,2573,2574,2575,2576,2577,2579,2580,2581,2582,2583,2584,2585,2586,2587,2589,2590,2591,2592,2593,2594,2595,2596,2597,2598,2599,2600,2601,2602,2603,2604,2605,2606,2607,2608,2609,2610,2611,2612,2613,2614,2615,2616,2617,2618,2619,2620,2621,2622,2623,2624,2625,2626,
;                                    2627,2627,2628,2629,2630,2631,2632,2633,2634,2634,2635,2636,2637,2638,2639,2640,2640,2641,2642,2643,2644,2645,2645,2646,2647,2648,2648,2649,2650,2651,2652,2652,2653,2654,2655,2655,2656,2657,2658,2658,2659,2660,2660,2661,2662,2662,2663,2664,2665,2665,2666,2667,2667,2668,2669,2669,2670,2670,2671,2672,2672,2673,2674,2674,2675,2675,2676,2677,2677,2678,2678,2679,2679,2680,2681,2681,2682,2682,2683,2683,2684,2684,2685,2685,2686,2686,2687,2687,2688,2688,2689,2689,2690,2690,2691,2691,2692,2692,2692,2693,2693,2694,2694,2695,2695,2695,2696,2696,2697,2697,2697,2698,2698,2698,2699,2699,2699,2700,2700,2701,2701,2701,2702,2702,2702,2702,2703,2703,2703,2704,2704,2704,2704,2705,2705,2705,2706,2706};
;
;//const unsigned int TDS_data17[98]={64,69,75,80,86,91,97,102,107,113,118,124,129,134,140,145,151,156,161,167,172,177,183,188,193,199,204,209,215,220,225,230,236,241,246,252,257,262,267,273,278,283,288,294,299,304,309,314,320,325,330,335,340,345,351,356,361,366,371,376,382,387,392,397,402,407,412,417,422,427,433,438,443,448,453,458,463,468,473,478,483,488,493,498,503,508,513,518,523,528,533,538,543,548,553,558,563,568};
;
;//const unsigned int TDS_data18[333]={573,578,582,587,592,597,602,607,612,617,622,626,631,636,641,646,651,656,660,665,670,675,680,684,689,694,699,704,708,713,718,723,727,732,737,742,746,751,756,761,765,770,775,779,784,789,793,798,803,807,812,817,821,826,831,835,840,845,849,854,858,863,868,872,877,881,886,890,895,900,904,909,913,918,922,927,931,936,940,945,949,954,958,963,967,972,976,981,985,990,994,998,1003,1007,1012,1016,1021,1025,1029,1034,1038,1042,1047,1051,1056,1060,1064,1069,1073,1077,1082,1086,1090,1095,1099,1103,1108,1112,1116,1120,1125,1129,1133,1138,1142,1146,1150,1155,1159,1163,1167,1171,1176,1180,1184,1188,1192,1197,1201,1205,1209,1213,1218,1222,1226,1230,1234,1238,1242,1247,1251,1255,1259,1263,1267,1271,1275,1279,1283,1287,1292,1296,1300,1304,1308,1312,1316,1320,1324,1328,1332,1336,1340,1344,1348,1352,1356,1360,1364,1368,1372,1376,1380,1384,1387,1391,1395,1399,1403,1407,1411,1415,1419,1423,1426,1430,1434,1438,1442,1446,1450,1454,1457,1461,1465,1469,1473,1476,1480,1484,1488,1492,1495,1499,1503,1507,1510,1514,1518,1522,1525,1529,1533,1537,1540,1544,1548,1552,1555,1559,1563,1566,1570,1574,1577,1581,1585,1588,1592,1596,1599,1603,1606,1610,1614,1617,1621,1624,1628,1632,1635,1639,1642,1646,1649,1653,1657,1660,1664,1667,1671,1674,1678,1681,1685,1688,1692,1695,1699,1702,1706,1709,1713,1716,1719,1723,1726,1730,1733,1737,1740,1743,1747,1750,1754,1757,1760,1764,1767,1771,1774,1777,1781,1784,1787,1791,1794,1797,1801,1804,1807,1810,1814,1817,1820,1824,1827,1830,1833,1837,1840,1843,1846,1850,1853,1856,1859,1863,1866,1869,1872,1875,1879
;                                    //,1882,1885,1888,1891,1894,1898,1901,1904,1907,1910};
;
;//const unsigned int TDS_data19[267]={1913,1916,1920,1923,1926,1929,1932,1935,1938,1941,1944,1947,1950,1954,1957,1960,1963,1966,1969,1972,1975,1978,1981,1984,1987,1990,1993,1996,1999,2002,2005,2008,2011,2014,2017,2019,2022,2025,2028,2031,2034,2037,2040,2043,2046,2049,2051,2054,2057,2060,2063,2066,2069,2071,2074,2077,2080,2083,2086,2088,2091,2094,2097,2100,2102,2105,2108,2111,2114,2116,2119,2122,2124,2127,2130,2133,2135,2138,2141,2144,2146,2149,2152,2154,2157,2160,2162,2165,2168,2170,2173,2176,2178,2181,2183,2186,2189,2191,2194,2196,2199,2202,2204,2207,2209,2212,2214,2217,2220,2222,2225,2227,2230,2232,2235,2237,2240,2242,2245,2247,2250,2252,2255,2257,2260,2262,2264,2267,2269,2272,2274,2277,2279,2281,2284,2286,2289,2291,2293,2296,2298,2301
;                                     //,2303,2305,2308,2310,2312,2315,2317,2319,2322,2324,2326,2329,2331,2333,2335,2338,2340,2342,2345,2347,2349,2351,2354,2356,2358,2360,2362,2365,
;									 //2367,2369,2371,2374,2376,2378,2380,2382,2384,2387,2389,2391,2393,2395,2397,2399,2402,2404,2406,2408,2410,2412,2414,2416,
;									 //2418,2420,2423,2425,2427,2429,2431,2433,2435,2437,2439,2441,2443,2445,2447,2449,2451,2453,2455,2457,2459,2461,2463,2465,2467,2469,2471,2473,2475,2476,2478,2480,2482,2484,2486,2488,2490,2492,
;									 //2494,2495,2497,2499,2501,2503,2505,2507,2508,2510,2512,2514,2516,2517,2519,2521,2523,2525,2526,2528,2530,2532,2533,2535,2537,2539,2540,2542,2544,2546,2547,
;									 //2549,2551,2552,2533};
;//const unsigned int TDS_data20[302]={2535,2537,2539,2540,2542,2544,2546,2547,2549,2551,2552,2554,2556,2558,2559,2561,2563,2564,2566,2567,2569,2571,2572,2574,2576,2577,2579,2580,2582,2584,2585,2587,2588,2590,2592,2593,2595,2596,2598,2599,2601,2602,2604,2605,2607,2608,2610,2611,2613,2614,2616,2617,2619,2620,2622,2623,2625,2626,2628,2629,2630,2632,2633,2635,2636,2638,2639,2640,2642,2643,2644,2646,2647,2649,2650,2651,2653,2654,2655,2657,2658,2659,2661,2662,2663,2664,2666,2667,2668,2670,2671,2672,2673,2675,2676,2677,2678,2680,2681,2682,2683,2684,2686,2687,2688,2689,2690,2692,2693,2694,2695,2696,2697,2698,2700,2701,2702,2703,2704,2705,2706,2707,2709,2710,2711,2712,2713,2714,2715,2716,2717,2718,2719,2720,2721,2722,2723,2724,2725,2726,2727,2728,2729,2730,2731,2732,2733,2734,2735,2736,2737,2738,2739,2740,2741,2742,2743,2743,2744,2745,2746,2747,2748,2749,2750,2750,2751,2752,2753,2754,2755,2756,2756,2757,2758,2759,2760,2760,2761,2762,2763,2764,2764,2765,2766,2767,2767,2768,2769,2770,2770,2771,2772,2772,2773,2774,2775,2775,2776,2777,2777,2778,2779,2779,2780,2781,2781,2782,2782,2783,2784,2784,2785,2786,2786,2787,2787,2788,2788,2789,2790,2790,2791,2791,2792,2792,2793,2793,2794,2794,2795,2795,2796,2796,2797,2797,2798,2798,2799,2799,2800,2800,2801,2801,2802,2802,2802,2803,2803,2804,2804,2804,2805,2805,2806,2806,2806,2807,2807,2807,2808,2808,2808,2809,2809,2809,2810,2810,2810,2811,2811,2811,2812,2812,2812,2812,2813,2813,2813,2813,2814,2814,2814,2814,2814,2815,2815,2815,2815,2816,2816,2816,2816,2816,2816,2817,2817,2817,2817,2817,2817,2817,2818,2818,2818,2818,2818,2818,2818,2818,2818,2818,2818,2818};
;
; const unsigned int TDS_data17[98]={64,69,75,80,86,91,97,102,107,113,118,124,129,134,140,145,151,156,161,167,172,177,183,188,193,199,204,209,215,220,225,230,236,241,246,252,257,262,267,273,278,283,288,294,299,304,309,314,320,325,330,335,340,345,351,356,361,366,371,376,382,387,392,397,402,407,412,417,422,427,433,438,443,448,453,458,463,468,473,478,483,488,493,498,503,508,513,518,523,528,533,538,543,548,553,558,563,568};
; const unsigned int TDS_data18[333]={573,578,582,587,592,597,602,607,612,617,622,626,631,636,641,646,651,656,660,665,670,675,680,684,689,694,699,704,708,713,718,723,727,732,737,742,746,751,756,761,765,770,775,779,784,789,793,798,803,807,812,817,821,826,831,835,840,845,849,854,858,863,868,872,877,881,886,890,895,900,904,909,913,918,922,927,931,936,940,945,949,954,958,963,967,972,976,981,985,990,994,998,1003,1007,1012,1016,1021,1025,1029,1034,1038,1042,1047,1051,1056,1060,1064,1069,1073,1077,1082,1086,1090,1095,1099,1103,1108,1112,1116,1120,1125,1129,1133,1138,1142,1146,1150,1155,1159,1163,1167,1171,1176,1180,1184,1188,1192,1197,1201,1205,1209,1213,1218,1222,1226,1230,1234,1238,1242,1247,1251,1255,1259,1263,1267,1271,1275,1279,1283,1287,1292,1296,1300,1304,1308,1312,1316,1320,1324,1328,1332,1336,1340,1344,1348,1352,1356,1360,1364,1368,1372,1376,1380,1384,1387,1391,1395,1399,1403,1407,1411,1415,1419,1423,1426,1430,1434,1438,1442,1446,1450,1454,1457,1461,1465,1469,1473,1476,1480,1484,1488,1492,1495,1499,1503,1507,1510,1514,1518,1522,1525,1529,1533,1537,1540,1544,1548,1552,1555,1559,1563,1566,1570,1574,1577,1581,1585,1588,1592,1596,1599,1603,1606,1610,1614,1617,1621,1624,1628,1632,1635,1639,1642,1646,1649,1653,1657,1660,1664,1667,1671,1674,1678,1681,1685,1688,1692,1695,1699,1702,1706,1709,1713,1716,1719,1723,1726,1730,1733,1737,1740,1743,1747,1750,1754,1757,1760,1764,1767,1771,1774,1777,1781,1784,1787,1791,1794,1797,1801,1804,1807,1810,1814,1817,1820,1824,1827,1830,1833,1837,1840,1843,1846,1850,1853,1856,1859,1863,1866,1869,1872,1875,1879,1882,1885,1888,1891,1894,1898,1901,1904,1907,1910};
; const unsigned int TDS_data19[267]={1913,1916,1920,1923,1926,1929,1932,1935,1938,1941,1944,1947,1950,1954,1957,1960,1963,1966,1969,1972,1975,1978,1981,1984,1987,1990,1993,1996,1999,2002,2005,2008,2011,2014,2017,2019,2022,2025,2028,2031,2034,2037,2040,2043,2046,2049,2051,2054,2057,2060,2063,2066,2069,2071,2074,2077,2080,2083,2086,2088,2091,2094,2097,2100,2102,2105,2108,2111,2114,2116,2119,2122,2124,2127,2130,2133,2135,2138,2141,2144,2146,2149,2152,2154,2157,2160,2162,2165,2168,2170,2173,2176,2178,2181,2183,2186,2189,2191,2194,2196,2199,2202,2204,2207,2209,2212,2214,2217,2220,2222,2225,2227,2230,2232,2235,2237,2240,2242,2245,2247,2250,2252,2255,2257,2260,2262,2264,2267,2269,2272,2274,2277,2279,2281,2284,2286,2289,2291,2293,2296,2298,2301,2303,2305,2308,2310,2312,2315,2317,2319,2322,2324,2326,2329,2331,2333,2335,2338,2340,2342,2345,2347,2349,2351,2354,2356,2358,2360,2362,2365,2367,2369,2371,2374,2376,2378,2380,2382,2384,2387,2389,2391,2393,2395,2397,2399,2402,2404,2406,2408,2410,2412,2414,2416,2418,2420,2423,2425,2427,2429,2431,2433,2435,2437,2439,2441,2443,2445,2447,2449,2451,2453,2455,2457,2459,2461,2463,2465,2467,2469,2471,2473,2475,2476,2478,2480,2482,2484,2486,2488,2490,2492,2494,2495,2497,2499,2501,2503,2505,2507,2508,2510,2512,2514,2516,2517,2519,2521,2523,2525,2526,2528,2530,2532,2533,2535,2537,2539,2540,2542,2544,2546,2547,2549,2551,2552,2554};
; const unsigned int TDS_data20[302]={2556,2558,2559,2561,2563,2564,2566,2567,2569,2571,2572,2574,2576,2577,2579,2580,2582,2584,2585,2587,2588,2590,2592,2593,2595,2596,2598,2599,2601,2602,2604,2605,2607,2608,2610,2611,2613,2614,2616,2617,2619,2620,2622,2623,2625,2626,2628,2629,2630,2632,2633,2635,2636,2638,2639,2640,2642,2643,2644,2646,2647,2649,2650,2651,2653,2654,2655,2657,2658,2659,2661,2662,2663,2664,2666,2667,2668,2670,2671,2672,2673,2675,2676,2677,2678,2680,2681,2682,2683,2684,2686,2687,2688,2689,2690,2692,2693,2694,2695,2696,2697,2698,2700,2701,2702,2703,2704,2705,2706,2707,2709,2710,2711,2712,2713,2714,2715,2716,2717,2718,2719,2720,2721,2722,2723,2724,2725,2726,2727,2728,2729,2730,2731,2732,2733,2734,2735,2736,2737,2738,2739,2740,2741,2742,2743,2743,2744,2745,2746,2747,2748,2749,2750,2750,2751,2752,2753,2754,2755,2756,2756,2757,2758,2759,2760,2760,2761,2762,2763,2764,2764,2765,2766,2767,2767,2768,2769,2770,2770,2771,2772,2772,2773,2774,2775,2775,2776,2777,2777,2778,2779,2779,2780,2781,2781,2782,2782,2783,2784,2784,2785,2786,2786,2787,2787,2788,2788,2789,2790,2790,2791,2791,2792,2792,2793,2793,2794,2794,2795,2795,2796,2796,2797,2797,2798,2798,2799,2799,2800,2800,2801,2801,2802,2802,2802,2803,2803,2804,2804,2804,2805,2805,2806,2806,2806,2807,2807,2807,2808,2808,2808,2809,2809,2809,2810,2810,2810,2811,2811,2811,2812,2812,2812,2812,2813,2813,2813,2813,2814,2814,2814,2814,2814,2815,2815,2815,2815,2816,2816,2816,2816,2816,2816,2817,2817,2817,2817,2817,2817,2817,2818,2818,2818,2818,2818,2818,2818,2818,2818,2818,2818,2818};
;
;
;//**********************************************TDS校验数组
;const unsigned int TDS_CHECK [CHCEK_len]={259,382,444,506};
; 
;  
;//***********************************************************通信相关
;
;#define  WIFI_WAIT_SYN_0 0x00//数据包头FA
;#define  WIFI_WAIT_SYN_1 0x01 // 2数据包头FB
;#define  WIFI_PROTOCOL_JUDGE 0x02//3协议版本
;#define  WIFI_TOTAL_FRAME_NUM 0x03//4总帧数量
;#define  WIFI_FRAME_NUM 0x04//5帧序号
;#define   WIFI_WAIT_CTL 0x05//控制字		 
;#define   WIFI_COMMAND_1 0x06// 7数据长度1
;#define   WIFI_COMMAND_2 0x07// 8数据长度2			 				  		
;#define   WIFI_LENGTH1 0x08// 9数据长度1
;#define   WIFI_LENGTH2 0x09// 10数据长度2
;#define   WIFI_CHCK 0x0a// 11校验
;#define   WIFI_RECEDATA 0x0b// 12数据内容
;#define   WIFI_WAITPADDING 0x0c// 13接收6个 0
;//------------------------------------------
;#define WIFI_SYN_0         0XFA 
;#define WIFI_SYN_1         0XFC   
;#define WIFI_PROTOCOL_VERSION  0X00   
;#define WIFIBUFLEN			50    
;/////////Data Type  
;#define CTL_ACK_DATA  							0x00//(主动发送指令要求对方回复) 
;#define ACK_DATA  							0x80//(返回指令) 
;#define NOA_DATA  							0x40//(主动发送无需对方回复)		
;////数据帧位置////////////////////////
;#define SYN        		0	    //
;#define CTL        		1	    //
;#define LENL        		2	    //
;#define LENH        		3	    //
;#define CHK        		4	    //
;#define CMD_DATA       	5	    //
;///////Wifi Control Command
;#define SCANNETWORK_DATA   0x00  	// 开始扫描网络命令
;#define LINKNETWORK_DATA   0X01	// 开始连接网络命令
;#define CLEARALLUSERBOUND_DATA   0x6001 //	清除所有用户绑定
;#define HANDSHAKE_DATA   0xccc0      //发送握手信号HANDSHAKE_DATA
;#define POWERONSMARTLINK_DATA 0XCCC2   //启动Smarklink
;#define CLOSENETWORK_DATA  0x02	// 开始断开网络命令
;#define SETNETPARA_DATA    0X03	// 设置参数命令
;#define QUERYNETPARA_DATA  0X04	// 查询参数命令
;#define RESTWIFI_DATA      0X05	// 复位命令
;#define TCPLINK_DATA       0x06	// TCP连接命令
;#define TCPSENDFAILED_DATA 0x07	// TCP发送失败
;
;
;
;//#define HANDSHAKE_DATA   0x00      //发送握手信号
;#define START_SMARTLINK_DATA   0x00      //启动Smarklink
;#define DATA_FRAME_NUM_EQUE_0  0x00
;#define DATA_FRAME_EQUE_0 0x00
;//#define NULL         0x00
;
;
;// 消息类型，模块到主机 属于消息
;#define SCANNET_END					0X40	// 扫描网络结果消息
;#define LINKNET_END					0X41	// 网络已连接消息 
;#define CLOSENET_END				0x42	// 网络已断开消息
;#define SETNETPARA_END     	0X43	// 设置参数结果消息
;#define QUERYNETPARA_END   	0X44	// 查询参数结果消息
;#define RESTWIFI_END       	0X45	// 初始化完成消息
;#define TCPLINK_END        	0x46	// TCP连接状态消息
;CYBIT falg_gcReceComm1OK;
;
;
;
;section3 uint8   Protocol_Edt;           //通信协议版本
;section3 uint8  Send_Frame_Len ;        //发送帧数据长度
;section3 uint8  Rev_Frame_Len;          //接收帧数据长度
;section3 uint8 Send_Data_Count;        //发送数据计数
;section3 uint8 Rev_Data_Count;         //接收数据计数
;uint8 Frame_len;              //帧长度
;uint8 Frame_Code;             //帧序号
;uint8 Frame_Sum;              //校验和
; uint8 Send_Buf[13];           //发送数据缓存区
;uint8 cBuf[25]; ////51 has only 256 data in soc
;
;//uint8 Rev_Buf[300];           //接收数据缓存区
;section3 uint8	gcWifiCommunState;   	// 通讯接收状态
;section3 uint8 gcWIFICTL;//wifi控制字
;section3 uint8 putchar_step;
;section3 uint8  RecData; 
;section3 uint16 giWIFICommand;//wifi控制命令
;section3 uint16 giWIFIDATALength;//wifi数据长度
;
;//***********************发送数据相关
;#define TDS1_H 0
;#define TDS1_L 1
;#define TDS2_H 2
;#define TDS2_L 3
;#define ADture_H 4
;#define ADture_L 5
;#define wendu   6
;#define liuliang_H 7
;#define liuliang_L 8
;#define TDS1_f_H 9
;#define TDS1_f_L 10
;#define TDS2_f_H 11
;#define TDS2_f_L 12
;
;
;typedef struct Buffer2
;{
;	uint8  	gcATReceData[20];  // wifi 模块一次传输1440字节，这里有51芯片只有1280个xdata
;	uint16 		gcATReceCount;
;} Buffer2;
;
;struct Buffer2    ATReceBuffer[1];
; uint16		iUartSendLen;
;uint16		iSendCounter;
;uint8		*cpSendBufPtr;
;
;uint16 find_position(uint16 a, const uint16 *p,uint16 num,uint16 chang_temp)
;{
;  uint16 i,j,k1,k2,m;
;
; m = j = num/2;
; k1 = 0;
; k2 = num;
; for (i=0;i<m;i++)
; {
;     if ( a>*(p+j) && a<*(p+j+1))
;      break;       //找到了 
;     else if ( a<*(p+j) ) 
;       {
;    			k2 = j;
;    			j = (k1+k2)/2;
;       }
;     else if ( a>*(p+j+1) )
;       {
;    			k1 = j+1;
;    			j = (k1+k2)/2 ;
;       }
;     else if ( a == *(p+j) )
;       break;
; }
; if ( j>=0 && j<(num-1) )
;     return (j+1+chang_temp);
; else 
; {    
;     if (j >= (num-1) )
;                 return ((num+chang_temp)+1); //超出最大值
;     else  
;         return (0+chang_temp); //超出最小值
;     
; }
;}
;//*********************************************delay
;void delay(unsigned int i)//通信时序延时
;{ 
;	unsigned int j;
;	j=i;
:0Xec  e783                     CLR             HRAM_0X83
:0Xed  7838                     MOVRA           _delayDATA                           ;_delayDATA: Bank 0    Addr: 56     
:0Xee  203a                     MOVAR           _delayDATA+2                         ;_delayDATA+2: Bank 0    Addr: 58     
:0Xef  7839                     MOVRA           _delayDATA+1                         ;_delayDATA+1: Bank 0    Addr: 57     
:0Xf0  203b                     MOVAR           _delayDATA+3                         ;_delayDATA+3: Bank 0    Addr: 59     
HADR_0XF1:
;	for(;i!=0;i--); 
:0Xf1  5038                     MOV             (_delayDATA)&7f,                A    ;(_delayDATA)&7f: Bank 0    Addr: 56     
:0Xf2  5839                     IOR             (_delayDATA+1)&7f,              A    ;(_delayDATA+1)&7f: Bank 0    Addr: 57     
:0Xf3  9a84                     JBC             HRAM_0X84,      2
:0Xf4  68fa                     GOTO            HADR_0XFA
:0Xf5  5038                     MOV             (_delayDATA)&7f,                A    ;(_delayDATA)&7f: Bank 0    Addr: 56     
:0Xf6  9a84                     JBC             HRAM_0X84,      2
:0Xf7  1139                     DEC             (_delayDATA+1)&7f,              R    ;(_delayDATA+1)&7f: Bank 0    Addr: 57     
:0Xf8  1138                     DEC             (_delayDATA)&7f,                R    ;(_delayDATA)&7f: Bank 0    Addr: 56     
:0Xf9  68f1                     GOTO            HADR_0XF1
HADR_0XFA:
;	for(;j!=0;j--); 
:0Xfa  503a                     MOV             (_delayDATA+2)&7f,              A    ;(_delayDATA+2)&7f: Bank 0    Addr: 58     
:0Xfb  583b                     IOR             (_delayDATA+3)&7f,              A    ;(_delayDATA+3)&7f: Bank 0    Addr: 59     
:0Xfc  9a84                     JBC             HRAM_0X84,      2
:0Xfd  6903                     GOTO            HADR_0X103
:0Xfe  503a                     MOV             (_delayDATA+2)&7f,              A    ;(_delayDATA+2)&7f: Bank 0    Addr: 58     
:0Xff  9a84                     JBC             HRAM_0X84,      2
:0X100  113b                    DEC             (_delayDATA+3)&7f,              R   ;(_delayDATA+3)&7f: Bank 0    Addr: 59     
:0X101  113a                    DEC             (_delayDATA+2)&7f,              R   ;(_delayDATA+2)&7f: Bank 0    Addr: 58     
:0X102  68fa                    GOTO            HADR_0XFA
HADR_0X103:
;}
:0X103  c183                    RET
HADR_0X104:
;
;
;
;
;
;
;
;//*********************************************************
;
;void WDserch(uint16 a)  //温度AD查询函数 
;{
; //unsigned int m0,m1,mid,t0,changdata;
;
; uint16 i,j,k1,k2,m,num,changdata;
;if(a>=0&&a<=568)
;{
;	
;	num=98;
;	temp_p=TDScheck1;
;	//temp_p=( const unsigned int *)TDS_data17;
;		
;	changdata=0;
;}
;
;
; else if(a>568&&a<=1910)
;{
;	
;	num=333;
;	temp_p=TDScheck2;
;	//temp_p=( const unsigned int *)TDS_data18;
;
;	changdata=98;
;}
;
;
;
;else if(a>1910&&a<=2554)
;{
;	
;	num=267;
;	temp_p=TDScheck3;
;	//temp_p=( const unsigned int *)TDS_data19;
;	
;	changdata=431;
;}
;else if(a>2554&&a<=2818)
;{
;	
;	num=302;
;	temp_p=TDScheck4;
;	//temp_p=( const unsigned int *)TDS_data20;
;	
;	changdata=698;
;	
;}
;else 
;{
;
;	num=302;
;	temp_p=TDScheck4;
;	changdata=698;	
;	a=2818;
;}
;TDSfrequency_temp=0;
;TDSfrequency_temp=find_position(a,temp_p,num,changdata);
; //m = j = num/2;
; //k1 = 0;
; //k2 = num;
; //for (i=0;i<m;i++)
; //{
;     //if ( a>*(p+j) && a<*(p+j+1))
;      //break;       //找到了 
;     //else if ( a<*(p+j) ) 
;       //{
;    			//k2 = j;
;    			//j = (k1+k2)/2;
;       //}
;     //else if ( a>*(p+j+1) )
;       //{
;    			//k1 = j+1;
;    			//j = (k1+k2)/2 ;
;       //}
;     //else if ( a == *(p+j) )
;       //break;
; //}
; //if ( j>=0 && j<(num-1) )
;     //return (j+1);
; //else 
; //{    
;     //if (j >= (num-1) )
;                 //return (num-1); //超出最大值
;     //else  
;         //return (p[0]); //超出最小值
;     
; //}
;//while(1)
;//{
;	//mid=m0+m1;
;	//mid>>=1;
;	//if(TDS1_frequency==datatemp[m1])return (m1+1+changdata);
;	//if(mid==m0) return (mid+1+changdata);
;	//t0=datatemp[mid];
;	//if(TDS1_frequency==t0) return (mid+1+changdata);
;	//else if (TDS1_frequency<t0) m1=mid-1;
;	//else m0=mid+1;
;//} 
;}
;//*************************************
;uint8 find_chcek(uint16 a, const uint16 *q,uint8 num)
;{
; uint8 i,j,k1,k2,m;
;
; m = j = num/2;
; k1 = 0;
; k2 = num;
; for (i=0;i<m;i++)
; {
;     if ( a>*(q+j) && a<*(q+j+1))
;      break;       //找到了 
;     else if ( a<*(q+j) ) 
;       {
;    			k2 = j;
;    			j = (k1+k2)/2;
;       }
;     else if ( a>*(q+j+1) )
;       {
;    			k1 = j+1;
;    			j = (k1+k2)/2 ;
;       }
;     else if ( a == *(q+j) )
;       break;
; }
; if ( j>=0 && j<(num-1) )
;     return (j+1);
; else 
; {    
;     if (j >= (num-1) )
;                 return (4); //超出最大值
;     else  
;         return (1); //超出最小值
;     
; }
;}
;
;/*********************************************************************************************************
;** 函数名称: void UART_SendData(unsigned char	 *data_buf,unsigned char	 count)
;** 功能描述: 从串口发送数据
;** 入口参数: data_buf:发送数据缓冲区首地址
;**			 count	:发送字节数
;** 出口参数:	无
;********************************************************************************************************/
;void UART_SendData(uint8	 *data_buf,uint16 iCount)
;{
;	iUartSendLen = iCount-1;
;	iSendCounter = 0;
;//  UART_UartPutChar(data_buf[0]);
;	cpSendBufPtr = &data_buf[0];
;}
;
;
;
;/*
;	========================================================================
;* 函 数 名: ProcessUARTData(   IN unsigned char  UartData)
;* 函数功能: 串口发送程序
;* 入口参数: UartData
;* 返    回: 
;	========================================================================
;*/
;void ProcessUARTData(uint8  UartData)
;{
;	switch (gcWifiCommunState)
;		{
;			 case WIFI_WAIT_SYN_0:		                 // 1数据包头FA
;			   		if(UartData==WIFI_SYN_0)
;  			   		gcWifiCommunState = WIFI_WAIT_SYN_1;
;  			  	ATReceBuffer[0].gcATReceData[0]= UartData;
;			  		break;
;			 case WIFI_WAIT_SYN_1:		                // 2数据包头FB
;			   		if(UartData==WIFI_SYN_1)
;  			   		gcWifiCommunState = WIFI_PROTOCOL_JUDGE;
;  			  	ATReceBuffer[0].gcATReceData[1]= UartData;
;			  		break;
;			 case WIFI_PROTOCOL_JUDGE:                //3协议版本
;			 			if(UartData==WIFI_PROTOCOL_VERSION)
;  			   		gcWifiCommunState = WIFI_TOTAL_FRAME_NUM;
;  			  	ATReceBuffer[0].gcATReceData[2]= UartData;
;			  		break;
;			 case WIFI_TOTAL_FRAME_NUM:               //4总帧数量
;			 			gcWifiCommunState = WIFI_FRAME_NUM;
;  			  	ATReceBuffer[0].gcATReceData[3]= UartData;
;			  		break;		
;			 case WIFI_FRAME_NUM:                    //5帧序号
;			 			gcWifiCommunState = WIFI_WAIT_CTL;
;  			  	ATReceBuffer[0].gcATReceData[4]= UartData;
;			  		break;		
;			 case WIFI_WAIT_CTL:	               // 6控制字
;			    	gcWIFICTL = UartData;
;						gcWifiCommunState = WIFI_COMMAND_1;
;  			  	ATReceBuffer[0].gcATReceData[5]= UartData;
;			 			break;		 
;			 case WIFI_COMMAND_1:	           // 7指令1
;			    	giWIFICommand = UartData;
;						gcWifiCommunState = WIFI_COMMAND_2;
;  			  	ATReceBuffer[0].gcATReceData[6]= UartData;
;			 			break;
;			 case WIFI_COMMAND_2:			  // 8指令2
;			    	giWIFICommand = (giWIFICommand<<8)+UartData;
;      				  gcWifiCommunState = WIFI_LENGTH1;     
;  			  	ATReceBuffer[0].gcATReceData[7]= UartData;
;			 			break;			 					  		
;			 case WIFI_LENGTH1:	           // 9数据长度1
;			    	giWIFIDATALength = UartData;
;						gcWifiCommunState = WIFI_LENGTH2;
;  			  	ATReceBuffer[0].gcATReceData[8]= UartData;
;			 			break;
;			 case WIFI_LENGTH2:			  // 10数据长度2
;			    	giWIFIDATALength = (giWIFIDATALength<<8)+UartData;
;    				if(giWIFIDATALength>0)   // 
;      				{
;      				  gcWifiCommunState = WIFI_RECEDATA;
;      				} 
;    				else
;      				{
;      				   gcWifiCommunState = WIFI_CHCK; 
;      				}
;  			  	ATReceBuffer[0].gcATReceData[9]= UartData;
;			 			break;
;    	case WIFI_CHCK:	  // 11校验          						
;  			    ATReceBuffer[0].gcATReceData[10+ATReceBuffer[0].gcATReceCount]= UartData;
;      			ATReceBuffer[0].gcATReceCount = 0;
;      			gcWifiCommunState = WIFI_WAIT_SYN_0;
;      			falg_gcReceComm1OK = 1;  // 数据成功接收完毕
;			 			break;
;		case WIFI_RECEDATA:  // 12数据内容
;    			 	ATReceBuffer[0].gcATReceData[10+ATReceBuffer[0].gcATReceCount]= UartData;
;    			    ATReceBuffer[0].gcATReceCount++;
;    				if(ATReceBuffer[0].gcATReceCount == giWIFIDATALength)
;    				{
;    				  	gcWifiCommunState = WIFI_CHCK;
;    				}
;    			 	break;
;		default:
;			 	gcWifiCommunState = WIFI_WAIT_SYN_0;	
;		}
;}
;
;/******************************************************************************
;* 函 数 名: Sum_Make_Verify (uint8 *pBuf, uint len)
;* 函数功能: 串口接收程序     和校验
;* 入口参数: 无
;* 返    回: 
;*******************************************************************************/
;uint8 Sum_Make_Verify ()
;{
;    uint8 Verify = 0;
;
;	Verify=Verify+cBuf[0];
;	Verify=Verify+cBuf[1];
:0X104  e783                    CLR             HRAM_0X83
:0X105  7815                    MOVRA           _cBuf                               ;_cBuf: Bank 0    Addr: 21     
:0X106  5e16                    ADD             (_cBuf+1)&7f,   A                   ;(_cBuf+1)&7f: Bank 0    Addr: 22     
:0X107  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[2];
:0X108  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X109  5e17                    ADD             (_cBuf+2)&7f,   A                   ;(_cBuf+2)&7f: Bank 0    Addr: 23     
:0X10a  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[3];
:0X10b  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X10c  5e18                    ADD             (_cBuf+3)&7f,   A                   ;(_cBuf+3)&7f: Bank 0    Addr: 24     
:0X10d  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[4];
:0X10e  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X10f  5e19                    ADD             (_cBuf+4)&7f,   A                   ;(_cBuf+4)&7f: Bank 0    Addr: 25     
:0X110  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[5];
:0X111  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X112  5e1a                    ADD             (_cBuf+5)&7f,   A                   ;(_cBuf+5)&7f: Bank 0    Addr: 26     
:0X113  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[6];
:0X114  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X115  5e1b                    ADD             (_cBuf+6)&7f,   A                   ;(_cBuf+6)&7f: Bank 0    Addr: 27     
:0X116  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[7];
:0X117  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X118  5e1c                    ADD             (_cBuf+7)&7f,   A                   ;(_cBuf+7)&7f: Bank 0    Addr: 28     
:0X119  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[8];
:0X11a  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X11b  5e1d                    ADD             (_cBuf+8)&7f,   A                   ;(_cBuf+8)&7f: Bank 0    Addr: 29     
:0X11c  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[9];
:0X11d  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X11e  5e1e                    ADD             (_cBuf+9)&7f,   A                   ;(_cBuf+9)&7f: Bank 0    Addr: 30     
:0X11f  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[10];
:0X120  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X121  5e1f                    ADD             (_cBuf+10)&7f,  A                   ;(_cBuf+10)&7f: Bank 0    Addr: 31     
:0X122  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[11];
:0X123  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X124  5e20                    ADD             (_cBuf+11)&7f,  A                   ;(_cBuf+11)&7f: Bank 0    Addr: 32     
:0X125  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[12];
:0X126  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X127  5e21                    ADD             (_cBuf+12)&7f,  A                   ;(_cBuf+12)&7f: Bank 0    Addr: 33     
:0X128  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[13];
:0X129  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X12a  5e22                    ADD             (_cBuf+13)&7f,  A                   ;(_cBuf+13)&7f: Bank 0    Addr: 34     
:0X12b  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[14];
:0X12c  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X12d  5e23                    ADD             (_cBuf+14)&7f,  A                   ;(_cBuf+14)&7f: Bank 0    Addr: 35     
:0X12e  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[15];
:0X12f  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X130  5e24                    ADD             (_cBuf+15)&7f,  A                   ;(_cBuf+15)&7f: Bank 0    Addr: 36     
:0X131  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[16];
:0X132  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X133  5e25                    ADD             (_cBuf+16)&7f,  A                   ;(_cBuf+16)&7f: Bank 0    Addr: 37     
:0X134  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[17];
:0X135  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X136  5e26                    ADD             (_cBuf+17)&7f,  A                   ;(_cBuf+17)&7f: Bank 0    Addr: 38     
:0X137  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[18];
:0X138  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X139  5e27                    ADD             (_cBuf+18)&7f,  A                   ;(_cBuf+18)&7f: Bank 0    Addr: 39     
:0X13a  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[19];
:0X13b  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X13c  5e28                    ADD             (_cBuf+19)&7f,  A                   ;(_cBuf+19)&7f: Bank 0    Addr: 40     
:0X13d  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[20];
:0X13e  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X13f  5e29                    ADD             (_cBuf+20)&7f,  A                   ;(_cBuf+20)&7f: Bank 0    Addr: 41     
:0X140  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[21];
:0X141  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X142  5e2a                    ADD             (_cBuf+21)&7f,  A                   ;(_cBuf+21)&7f: Bank 0    Addr: 42     
:0X143  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	Verify=Verify+cBuf[22];
:0X144  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X145  5e2b                    ADD             (_cBuf+22)&7f,  A                   ;(_cBuf+22)&7f: Bank 0    Addr: 43     
:0X146  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	
;
;    
;    return (~Verify + 1);
:0X147  523a                    COM             (_Sum_Make_VerifyDATA)&7f,      A   ;(_Sum_Make_VerifyDATA)&7f: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X148  203b                    MOVAR           _Sum_Make_VerifyDATA+1              ;_Sum_Make_VerifyDATA+1: Bank 0    Addr: 59    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X149  783b                    MOVRA           _Sum_Make_VerifyDATA+1              ;_Sum_Make_VerifyDATA+1: Bank 0    Addr: 59    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X14a  e001                    ADDI            0X1
:0X14b  203a                    MOVAR           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X14c  783a                    MOVRA           _Sum_Make_VerifyDATA                ;_Sum_Make_VerifyDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X14d  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X14e  c183                    RET
HADR_0X14F:
;}
;/******************************************************************************
;* 函 数 名: *memcpy (void *destaddr,void const *srcaddr, size_t len)
;* 函数功能: 串口接收程序    
;* 入口参数: 无
;* 返    回: 
;*******************************************************************************/
;void memcpy ()
;
;{
;	
;
;	cBuf[10]=Send_Buf[0];
:0X14f  e783                    CLR             HRAM_0X83
:0X150  7808                    MOVRA           _Send_Buf                           ;_Send_Buf: Bank 0    Addr: 8     
:0X151  201f                    MOVAR           _cBuf+10                            ;_cBuf+10: Bank 0    Addr: 31     
;	cBuf[11]=Send_Buf[1];
:0X152  7809                    MOVRA           _Send_Buf+1                         ;_Send_Buf+1: Bank 0    Addr: 9     
:0X153  2020                    MOVAR           _cBuf+11                            ;_cBuf+11: Bank 0    Addr: 32     
;	cBuf[12]=Send_Buf[2];
:0X154  780a                    MOVRA           _Send_Buf+2                         ;_Send_Buf+2: Bank 0    Addr: 10     
:0X155  2021                    MOVAR           _cBuf+12                            ;_cBuf+12: Bank 0    Addr: 33     
;	cBuf[13]=Send_Buf[3];
:0X156  780b                    MOVRA           _Send_Buf+3                         ;_Send_Buf+3: Bank 0    Addr: 11     
:0X157  2022                    MOVAR           _cBuf+13                            ;_cBuf+13: Bank 0    Addr: 34     
;  	cBuf[14]=Send_Buf[4];
:0X158  780c                    MOVRA           _Send_Buf+4                         ;_Send_Buf+4: Bank 0    Addr: 12     
:0X159  2023                    MOVAR           _cBuf+14                            ;_cBuf+14: Bank 0    Addr: 35     
;   	cBuf[15]=Send_Buf[5];
:0X15a  780d                    MOVRA           _Send_Buf+5                         ;_Send_Buf+5: Bank 0    Addr: 13     
:0X15b  2024                    MOVAR           _cBuf+15                            ;_cBuf+15: Bank 0    Addr: 36     
;	cBuf[16]=Send_Buf[6];
:0X15c  780e                    MOVRA           _Send_Buf+6                         ;_Send_Buf+6: Bank 0    Addr: 14     
:0X15d  2025                    MOVAR           _cBuf+16                            ;_cBuf+16: Bank 0    Addr: 37     
;	cBuf[17]=Send_Buf[7];
:0X15e  780f                    MOVRA           _Send_Buf+7                         ;_Send_Buf+7: Bank 0    Addr: 15     
:0X15f  2026                    MOVAR           _cBuf+17                            ;_cBuf+17: Bank 0    Addr: 38     
;	cBuf[18]=Send_Buf[8];
:0X160  7810                    MOVRA           _Send_Buf+8                         ;_Send_Buf+8: Bank 0    Addr: 16     
:0X161  2027                    MOVAR           _cBuf+18                            ;_cBuf+18: Bank 0    Addr: 39     
;	cBuf[19]=Send_Buf[9];
:0X162  7811                    MOVRA           _Send_Buf+9                         ;_Send_Buf+9: Bank 0    Addr: 17     
:0X163  2028                    MOVAR           _cBuf+19                            ;_cBuf+19: Bank 0    Addr: 40     
;	cBuf[20]=Send_Buf[10];
:0X164  7812                    MOVRA           _Send_Buf+10                        ;_Send_Buf+10: Bank 0    Addr: 18     
:0X165  2029                    MOVAR           _cBuf+20                            ;_cBuf+20: Bank 0    Addr: 41     
;	cBuf[21]=Send_Buf[11];
:0X166  7813                    MOVRA           _Send_Buf+11                        ;_Send_Buf+11: Bank 0    Addr: 19     
:0X167  202a                    MOVAR           _cBuf+21                            ;_cBuf+21: Bank 0    Addr: 42     
;	cBuf[22]=Send_Buf[12];
:0X168  7814                    MOVRA           _Send_Buf+12                        ;_Send_Buf+12: Bank 0    Addr: 20     
:0X169  202b                    MOVAR           _cBuf+22                            ;_cBuf+22: Bank 0    Addr: 43     
;
;}
:0X16a  c183                    RET
HADR_0X16B:
;
;
;
;/******************************************************************************
;* 函 数 名: *memcpy (void *destaddr,void const *srcaddr, size_t len)
;* 函数功能: 串口接收程序    
;* 入口参数: 无
;* 返    回: 
;*******************************************************************************/
;void memset()
;{
;
;	for(i=0;i<24;i++)
:0X16b  e783                    CLR             HRAM_0X83
:0X16c  ea02                    SECTION         0X2
:0X16d  e700                    CLR             (_i)&7f                             ;(_i)&7f: Bank 0    Addr: 0     
HADR_0X16E:
:0X16e  e518                    MOVI            0X18
:0X16f  ee00                    SUB             (_i)&7f,        A                   ;(_i)&7f: Bank 0    Addr: 0     
:0X170  9884                    JBC             HRAM_0X84,      0
:0X171  697f                    GOTO            HADR_0X17F
;	{
;	
;		cBuf[i]=0;
:0X172  e515                    MOVI            _cBuf
:0X173  5e00                    ADD             (_i)&7f,        A                   ;(_i)&7f: Bank 0    Addr: 0     
:0X174  203a                    MOVAR           _memsetDATA                         ;_memsetDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X175  783a                    MOVRA           _memsetDATA                         ;_memsetDATA: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X176  e681                    MOVA            HRAM_0X81
:0X177  e500                    MOVI            0X0
:0X178  e682                    MOVA            HRAM_0X82
:0X179  e500                    MOVI            0X0
:0X17a  e680                    MOVA            HRAM_0X80
:0X17b  1f81                    JINC            HRAM_0X81,      R
:0X17c  ffff                    NOP
:0X17d  5500                    INC             (_i)&7f,        R                   ;(_i)&7f: Bank 0    Addr: 0     
;	
;	}
:0X17e  696e                    GOTO            HADR_0X16E
HADR_0X17F:
;}
:0X17f  ea00                    SECTION         0X0
:0X180  c183                    RET
HADR_0X181:
;
;
;
;
;
;
;
;
;
;/*
;*********************************************************************************************************
;** 函数名称 ：SendDataToWifi()
;** 函数功能 ：发送数据到WIFI模块                          
;** 入口参数 ：cCtl：控制字类型 
;  							0x00(主动发送指令要求对方回复) 
;  							0x80(返回指令) 
;  							0x40(主动发送无需对方回复)
;              unsigned char  *DataBuf  数据缓存区            
;              unsigned int   iLength   数据长度          
;** 出口参数 ：无
;*********************************************************************************************************
;*/
;void  SendDataToWifi(void)
;{
;    
;	  memset();
:0X181  e783                    CLR             HRAM_0X83
:0X182  ec00                    PAGE            (_memset)>>11
:0X183  616b                    CALL            HADR_0X16B
:0X184  ec00                    PAGE            (_17)>>11
;	  cBuf[0] = WIFI_SYN_0;        	     // SYNC0
:0X185  e5fa                    MOVI            0XFA
:0X186  2015                    MOVAR           _cBuf                               ;_cBuf: Bank 0    Addr: 21     
;    cBuf[1] = WIFI_SYN_1;        	     // SYNC1
:0X187  e5fc                    MOVI            0XFC
:0X188  2016                    MOVAR           _cBuf+1                             ;_cBuf+1: Bank 0    Addr: 22     
;    cBuf[2] = 0x00;   //MCU_PROTOCOL_VERSION       
:0X189  e500                    MOVI            0X0
:0X18a  2017                    MOVAR           _cBuf+2                             ;_cBuf+2: Bank 0    Addr: 23     
;    cBuf[3] = 0x00;   //FRAME_EQUE_0       
:0X18b  e500                    MOVI            0X0
:0X18c  2018                    MOVAR           _cBuf+3                             ;_cBuf+3: Bank 0    Addr: 24     
;    cBuf[4]= 0x00;//帧需要
:0X18d  e500                    MOVI            0X0
:0X18e  2019                    MOVAR           _cBuf+4                             ;_cBuf+4: Bank 0    Addr: 25     
;	  cBuf[5] = 0x40;   	 // Wctrl
:0X18f  e540                    MOVI            0X40
:0X190  201a                    MOVAR           _cBuf+5                             ;_cBuf+5: Bank 0    Addr: 26     
;	  cBuf[6]=(0x1000)>>8;//长度0
:0X191  e510                    MOVI            0X10
:0X192  201b                    MOVAR           _cBuf+6                             ;_cBuf+6: Bank 0    Addr: 27     
;	  cBuf[7]=(0x1000)&0x00ff;//长度1	  cBuf[8]=(iLength)>>8;//长度0
:0X193  e500                    MOVI            0X0
:0X194  201c                    MOVAR           _cBuf+7                             ;_cBuf+7: Bank 0    Addr: 28     
;	  cBuf[8]=(13)>>8;//长度0
:0X195  e500                    MOVI            0X0
:0X196  201d                    MOVAR           _cBuf+8                             ;_cBuf+8: Bank 0    Addr: 29     
;	  cBuf[9]=(13)&0x00ff;//长度1
:0X197  e50d                    MOVI            0XD
:0X198  201e                    MOVAR           _cBuf+9                             ;_cBuf+9: Bank 0    Addr: 30     
;	  
;	  	    memcpy();
:0X199  ec00                    PAGE            (_memcpy)>>11
:0X19a  614f                    CALL            HADR_0X14F
:0X19b  ec00                    PAGE            (_18)>>11
;         cBuf[23] = Sum_Make_Verify();
:0X19c  ec00                    PAGE            (_Sum_Make_Verify)>>11
:0X19d  6104                    CALL            HADR_0X104
:0X19e  ec00                    PAGE            (_19)>>11
:0X19f  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X1a0  202c                    MOVAR           _cBuf+23                            ;_cBuf+23: Bank 0    Addr: 44     
;       
;      
;	 // UART_SendData(cBuf,iLength+11);   ///The Last six 0x00 is PADDING
;}
:0X1a1  c183                    RET
HADR_0X1A2:
;
;//*****************************************************************************
;//                            TDS值校验
;//*****************************************************************************
;void CHECK(void)
;{
;	//if()
;
;	if(giWIFICommand==0x2000)
;	{
;		switch(CHECK_step)
;		{
;			case 0:
;				//TDSchcek_num=find_chcek(TDS1_frequency, TDS_CHECK ,4);
;				TDSchcek_num=4;
;				CHECK_step++;
;				break;
;			case 1:
;				switch(TDSchcek_num)
;		
;				{
;					case 1:
;						TDScheck1=( const unsigned int *)TDS_data1;
;						TDScheck2=( const unsigned int *)TDS_data2;
;						TDScheck3=( const unsigned int *)TDS_data3;
;						TDScheck4=( const unsigned int *)TDS_data4;	
;						
;						break;
;					case 2:
;						TDScheck1=( const unsigned int *)TDS_data5;
;						TDScheck2=( const unsigned int *)TDS_data6;
;						TDScheck3=( const unsigned int *)TDS_data7;
;						TDScheck4=( const unsigned int *)TDS_data8;	
;						
;						break;
;					case 3:
;						TDScheck1=( const unsigned int *)TDS_data9;
;						TDScheck2=( const unsigned int *)TDS_data10;
;						TDScheck3=( const unsigned int *)TDS_data11;
;						TDScheck4=( const unsigned int *)TDS_data12;
;							
;						break;
;					case 4:
;						TDScheck1=( const unsigned int *)TDS_data13;
;						TDScheck2=( const unsigned int *)TDS_data14;
;						TDScheck3=( const unsigned int *)TDS_data15;
;						TDScheck4=( const unsigned int *)TDS_data16;
;						
;						break;
;					default:
;						TDScheck1=( const unsigned int *)TDS_data5;
;						TDScheck2=( const unsigned int *)TDS_data6;
;						TDScheck3=( const unsigned int *)TDS_data7;
;						TDScheck4=( const unsigned int *)TDS_data8;
;						
;						break;
;	
;	
;				}
;				CHECK_step++;
;				break;
;			case 2:
;				giWIFICommand=0x0000;
;				break;
;		}
;
;
;	}
;	
;	
;	
;	
;}
;
;
;
;
;//*****************************************************************************
;//                             定时器初始化
;//*****************************************************************************
;void Iint_timer(void)
;{
;//******************************定时器T8N初始化
;	//T8NC = 0x02;	    //设置T8N为定时器模式，分频比为1:8 
;  // T8N = 223;		    //设定时器初值，125us
;	//T8N = 230;//100us
;    //T8NPRE = 1;		 //使能预分频器
;    //T8NIE = 1;		    //使能T8N定时器中断
;    		    
;    //T8NEN = 1;		    //打开T8NEN定时器
;
;//********************************设置TN8采集外部频率
;	T8NC=0x00;//分频比为1:2
:0X1a2  e783                    CLR             HRAM_0X83
:0X1a3  e7bc                    CLR             _T8NC                               ;_T8NC: Bank 511    Addr: 65468    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	T8NPRE = 0;		 //禁止预分频器
:0X1a4  abbc                    BCC             (_T8NPRE)>>3,   3                   ;(_T8NPRE)>>3: Bank 511    Addr: 65468    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	T8NEG =0;//上升沿计数
:0X1a5  acbc                    BCC             (_T8NEG)>>3,    4                   ;(_T8NEG)>>3: Bank 511    Addr: 65468    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	T8NM=1;//同步计数模式
:0X1a6  a5bc                    BSS             (_T8NM)>>3,     5                   ;(_T8NM)>>3: Bank 511    Addr: 65468    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	T8NEN = 1;
:0X1a7  a7bc                    BSS             (_T8NEN)>>3,    7                   ;(_T8NEN)>>3: Bank 511    Addr: 65468    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;
;
;//******************************时基定时器T8P1初始化
;	T8P1C = 0x06;    //使能T8P1，定时器工作模式，设置预分频1:8，后分频1：1
:0X1a8  e506                    MOVI            0X6
:0X1a9  e6be                    MOVA            _T8P1C                              ;_T8P1C: Bank 511    Addr: 65470    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	T8P1P =125 ;   //设置PWM周期寄存器初始值（125us）
:0X1aa  e57d                    MOVI            0X7D
:0X1ab  e6bf                    MOVA            _T8P1P                              ;_T8P1P: Bank 511    Addr: 65471    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	T8P1IE=1;//使能T8P1匹配中断
:0X1ac  a29a                    BSS             (_T8P1IE)>>3,   2                   ;(_T8P1IE)>>3: Bank 511    Addr: 65434    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	
;//**************************************定时器T8P2初始化	
;	T8P2C = 0x06;    //使能T8P2，定时器工作模式，设置预分频1:8，后分频1：1
:0X1ad  e506                    MOVI            0X6
:0X1ae  e6c4                    MOVA            _T8P2C                              ;_T8P2C: Bank 511    Addr: 65476    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	T8P2P =125 ;   //设置PWM周期寄存器初始值（125us）
:0X1af  e57d                    MOVI            0X7D
:0X1b0  e6c5                    MOVA            _T8P2P                              ;_T8P2P: Bank 511    Addr: 65477    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	
;	T8P2IE=1;//使能T8P2匹配中断
:0X1b1  a39a                    BSS             (_T8P2IE)>>3,   3                   ;(_T8P2IE)>>3: Bank 511    Addr: 65434    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;
;
;	GIE = 1;//使能总中断
:0X1b2  a796                    BSS             (_GIE)>>3,      7                   ;(_GIE)>>3: Bank 511    Addr: 65430    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;
;
;}
:0X1b3  c183                    RET
HADR_0X1B4:
;//*****************************************************************************
;//                             I/O初始化
;//*****************************************************************************
;void   Iint_IO(void)
;{
;
;	ANSH = 0xff; 
:0X1b4  e783                    CLR             HRAM_0X83
:0X1b5  e5ff                    MOVI            0XFF
:0X1b6  e6df                    MOVA            _ANSH                               ;_ANSH: Bank 511    Addr: 65503    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	ANSL= 0xff;		 //设置PA1为I/O
:0X1b7  e5ff                    MOVI            0XFF
:0X1b8  e6de                    MOVA            _ANSL                               ;_ANSL: Bank 511    Addr: 65502    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	ANSL&=0xfb;//设置PA3/AN2 为模拟输入  漏水检测
:0X1b9  aade                    BCC             _ANSL,          2                   ;_ANSL: Bank 511    Addr: 65502    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	ANSL&=0xef;//设置PA5/AN4为模拟输入  漏水检测
:0X1ba  acde                    BCC             _ANSL,          4                   ;_ANSL: Bank 511    Addr: 65502    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;
;	PAT0=1;         //输入模式
:0X1bb  a0ab                    BSS             (_PAT0)>>3,     0                   ;(_PAT0)>>3: Bank 511    Addr: 65451    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	PAT1= 0;
:0X1bc  a9ab                    BCC             (_PAT1)>>3,     1                   ;(_PAT1)>>3: Bank 511    Addr: 65451    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	
;	PAT5=0;//设置PA4口为输出模式
:0X1bd  adab                    BCC             (_PAT5)>>3,     5                   ;(_PAT5)>>3: Bank 511    Addr: 65451    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;			    //设置PA1端口输出低电平
;	 		    //设置PA1端口为输出口      
;	PA5=0;                 //LED置1 
:0X1be  adaa                    BCC             (_PA5)>>3,      5                   ;(_PA5)>>3: Bank 511    Addr: 65450    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;    PBT4=0;//设置PB4 为输出模式
:0X1bf  acad                    BCC             (_PBT4)>>3,     4                   ;(_PBT4)>>3: Bank 511    Addr: 65453    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	PB4=0;                      //debug 调试
:0X1c0  acac                    BCC             (_PB4)>>3,      4                   ;(_PB4)>>3: Bank 511    Addr: 65452    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;
;	//PBT5=0;
;	//PB5=0;
;	PBT5=1;//PB5为输入
:0X1c1  a5ad                    BSS             (_PBT5)>>3,     5                   ;(_PBT5)>>3: Bank 511    Addr: 65453    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	PBPU = 0x20;
:0X1c2  e520                    MOVI            0X20
:0X1c3  e6b1                    MOVA            _PBPU                               ;_PBPU: Bank 511    Addr: 65457    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	PBT6=0;
:0X1c4  aead                    BCC             (_PBT6)>>3,     6                   ;(_PBT6)>>3: Bank 511    Addr: 65453    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	PBT7=0;
:0X1c5  afad                    BCC             (_PBT7)>>3,     7                   ;(_PBT7)>>3: Bank 511    Addr: 65453    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	KMSK1=1;
:0X1c6  a198                    BSS             (_KMSK1)>>3,    1                   ;(_KMSK1)>>3: Bank 511    Addr: 65432    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	KIF = 0;     //清除KINT外部按键中断标志
:0X1c7  a89b                    BCC             (_KIF)>>3,      0                   ;(_KIF)>>3: Bank 511    Addr: 65435    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	KIE = 1;     //使能电平变化中断位
:0X1c8  a09a                    BSS             (_KIE)>>3,      0                   ;(_KIE)>>3: Bank 511    Addr: 65434    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;
;}
:0X1c9  c183                    RET
HADR_0X1CA:
;
;//*****************************************************************************
;//                             串口通讯初始化
;//*****************************************************************************
;void Iint_uart(void)
;{
;
;	PC = 0;         //设置PC端口输出低电平 
:0X1ca  e783                    CLR             HRAM_0X83
:0X1cb  e7ae                    CLR             _PC                                 ;_PC: Bank 511    Addr: 65454    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;    PCT1 = 0;       //TX方向输出
:0X1cc  a9af                    BCC             (_PCT1)>>3,     1                   ;(_PCT1)>>3: Bank 511    Addr: 65455    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;    PCT0 = 1;       //RX方向输入
:0X1cd  a0af                    BSS             (_PCT0)>>3,     0                   ;(_PCT0)>>3: Bank 511    Addr: 65455    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;    BRGH = 1;       //波特率高速模式，Fosc/(16*(BRR+1))
:0X1ce  a5e3                    BSS             (_BRGH)>>3,     5                   ;(_BRGH)>>3: Bank 511    Addr: 65507    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;    BRR = 25;       //设置波特率9600，BRR=4MHz/9600/16-1
:0X1cf  e519                    MOVI            0X19
:0X1d0  e6e4                    MOVA            _BRR                                ;_BRR: Bank 511    Addr: 65508    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;    TXM = 0;        //发送8位数据格式
:0X1d1  aee3                    BCC             (_TXM)>>3,      6                   ;(_TXM)>>3: Bank 511    Addr: 65507    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;    TXEN = 1;       //UART发送使能   
:0X1d2  a7e3                    BSS             (_TXEN)>>3,     7                   ;(_TXEN)>>3: Bank 511    Addr: 65507    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;   // RXM = 0;        //接收8位数据格式
;  //  RXEN = 1;       //UART接收使能
;	//RXIE = 1;       //UART接收中断使能
;   
;
;
;}
:0X1d3  c183                    RET
HADR_0X1D4:
;
;
;
;
;
;//*****************************************************************************
;//                            初始化
;//*****************************************************************************
;void Iint(void)
;{
;	 Iint_IO();//IO口初始化
:0X1d4  e783                    CLR             HRAM_0X83
:0X1d5  ec00                    PAGE            (_Iint_IO)>>11
:0X1d6  61b4                    CALL            HADR_0X1B4
:0X1d7  ec00                    PAGE            (_1a)>>11
;	 Iint_timer();//定时器初始化
:0X1d8  ec00                    PAGE            (_Iint_timer)>>11
:0X1d9  61a2                    CALL            HADR_0X1A2
:0X1da  ec00                    PAGE            (_1b)>>11
;	 //t0=PA0;//读原始状态
;	 Iint_uart();//串口通讯初始化
:0X1db  ec00                    PAGE            (_Iint_uart)>>11
:0X1dc  61ca                    CALL            HADR_0X1CA
:0X1dd  ec00                    PAGE            (_1c)>>11
;
;	 T_timeOn_flag=0;
:0X1de  a93e                    BCC             ((_T_timeOn_flag)>>3)&7f,       1   ;((_T_timeOn_flag)>>3)&7f: Bank 0    Addr: 62     
;
;	 T_upcnt=0;
:0X1df  ea02                    SECTION         0X2
:0X1e0  e701                    CLR             (_T_upcnt)&7f                       ;(_T_upcnt)&7f: Bank 0    Addr: 1     
;	 ADFM = 0; //转换结果高位对齐
:0X1e1  afdd                    BCC             (_ADFM)>>3,     7                   ;(_ADFM)>>3: Bank 511    Addr: 65501    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	 Send_Buf[wendu]=0x00;
:0X1e2  e500                    MOVI            0X0
:0X1e3  200e                    MOVAR           _Send_Buf+6                         ;_Send_Buf+6: Bank 0    Addr: 14     
;	 Send_Buf[liuliang_H]=0x00;
:0X1e4  e500                    MOVI            0X0
:0X1e5  200f                    MOVAR           _Send_Buf+7                         ;_Send_Buf+7: Bank 0    Addr: 15     
;	 Send_Buf[liuliang_L]=0x00;
:0X1e6  e500                    MOVI            0X0
:0X1e7  2010                    MOVAR           _Send_Buf+8                         ;_Send_Buf+8: Bank 0    Addr: 16     
;	 //Send_Buf[TDS2_H]=0x00;
;	 //Send_Buf[TDS2_L]=0x00;
;
;}
:0X1e8  ea00                    SECTION         0X0
:0X1e9  c183                    RET
HADR_0X1EA:
;
;
;//*****************************************************************************
;//                            ADC
;//*****************************************************************************
;void ADC(void)
;{
;	
;
;	ADCCL = 0x21; //使能ADC转换器，选中通道2
:0X1ea  e783                    CLR             HRAM_0X83
:0X1eb  e521                    MOVI            0X21
:0X1ec  e6dc                    MOVA            _ADCCL                              ;_ADCCL: Bank 511    Addr: 65500    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	SMPS = 1; //硬件控制ADC采样模式
:0X1ed  a2dc                    BSS             (_SMPS)>>3,     2                   ;(_SMPS)>>3: Bank 511    Addr: 65500    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;	ADTRG = 1; //触发AD转换
:0X1ee  a1dc                    BSS             (_ADTRG)>>3,    1                   ;(_ADTRG)>>3: Bank 511    Addr: 65500    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
HADR_0X1EF:
;	while( ADTRG); //等待A/D转换完成
:0X1ef  99dc                    JBC             HRAM_0XDC,      1
:0X1f0  69ef                    GOTO            HADR_0X1EF
;	ADCRH1 = (ADCRH<<8)+ADCRL; //读取AD值
:0X1f1  50db                    MOV             _ADCRH,         A                   ;_ADCRH: Bank 511    Addr: 65499    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1f2  2038                    MOVAR           _ADCDATA                            ;_ADCDATA: Bank 0    Addr: 56    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1f3  e739                    CLR             (_ADCDATA+1)&7f                     ;(_ADCDATA+1)&7f: Bank 0    Addr: 57    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1f4  5038                    MOV             (_ADCDATA)&7f,  A                   ;(_ADCDATA)&7f: Bank 0    Addr: 56    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1f5  e63b                    MOVA            (_ADCDATA+3)&7f                     ;(_ADCDATA+3)&7f: Bank 0    Addr: 59    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1f6  e73a                    CLR             (_ADCDATA+2)&7f                     ;(_ADCDATA+2)&7f: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1f7  50da                    MOV             _ADCRL,         A                   ;_ADCRL: Bank 511    Addr: 65498    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1f8  2038                    MOVAR           _ADCDATA                            ;_ADCDATA: Bank 0    Addr: 56    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1f9  e739                    CLR             (_ADCDATA+1)&7f                     ;(_ADCDATA+1)&7f: Bank 0    Addr: 57    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1fa  7838                    MOVRA           _ADCDATA                            ;_ADCDATA: Bank 0    Addr: 56    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1fb  5e3a                    ADD             (_ADCDATA+2)&7f,                A   ;(_ADCDATA+2)&7f: Bank 0    Addr: 58    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1fc  2182                    MOVAR           _ADCRH1                             ;_ADCRH1: Bank 3    Addr: 386     
:0X1fd  7839                    MOVRA           _ADCDATA+1                          ;_ADCDATA+1: Bank 0    Addr: 57    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1fe  143b                    ADDC            (_ADCDATA+3)&7f,                A   ;(_ADCDATA+3)&7f: Bank 0    Addr: 59    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X1ff  2183                    MOVAR           _ADCRH1+1                           ;_ADCRH1+1: Bank 3    Addr: 387     
;	ADCRH1=(ADCRH1>>4);
:0X200  e504                    MOVI            0X4
:0X201  e001                    ADDI            0X1
:0X202  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X203  7982                    MOVRA           _ADCRH1                             ;_ADCRH1: Bank 3    Addr: 386     
:0X204  2031                    MOVAR           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X205  7983                    MOVRA           _ADCRH1+1                           ;_ADCRH1+1: Bank 3    Addr: 387     
:0X206  2032                    MOVAR           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X207  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X208  6a0c                    GOTO            HADR_0X20C
HADR_0X209:
:0X209  a884                    BCC             HRAM_0X84,      0
:0X20a  d132                    RRB             (?_TMP+2)&7f,   R,              0X1 ;(?_TMP+2)&7f: Bank 0    Addr: 50     
:0X20b  d131                    RRB             (?_TMP+1)&7f,   R,              0X1 ;(?_TMP+1)&7f: Bank 0    Addr: 49     
HADR_0X20C:
:0X20c  e0ff                    ADDI            0XFF
:0X20d  9284                    JBS             HRAM_0X84,      2
:0X20e  6a09                    GOTO            HADR_0X209
:0X20f  7831                    MOVRA           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X210  2182                    MOVAR           _ADCRH1                             ;_ADCRH1: Bank 3    Addr: 386     
:0X211  7832                    MOVRA           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X212  2183                    MOVAR           _ADCRH1+1                           ;_ADCRH1+1: Bank 3    Addr: 387     
;	ADsum=ADsum+ADCRH1;
:0X213  7982                    MOVRA           _ADCRH1                             ;_ADCRH1: Bank 3    Addr: 386     
:0X214  ea03                    SECTION         0X3
:0X215  5e05                    ADD             (_ADsum)&7f,    A                   ;(_ADsum)&7f: Bank 0    Addr: 5     
:0X216  2185                    MOVAR           _ADsum                              ;_ADsum: Bank 3    Addr: 389     
:0X217  7983                    MOVRA           _ADCRH1+1                           ;_ADCRH1+1: Bank 3    Addr: 387     
:0X218  1406                    ADDC            (_ADsum+1)&7f,  A                   ;(_ADsum+1)&7f: Bank 0    Addr: 6     
:0X219  2186                    MOVAR           _ADsum+1                            ;_ADsum+1: Bank 3    Addr: 390     
;	ADcnt++;
:0X21a  5504                    INC             (_ADcnt)&7f,    R                   ;(_ADcnt)&7f: Bank 0    Addr: 4     
;	if(ADcnt>7)	
:0X21b  7984                    MOVRA           _ADcnt                              ;_ADcnt: Bank 3    Addr: 388     
:0X21c  ce07                    SUBI            0X7
:0X21d  9884                    JBC             HRAM_0X84,      0
:0X21e  6a4f                    GOTO            HADR_0X24F
;	{
;		
;		ADture=(ADsum>>3);
:0X21f  e503                    MOVI            0X3
:0X220  e001                    ADDI            0X1
:0X221  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X222  7985                    MOVRA           _ADsum                              ;_ADsum: Bank 3    Addr: 389     
:0X223  2031                    MOVAR           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X224  7986                    MOVRA           _ADsum+1                            ;_ADsum+1: Bank 3    Addr: 390     
:0X225  2032                    MOVAR           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X226  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X227  6a2c                    GOTO            HADR_0X22C
HADR_0X228:
:0X228  a884                    BCC             HRAM_0X84,      0
:0X229  ea00                    SECTION         0X0
:0X22a  d132                    RRB             (?_TMP+2)&7f,   R,              0X1 ;(?_TMP+2)&7f: Bank 0    Addr: 50     
:0X22b  d131                    RRB             (?_TMP+1)&7f,   R,              0X1 ;(?_TMP+1)&7f: Bank 0    Addr: 49     
HADR_0X22C:
:0X22c  e0ff                    ADDI            0XFF
:0X22d  9284                    JBS             HRAM_0X84,      2
:0X22e  6a28                    GOTO            HADR_0X228
:0X22f  7831                    MOVRA           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X230  2102                    MOVAR           _ADture                             ;_ADture: Bank 2    Addr: 258     
:0X231  7832                    MOVRA           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X232  2103                    MOVAR           _ADture+1                           ;_ADture+1: Bank 2    Addr: 259     
;		Send_Buf[ADture_L]=ADture;
:0X233  7902                    MOVRA           _ADture                             ;_ADture: Bank 2    Addr: 258     
:0X234  200d                    MOVAR           _Send_Buf+5                         ;_Send_Buf+5: Bank 0    Addr: 13     
;		ADture=ADture>>8;
:0X235  e508                    MOVI            0X8
:0X236  e001                    ADDI            0X1
:0X237  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X238  7902                    MOVRA           _ADture                             ;_ADture: Bank 2    Addr: 258     
:0X239  2031                    MOVAR           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X23a  7903                    MOVRA           _ADture+1                           ;_ADture+1: Bank 2    Addr: 259     
:0X23b  2032                    MOVAR           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X23c  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X23d  6a42                    GOTO            HADR_0X242
HADR_0X23E:
:0X23e  a884                    BCC             HRAM_0X84,      0
:0X23f  ea00                    SECTION         0X0
:0X240  d132                    RRB             (?_TMP+2)&7f,   R,              0X1 ;(?_TMP+2)&7f: Bank 0    Addr: 50     
:0X241  d131                    RRB             (?_TMP+1)&7f,   R,              0X1 ;(?_TMP+1)&7f: Bank 0    Addr: 49     
HADR_0X242:
:0X242  e0ff                    ADDI            0XFF
:0X243  9284                    JBS             HRAM_0X84,      2
:0X244  6a3e                    GOTO            HADR_0X23E
:0X245  7831                    MOVRA           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X246  2102                    MOVAR           _ADture                             ;_ADture: Bank 2    Addr: 258     
:0X247  7832                    MOVRA           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X248  2103                    MOVAR           _ADture+1                           ;_ADture+1: Bank 2    Addr: 259     
;		Send_Buf[ADture_H]=ADture;
:0X249  7902                    MOVRA           _ADture                             ;_ADture: Bank 2    Addr: 258     
:0X24a  200c                    MOVAR           _Send_Buf+4                         ;_Send_Buf+4: Bank 0    Addr: 12     
;
;		ADcnt=0;
:0X24b  ea03                    SECTION         0X3
:0X24c  e704                    CLR             (_ADcnt)&7f                         ;(_ADcnt)&7f: Bank 0    Addr: 4     
;		ADsum=0;
:0X24d  e705                    CLR             (_ADsum)&7f                         ;(_ADsum)&7f: Bank 0    Addr: 5     
:0X24e  e706                    CLR             (_ADsum+1)&7f                       ;(_ADsum+1)&7f: Bank 0    Addr: 6     
HADR_0X24F:
;	}
;	
;	//delay(7);
;	//ADCCL = 0x41; //使能ADC转换器，选中通道4
;	//SMPS = 1; //硬件控制ADC采样模式
;	//ADTRG = 1; //触发AD转换
;	//while( ADTRG); //等待A/D转换完成
;	//ADCRH1_WD = (ADCRH<<8)+ADCRL; //读取AD值
;	//ADsum_WD=ADsum_WD+ADCRH1_WD;
;	//ADcnt_WD++;
;	//if(ADcnt_WD>7)	
;	//{
;		
;		//ADture_WD=(ADsum_WD>>3);
;		
;		//Send_Buf[wendu]=ADture_WD;
;
;		//ADcnt_WD=0;
;		//ADsum_WD=0;
;	//}
;
;
;
;}
:0X24f  ea00                    SECTION         0X0
:0X250  c183                    RET
HADR_0X251:
;
;//*****************************************************************************
;//                           TDS 
;//*****************************************************************************
;uint16 watch_TDS(unsigned int fey)
;{
;	 unsigned int TDS_jisuan;
;	if((fey>=35)&&(fey<=519))
;	{
;		a=482;
;		b=13;
;		TDS_jisuan=(((fey-b)*100)/a);
;	
;	}
;	if((fey>519)&&(fey<=1678))  //TDS 在108 和 540 之前
;	{
;		a=27;
;		b=230;
;		TDS_jisuan=(((fey-b)*10)/a);
;	
;	}
;	if((fey>1678)&&fey<4000)
;	{
;	
;		a=15;
;		b=868;
;		TDS_jisuan=(((fey-b)*10)/a);
;	
;	
;	
;	}
;	
;	if(fey>4000)
;	{
;		TDS_jisuan=2000;
;	
;	}
;	if(fey<=35)
;	{
;		TDS_jisuan=1;
;	
;	}
;
;	return (TDS_jisuan);
;
;
;
;}
;
;
;
;
;
;//*****************************************************************************
;//                            比较程序 挑出最大最小值 去掉 取平均值
;//*****************************************************************************
;unsigned char	frequencydata_del(unsigned char temp[Len])
;{
;	
;	unsigned char max=temp[0],min=temp[0],i;
;	unsigned int avg;
;	unsigned int T_sum;
;	//for(i=1;i<Len;i++)
;	//{
;		//if(temp[i]>max)
;		//{
;		
;			//max=temp[i];
;		//}
;		//else if(temp[i]<min)
;		//{
;			//min=temp[i];
;		
;		//}
;	
;	//}
;	for(i=0;i<Len;i++)
;	{
;		
;		T_sum=T_sum+temp[i];
;	
;	}
;	//T_sum=((T_sum-max)-min);
;
;	//avg=(T_sum>>3);
;	avg=T_sum/10;
;
;	return(avg);
;}
;
;void UART(void)
;{
;
;	while(!TRMT);           //等待发送移位寄存器TXR空
;				//TXB  =  0x55;   //发送字符串
;				//TXB  = TDS_ture;
;				if(i==0)
;					//TXB=TDS_temp[0];
;					TXB=0x01;
;					//TXB=T8N;
;                else if(i==1)
;					//TXB=TDS_temp[1];
;					TXB=0x02;
;					//TXB=T8N;
;					i++;
;					if(i>1)
;						i=0;
;				 //TXB  =  TDS_frequency;   //发送字符串
;					//		TXB  = TDS_cnt;
;				   //UART_0_UartPutChar(cpSendBufPtr[iSendCounter++]);
;				 //TXB=cpSendBufPtr[iSendCounter];
;				 while(!TXIF);           //等待发送中断标志位 
;				 TXIF = 0;               //清发送中断标志位 
;
;
;
;
;}
;
;
;
;//*****************************************************************************
;//                              中断服务程序
;//*****************************************************************************
;void TDS_DEL(void)
;{
;	    if(flag)
:0X251  e783                    CLR             HRAM_0X83
:0X252  933e                    JBS             HRAM_0X3E,      3
:0X253  6ab9                    GOTO            HADR_0X2B9
;		{
;			
;				//WDserch(TDS1_frequency);
;				//WDserch(788);
;				//WDserch(45);
;
;				//TDSfrequency_temp=((TDS1_frequency+612)/11);
;				//TDSfrequency_temp_yushu=((TDS1_frequency+612)%11);
;				//TDSfrequency_temp=(TDSfrequency_temp+TDSfrequency_temp_yushu);
;
;				//TDSfrequency_temp=watch_TDS(TDS1_frequency);
;				TDS_IN_ture=TDS1_frequency;
:0X254  7988                    MOVRA           _TDS1_frequency                     ;_TDS1_frequency: Bank 3    Addr: 392     
:0X255  2191                    MOVAR           _TDS_IN_ture                        ;_TDS_IN_ture: Bank 3    Addr: 401     
:0X256  7989                    MOVRA           _TDS1_frequency+1                   ;_TDS1_frequency+1: Bank 3    Addr: 393     
:0X257  2192                    MOVAR           _TDS_IN_ture+1                      ;_TDS_IN_ture+1: Bank 3    Addr: 402     
;				//TDSfrequency_temp=	TDS1_frequency;
;				Send_Buf[TDS1_L]=TDSfrequency_temp;
:0X258  798c                    MOVRA           _TDSfrequency_temp                  ;_TDSfrequency_temp: Bank 3    Addr: 396     
:0X259  2009                    MOVAR           _Send_Buf+1                         ;_Send_Buf+1: Bank 0    Addr: 9     
;				TDSfrequency_temp=TDSfrequency_temp>>8;
:0X25a  e508                    MOVI            0X8
:0X25b  e001                    ADDI            0X1
:0X25c  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X25d  798c                    MOVRA           _TDSfrequency_temp                  ;_TDSfrequency_temp: Bank 3    Addr: 396     
:0X25e  2031                    MOVAR           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X25f  798d                    MOVRA           _TDSfrequency_temp+1                ;_TDSfrequency_temp+1: Bank 3    Addr: 397     
:0X260  2032                    MOVAR           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X261  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X262  6a66                    GOTO            HADR_0X266
HADR_0X263:
:0X263  a884                    BCC             HRAM_0X84,      0
:0X264  d132                    RRB             (?_TMP+2)&7f,   R,              0X1 ;(?_TMP+2)&7f: Bank 0    Addr: 50     
:0X265  d131                    RRB             (?_TMP+1)&7f,   R,              0X1 ;(?_TMP+1)&7f: Bank 0    Addr: 49     
HADR_0X266:
:0X266  e0ff                    ADDI            0XFF
:0X267  9284                    JBS             HRAM_0X84,      2
:0X268  6a63                    GOTO            HADR_0X263
:0X269  7831                    MOVRA           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X26a  218c                    MOVAR           _TDSfrequency_temp                  ;_TDSfrequency_temp: Bank 3    Addr: 396     
:0X26b  7832                    MOVRA           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X26c  218d                    MOVAR           _TDSfrequency_temp+1                ;_TDSfrequency_temp+1: Bank 3    Addr: 397     
;				Send_Buf[TDS1_H]=TDSfrequency_temp;
:0X26d  798c                    MOVRA           _TDSfrequency_temp                  ;_TDSfrequency_temp: Bank 3    Addr: 396     
:0X26e  2008                    MOVAR           _Send_Buf                           ;_Send_Buf: Bank 0    Addr: 8     
;				
;				
;				 
;				Send_Buf[TDS1_f_L]=TDS_IN_ture;
:0X26f  7991                    MOVRA           _TDS_IN_ture                        ;_TDS_IN_ture: Bank 3    Addr: 401     
:0X270  2012                    MOVAR           _Send_Buf+10                        ;_Send_Buf+10: Bank 0    Addr: 18     
;				TDS_IN_ture=TDS_IN_ture>>8;
:0X271  e508                    MOVI            0X8
:0X272  e001                    ADDI            0X1
:0X273  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X274  7991                    MOVRA           _TDS_IN_ture                        ;_TDS_IN_ture: Bank 3    Addr: 401     
:0X275  2031                    MOVAR           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X276  7992                    MOVRA           _TDS_IN_ture+1                      ;_TDS_IN_ture+1: Bank 3    Addr: 402     
:0X277  2032                    MOVAR           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X278  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X279  6a7d                    GOTO            HADR_0X27D
HADR_0X27A:
:0X27a  a884                    BCC             HRAM_0X84,      0
:0X27b  d132                    RRB             (?_TMP+2)&7f,   R,              0X1 ;(?_TMP+2)&7f: Bank 0    Addr: 50     
:0X27c  d131                    RRB             (?_TMP+1)&7f,   R,              0X1 ;(?_TMP+1)&7f: Bank 0    Addr: 49     
HADR_0X27D:
:0X27d  e0ff                    ADDI            0XFF
:0X27e  9284                    JBS             HRAM_0X84,      2
:0X27f  6a7a                    GOTO            HADR_0X27A
:0X280  7831                    MOVRA           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X281  2191                    MOVAR           _TDS_IN_ture                        ;_TDS_IN_ture: Bank 3    Addr: 401     
:0X282  7832                    MOVRA           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X283  2192                    MOVAR           _TDS_IN_ture+1                      ;_TDS_IN_ture+1: Bank 3    Addr: 402     
;				Send_Buf[TDS1_f_H]=TDS_IN_ture;
:0X284  7991                    MOVRA           _TDS_IN_ture                        ;_TDS_IN_ture: Bank 3    Addr: 401     
:0X285  2011                    MOVAR           _Send_Buf+9                         ;_Send_Buf+9: Bank 0    Addr: 17     
;
;				//WDserch(TDS2_frequency);
;				//TDSfrequency_temp=watch_TDS(TDS2_frequency);
;				//TDS_OUT_ture=TDSfrequency_temp;
;				//TDSfrequency_temp=	TDS2_frequency;
;				TDS_OUT_ture=TDS2_frequency;
:0X286  798a                    MOVRA           _TDS2_frequency                     ;_TDS2_frequency: Bank 3    Addr: 394     
:0X287  2193                    MOVAR           _TDS_OUT_ture                       ;_TDS_OUT_ture: Bank 3    Addr: 403     
:0X288  798b                    MOVRA           _TDS2_frequency+1                   ;_TDS2_frequency+1: Bank 3    Addr: 395     
:0X289  2194                    MOVAR           _TDS_OUT_ture+1                     ;_TDS_OUT_ture+1: Bank 3    Addr: 404     
;
;				Send_Buf[TDS2_L]=TDSfrequency_temp;
:0X28a  798c                    MOVRA           _TDSfrequency_temp                  ;_TDSfrequency_temp: Bank 3    Addr: 396     
:0X28b  200b                    MOVAR           _Send_Buf+3                         ;_Send_Buf+3: Bank 0    Addr: 11     
;				
;				TDSfrequency_temp=TDSfrequency_temp>>8;
:0X28c  e508                    MOVI            0X8
:0X28d  e001                    ADDI            0X1
:0X28e  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X28f  798c                    MOVRA           _TDSfrequency_temp                  ;_TDSfrequency_temp: Bank 3    Addr: 396     
:0X290  2031                    MOVAR           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X291  798d                    MOVRA           _TDSfrequency_temp+1                ;_TDSfrequency_temp+1: Bank 3    Addr: 397     
:0X292  2032                    MOVAR           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X293  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X294  6a98                    GOTO            HADR_0X298
HADR_0X295:
:0X295  a884                    BCC             HRAM_0X84,      0
:0X296  d132                    RRB             (?_TMP+2)&7f,   R,              0X1 ;(?_TMP+2)&7f: Bank 0    Addr: 50     
:0X297  d131                    RRB             (?_TMP+1)&7f,   R,              0X1 ;(?_TMP+1)&7f: Bank 0    Addr: 49     
HADR_0X298:
:0X298  e0ff                    ADDI            0XFF
:0X299  9284                    JBS             HRAM_0X84,      2
:0X29a  6a95                    GOTO            HADR_0X295
:0X29b  7831                    MOVRA           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X29c  218c                    MOVAR           _TDSfrequency_temp                  ;_TDSfrequency_temp: Bank 3    Addr: 396     
:0X29d  7832                    MOVRA           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X29e  218d                    MOVAR           _TDSfrequency_temp+1                ;_TDSfrequency_temp+1: Bank 3    Addr: 397     
;				
;				Send_Buf[TDS2_H]=TDSfrequency_temp;
:0X29f  798c                    MOVRA           _TDSfrequency_temp                  ;_TDSfrequency_temp: Bank 3    Addr: 396     
:0X2a0  200a                    MOVAR           _Send_Buf+2                         ;_Send_Buf+2: Bank 0    Addr: 10     
;
;
;				Send_Buf[TDS2_f_L]=TDS_OUT_ture;
:0X2a1  7993                    MOVRA           _TDS_OUT_ture                       ;_TDS_OUT_ture: Bank 3    Addr: 403     
:0X2a2  2014                    MOVAR           _Send_Buf+12                        ;_Send_Buf+12: Bank 0    Addr: 20     
;				TDS_OUT_ture=TDS_OUT_ture>>8;
:0X2a3  e508                    MOVI            0X8
:0X2a4  e001                    ADDI            0X1
:0X2a5  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X2a6  7993                    MOVRA           _TDS_OUT_ture                       ;_TDS_OUT_ture: Bank 3    Addr: 403     
:0X2a7  2031                    MOVAR           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X2a8  7994                    MOVRA           _TDS_OUT_ture+1                     ;_TDS_OUT_ture+1: Bank 3    Addr: 404     
:0X2a9  2032                    MOVAR           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X2aa  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X2ab  6aaf                    GOTO            HADR_0X2AF
HADR_0X2AC:
:0X2ac  a884                    BCC             HRAM_0X84,      0
:0X2ad  d132                    RRB             (?_TMP+2)&7f,   R,              0X1 ;(?_TMP+2)&7f: Bank 0    Addr: 50     
:0X2ae  d131                    RRB             (?_TMP+1)&7f,   R,              0X1 ;(?_TMP+1)&7f: Bank 0    Addr: 49     
HADR_0X2AF:
:0X2af  e0ff                    ADDI            0XFF
:0X2b0  9284                    JBS             HRAM_0X84,      2
:0X2b1  6aac                    GOTO            HADR_0X2AC
:0X2b2  7831                    MOVRA           ?_TMP+1                             ;?_TMP+1: Bank 0    Addr: 49     
:0X2b3  2193                    MOVAR           _TDS_OUT_ture                       ;_TDS_OUT_ture: Bank 3    Addr: 403     
:0X2b4  7832                    MOVRA           ?_TMP+2                             ;?_TMP+2: Bank 0    Addr: 50     
:0X2b5  2194                    MOVAR           _TDS_OUT_ture+1                     ;_TDS_OUT_ture+1: Bank 3    Addr: 404     
;				Send_Buf[TDS2_f_H]=TDS_OUT_ture;
:0X2b6  7993                    MOVRA           _TDS_OUT_ture                       ;_TDS_OUT_ture: Bank 3    Addr: 403     
:0X2b7  2013                    MOVAR           _Send_Buf+11                        ;_Send_Buf+11: Bank 0    Addr: 19     
;		   
;		       //frequency_cnt++;
;			   //TDS1_sum=TDS1_sum+
;			   //if(frequency_cnt>7)
;			   //{
;					//frequency_cnt=0;
;
;			   //}
;
;
;			
;			//frequency_cnt++;
;			//if(frequency_cnt>=Len)
;			//{
;				//frequency_sum_cnt++;/*记下赋值的重复次数*/
;				//frequency_cnt=0;
;			//}
;			//if(frequency_sum_cnt>=frequency_sum_len )//数组正赋值次数达到设定次数次时
;			//{
;				//TDS_ture=frequencydata_del(temp_frequency);
;				
;				
;				//frequency_sum_cnt=0;
;
;			//}
;			//TimeOn_flag=0;
;			///*if(frequency_sum_flag)/*开始从temp_frequency[0]-temp_frequency[9]*/
;			//{
;				//frequency_cnt++;
;            //}
;			//else/*之后从temp_frequency[9]-temp_frequency[0]赋值*/
;			//{
;				//if(frequency_cnt>0)
;					//frequency_cnt--;
;                //else if(frequency_cnt==0)
;				//{
;					
;					//frequency_sum_flag=1;
;					//frequency_sum_cnt++;/*记下赋值的重复次数*/
;				//}
;			
;			//}
;			 //if(frequency_cnt>=Len)/*赋值到最大*/
;			//{
;				//frequency_sum_flag=0;
;				//frequency_cnt=(frequency_cnt-1);
;				
;			//}
;
;			//if(frequency_sum_cn>=frequency_sum_len )//数组正赋值次数达到设定次数次时
;			//{
;			
;			
;			
;			
;				
;			//}*/
;
;
;
;			flag=0;
:0X2b8  ab3e                    BCC             ((_flag)>>3)&7f,                3   ;((_flag)>>3)&7f: Bank 0    Addr: 62     
HADR_0X2B9:
;        }
;
;		
;		
;
;
;
;
;}
:0X2b9  c183                    RET
HADR_0X2BA:
;//*****************************************************************************
;//                              串口通讯程序
;//*****************************************************************************
;void UART_putchar(void)	
;{
;	   
;	   
;		switch(putchar_step)
:0X2ba  e783                    CLR             HRAM_0X83
:0X2bb  ea03                    SECTION         0X3
:0X2bc  5015                    MOV             (_putchar_step)&7f,             A   ;(_putchar_step)&7f: Bank 0    Addr: 21     
:0X2bd  e300                    XORI            0X0
:0X2be  9a84                    JBC             HRAM_0X84,      2
:0X2bf  6acb                    GOTO            HADR_0X2CB
:0X2c0  e301                    XORI            0X1
:0X2c1  9a84                    JBC             HRAM_0X84,      2
:0X2c2  6ad2                    GOTO            HADR_0X2D2
:0X2c3  e303                    XORI            0X3
:0X2c4  9a84                    JBC             HRAM_0X84,      2
:0X2c5  6af2                    GOTO            HADR_0X2F2
:0X2c6  e301                    XORI            0X1
:0X2c7  9a84                    JBC             HRAM_0X84,      2
:0X2c8  6b03                    GOTO            HADR_0X303
:0X2c9  6aca                    GOTO            HADR_0X2CA
HADR_0X2CA:
:0X2ca  6b08                    GOTO            HADR_0X308
HADR_0X2CB:
;		{
;			case 0:
:0X2cb  ec00                    PAGE            (_SendDataToWifi)>>11
:0X2cc  ea00                    SECTION         0X0
:0X2cd  6181                    CALL            HADR_0X181
:0X2ce  ec00                    PAGE            (_24)>>11
;				}
;		
;				putchar_step++;
:0X2cf  ea03                    SECTION         0X3
:0X2d0  5515                    INC             (_putchar_step)&7f,             R   ;(_putchar_step)&7f: Bank 0    Addr: 21     
;				break;
:0X2d1  6b08                    GOTO            HADR_0X308
HADR_0X2D2:
;		    case 1:
;			   
;				/*while(!TRMT);           //等待发送移位寄存器TXR空
;				
;				 TXB=cBuf[iSendCounter];
;				 while(!TXIF);           //等待发送中断标志位 
;				 TXIF = 0;        */       //清发送中断标志位 
;				 //if(iSendCounter < iUartSendLen+1)
;
;				while((!TRMT)||(!TXIF));
:0X2d2  91e3                    JBS             HRAM_0XE3,      1
:0X2d3  6ad2                    GOTO            HADR_0X2D2
:0X2d4  909f                    JBS             HRAM_0X9F,      0
:0X2d5  6ad2                    GOTO            HADR_0X2D2
;				 TXB=cBuf[iSendCounter];
:0X2d6  782e                    MOVRA           _iSendCounter                       ;_iSendCounter: Bank 0    Addr: 46     
:0X2d7  2038                    MOVAR           _UART_putcharDATA                   ;_UART_putcharDATA: Bank 0    Addr: 56    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X2d8  7838                    MOVRA           _UART_putcharDATA                   ;_UART_putcharDATA: Bank 0    Addr: 56    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X2d9  e015                    ADDI            _cBuf
:0X2da  2039                    MOVAR           _UART_putcharDATA+1                 ;_UART_putcharDATA+1: Bank 0    Addr: 57    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X2db  7839                    MOVRA           _UART_putcharDATA+1                 ;_UART_putcharDATA+1: Bank 0    Addr: 57    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
:0X2dc  e681                    MOVA            HRAM_0X81
:0X2dd  e500                    MOVI            0X0
:0X2de  e682                    MOVA            HRAM_0X82
:0X2df  5080                    MOV             HRAM_0X80,      A
:0X2e0  2030                    MOVAR           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X2e1  7830                    MOVRA           ?_TMP                               ;?_TMP: Bank 0    Addr: 48     
:0X2e2  e6e2                    MOVA            _TXB                                ;_TXB: Bank 511    Addr: 65506    G:\5.23\1211\HRCC Project Application1\HRCC Project Application1\debug\sample.obj 
;
;					iSendCounter++;
:0X2e3  ea00                    SECTION         0X0
:0X2e4  552e                    INC             (_iSendCounter)&7f,             R   ;(_iSendCounter)&7f: Bank 0    Addr: 46     
:0X2e5  9a84                    JBC             HRAM_0X84,      2
:0X2e6  552f                    INC             (_iSendCounter+1)&7f,           R   ;(_iSendCounter+1)&7f: Bank 0    Addr: 47     
;         //if(iSendCounter>=(iUartSendLen+1))
;				if(iSendCounter>=24)
:0X2e7  e500                    MOVI            0X0
:0X2e8  ee2f                    SUB             (_iSendCounter+1)&7f,           A   ;(_iSendCounter+1)&7f: Bank 0    Addr: 47     
:0X2e9  9284                    JBS             HRAM_0X84,      2
:0X2ea  6aed                    GOTO            HADR_0X2ED
:0X2eb  e518                    MOVI            0X18
:0X2ec  ee2e                    SUB             (_iSendCounter)&7f,             A   ;(_iSendCounter)&7f: Bank 0    Addr: 46     
HADR_0X2ED:
:0X2ed  9084                    JBS             HRAM_0X84,      0
:0X2ee  6b08                    GOTO            HADR_0X308
;				 {
;					
;					
;				    putchar_step++;
:0X2ef  ea03                    SECTION         0X3
:0X2f0  5515                    INC             (_putchar_step)&7f,             R   ;(_putchar_step)&7f: Bank 0    Addr: 21     
;					
;				 }
;
;				break;
:0X2f1  6b08                    GOTO            HADR_0X308
HADR_0X2F2:
;			case 2:
:0X2f2  ea02                    SECTION         0X2
:0X2f3  5508                    INC             (_uartsendcnt)&7f,              R   ;(_uartsendcnt)&7f: Bank 0    Addr: 8     
:0X2f4  9a84                    JBC             HRAM_0X84,      2
:0X2f5  5509                    INC             (_uartsendcnt+1)&7f,            R   ;(_uartsendcnt+1)&7f: Bank 0    Addr: 9     
;				if(uartsendcnt>8000) 
:0X2f6  7909                    MOVRA           _uartsendcnt+1                      ;_uartsendcnt+1: Bank 2    Addr: 265     
:0X2f7  ce1f                    SUBI            0X1F
:0X2f8  9284                    JBS             HRAM_0X84,      2
:0X2f9  6afc                    GOTO            HADR_0X2FC
:0X2fa  7908                    MOVRA           _uartsendcnt                        ;_uartsendcnt: Bank 2    Addr: 264     
:0X2fb  ce40                    SUBI            0X40
HADR_0X2FC:
:0X2fc  9884                    JBC             HRAM_0X84,      0
:0X2fd  6b08                    GOTO            HADR_0X308
;				{
;					uartsendcnt=0;
:0X2fe  e708                    CLR             (_uartsendcnt)&7f                   ;(_uartsendcnt)&7f: Bank 0    Addr: 8     
:0X2ff  e709                    CLR             (_uartsendcnt+1)&7f                 ;(_uartsendcnt+1)&7f: Bank 0    Addr: 9     
;					putchar_step++;
:0X300  ea03                    SECTION         0X3
:0X301  5515                    INC             (_putchar_step)&7f,             R   ;(_putchar_step)&7f: Bank 0    Addr: 21     
;				}
;				
;				break;
:0X302  6b08                    GOTO            HADR_0X308
HADR_0X303:
;			case 3:
:0X303  ea00                    SECTION         0X0
:0X304  e72e                    CLR             (_iSendCounter)&7f                  ;(_iSendCounter)&7f: Bank 0    Addr: 46     
:0X305  e72f                    CLR             (_iSendCounter+1)&7f                ;(_iSendCounter+1)&7f: Bank 0    Addr: 47     
;				putchar_step=0;
:0X306  ea03                    SECTION         0X3
:0X307  e715                    CLR             (_putchar_step)&7f                  ;(_putchar_step)&7f: Bank 0    Addr: 21     
HADR_0X308:
;				break;
;
;		
;		}
;
;		 
;
;
;
;
;
;
;}
:0X308  ea00                    SECTION         0X0
:0X309  c183                    RET
HADR_0X30A:
;
;
;	 
;//*****************************************************************************
;//                           时基程序
;//*****************************************************************************
;void Timer(void)
;{
;    
;	  
;		if(Timer1S_cnt<65520)
:0X30a  e783                    CLR             HRAM_0X83
:0X30b  e5ff                    MOVI            0XFF
:0X30c  ea03                    SECTION         0X3
:0X30d  ee01                    SUB             (_Timer1S_cnt+1)&7f,            A   ;(_Timer1S_cnt+1)&7f: Bank 0    Addr: 1     
:0X30e  9284                    JBS             HRAM_0X84,      2
:0X30f  6b12                    GOTO            HADR_0X312
:0X310  e5f0                    MOVI            0XF0
:0X311  ee00                    SUB             (_Timer1S_cnt)&7f,              A   ;(_Timer1S_cnt)&7f: Bank 0    Addr: 0     
HADR_0X312:
:0X312  9884                    JBC             HRAM_0X84,      0
:0X313  6b17                    GOTO            HADR_0X317
;			Timer1S_cnt++;
:0X314  5500                    INC             (_Timer1S_cnt)&7f,              R   ;(_Timer1S_cnt)&7f: Bank 0    Addr: 0     
:0X315  9a84                    JBC             HRAM_0X84,      2
:0X316  5501                    INC             (_Timer1S_cnt+1)&7f,            R   ;(_Timer1S_cnt+1)&7f: Bank 0    Addr: 1     
HADR_0X317:
;		if(Timer1S_cnt>=10000)
:0X317  e527                    MOVI            0X27
:0X318  ee01                    SUB             (_Timer1S_cnt+1)&7f,            A   ;(_Timer1S_cnt+1)&7f: Bank 0    Addr: 1     
:0X319  9284                    JBS             HRAM_0X84,      2
:0X31a  6b1d                    GOTO            HADR_0X31D
:0X31b  e510                    MOVI            0X10
:0X31c  ee00                    SUB             (_Timer1S_cnt)&7f,              A   ;(_Timer1S_cnt)&7f: Bank 0    Addr: 0     
HADR_0X31D:
:0X31d  9084                    JBS             HRAM_0X84,      0
:0X31e  6b23                    GOTO            HADR_0X323
;		{
;			Timer1S_cnt=0;
:0X31f  e700                    CLR             (_Timer1S_cnt)&7f                   ;(_Timer1S_cnt)&7f: Bank 0    Addr: 0     
:0X320  e701                    CLR             (_Timer1S_cnt+1)&7f                 ;(_Timer1S_cnt+1)&7f: Bank 0    Addr: 1     
;			Timer1S_flag=1;
:0X321  ea00                    SECTION         0X0
:0X322  a03e                    BSS             ((_Timer1S_flag)>>3)&7f,        0   ;((_Timer1S_flag)>>3)&7f: Bank 0    Addr: 62     
HADR_0X323:
;			
;		}
:0X323  ea00                    SECTION         0X0
:0X324  903e                    JBS             HRAM_0X3E,      0
:0X325  6b2e                    GOTO            HADR_0X32E
;	{
;		
;		if(POWERSTART_cnt<12)
:0X326  e50c                    MOVI            0XC
:0X327  ea03                    SECTION         0X3
:0X328  ee07                    SUB             (_POWERSTART_cnt)&7f,           A   ;(_POWERSTART_cnt)&7f: Bank 0    Addr: 7     
:0X329  9884                    JBC             HRAM_0X84,      0
:0X32a  6b2c                    GOTO            HADR_0X32C
;			POWERSTART_cnt++;
:0X32b  5507                    INC             (_POWERSTART_cnt)&7f,           R   ;(_POWERSTART_cnt)&7f: Bank 0    Addr: 7     
HADR_0X32C:
;		
;		Timer1S_flag=0;
:0X32c  ea00                    SECTION         0X0
:0X32d  a83e                    BCC             ((_Timer1S_flag)>>3)&7f,        0   ;((_Timer1S_flag)>>3)&7f: Bank 0    Addr: 62     
HADR_0X32E:
;
;	}
;
;
;
;
;
;}
:0X32e  c183                    RET

                                END
