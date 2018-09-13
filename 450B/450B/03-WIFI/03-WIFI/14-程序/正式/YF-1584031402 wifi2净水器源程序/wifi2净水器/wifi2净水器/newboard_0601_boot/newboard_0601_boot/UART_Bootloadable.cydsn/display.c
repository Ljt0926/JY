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
#define _DISPLAY_
#include "config.h"
void Led_Pannel_Shutdown(void)
{
	LED_FC_Write(1);
	LED_BC_Write(1);  
	LED_PP_Write(1); 
	LED_RO1_Write(1); 
	LED_RO2_Write(1); 
	LED_RO3_Write(1);
	LED_WIFI_Write(1); 
	LED_KEY_SETTING_Write(1); 
	LED_KEY_WIFI_Write(1);
}

void Led_Pannel_Test(uint8 sn)
{
	switch (sn)
	{
		case 0:
			LED_PP_Write(0); 
			LED_FC_Write(0);
			LED_RO1_Write(0); 
			break;
		case 1:
			LED_RO2_Write(0); 
			LED_RO3_Write(0); 
			LED_BC_Write(0);
			break;
		case 2:
			LED_WIFI_Write(0); 
			LED_KEY_SETTING_Write(0); 
			LED_KEY_WIFI_Write(0);
			break;
		default:
			break;
			
	}	
}
void Led_Pannel_Filter_Setting(uint8 sn)
{
		//**************wified show
	if(DisFlag_Wifi.on_wifi==1)
		{
			LED_WIFI_Write(0);
		}
	else if (DisFlag_Wifi.off_wifi==1) 
		{
			LED_WIFI_Write(1);
		}
	else if(DisFlag_Wifi.sflash_wifi==1)
		{
			if(F_Ssync_Clock)
				{
					LED_WIFI_Write(1);
				}
			else
				{
					LED_WIFI_Write(0);
				}
		}
	else if(DisFlag_Wifi.fflash_wifi==1)
		{
			if(F_Fsync_Clock)
				{
					LED_WIFI_Write(1);
				}
			else
				{
					LED_WIFI_Write(0);
				}
		}
	switch (sn)
	{
		case 0:
			LED_PP_Write(0); 
			LED_FC_Write(1);
			LED_RO1_Write(1); 
			LED_RO2_Write(1); 
			LED_RO3_Write(1); 
			LED_BC_Write(1);
			break;
		case 1:
			LED_PP_Write(1); 
			LED_FC_Write(0);
			LED_RO1_Write(1); 
			LED_RO2_Write(1); 
			LED_RO3_Write(1); 
			LED_BC_Write(1);
			break;
		case 2:
			LED_PP_Write(1); 
			LED_FC_Write(1);
			LED_RO1_Write(0); 
			LED_RO2_Write(1); 
			LED_RO3_Write(1); 
			LED_BC_Write(1);
			break;
		case 3:
			LED_PP_Write(1); 
			LED_FC_Write(1);
			LED_RO1_Write(1); 
			LED_RO2_Write(0); 
			LED_RO3_Write(1); 
			LED_BC_Write(1);
			break;
		case 4:
			LED_PP_Write(1); 
			LED_FC_Write(1);
			LED_RO1_Write(1); 
			LED_RO2_Write(1); 
			LED_RO3_Write(0); 
			LED_BC_Write(1);
			break;
		case 5:
			LED_PP_Write(1); 
			LED_FC_Write(1);
			LED_RO1_Write(1); 
			LED_RO2_Write(1); 
			LED_RO3_Write(1); 
			LED_BC_Write(0);
			break;
		default:
			break;
			
	}
}

