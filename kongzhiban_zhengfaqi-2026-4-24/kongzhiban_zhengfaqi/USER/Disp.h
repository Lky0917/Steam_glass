#ifndef DISP_H
#define DISP_H


//******************************
#ifdef   LED_DISP

typedef struct
{
	unsigned char  Disp_Buffer[10];
	unsigned char  Disp_BufferTemp[10];
	unsigned char  Num_State;
}LEDDISP;

#define  LED_SEG_8_CLEAR   (GPIOB->ODR &= 0xfc07,GPIOD->ODR &= 0xfffd)
//#define  LED_SEG_8(data)   (GPIOB->ODR |= (unsigned int)(data)<<3) 
#define  LED_COM_ALL_CLOSE (GPIOC->ODR |= 0xfc07,GPIOA->ODR |= 0x1000)
#define  LED_COM1_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define  LED_COM2_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_2)
#define  LED_COM3_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_1)
#define  LED_COM4_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_14)
#define  LED_COM5_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_12)
#define  LED_COM6_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_11)
#define  LED_COM7_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_10)
#define  LED_COM8_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_15)
#define  LED_COM9_ON       GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define  LED_COM10_ON      GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define  LED_SEG_A_ON       GPIO_SetBits(GPIOB,GPIO_Pin_3);
#define  LED_SEG_B_ON       GPIO_SetBits(GPIOB,GPIO_Pin_4);
#define  LED_SEG_C_ON       GPIO_SetBits(GPIOB,GPIO_Pin_5);
#define  LED_SEG_D_ON       GPIO_SetBits(GPIOB,GPIO_Pin_6);
#define  LED_SEG_E_ON       GPIO_SetBits(GPIOB,GPIO_Pin_7);
#define  LED_SEG_F_ON       GPIO_SetBits(GPIOB,GPIO_Pin_8);
#define  LED_SEG_G_ON       GPIO_SetBits(GPIOB,GPIO_Pin_9);
#define  LED_SEG_H_ON       GPIO_SetBits(GPIOD,GPIO_Pin_2);





extern LEDDISP  LED_Disp;

void f_Disp_LED(LEDDISP* LEDDisp);//1ms调用
void f_Disp2LED(LEDDISP* LEDDisp);//1s调用
#endif

#ifdef  EPD_DISP
#define EPD_W21_MOSI_0	GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define EPD_W21_MOSI_1	GPIO_SetBits(GPIOA, GPIO_Pin_6)

#define EPD_W21_CLK_0	GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define EPD_W21_CLK_1	GPIO_SetBits(GPIOA, GPIO_Pin_7)

#define EPD_W21_CS_0	GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define EPD_W21_CS_1	GPIO_SetBits(GPIOA, GPIO_Pin_4)

#define EPD_W21_DC_0	GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define EPD_W21_DC_1	GPIO_SetBits(GPIOA, GPIO_Pin_5)

#define EPD_W21_RST_0	GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define EPD_W21_RST_1	GPIO_SetBits(GPIOA, GPIO_Pin_3)

#define Wait_BUSY_IO GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)

extern void driver_delay_us(unsigned int xus);
extern void driver_delay_xms(unsigned long xms);

void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
void f_Disp(void);
#endif

void f_Disp(void);




#endif
