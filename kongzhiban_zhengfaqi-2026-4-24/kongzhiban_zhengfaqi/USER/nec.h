#ifndef NEC_H
#define NEC_H


typedef enum
 {
	 NEC_SEND_START,
	 NEC_SEND_INT,// ¼ä¸ô·û
	 NEC_SEND_DATA,
	 NEC_SEND_STOP
 }NECSendSTATE;

#define  IR_IN   P0_6

#define  IO_SEND  SDA_KEY 

#define  LEN_SEND_DATA   4
#define  LEN_RECE_DATA   9
extern unsigned char KeyGetIR;
extern unsigned char key_IR;
extern unsigned char SendData[LEN_SEND_DATA];
extern unsigned char SendDataInt[LEN_SEND_DATA];

extern unsigned char idata RceKey[LEN_RECE_DATA];
extern unsigned char KeyNum;

extern NECSendSTATE NECSendState;
extern unsigned char TimeNECSend;
extern unsigned int TmInt;

extern byte_def NECFlag;
#define  bNStartRec      NECFlag.m_bit.b0
#define  bNStartSend     NECFlag.m_bit.b1
#define  bNSucceRce      NECFlag.m_bit.b2
#define  bNSendOverBit   NECFlag.m_bit.b3
#define  nNECFlag		 NECFlag.m_byte

extern TYPE_INT idata KeyIRFlag;
#define   bKeyIR_Power     KeyIRFlag.int_bit.b0
#define   bKeyIR_Timer     KeyIRFlag.int_bit.b1
#define   bKeyIR_Sleep     KeyIRFlag.int_bit.b2
#define   bKeyIR_CF        KeyIRFlag.int_bit.b3
#define   bKeyIR_LOW       KeyIRFlag.int_bit.b4
#define   bKeyIR_High      KeyIRFlag.int_bit.b5
#define   bKeyIR_Strong    KeyIRFlag.int_bit.b6
#define   bKeyIR_Cool      KeyIRFlag.int_bit.b7
#define   bKeyIR_Dry       KeyIRFlag.int_bit.b8
#define   bKeyIR_Fan       KeyIRFlag.int_bit.b9
#define   bKeyIR_UP        KeyIRFlag.int_bit.b10
#define   bKeyIR_DOWN      KeyIRFlag.int_bit.b11
#define   bKeyIR_SWING     KeyIRFlag.int_bit.b12
#define   bKeyIR_Lock      KeyIRFlag.int_bit.b13
#define   bKeyIR_Mode      KeyIRFlag.int_bit.b14
#define   bKeyIR_FanCtrl   KeyIRFlag.int_bit.b15

#define   nKeyIRFlag       KeyIRFlag.int_byte

extern TYPE_INT idata KeyIRFlag1;
#define   bKeyIR_Heat     KeyIRFlag1.int_bit.b0
#define   bKeyIR_Auto     KeyIRFlag1.int_bit.b1
#define   bKeyIR_Saving   KeyIRFlag1.int_bit.b2
#define   bKeyIR_SC       KeyIRFlag1.int_bit.b3


#define   nKeyIRFlag1       KeyIRFlag1.int_byte

void f_NEC_Rec(void);
void f_NEC_Send(void);
void f_NECStart(void);
void f_IRKeyGet(void);
void f_NECInit(void);
void f_INTREC(void);




#endif
