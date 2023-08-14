#ifndef _ADXL345_H
#define _ADXL345_H


#define   uchar unsigned char
#define   uint unsigned int


#define SlaveAddress   0xA6     //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
//ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A
typedef unsigned char  BYTE;
typedef unsigned short WORD;

extern sbit SCL;
extern sbit SDA;
extern BYTE BUF[8];
extern uint step_all;
extern int dis_data;
extern uint average_all ;         //3个方向xyz  的  average_all_times次的平均值
extern uint average_all_temp ;    //单次的数据值
extern uint average_all_num ;     //第几个
#define average_all_times 3   //当获得3次数据  后取平均为average_all

//------------------------------------
void Delay5us();
void Delay5ms();
void ADXL345_Start();
void ADXL345_Stop();
void ADXL345_SendACK(bit ack);
bit  ADXL345_RecvACK();
void ADXL345_SendByte(BYTE dat);
BYTE ADXL345_RecvByte();
void ADXL345_ReadPage();
void ADXL345_WritePage();
//-----------------------------------

#endif