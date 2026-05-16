#ifndef  _DRIVER_ET6238_H
#define  _DRIVER_ET6238_H

//SC12A
#define SCL_SC12A_High        GPIO_SetBits(GPIOA,GPIO_Pin_11)//SCL H
#define SCL_SC12A_Low         GPIO_ResetBits(GPIOA,GPIO_Pin_11)//SCL L
#define SDA_SC12A_OUT_H       GPIO_SetBits(GPIOA,GPIO_Pin_12)//SDA H
#define SDA_SC12A_OUT_L       GPIO_ResetBits(GPIOA,GPIO_Pin_12)//SDA l

#define SDA_SC12A_IN           GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)


//SC12A
#define SCL_SC12A_High_1        GPIO_SetBits(GPIOC,GPIO_Pin_14)//SCL H
#define SCL_SC12A_Low_1         GPIO_ResetBits(GPIOC,GPIO_Pin_14)//SCL L
#define SDA_SC12A_OUT_H_1       GPIO_SetBits(GPIOC,GPIO_Pin_15)//SDA H
#define SDA_SC12A_OUT_L_1       GPIO_ResetBits(GPIOC,GPIO_Pin_15)//SDA l

#define SDA_SC12A_IN_1           GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)

void Delay_1us(void);

void Delay_us(unsigned char us);

void I2C_start(void);

void I2C_stop(void);

void I2C_waitack(void);

void I2C_sendbyte(unsigned char sendbyte);

unsigned char I2C_readbyte(void);

void I2C_setSDAout2in(void);

void  I2C_setSDAin2out(void);

void SC12A_work(void);
void SC12A_work_1(void);


#endif

