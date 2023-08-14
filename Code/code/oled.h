#include "REG52.h"
#ifndef __OLED_H_
#define __OLED_H_                      
#define  uint8      unsigned char 
#define  uint16     unsigned int    
#define  uint32     unsigned long 
#define  OLED_CMD   0   //写命令
#define  OLED_DATA  1   //写数据
#define  OLED_MODE  0

extern sbit SCL;       //时钟 D0（SCLK）
extern sbit SDA;       //数据 D1（MOSI） 

#define OLED_SCL_Rst() SCL=0
#define OLED_SCL_Set() SCL=1

#define OLED_SDA_Rst() SDA=0
#define OLED_SDA_Set() SDA=1

#define SIZE        16
#define XLevelL     0x00
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF 
#define X_WIDTH     128
#define Y_WIDTH     64    

void IIC_Start();
void IIC_Stop();
void IIC_Wait_Ack();
void Write_IIC_Byte(uint8 IIC_Byte);
void Write_IIC_Command(uint8 IIC_Command);
void Write_IIC_Data(uint8 IIC_Data);
void OLED_WR_Byte(uint8 Data,uint8 cmd);
void Fill_Picture(uint8 Fill_Data);
void OLED_Set_Pos(uint8 x,uint8 y);
void OLED_Clear();
void OLED_Show_Char(uint8 x,uint8 y,uint8 Char,uint8 Char_Size);
void OLED_Show_Chinese(uint8 x,uint8 y,uint8 number);
uint16 Pow(uint8 n);
void OLED_Show_Number(uint8 x,uint8 y,uint16 number,uint8 len,uint8 Char_size);
void OLED_Init();

#endif