#include"adxl345.h"
#include  <REG51.H>
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library  

/**************************************
  延时5微秒(STC90C52RC@12M)
  不同的工作环境,需要调整此函数，注意时钟过快时需要修改
  当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5us()
{
  _nop_(); _nop_(); _nop_(); _nop_();
  _nop_(); _nop_(); _nop_(); _nop_();
  _nop_(); _nop_(); _nop_(); _nop_();
}

/**************************************
  延时5毫秒(STC90C52RC@12M)
  不同的工作环境,需要调整此函数
  当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms()
{
  WORD n = 560;

  while (n--);
}

/**************************************
  起始信号
**************************************/
void ADXL345_Start()
{
  SDA = 1;                    //拉高数据线
  SCL = 1;                    //拉高时钟线
  Delay5us();                 //延时
  SDA = 0;                    //产生下降沿
  Delay5us();                 //延时
  SCL = 0;                    //拉低时钟线
}

/**************************************
  停止信号
**************************************/
void ADXL345_Stop()
{
  SDA = 0;                    //拉低数据线
  SCL = 1;                    //拉高时钟线
  Delay5us();                 //延时
  SDA = 1;                    //产生上升沿
  Delay5us();                 //延时
}
/**************************************
  发送应答信号
  入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(bit ack)
{
  SDA = ack;                  //写应答信号
  SCL = 1;                    //拉高时钟线
  Delay5us();                 //延时
  SCL = 0;                    //拉低时钟线
  Delay5us();                 //延时
}

/**************************************
  接收应答信号
**************************************/
bit ADXL345_RecvACK()
{
  SCL = 1;                    //拉高时钟线
  Delay5us();                 //延时
  CY = SDA;                   //读应答信号
  SCL = 0;                    //拉低时钟线
  Delay5us();                 //延时

  return CY;
}

/**************************************
  向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(BYTE dat)
{
  BYTE i;

  for (i = 0; i < 8; i++)     //8位计数器
  {
    dat <<= 1;              //移出数据的最高位
    SDA = CY;               //送数据口
    SCL = 1;                //拉高时钟线
    Delay5us();             //延时
    SCL = 0;                //拉低时钟线
    Delay5us();             //延时
  }
  ADXL345_RecvACK();
}

/**************************************
  从IIC总线接收一个字节数据
**************************************/
BYTE ADXL345_RecvByte()
{
  BYTE i;
  BYTE dat = 0;

  SDA = 1;                    //使能内部上拉,准备读取数据,
  for (i = 0; i < 8; i++)     //8位计数器
  {
    dat <<= 1;
    SCL = 1;                //拉高时钟线
    Delay5us();             //延时
    dat |= SDA;             //读数据
    SCL = 0;                //拉低时钟线
    Delay5us();             //延时
  }
  return dat;
}

//******单字节写入*******************************************

void Single_Write_ADXL345(uchar REG_Address, uchar REG_data)
{
  ADXL345_Start();                  //起始信号
  ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
  ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页
  ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页
  ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
uchar Single_Read_ADXL345(uchar REG_Address)
{ uchar REG_data;
  ADXL345_Start();                          //起始信号
  ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
  ADXL345_SendByte(REG_Address);            //发送存储单元地址，从0开始
  ADXL345_Start();                          //起始信号
  ADXL345_SendByte(SlaveAddress + 1);       //发送设备地址+读信号
  REG_data = ADXL345_RecvByte();            //读出寄存器数据
  ADXL345_SendACK(1);
  ADXL345_Stop();                           //停止信号
  return REG_data;
}
//*********************************************************
//
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_read_ADXL345(void)
{ uchar i;
  ADXL345_Start();                          //起始信号
  ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
  ADXL345_SendByte(0x32);                   //发送存储单元地址，从0x32开始
  ADXL345_Start();                          //起始信号
  ADXL345_SendByte(SlaveAddress + 1);       //发送设备地址+读信号
  for (i = 0; i < 6; i++)                  //连续读取6个地址数据，存储中BUF
  {
    BUF[i] = ADXL345_RecvByte();          //BUF[0]存储0x32地址中的数据
    if (i == 5)
    {
      ADXL345_SendACK(1);                //最后一个数据需要回NOACK
    }
    else
    {
      ADXL345_SendACK(0);                //回应ACK
    }
  }
  ADXL345_Stop();                          //停止信号
  Delay5ms();
}


//*****************************************************************

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345()
{
  Single_Write_ADXL345(0x31, 0x0B);  //测量范围,正负16g，13位模式
  Single_Write_ADXL345(0x2C, 0x08);  //速率设定为12.5 参考pdf13页
  Single_Write_ADXL345(0x2D, 0x08);  //选择电源模式   参考pdf24页
  Single_Write_ADXL345(0x2E, 0x80);  //使能 DATA_READY 中断
  Single_Write_ADXL345(0x1E, 0x00);  //X 偏移量 根据测试传感器的状态写入pdf29页
  Single_Write_ADXL345(0x1F, 0x00);  //Y 偏移量 根据测试传感器的状态写入pdf29页
  Single_Write_ADXL345(0x20, 0x05);  //Z 偏移量 根据测试传感器的状态写入pdf29页
}
//整合xyz轴的数据,正整数，返回 x*x+y*y+z*z	的计算值
float ADXL345_xyz()
{
  float temp;
  float all = 0.0;
  dis_data = (BUF[1] << 8) + BUF[0]; //合成数据
  if (dis_data < 0)  dis_data = -dis_data;
  temp = (float)dis_data / 10;
  all += temp * temp;

  dis_data = (BUF[3] << 8) + BUF[2]; //合成数据
  if (dis_data < 0)  dis_data = -dis_data;
  temp = (float)dis_data / 10;
  all += temp * temp;

  dis_data = (BUF[5] << 8) + BUF[4]; //合成数据
  if (dis_data < 0)  dis_data = -dis_data;
  temp = (float)dis_data / 10;
  all += temp * temp;
  return all;
}

//获取2次数据作为当前的获得数据，多次数据取平均值作为判断步数的阈值，与当前获得数据比较 ，保存总步数到eeprom
void calculate_xyz()
{
  float temp;
  temp = ADXL345_xyz();
  delay(20);
  Multiple_Read_ADXL345();
  temp = (temp + ADXL345_xyz()) / 2; //两次值取平均


  average_all_temp += (uint)(temp / average_all_times);
  average_all_num++;
  if (average_all_num >= average_all_times) {        //达到average_all_times次数  数据的平局作为阈值判断
    average_all_num = 0;
    average_all = average_all_temp;
    average_all_temp = 0;
  }

  if (temp > average_all + 55) {			  //当测量值 比阈值+55大，说明走了一步
    step_all++;
    delay(150);								 //延时，避免一步当做多步
  }
}