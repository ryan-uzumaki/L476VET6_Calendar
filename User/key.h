#ifndef _KEY_H
#define _KEY_H
#include "sys.h"

#define KEY_1			KEY_RET
#define KEY_2			KEY_VOID
#define KEY_3			KEY_SET
#define KEY_4			KEY_DOWN
#define KEY_5			KEY_RIGHT
#define KEY_6			KEY_INC


typedef enum
{
	KEY_RET,
	KEY_VOID,
	KEY_SET,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_INC,
	NONE,//没有任何键被按下
}KEY_VALUE;


typedef struct
{
	int key_dpress_flag;
	int key_dpress_count;
	int key_duration_flag;
	float key_duration;
}KEY_STATUS;


typedef struct
{
	u8 key_suf;
	u8 key_flag;
	KEY_VALUE key_value_read;
}KEY_DETECT_T;

extern KEY_STATUS ks;
extern KEY_DETECT_T kd;
void GetKeyValue(void);
void KeyDeal(void);

#endif
