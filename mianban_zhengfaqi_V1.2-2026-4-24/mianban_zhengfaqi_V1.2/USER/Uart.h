#ifndef  UART_C
#define  UART_C

#define  UARTDELAYTIME  2


#define  LENS_TX_BUFFER   100
#define  LENS_RX_BUFFER   100

typedef struct
{
//	unsigned char  TxBufferTemp[LENS_TX_BUFFER];
	unsigned char  RxBufferTemp[LENS_RX_BUFFER];
	unsigned char  TxBuffer[LENS_TX_BUFFER];
	unsigned char  RxBuffer[LENS_RX_BUFFER];
	unsigned long  nRceTimefromSysTick;
	unsigned char  nCurTxPos;
	unsigned char  nCurRxPos;
	unsigned char  LensSendData;
	unsigned char  bAnasyingFlag     :1;//解析中
	unsigned char  bSendingFlag      :1;//发送中
}UARTINF;

typedef struct
{
	unsigned char  ID_Hotas;
	unsigned char  CMD_Hotas;
	unsigned char  CheckSum;

}MCHINF_RCE;

typedef struct
{
	unsigned char  nCalNow;
	unsigned char  ID_Mch;
	unsigned char  Key_S1;
	unsigned char  Key_S2;
	unsigned char  Key_S3;
	unsigned char  Key_S4;
	unsigned char  Key_S5;
	unsigned char  Key_S6;
	unsigned char  Key_S7;
	unsigned char  Key_S8;
	unsigned char  Adc_UpDown_Low;
	unsigned char  Adc_UpDown_High;
	unsigned char  Adc_LeftRight_Low;
	unsigned char  Adc_LeftRight_High;
	unsigned char  Adc_Angle_Low;
	unsigned char  Adc_Angle_High;
	unsigned char  Mode_Work;
	unsigned char  Mchstate;

	unsigned char  CheckSum;

}MCHINF_SEND;


extern unsigned long SystemTick_Get_Ticks_ms;
#ifdef  ENABLE_UART1
	extern UARTINF  Uart1_Inf;
#endif

#ifdef  ENABLE_UART2
	extern UARTINF  Uart2_Inf;
#endif

#ifdef  ENABLE_UART3
	extern UARTINF  Uart3_Inf;
#endif

extern MCHINF_RCE   MchInf_Rce ;
extern MCHINF_SEND  MchInf_Send ;

void f_StartSend_Uart(UARTINF* UartInf,USART_TypeDef* USARTx);

void f_Interrupt_RceDeal(UARTINF* UartInf,USART_TypeDef* USARTx);

void f_Interrupt_SendDeal(UARTINF* UartInf,USART_TypeDef* USARTx);

void f_SendDeal(UARTINF* UartInf,USART_TypeDef * USARTx);

void f_RceDeal(UARTINF* UartInf,USART_TypeDef * USARTx);

void f_RceDeal_1(UARTINF* UartInf,USART_TypeDef * USARTx);

void f_Interrupt_RceDeal_1(UARTINF* UartInf,USART_TypeDef* USARTx);
#endif

