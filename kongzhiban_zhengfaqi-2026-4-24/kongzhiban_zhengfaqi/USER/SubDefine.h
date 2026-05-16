#ifndef _SUBDEFINE_H
#define _SUBDEFINE_H


//逻辑值定义
#define  false 0
#define  true  1


//**************
typedef  union
{
    unsigned int  m_word;
    struct
    {
        unsigned char high_byte;
        unsigned char low_byte;
    }m_byte;
}int_def;

//uchar 字节位定义
typedef struct
{
    unsigned char b0 :1;
    unsigned char b1 :1;
    unsigned char b2 :1;
    unsigned char b3 :1;
    unsigned char b4 :1;
    unsigned char b5 :1;
    unsigned char b6 :1;
    unsigned char b7 :1;
}bit_def;

typedef union
{
    bit_def  m_bit;
    unsigned char m_byte;
}byte_def;

//uint 位拆解

typedef struct
{
    unsigned int  b0 :1;
    unsigned int  b1 :1;
    unsigned int  b2 :1;
    unsigned int  b3 :1;
    unsigned int  b4 :1;
    unsigned int  b5 :1;
    unsigned int  b6 :1;
    unsigned int  b7 :1;
    unsigned int  b8 :1;
    unsigned int  b9 :1;
    unsigned int  b10 :1;
    unsigned int  b11 :1;
    unsigned int  b12 :1;
    unsigned int  b13 :1;
    unsigned int  b14 :1;
    unsigned int  b15 :1;
}intbit_def;

typedef union
{
    intbit_def  int_bit;
    unsigned int int_byte;
}TYPE_INT;

#endif


