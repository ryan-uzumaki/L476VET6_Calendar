#include "key.h"
#include "lcd_st7920.h"
#include "usart.h"
#include "low_pwr.h"

KEY_DETECT_T kd={0,0,NONE};
KEY_STATUS ks={1,0,1,0};

void GetKeyValue(void)
{
	kd.key_suf=(GPIOE->IDR)&0xfc;
	if(kd.key_suf!=0xfc)
	{
		if(kd.key_suf==0x7c)
		{
			kd.key_value_read=KEY_1;//KEY_RET
		}
		
		else if(kd.key_suf==0xbc)
		{
			kd.key_value_read=KEY_2;//KEY_VOID免装按键(WKUP键)
		}
		
		else if(kd.key_suf==0xdc)
		{
			kd.key_value_read=KEY_3;//KEY_SET
		}
		
		else if(kd.key_suf==0xec)
		{
			kd.key_value_read=KEY_4;//KEY_DOWN
		}
		
		else if(kd.key_suf==0xf4)
		{
			kd.key_value_read=KEY_5;//KEY_RIGHT
		}
		
		else if(kd.key_suf==0xf8)
		{
			kd.key_value_read=KEY_6;//KEY_INC
		}
	}
}


void KeyDeal(void)
{
	if(kd.key_value_read==KEY_RET)
	{
		printf("KEY_RET PRESS\r\n");
		kd.key_value_read=NONE;
	}
	if(kd.key_value_read==KEY_SET)
	{
		printf("KEY_SET PRESS\r\n");
		kd.key_value_read=NONE;
	}
	if(kd.key_value_read==KEY_VOID)//WKUP低功耗唤醒键
	{
		printf("KEY_VOID PRESS\r\n");
		kd.key_value_read=NONE;
		low_pwr_struct.low_pwr_count=LOW_PWR_COUNTDOWN;//每次按下都更新countdown值
		if(low_pwr_struct.low_pwr_flag)
		{
			low_pwr_struct.low_pwr_flag=0;
			low_pwr_struct.low_pwr_count=LOW_PWR_COUNTDOWN;
			LOW_PWR_Exit();
		}
	}
	if(kd.key_value_read==KEY_DOWN)
	{
		printf("KEY_DOWN PRESS\r\n");
		kd.key_value_read=NONE;
	}
	if(kd.key_value_read==KEY_RIGHT)
	{
		printf("KEY_RIGHT PRESS\r\n");
		kd.key_value_read=NONE;
	}
	if(kd.key_value_read==KEY_INC)
	{
		printf("KEY_INC PRESS\r\n");
		kd.key_value_read=NONE;
	}
}










