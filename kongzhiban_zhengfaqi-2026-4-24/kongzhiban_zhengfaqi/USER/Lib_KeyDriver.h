#ifndef __LIB_KEYDRIVER_H
#define __LIB_KEYDRIVER_H

#include "SubDefine.h"

#ifdef   VAR_KEY_DRIVER_GLOBALS
	#define  KEY_DRIVER_EXT
#else
	#define  KEY_DRIVER_EXT  extern
#endif

typedef enum
{//按键单按\组合状态
	KEY_FREE,
	KEY_COM_PRESS_1,
	KEY_COM_PRESS_2,
	KEY_COM_PRESS_3,
	KEY_COM_PRESS_4,
	KEY_COM_PRESS_5,
	KEY_COM_PRESS_6,
	KEY_COM_PRESS_7,
	KEY_COM_PRESS_8,
	KEY_SIGNAL_PRESS_1,
	KEY_SIGNAL_PRESS_2,
	KEY_SIGNAL_PRESS_3,
	KEY_SIGNAL_PRESS_4,
	KEY_SIGNAL_PRESS_5,
	KEY_SIGNAL_PRESS_6,
	KEY_SIGNAL_PRESS_7,
	KEY_SIGNAL_PRESS_8,
	KEY_SIGNAL_PRESS_9,
	KEY_SIGNAL_PRESS_10,
	KEY_SIGNAL_PRESS_11,
	KEY_SIGNAL_PRESS_12,
	KEY_SIGNAL_PRESS_13,
	KEY_SIGNAL_PRESS_14,
	KEY_SIGNAL_PRESS_15,
	KEY_SIGNAL_PRESS_16,
	KEY_SIGNAL_PRESS_17,
	KEY_SIGNAL_PRESS_18,
	KEY_SIGNAL_PRESS_19,
	KEY_SIGNAL_PRESS_20,
	KEY_SIGNAL_PRESS_21,
	KEY_SIGNAL_PRESS_22,
	KEY_SIGNAL_PRESS_23,
	KEY_SIGNAL_PRESS_24
}KEY_PRESSED_STATE;

//----------按键进程状态,最大支持8钟-----------
#define PRESSED			0x01	//按下短按
#define PRESSED_RE		0x02	//释放短按
#define PRESSED_1S		0x04	//1S长按
#define PRESSED_1d5S	0x08	//1.5S长按
#define PRESSED_2S		0x10	//2S长按
#define PRESSED_3S		0x20	//3S长按
#define PRESSED_5S		0x40	//5S长按
#define PRESSED_300mS	0x80	//300mS长按

//---------------状态时间定义,与状态一致--------------
#define KEY_DELAY_TIME			5//5*10ms
#define KEY_SHORT_TIME			90//释放有效时间 80*10ms
#define KEY_PRESS_TIME_300mS	30//30*10ms
#define KEY_PRESS_TIME_1000mS	100//100*10ms
#define KEY_PRESS_TIME_1500mS	150//150*10ms
#define KEY_PRESS_TIME_2S		200//200*10ms
#define KEY_PRESS_TIME_3S		300//300*10ms
#define KEY_PRESS_TIME_5S		500//500*10ms
#define KEY_PRESS_TIME_10S		1000//1000*10ms
#define KEY_PRESS_TIME_15S		1500//1000*10ms

#define NO_KEY 		0

//----------------变量声明------------------
KEY_DRIVER_EXT unsigned long nKeyInf;				//获取过来的原始按键信息
KEY_DRIVER_EXT unsigned char nKeyResultInf;			//按键键输出结果
KEY_DRIVER_EXT KEY_PRESSED_STATE KeyPressName;		//按下按键名
KEY_DRIVER_EXT unsigned int nKeyReleseTm;

KEY_DRIVER_EXT byte_def keyCtrlFlag;
#define		 bKeyUsedFlag				keyCtrlFlag.m_bit.b0//按键结果被使用
#define		 bKeyFirstRelse				keyCtrlFlag.m_bit.b1//按键第一次被释放
#define		 bLongPressFlag				keyCtrlFlag.m_bit.b2
#define		 bKeyPressFlag				keyCtrlFlag.m_bit.b3//按键被按下标志

//---------------固定函数声明-------------
KEY_DRIVER_EXT void f_KeyScan(void);
KEY_DRIVER_EXT void f_KeyInit(void);
KEY_DRIVER_EXT void f_AddKeyPressTm(void);
KEY_DRIVER_EXT void f_NoReleaseInf(void);
KEY_DRIVER_EXT void f_LongTmPressCnt(void);

#endif//__LIB_KEYDRIVER_H
