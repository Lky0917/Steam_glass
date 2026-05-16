#ifndef  _ADC_H
#define  _ADC_H

#ifdef   VAR_ADC_GLOBALS
	#define  VAR_ADC_EXT
#else
	#define  VAR_ADC_EXT  extern
#endif

//;



#define  CHANNEL_ADC0    0x00
#define  CHANNEL_ADC1    0x01
#define  CHANNEL_ADC2    0x02
#define  CHANNEL_ADC3    0x03
#define  CHANNEL_ADC4    0x04
#define  CHANNEL_ADC5    0x05
#define  CHANNEL_ADC6    0x06
#define  CHANNEL_ADC7    0x07
#define  CHANNEL_ADC8    0x08



unsigned int f_Hmdy_CheckTab(unsigned char Tmper,unsigned int ADC_Hmdy);
unsigned int f_FilterMeanValue(unsigned int *ADC_Value);
unsigned char f_NTC_CheckTab(unsigned int ADC_Data);
unsigned int f_MCU_ADCSwitch(unsigned char Channel_AN);
void f_HmdyDeal(void);
void f_HmdyStart(void);
void f_TmprDeal(unsigned char CHANNEL,unsigned char Num);



#endif
