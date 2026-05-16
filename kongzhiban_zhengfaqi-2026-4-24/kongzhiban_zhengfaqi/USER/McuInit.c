#include "HeadInclude.h"
byte_def    nTime_Flag;
byte_def    nFreq_Flag;

unsigned int PrescalerValue = 0;

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
void RCC_Configuration(void)
{
	ErrorStatus  HSEStartUpStatus;
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);//使用外部晶振
	/*Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
		/*Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		/*Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		//使能FLASH 预取缓存
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		/*HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/*PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1);
		/*PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);
		/*ADCCLK = PCLK2/6*/
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC时钟
		/*PLLCLK = 8M * 9 = 72Mhz*/
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		/*Enable PLL */
		RCC_PLLCmd(ENABLE);
		/*Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{}
		/*Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/*Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)
		{}
	}
}

void f_NVIC_Config(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;
#ifdef  ENABLE_TIMER2
	//time2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//Tim2 中断NVIC设置:允许中断，设置优先级
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//更新事件
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//允许中断
		NVIC_Init(&NVIC_InitStructure);//写入设置
#endif
	
#ifdef   ENABLE_TIMER3
	//time3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//Tim3 中断NVIC设置:允许中断，设置优先级
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//更新事件
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//允许中断
		NVIC_Init(&NVIC_InitStructure);//写入设置
#endif

#ifdef   ENABLE_UART2
	//DMA  UART2 RX  channel 6
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//最高
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
#endif

}


//1ms 时基
void f_Time2_Config(void)
{
#ifdef  ENABLE_TIMER2

	TIM_DeInit(TIM2);

	/* Compute the prescaler value -系统时钟72M-分频到1M*/
	PrescalerValue = (uint16_t)(SystemCoreClock/1000000)-1;

	/*Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;//定时1ms
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing; /*Channel1*/
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2,ENABLE);

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//中断使能
	
	TIM_Cmd(TIM2,ENABLE);//TIM2 enable counter
#endif
}

//200us时基
void f_Time3_Config(void)
{
#ifdef  ENABLE_TIMER3
//	u16 CCR1_Val = 0x7fff;   //PWM 占空比调整参数，  0xffff 背光最亮    0x0  背光最暗
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PA时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//RGB
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//RGB
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_DeInit(TIM3);
	/* Compute the prescaler value -系统时钟72M-分频到1M*/
	PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 499;//周期500-2khz 设置在下一个更新事件装入活动的自动重装载寄存器周期的值	80K
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;//预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数模式	:UP
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
        
	/* PWM2 Mode configuration: Channel1-呼吸灯 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性:TIM输出比较极性高
        
	TIM_OC1Init(TIM3,&TIM_OCInitStructure); //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
	TIM_ARRPreloadConfig(TIM3,ENABLE);//使能 TIM3 在 ARR 上的预装载寄存器

//****************配置通道2  FAN_PWM
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 500;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//输出极性:TIM输出比较极性高

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
//****************配置通道3  BUZZ 

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性:TIM输出比较极性高

	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);

	/* TIM3 enable counter*/
	TIM_Cmd(TIM3,ENABLE);
#endif
}


//定时器pwm输出
void f_Time4_Config(void)
{
#ifdef  ENABLE_TIMER4
//	u16 CCR1_Val = 0x7fff;   //PWM 占空比调整参数，  0xffff 背光最亮    0x0  背光最暗
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能TIM4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;//RGB
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);


	
	TIM_DeInit(TIM4);
	/* Compute the prescaler value -系统时钟72M-分频到1M*/
	PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 499;//周期500-2khz 设置在下一个更新事件装入活动的自动重装载寄存器周期的值	80K
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;//预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数模式	:UP
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
        
	/* PWM2 Mode configuration: Channel1-呼吸灯 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//输出极性:TIM输出比较极性高
        
	TIM_OC1Init(TIM4,&TIM_OCInitStructure); //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
	TIM_ARRPreloadConfig(TIM4,ENABLE);//使能 TIM4 在 ARR 上的预装载寄存器

//****************配置通道2  FAN_PWM
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 500;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性:TIM输出比较极性高

	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	
//****************配置通道3  BUZZ 

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//输出极性:TIM输出比较极性高

	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4,ENABLE);

	/* TIM4 enable counter*/
	TIM_Cmd(TIM4,ENABLE);
#endif
}


void f_GPIO_Config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15);

	//********************************************************************
#ifndef ENABLE_JTAG
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);	
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//PB3 PB4 
#endif
	//输出上拉引脚 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2| GPIO_Pin_8|GPIO_Pin_9 |GPIO_Pin_10;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);


	GPIO_ResetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);


	//********************************************************************

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

}

/***********************************
*函数名称:
//初始化独立看门狗
//prer:分频数:0~7(只有低 3 位有效!)
//分频因子=4*2^prer.但最大值只能是 256!
//rlr:重装载寄存器值:低 11 位有效.
//时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
***********************************/
void f_IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//使能对寄存器操作
	IWDG_SetPrescaler(prer);//设置预分频值
	IWDG_SetReload(rlr);//设置重装载值
	IWDG_ReloadCounter();//按照重装载寄存器的值重装载计数器
	IWDG_Enable();//使能IWDG
}

void f_MCU_FeedDog(void)	
{
	IWDG_ReloadCounter();//reload
}

//***********************************/

