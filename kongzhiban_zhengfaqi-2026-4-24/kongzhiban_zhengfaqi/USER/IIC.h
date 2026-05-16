#ifndef  _DRIVER_ET6238_H
#define  _DRIVER_ET6238_H


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

#endif

