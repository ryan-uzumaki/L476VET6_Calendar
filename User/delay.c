/*******************************************************************************
* ����  : delay.c
* ����  : fanggang
* ˵��  : ��ʱ���� 
* �汾  ��V1.00  15/06/2020   
*******************************************************************************/
#include "delay.h"

static unsigned int  fac_us=0;							//us��ʱ������			   
static unsigned int  fac_ms=0;							//ms��ʱ������

			   
/**********************************************
����˵���� ��ʱ���ܳ�ʼ��
��ڲ�����  
���ز����� 
***********************************************/
void DelayInit(void)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
  fac_us = 10;	
	fac_ms=(unsigned int)fac_us*1000;					    				//ÿ��ms��Ҫ��systickʱ����	
}								    


/**********************************************
����˵���� ΢����ʱ����
��ڲ����� 
���ز����� 
***********************************************/		    								   
void DelayUs(unsigned int nus)
{		
	unsigned int temp;	    	 
	SysTick->LOAD=nus*fac_us; 					      		//ʱ�����	  		 
	SysTick->VAL=0x00;        					      		//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;			//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		 			//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; 			//�رռ�����
	SysTick->VAL =0X00;      					       			//��ռ�����	 
}

/**********************************************
����˵����������ʱ����
��ڲ����� 
���ز����� 
***********************************************/
void DelayMs(unsigned int nms)
{	 		  	  
	unsigned int temp;		   
	SysTick->LOAD=(unsigned int)nms*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							      				//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;			//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));					//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;			//�رռ�����
	SysTick->VAL =0X00;       										//��ռ�����	  	    
} 
 