void Led_Pannel_Display(void)		
{
	//**************key_show
	LED_KEY_WIFI_Write(0);
	LED_KEY_SETTING_Write(0);
	//**************wified show
	if(DisFlag_Wifi.on_wifi==1)
		{
			LED_WIFI_Write(0);
		}
	else if (DisFlag_Wifi.off_wifi==1) 
		{
			LED_WIFI_Write(1);
		}
	else if(DisFlag_Wifi.sflash_wifi==1)
		{
			if(F_Ssync_Clock)
				{
					LED_WIFI_Write(1);
				}
			else
				{
					LED_WIFI_Write(0);
				}
		}
	else if(DisFlag_Wifi.fflash_wifi==1)
		{
			if(F_Fsync_Clock)
				{
					LED_WIFI_Write(1);
				}
			else
				{
					LED_WIFI_Write(0);
				}
		}
	//**************pp show
	if(DisFlag_Filter.on_pp==1)
		{
			LED_PP_Write(0);
		}
	else if (DisFlag_Filter.off_pp==1) 
		{
			LED_PP_Write(1);
		}
	else if(DisFlag_Filter.sflash_pp==1)
		{
			if(F_Ssync_Clock)
				{
					LED_PP_Write(1);
				}
			else
				{
					LED_PP_Write(0);
				}
		}
	else if(DisFlag_Filter.fflash_pp==1)
		{
			if(F_Fsync_Clock)
				{
					LED_PP_Write(1);
				}
			else
				{
					LED_PP_Write(0);
				}
		}
			//**************fc show
	if(DisFlag_Filter.on_fc==1)
		{
			LED_FC_Write(0);
		}
	else if (DisFlag_Filter.off_fc==1) 
		{
			LED_FC_Write(1);
		}
	else if(DisFlag_Filter.sflash_fc==1)
		{
			if(F_Ssync_Clock)
				{
					LED_FC_Write(1);
				}
			else
				{
					LED_FC_Write(0);
				}
		}
	else if(DisFlag_Filter.fflash_fc==1)
		{
			if(F_Fsync_Clock)
				{
					LED_FC_Write(1);
				}
			else
				{
					LED_FC_Write(0);
				}
		}
			//**************ro1 show
	if(DisFlag_Filter.on_ro1==1)
		{
			LED_RO1_Write(0);
		}
	else if (DisFlag_Filter.off_ro1==1) 
		{
			LED_RO1_Write(1);
		}
	else if(DisFlag_Filter.sflash_ro1==1)
		{
			if(F_Ssync_Clock)
				{
					LED_RO1_Write(1);
				}
			else
				{
					LED_RO1_Write(0);
				}
		}
	else if(DisFlag_Filter.fflash_ro1==1)
		{
			if(F_Fsync_Clock)
				{
					LED_RO1_Write(1);
				}
			else
				{
					LED_RO1_Write(0);
				}
		}
			//**************ro2 show
	if(DisFlag_Filter.on_ro2==1)
		{
			LED_RO2_Write(0);
		}
	else if (DisFlag_Filter.off_ro2==1) 
		{
			LED_RO2_Write(1);
		}
	else if(DisFlag_Filter.sflash_ro2==1)
		{
			if(F_Ssync_Clock)
				{
					LED_RO2_Write(1);
				}
			else
				{
					LED_RO2_Write(0);
				}
		}
	else if(DisFlag_Filter.fflash_ro2==1)
		{
			if(F_Fsync_Clock)
				{
					LED_RO2_Write(1);
				}
			else
				{
					LED_RO2_Write(0);
				}
		}
	//**************ro3 show
	if(DisFlag_Filter.on_ro3==1)
		{
			LED_RO3_Write(0);
		}
	else if (DisFlag_Filter.off_ro3==1) 
		{
			LED_RO3_Write(1);
		}
	else if(DisFlag_Filter.sflash_ro3==1)
		{
			if(F_Ssync_Clock)
				{
					LED_RO3_Write(1);
				}
			else
				{
					LED_RO3_Write(0);
				}
		}
	else if(DisFlag_Filter.fflash_ro3==1)
		{
			if(F_Fsync_Clock)
				{
					LED_RO3_Write(1);
				}
			else
				{
					LED_RO3_Write(0);
				}
		}
//**************bc show
	if(DisFlag_Filter.on_bc==1)
		{
			LED_BC_Write(0);
		}
	else if (DisFlag_Filter.off_bc==1) 
		{
			LED_BC_Write(1);
		}
	else if(DisFlag_Filter.sflash_bc==1)
		{
			if(F_Ssync_Clock)
				{
					LED_BC_Write(1);
				}
			else
				{
					LED_BC_Write(0);
				}
		}
	else if(DisFlag_Filter.fflash_bc==1)
		{
			if(F_Fsync_Clock)
				{
					LED_BC_Write(1);
				}
			else
				{
					LED_BC_Write(0);
				}
		}
}
void Led_Pannel_Allon(void)	
{
	LED_FC_Write(0);
	LED_BC_Write(0);  
	LED_PP_Write(0); 
	LED_RO1_Write(0); 
	LED_RO2_Write(0); 
	LED_RO3_Write(0);
	LED_WIFI_Write(0); 
	LED_KEY_SETTING_Write(0); 
	LED_KEY_WIFI_Write(0);
}
void Led_Pannel_Alarm(void)	
{
	if(F_Ssync_Clock)
		{
			LED_FC_Write(1);
			LED_BC_Write(1);  
			LED_PP_Write(1); 
			LED_RO1_Write(1); 
			LED_RO2_Write(1); 
			LED_RO3_Write(1);
			LED_WIFI_Write(1); 
			LED_KEY_SETTING_Write(1); 
			LED_KEY_WIFI_Write(1);
		}
	else
		{
			LED_FC_Write(0);
			LED_BC_Write(0);  
			LED_PP_Write(0); 
			LED_RO1_Write(0); 
			LED_RO2_Write(0); 
			LED_RO3_Write(0);
			LED_WIFI_Write(0); 
			LED_KEY_SETTING_Write(0); 
			LED_KEY_WIFI_Write(0);
		}
}
void Led_Pannel_Process(uint8 flownum,uint8 testsn,uint8 settingsn)
{
	switch (flownum)
	{
		case 0:
			Led_Pannel_Shutdown();
			break;
		case 1:
			Led_Pannel_Display(); 
			break;
		case 2:
			Led_Pannel_Test(testsn);
			break;
		case 3:
			Led_Pannel_Filter_Setting(settingsn);
			break;
		case 4:
			Led_Pannel_Allon();
			break;
		case 5:
			Led_Pannel_Alarm();	
			break;
		default:
			break;			
	}	
} 
/*****************************************************************\
\*****************************************************************/

/* [] END OF FILE */
