#ifndef __DISPLAY_CONST_H
#define __DISPLAY_CONST_H

#define LED_A		0x01					//          __________
#define LED_B		0x02       				//         |     A    |
#define LED_C		0x04       				//         |F        B|
#define LED_D		0x08					//         |          |
#define LED_E		0x10					//         |_____G____|
#define LED_F		0x20					//         |          |
#define LED_G		0x40					//         |          |
#define LED_H	  	0x80					//         |E        C|
//#define LED_H_OFF	~LED_H					//         |_____D____|

const unsigned char nTab_Number[]
= 
{
	LED_A + LED_B + LED_C + LED_D + LED_E + LED_F, 			      	// 0	0
	LED_B + LED_C, 													// 1	1
	LED_A + LED_B + LED_D + LED_E + LED_G, 					        // 2	2
	LED_A + LED_B + LED_C + LED_D + LED_G, 					        // 3	3
	LED_B + LED_C + LED_F + LED_G,								    // 4	4
	LED_A + LED_C + LED_D + LED_F + LED_G, 					        // 5	5
	LED_A + LED_G + LED_C + LED_D + LED_E + LED_F, 			      	// 6	6
	LED_A + LED_B + LED_C, 											// 7	7
	LED_A + LED_B + LED_C + LED_D + LED_E + LED_F + LED_G,    		// 8	8
	LED_A + LED_B + LED_C + LED_D + LED_F + LED_G, 			      	// 9	9
	LED_A + LED_B + LED_C + LED_G + LED_E + LED_F, 			      	// A    10
	LED_C + LED_D + LED_E + LED_F + LED_G, 					        // b    11 
	LED_A + LED_D + LED_E + LED_F, 								    // C	12
	LED_D + LED_E + LED_G,											//c		13
	LED_B + LED_C + LED_D + LED_E + LED_G, 					        // d	14
	LED_A + LED_D + LED_E + LED_F + LED_G, 					        // E	15
	LED_A + LED_E + LED_F + LED_G, 								    // F    16
	LED_A + LED_C + LED_D + LED_E + LED_F,							//G		17
	LED_B + LED_C + LED_E + LED_F + LED_G,							//H		18
	LED_C + LED_E + LED_F + LED_G,									//h		19
	LED_B + LED_C + LED_D + LED_E,									//J		20
	LED_D + LED_E + LED_F,											//L		21
	LED_B + LED_C + LED_D + LED_F + LED_G,							//y		22
	LED_C + LED_D + LED_E + LED_G,									//o		23
	LED_G,															//-		24
	LED_A + LED_B + LED_E + LED_F + LED_G,							//P		25
	LED_C + LED_E + LED_G,											//n		26
	LED_B + LED_C + LED_D + LED_E + LED_F,							//U		27
	LED_C + LED_D + LED_E,											//u		28
	LED_D + LED_E + LED_F + LED_G,									//t		29
	LED_E + LED_G,													//r		30
	0x00                                                          	//Ãð    31
}
;
#define    LEDCLOSE      31
#define    LED_ZIMU_L      21
#define    LED_ZIMU_h      19
#define    LED_ZIMU_C      12
#define    LED_FUHAO       24
#define    LED_ZIMU_H      18




#endif

