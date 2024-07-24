/* USER CODE BEGIN Header */
//#include "stdlib.h"
#include "rtc.h"
//#include "string.h"
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
USART2_RXBUF rxbuf_struct={0};//ʵ�����ջ�����
DATE_TIME dt_struct={0}; 

//�����ض���
int fputc(int ch, FILE *f)
{
    while((USART2->ISR & 0X40) == 0); //USART1����
    USART2->TDR = (u8) ch;
//		HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}


void USART2_BUF_INIT(USART2_RXBUF* p)
{
	p->rx_init_flag=1;
	p->rx_count=0;
	//��ʼ������������
	for(int i=0;i<USART2_BUF_SIZE;i++)
	{
		p->rxbuf[i]=0;
	}
}

//�����ʼ��ʧ��
void USART2_BUF_DEINIT(USART2_RXBUF* p)
{
	p->rx_init_flag=0;
}

void USART2_CLEAR_BUF(USART2_RXBUF* p)
{
	//��ջ���������
	for(int i=0;i<p->rx_count;i++)
	{
		p->rxbuf[i]=0;
	}
}

/* USER CODE END 0 */

UART_HandleTypeDef huart2;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);//����USART2���ռĴ����ǿ��ж�
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);
	HAL_UARTEx_ReceiveToIdle_IT(&huart2,rxbuf_struct.rxbuf,USART2_BUF_SIZE);
  /* USER CODE END USART2_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**********************************************
����    �� ����2����1���ַ�
��ڲ����� 
����ֵ  �� 
***********************************************/
void USART2SendByte(u8 data)
{ 	
	 while((USART2->ISR & 0X40) == 0){}; //ѭ������,ֱ���������
   USART2->TDR = (u8) data;	
}

/**********************************************
����    �� ����2����1���ַ�
��ڲ����� �ַ����׵�ַ �ַ�������
����ֵ  �� 
***********************************************/
void USART2Write(u8 *data,u16 len)
{
	u16 i;
	for (i=0; i<len; i++){
		USART2SendByte(data[i]);
	}		
}


/**********************************************
����    �� �������������ս���Э��
�����ʽ�� �����������޿ո񣨴������ֹ��Ϸ������У� EX:20240723
����ֵ  �� 
***********************************************/
void Protocal_DATE(USART2_RXBUF* src,DATE_TIME* dest)
{	
	//��byteתΪbcd��
	dest->year=(((src->rxbuf[2]&0x0f)<<4)|(src->rxbuf[3]&0x0f));
	dest->month=(((src->rxbuf[4]&0x0f)<<4)|(src->rxbuf[5]&0x0f));
	dest->date=(((src->rxbuf[6]&0x0f)<<4)|(src->rxbuf[7]&0x0f));
	dest->weekday=(((src->rxbuf[8]&0x0f)<<4)|(src->rxbuf[9]&0x0f));
	
	printf("DATE: %02d/%02d/%02d\r\nWEEKDAY: %02d\r\n",2000 + (uint8_t)RTC_Bcd2ToByte(dest->year), \
														   (uint8_t)RTC_Bcd2ToByte(dest->month),\
									                       (uint8_t)RTC_Bcd2ToByte(dest->date), \
									                       (uint8_t)RTC_Bcd2ToByte(dest->weekday));
}


/**********************************************
����    �� ��������ʱ�������Э��
�����ʽ�� 24Сʱ��ʱ�����м��޿ո񣨴������ֹ��Ϸ������У� EX:152020
����ֵ  �� 
***********************************************/
void Protocal_TIME(USART2_RXBUF* src,DATE_TIME* dest)
{
	//��byteתΪbcd��
	dest->hour=(((src->rxbuf[0]&0x0f)<<4)|(src->rxbuf[1]&0x0f));
	dest->min=(((src->rxbuf[2]&0x0f)<<4)|(src->rxbuf[3]&0x0f));
	dest->sec=(((src->rxbuf[4]&0x0f)<<4)|(src->rxbuf[5]&0x0f));
	
	printf("TIME: %02d:%02d:%02d\r\n",(uint8_t)RTC_Bcd2ToByte(dest->hour), \
									(uint8_t)RTC_Bcd2ToByte(dest->min),  \
									(uint8_t)RTC_Bcd2ToByte(dest->sec));
}

void USART2_Modify_DATE(DATE_TIME* dest)
{
	HAL_RTC_MspDeInit(&hrtc);//ʧ��rtc
	Date.WeekDay = dest->weekday;
	Date.Month = dest->month;
	Date.Date = dest->date;
	Date.Year = dest->year;
	HAL_RTC_MspInit(&hrtc);//ʹ��rtc
  if (HAL_RTC_SetDate(&hrtc, &Date, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
}

void USART2_Modify_TIME(DATE_TIME* dest)
{
	HAL_RTC_MspDeInit(&hrtc);//ʧ��rtc
	Time.Hours = dest->hour;
	Time.Minutes = dest->min;
	Time.Seconds = dest->sec;
	Time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	Time.StoreOperation = RTC_STOREOPERATION_RESET;
	HAL_RTC_MspInit(&hrtc);//ʹ��rtc
  if (HAL_RTC_SetTime(&hrtc, &Time, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
}




/* USER CODE END 1 */
