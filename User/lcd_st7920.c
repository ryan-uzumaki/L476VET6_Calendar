#include "lcd_st7920.h"
#include "delay.h"
#include "rtc.h"
#include "stdio.h"

DISP_DEAL_T  lcd={0};
u8 LCD_FRAME_STR[LCD_FRAME_SIZE];

void LCD_ST7920_DataIO_Set_In(void)//LCDst7920�˿ڳ�ʼ��,����Ϊ����
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = LCD_ST7920_DATAIO;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//���븡��
	GPIO_InitStruct.Pull = GPIO_NOPULL;//GPIO_PULLUP;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void LCD_ST7920_DataIO_Set_Out(void)//LCDst7920�˿ڳ�ʼ��,����Ϊ���
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = LCD_ST7920_DATAIO;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

//..........��æ..........
void Chk_Busy(void)
{
	LCD_ST7920_DataIO_Set_In();
	LCD_ST7920_RS_OFF;
	LCD_ST7920_RW_ON;
	LCD_ST7920_E_ON;
	DelayUs(2);
	lcd.lcd_busy_overtime=20;//100ms
	while(((GPIOD->IDR)&0x8000)!=0&&lcd.lcd_busy_overtime!=0);
	LCD_ST7920_E_OFF;
}

/**
 * @brief	  LCDst7920 ����д�뺯��
 * @param   cmd д������ֵ			
 */
void LCD_ST7920_WriteCmd(u16 cmd)//����дָ��     //�޸�ODRֵ�ĸ�ֵ��ʽ������PD8-16�˿ڲ���Ӱ��PD0-7�˿ڵ�����ʹ��  DMS-20220528
{
  	u16 cmd_tmp;
	Chk_Busy();//�ȴ�Һ��׼����
	LCD_ST7920_DataIO_Set_Out();
  	LCD_ST7920_RS_OFF;//дָ��
  	LCD_ST7920_RW_OFF;

	cmd_tmp =cmd<< 8;//((((cmd&0x0080) << 1))+(((cmd&0x0040) << 3))+(((cmd&0x0020) << 5))+(((cmd&0x0010) << 7))
							//+(((cmd&0x0008) << 9))+(((cmd&0x0004) << 11))+(((cmd&0x0002) << 13))+(((cmd&0x0001) << 15)));    
		//DelayUs(50);
	GPIOD->ODR= (GPIOD->ODR & 0x00FF)|cmd_tmp;
	
	DelayUs(100);
	LCD_ST7920_E_ON;
	DelayUs(250);
	LCD_ST7920_E_OFF;
}

/**
 * @brief	  LCDst7920 ����д�뺯��
 * @param   dataд������ֵ	
 */
void LCD_ST7920_WriteData(u16 data)//����д����    //�޸�ODRֵ�ĸ�ֵ��ʽ������PD8-16�˿ڲ���Ӱ��PD0-7�˿ڵ�����ʹ��  DMS-20220528
{
	u16 data_tmp;
	Chk_Busy();//�ȴ�Һ��׼����
	LCD_ST7920_DataIO_Set_Out();
  	LCD_ST7920_RS_ON;	//д����
  	LCD_ST7920_RW_OFF;

	data_tmp =data<< 8;//((((data&0x0080) << 1))+(((data&0x0040) << 3))+(((data&0x0020) << 5))+(((data&0x0010) << 7))
							//+(((data&0x0008) << 9))+(((data&0x0004) << 11))+(((data&0x0002) << 13))+(((data&0x0001) << 15)));
		//DelayUs(50);
	GPIOD->ODR= (GPIOD->ODR & 0x00FF)|data_tmp;
	
	DelayUs(100);
	LCD_ST7920_E_ON;
	DelayUs(250);//
	LCD_ST7920_E_OFF;
}

/**
 * @brief	  LCDst7920 ��ʾ����д�뺯��
 * @param  ������� x:0~7 0~15  y:0~3  vvvvvvvvvvvvvvvvvv������� 1����������  0��ִ�гɹ�	
 */
