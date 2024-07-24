/*******************************************************************************
* 名称  : delay.c
* 作者  : fanggang
* 说明  : 延时函数 
* 版本  ：V1.00  15/06/2020   
*******************************************************************************/
#include "delay.h"

static unsigned int  fac_us=0;							//us延时倍乘数			   
static unsigned int  fac_ms=0;							//ms延时倍乘数

			   
/**********************************************
功能说明： 延时功能初始化
入口参数：  
返回参数： 
***********************************************/
void DelayInit(void)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
  fac_us = 10;	
	fac_ms=(unsigned int)fac_us*1000;					    				//每个ms需要的systick时钟数	
}								    


/**********************************************
功能说明： 微秒延时函数
入口参数： 
返回参数： 
***********************************************/		    								   
void DelayUs(unsigned int nus)
{		
	unsigned int temp;	    	 
	SysTick->LOAD=nus*fac_us; 					      		//时间加载	  		 
	SysTick->VAL=0x00;        					      		//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;			//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		 			//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; 			//关闭计数器
	SysTick->VAL =0X00;      					       			//清空计数器	 
}

/**********************************************
功能说明：毫秒延时函数
入口参数： 
返回参数： 
***********************************************/
void DelayMs(unsigned int nms)
{	 		  	  
	unsigned int temp;		   
	SysTick->LOAD=(unsigned int)nms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							      				//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;			//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));					//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;			//关闭计数器
	SysTick->VAL =0X00;       										//清空计数器	  	    
} 
 