void f_InitUart(void)
{
  	NVIC_InitTypeDef  NVIC_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	
#ifdef ENABLE_UART1
  	//uart 1\2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/*configure the NVIC Preemption Priority Bits*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/*Enable the USART 1 Interrupt*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//复用推挽输出PA9  USART1 口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//tx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_ClockInit(USART1,&USART_ClockInitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Odd;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART1,USART_IT_TC,ENABLE);

	//enable the USART
	USART_Cmd(USART1,ENABLE);
#endif


#ifdef ENABLE_UART2

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	/*Enable the USART 2 Interrupt*/
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//复用推挽输出PA2 3  USART2 口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//tx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_ClockInit(USART2,&USART_ClockInitStructure);
	
	//configure USART2
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Odd;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2,&USART_InitStructure);

	//enable USART Receive and Transmit interrupts


	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART2,USART_IT_TC,ENABLE);

	//enable the USART
	USART_Cmd(USART2,ENABLE);
#endif

#ifdef ENABLE_UART3

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	/*Enable the USART 2 Interrupt*/
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//复用推挽输出PB 10  11  USART2 口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//tx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_ClockInit(USART3,&USART_ClockInitStructure);
	
	//configure USART3
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Odd;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3,&USART_InitStructure);

	//enable USART Receive and Transmit interrupts

	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART3,USART_IT_TC,ENABLE);

	//enable the USART
	USART_Cmd(USART3,ENABLE);
#endif



}

#ifdef ENABLE_DMA
//串口接收缓冲 
unsigned char uart2_data_temp1[2048] = {0};
unsigned char uart2_data_temp2[2048] = {0};

void f_InitDMA(void)
{
	
	DMA_InitTypeDef	DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	DMA_DeInit(DMA1_Channel6);//将DMA通道6寄存器设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(USART2->DR));
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)uart2_data_temp1;//目标BUF写入数组名
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//外设为源头，作为数据传输目的地还是来源

	DMA_InitStructure.DMA_BufferSize = 2048;//设置DMA在传输时缓冲区的长度，前面有定义过了buffer的起始地址，
										//为了安全性和可靠性，一般需要给buffer定义一个储存片区，这个参数的单位有三种类型：Byte、HalfWord、word，我设置的2个half-word(见下面的设置)；32位的MCU中1个half-word占16 bits。
	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;										
	//上面的这句是设置DMA的外设递增模式，如果DMA选用的通道（CHx）有多个外设连接，需要使用外设递增模式：DMA_PeripheralInc_Enable;我的例子里DMA只与ADC1建立了联系，所以选用DMA_PeripheralInc_Disable
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	//上面的这句是设置DMA的内存递增模式，DMA访问多个内存参数时，需要使用DMA_MemoryInc_Enable，当DMA只访问一个内存参数时，可设置成：DMA_MemoryInc_Disable。
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	//上面的这句是设置DMA在访问时每次操作的数据长度。
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//内存数据宽度半字节
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//不停传送
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//优先级高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//非内存到内存

	DMA_Init(DMA1_Channel6,&DMA_InitStructure);

	   /** DMA_ IT **/
    USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE); //enable the usart2 reception Interruption

	DMA_ITConfig(DMA1_Channel6,DMA_IT_TC|DMA_IT_HT,ENABLE);//使能传输完成中断
	DMA_Cmd(DMA1_Channel6,ENABLE);
	
}
#endif


#ifdef  ENABLE_ADC
void f_ADC_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
	RCC_APB2Periph_ADC1 , ENABLE ); //使能 ADC1 通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置 ADC 分频因子 6 
	//72M/6=12,ADC 最大时间不能超过 14M
	//PA1 作为模拟通道输入引脚 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIOA.1
	ADC_DeInit(ADC1); //复位 ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC 独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//转换由
	//软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1; //顺序进行规则转换的ADC 通道的数目
	ADC_Init(ADC1, &ADC_InitStructure); //根据指定的参数初始化外设 ADCx 
	ADC_Cmd(ADC1, ENABLE); //使能指定的 ADC1
	ADC_ResetCalibration(ADC1); //开启复位校准 
	while(ADC_GetResetCalibrationStatus(ADC1)); //等待复位校准结束
	ADC_StartCalibration(ADC1); //开启 AD 校准
	while(ADC_GetCalibrationStatus(ADC1)); //等待校准结束

}
//获得 ADC 值
//ch:通道值 10~13
u16 f_Get_Adc(u8 ch) 
{
	 //设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 ); //通道 1
	//规则采样顺序值为 1,采样时间为 239.5 周期 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能指定的 ADC1 的软件转换功能
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1); //返回最近一次 ADC1 规则组的转换结果
}
#endif

#ifdef  ENABLE_SPI1
unsigned char SPI2_ReadWriteByte(unsigned char TxData)
{
	unsigned char retry=0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) 
	{
		retry++;
		if(retry>200)
			return 0;
	} 
	SPI_I2S_SendData(SPI1, TxData); 
	retry=0;
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) 
	{
		retry++;
		if(retry>200)return 0;
	}
	return SPI_I2S_ReceiveData(SPI1); 
}


void f_SPI_Config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	SPI_InitTypeDef     SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	//
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//
  SPI_InitStructure.SPI_CRCPolynomial = 7;//
	SPI_Init(SPI1, &SPI_InitStructure);  //
	
  SPI_Cmd(SPI1, ENABLE); //
//  SPI1_ReadWriteByte(0xFF);//
}
#endif
/***********************************
*函数名称:


***********************************/
void f_MCU_InitSfr(void)
{

	RCC_Configuration();//时钟配置
	f_IWDG_Init(4,625);//分频64，重载625，溢出时间1s
	f_GPIO_Config();//GPIO配置
	f_NVIC_Config();//中断向量配置
	f_Time2_Config();//1ms
	f_Time3_Config();//200us
	f_Time4_Config();//pwm定时器配置
#ifdef ENABLE_ADC
	f_ADC_Config();
#endif
	f_InitUart();//串口初始化
}


