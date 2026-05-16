#ifndef   RGB_H
#define   RGB_H

typedef enum
{
	RGB_CLOSE = 0,
	RGB_WHITE,
	RGB_YELLOW,
	RGB_ORANGE,
	RGB_RED,
	RGB_FENSE,	
	RGB_ZISe,
	RGB_BLUE,
	RGB_SKYBLUE,	
	RGB_GREEN
	
}RGBMODE;


void f_MCU_OutRGBPWM_1(RGBMODE state);

#endif