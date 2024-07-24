#include "low_pwr.h"
#include "lcd_st7920.h"
#include "usart.h"

LOW_PWR_STRUCT low_pwr_struct={0,0};

void LOW_PWR_Init(long int countdown)
{
	low_pwr_struct.low_pwr_flag=0;
	low_pwr_struct.low_pwr_count=countdown;
}


void LOW_PWR_Enter(void)
{
	LCD_ST7920_DeInit();
//	HAL_UART_DeInit(&huart2);
//	HAL_UART_MspDeInit(&huart2);
}

void LOW_PWR_Exit(void)
{
	LCD_ST7920_Init();
//	HAL_UART_Init(&huart2);
//	HAL_UART_MspInit(&huart2);
}







