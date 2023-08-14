#ifndef _ALL_H
#define _ALL_H

#include<reg52.h>

#define  uint8      unsigned char 
#define  uint16     unsigned int  
	
typedef unsigned char  BYTE;
typedef unsigned short WORD;


sbit SCL=P1^3;       //?? D0(SCLK)
sbit SDA=P1^4;    //?? D1(MOSI)


int  dis_data;                       //??
uint16 average_all = 0;         //3???xyz  ?  average_all_times?????
uint16 average_all_temp = 0;    //??????
uint16 average_all_num = 0;     //???
#define average_all_times 3   //???3???  ?????average_all

BYTE BUF[8];                         //???????
uint16 step_all = 0;            //???

#endif