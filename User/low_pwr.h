#ifndef __LOW_PWR_H
#define __LOW_PWR_H

#include "sys.h"

#define LOW_PWR_COUNTDOWN			3000

typedef struct
{
	int low_pwr_flag;//休眠模式标志位
	long int low_pwr_count;//定时计数
}LOW_PWR_STRUCT;

extern LOW_PWR_STRUCT low_pwr_struct;

void LOW_PWR_Init(long int);
void LOW_PWR_Enter(void);
void LOW_PWR_Exit(void);

#endif

