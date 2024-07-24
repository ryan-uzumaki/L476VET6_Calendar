#ifndef __LCD_st7920__
#define __LCD_st7920__

#include "sys.h"

#define LCD_35V_CTL_H				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET)
#define LCD_35V_CTL_L  				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET)

#define  LCD_ST7920_DATAIO   GPIO_PIN_8 |  GPIO_PIN_9 |  GPIO_PIN_10 |  GPIO_PIN_11 |  GPIO_PIN_12 |  GPIO_PIN_13 |  GPIO_PIN_14 |  GPIO_PIN_15

#define  LCD_ST7920_RS_ON   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
#define  LCD_ST7920_RW_ON   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
#define  LCD_ST7920_E_ON    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
#define  LCD_ST7920_PSB_ON   HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);
#define  LCD_ST7920_RST_ON   HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);

#define  LCD_ST7920_RS_OFF   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
#define  LCD_ST7920_RW_OFF   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
#define  LCD_ST7920_E_OFF    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
#define  LCD_ST7920_PSB_OFF   HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
#define  LCD_ST7920_RST_OFF   HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);

//液晶电源MOS控制：
#define LCD_35V_CTL_H				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET)
#define LCD_35V_CTL_L  			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET)
#define LED_35V_CTL_H				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)
#define LED_35V_CTL_L  			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)

#define LCD_FRAME_SIZE			50


typedef  struct            
{  
	u8 lcd_busy_overtime;
}DISP_DEAL_T;

extern u8 LCD_FRAME_STR[LCD_FRAME_SIZE];
extern DISP_DEAL_T  lcd;


void LCD_ST7920_DataIO_Set_In(void);//LCDst7920端口初始化,配置为输入
void LCD_ST7920_DataIO_Set_Out(void);//LCDst7920端口初始化,配置为输出
void Chk_Busy(void);//..........测忙..........
void LCD_ST7920_WriteCmd(u16 cmd);//用于写指令
void LCD_ST7920_WriteData(u16 data);//用于写数据
u8 LCD_ST7920_SetAddress(u8 x,u8 y);//显示坐标写入函数
int LCD_ST7920_ShowStr(unsigned char x,unsigned char y,unsigned char *str);//LCDst7920显示字符串
int LCD_ST7920_ShowSetChar(u8 x,u8 y,u8 *str,u8 num);//显示设定数量的字符
void LCDClrDisplay(void);//清屏
void LCD_ST7920_Init(void);//液晶初始化函数
void LCD_ST7920_DeInit(void);//液晶关闭函数
void LCD_Display(void);
//void DisplayDeal(void);//显示处理

#endif
