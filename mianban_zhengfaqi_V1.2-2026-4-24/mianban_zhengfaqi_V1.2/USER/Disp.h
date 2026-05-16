#ifndef DISP_H
#define DISP_H

#include "HeadInclude.h"

#define ERR_LOWTEMPER 6     // 低于6度
#define ERR_HIGHTEMPER 60   // 高于  60度
#define ERR_WATERTEMPER 115 // 蒸汽高于115度

extern TYPE_INT IconDisp;
#define bIconB1 IconDisp.int_bit.b0
#define bIconB2 IconDisp.int_bit.b1
#define bIconLED2 IconDisp.int_bit.b2
#define bIconSound IconDisp.int_bit.b3
#define bIconAdd IconDisp.int_bit.b4
#define bIconJIan IconDisp.int_bit.b5
#define bIconLV1 IconDisp.int_bit.b6
#define bIconLV2 IconDisp.int_bit.b7
#define bIconLV3 IconDisp.int_bit.b8
#define bIConStart IconDisp.int_bit.b9
#define bIConWaterHard1 IconDisp.int_bit.b10
#define bIConWaterHard2 IconDisp.int_bit.b11
#define bIConWaterHard3 IconDisp.int_bit.b12
#define bIConWaterHard4 IconDisp.int_bit.b13
#define bIConChuGou IconDisp.int_bit.b14
#define bIConSleep IconDisp.int_bit.b15

#define nIconDisp IconDisp.int_byte

extern TYPE_INT IconDisp1;
#define bIconWaterLOW IconDisp1.int_bit.b0
#define bIconWaterMID IconDisp1.int_bit.b1
#define bIconWaterHIGH IconDisp1.int_bit.b2
#define bIconIn IconDisp1.int_bit.b3
#define bIconOut IconDisp1.int_bit.b4
#define bIconTmr IconDisp1.int_bit.b5
#define bIconWater IconDisp1.int_bit.b6

#define nIconDisp1 IconDisp1.int_byte

void f_Disp(void);
void f_Deal_Seg(void);
extern unsigned char RGBModeLast;
extern unsigned char bflagUp98du;
void f_Disp_saomiao(void);

#endif
