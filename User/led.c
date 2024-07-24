#include "led.h"
#include "delay.h"

void LED_TOGGLE(void)
{
	LED1_ON();
//	HAL_Delay(500);
	DelayMs(500);
	LED1_OFF();
//	HAL_Delay(500);
	DelayMs(500);
}




