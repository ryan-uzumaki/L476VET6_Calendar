
#ifndef __LED_H
#define	__LED_H

#include "sys.h"

#define     LED1_ON()       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);  
#define     LED1_OFF()      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);


void LED_TOGGLE(void);

#endif