u8 LCD_ST7920_SetAddress(u8 x,u8 y)
{
	if((x>7)||(y>3))
	return 1;
	LCD_ST7920_WriteCmd(0x30);	/*30H--����ָ���*/
	if(y == 0)
	{LCD_ST7920_WriteCmd(0x80|x);}//�ӵ� 1 �п�ʼ��ʾ}
	else if ( y == 1 )
	{LCD_ST7920_WriteCmd(0x90|x);}//�ӵ� 2 �п�ʼ��ʾ}
	else if( y == 2 )
	{LCD_ST7920_WriteCmd(0x88|x);}//�ӵ� 3 �п�ʼ��ʾ
	else
	{LCD_ST7920_WriteCmd(0x98|x);}//�ӵ� 4 �п�ʼ��ʾ
	return 0; 
}

/**
 * @brief	  LCDst7920 ��ʾ�ַ�������
 *
 * @remark	
* @param  ������� x:0~15  y:0~1  *str:�ַ����׵�ַ  ������� 1����������  0��ִ�гɹ�
* @return  				
*/
int LCD_ST7920_ShowStr(unsigned char x,unsigned char y,unsigned char *str)//LCDst7920��ʾ�ַ���
{
//	if(key_set.wakeup_flg!=1)
//		return 0;
	
	if(LCD_ST7920_SetAddress(x,y))    //�������ݵ�ַָ��
	return 1;	
	while(*str !='\0')
	LCD_ST7920_WriteData(*str++);//д����
	return 0;  
}

//��ʾ�趨�������ַ�
int LCD_ST7920_ShowSetChar(u8 x,u8 y,u8 *str,u8 num)//��ʾ�趨�������ַ�
{
	u8 i;
//	if(key_set.wakeup_flg!=1)
//		return 0;
	
	if(LCD_ST7920_SetAddress(x,y))    //�������ݵ�ַָ��
	return 1;	
	for(i=0; i<num; i++)
		LCD_ST7920_WriteData(*str++);//д����
	return 0;  
}

//..........����DDRAM..........
void LCDClrDisplay(void)
{
	LCD_ST7920_WriteCmd(0x30);	/*30H--����ָ���*/
	LCD_ST7920_WriteCmd(0x01);	/*��������ַָ��ָ��00H*/
}

/**
 * @brief	  LCDst7920 Һ����ʼ������	
 */          
void LCD_ST7920_Init(void)//Һ����ʼ������
{
	
	LCD_35V_CTL_L;//����
	LCD_ST7920_RST_ON;
	LCD_ST7920_PSB_ON;
	LED_35V_CTL_L;//3.5v��ԴоƬʹ��
	DelayMs(50);
	LCDClrDisplay();//����
	//DelayMs(150);
	LCD_ST7920_WriteCmd(0x06);	/*�����ƶ�����*/
	LCD_ST7920_WriteCmd(0x0c);	/*����ʾ���ع��*/
}


void LCD_ST7920_DeInit(void)//Һ���رպ���
{
	
	LCD_35V_CTL_H;//LCD�رչ���
	LED_35V_CTL_H;//3.5v��ԴоƬʧ��
	LCD_ST7920_RST_OFF;
	LCD_ST7920_PSB_OFF;
}


void LCD_Display(void)
{
	sprintf((char*)LCD_FRAME_STR, "%04d/%02d/%02d", 2000+Date.Year,Date.Month,Date.Date);
	LCD_ST7920_ShowStr(0,0,(unsigned char *)LCD_FRAME_STR);
	
	switch(Date.WeekDay)
	{
		case 0x01:
			LCD_ST7920_ShowStr(0,1,(unsigned char *)"MONDAY");
			break;
		case 0x02:
			LCD_ST7920_ShowStr(0,1,(unsigned char *)"TUESDAY");
			break;
		case 0x03:
			LCD_ST7920_ShowStr(0,1,(unsigned char *)"WEDNESDAY");
			break;
		case 0x04:
			LCD_ST7920_ShowStr(0,1,(unsigned char *)"THURSDAY");
			break;
		case 0x05:
			LCD_ST7920_ShowStr(0,1,(unsigned char *)"FRIDAY");
			break;
		case 0x06:
			LCD_ST7920_ShowStr(0,1,(unsigned char *)"SATURDAY");
			break;
		case 0x07:
			LCD_ST7920_ShowStr(0,1,(unsigned char *)"SUNDAY");
			break;
	}

	
	sprintf((char*)LCD_FRAME_STR, "%02d:%02d:%02d", Time.Hours,Time.Minutes,Time.Seconds);
	LCD_ST7920_ShowStr(0,2,(unsigned char *)LCD_FRAME_STR);
}











