#ifndef __LIB_KEYDDRIVER_CONST_H
#define __LIB_KEYDDRIVER_CONST_H


#if 0
	调用时修改 (1)(2)(3)
#endif
//--------------------需根据需要修改------------------------------(1)

//----------------时间与状态关联--------------

typedef struct
{
	unsigned int StateTm;
	unsigned char StateName;
}ST_KeyTimeState;
//----------------根据需要修改对数组----------------------------------(2)
#define MAX_STEP 	8//为Tab_KeyOutState[]长度
const ST_KeyTimeState Tab_KeyOutState[]//更具需要的按键输出信息填写(所有按键信息汇总,不包括PRESSED_RE)
=
{
	{KEY_DELAY_TIME , PRESSED},
    {KEY_PRESS_TIME_300mS , PRESSED_300mS},
	{KEY_PRESS_TIME_1000mS , PRESSED_1S},
	{KEY_PRESS_TIME_2S , PRESSED_2S},
	{KEY_PRESS_TIME_3S , PRESSED_3S},
	{KEY_PRESS_TIME_5S , PRESSED_5S},
	//{KEY_PRESS_TIME_10S , PRESSED_10S},
	//{KEY_PRESS_TIME_15S , PRESSED_15S},	
	{0,0xff}
};


//------------------以下为固定定义和声明-----------------------------
#define GetTime(nKey)		(Tab_KeyOutState[nKey].StateTm)//获取对应名字按键时间
#define SetTimeInf(nKey)	(Tab_KeyOutState[nKey].StateName)//对达到时间的，赋值按键状态

#define MAX_TOTAL_SIG_KET_NUMB	32//总单键数量
#define MAX_TOTAL_COM_KET_NUMB	8//总组合键数量
//--------------单键,最大支持16个-------
#define KEY_SIG_1	0x000001
#define KEY_SIG_2	0x000002
#define KEY_SIG_3	0x000004
#define KEY_SIG_4	0x000008
#define KEY_SIG_5	0x000010
#define KEY_SIG_6	0x000020
#define KEY_SIG_7	0x000040
#define KEY_SIG_8	0x000080
#define KEY_SIG_9	0x000100
#define KEY_SIG_10	0x000200
#define KEY_SIG_11	0x000400
#define KEY_SIG_12	0x000800
#define KEY_SIG_13	0x001000
#define KEY_SIG_14	0x002000
#define KEY_SIG_15	0x004000
#define KEY_SIG_16	0x008000
#define KEY_SIG_17	0x010000
#define KEY_SIG_18	0x020000
#define KEY_SIG_19	0x040000
#define KEY_SIG_20	0x080000
#define KEY_SIG_21	0x100000
#define KEY_SIG_22	0x200000
#define KEY_SIG_23	0x400000
#define KEY_SIG_24	0x800000


//---------------组合按键键值,更具需要定义,最大8个-----------------------  (3)
#define KEY_COM_1	(KEY_SIG_1 | KEY_SIG_2)//模式+速度-复位
#define KEY_COM_2	(KEY_SIG_1 | KEY_SIG_3)//模式+定时-自检
#define KEY_COM_3	0
#define KEY_COM_4	0
#define KEY_COM_5	0
#define KEY_COM_6	0
#define KEY_COM_7	0
#define KEY_COM_8	0

#define KEY_TOTAL_COM (KEY_COM_1 | KEY_COM_2)

//---------------所以键值-----------
#define KEY_ALL		0xffffffff
#define SIG_BASE 8

const unsigned long nTab_KeyHexDef[]
=
{
	KEY_COM_1,
	KEY_COM_2,
	KEY_COM_3,
	KEY_COM_4,
	KEY_COM_5,
	KEY_COM_6,
	KEY_COM_7,
	KEY_COM_8,
	
	KEY_SIG_1,
	KEY_SIG_2,
	KEY_SIG_3,
	KEY_SIG_4,
	KEY_SIG_5,
	KEY_SIG_6,
	KEY_SIG_7,
	KEY_SIG_8,
	KEY_SIG_9,
	KEY_SIG_10,
	KEY_SIG_11,
	KEY_SIG_12,
	KEY_SIG_13,
	KEY_SIG_14,
	KEY_SIG_15,
	KEY_SIG_16,
	KEY_SIG_17,
	KEY_SIG_18,
	KEY_SIG_19,
	KEY_SIG_20,
	KEY_SIG_21,
	KEY_SIG_22,
	KEY_SIG_23,
	KEY_SIG_24
};

#endif//__LIB_KEYDDRIVER_CONST_H
