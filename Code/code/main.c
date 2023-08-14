#include  <REG51.H>
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library 
#include "adxl345.h" 


#define   uchar unsigned char
#define   uint unsigned int

sbit      SCL = P1^3;    //IIC时钟引脚定义
sbit      SDA = P1^4;    //IIC数据引脚定义
int  dis_data;                       //变量
uint average_all = 0;         //3个方向xyz  的  average_all_times次的平均值
uint average_all_temp = 0;    //单次的数据值
uint average_all_num = 0;     //第几个
#define average_all_times 3   //当获得3次数据  后取平均为average_all

typedef unsigned char  BYTE;
typedef unsigned short WORD;

BYTE BUF[8];                         //接收数据缓存区
uint step_all = 0;            //总步数

void delay(unsigned int k);

void main(){
  uchar devid;
  uint i;
  uint cal_temp = 0;
  delay(100);  

  Init_ADXL345();                         //初始化ADXL345
  devid = Single_Read_ADXL345(0X00);      //读出的数据为0XE5,表示正确
  delay(100);
 for (i = 0; i < average_all_times; i++) //初始化  计算合加速度数据的阈值
  {
    Multiple_Read_ADXL345();
    average_all_temp += (uint)(ADXL345_xyz() / average_all_times);
    average_all_num++;
    if (average_all_num >= average_all_times) {  //达到次数  所测的数据平均值作为阈值
      average_all_num = 0;
      average_all = average_all_temp;
      average_all_temp = 0;
    }
    delay(80);
  }
  
}

/*******************************/
void delay(unsigned int k)	    //延时函数ms
{
  unsigned int i, j;
  for (i = 0; i < k; i++)
  {
    for (j = 0; j < 121; j++)
    {
      ;
    }
  }
}