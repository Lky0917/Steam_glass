#ifndef __KEYDEAL_H
#define __KEYDEAL_H

#ifdef   VAR_KEYDEAL_GLOBALS
	#define  KEYDEAL_EXT
#else
	#define  KEYDEAL_EXT  extern
#endif
extern unsigned NUM_key;
//---------------处理函数声明-------------
KEYDEAL_EXT void f_KeyDeal(void);

typedef struct
{
	unsigned int longtimeKey7;
	unsigned int longtimeKey8;
	unsigned int longtimeKey9;

}KEYINF;

extern KEYINF   KeyInf;

#endif//__KEYDEAL_H

