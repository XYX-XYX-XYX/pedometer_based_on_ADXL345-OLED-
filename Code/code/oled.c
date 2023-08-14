#include "oled.h"
#include "oledfont.h"

void IIC_Start()        //起始信号
{
    OLED_SCL_Set();
    OLED_SDA_Set();
    OLED_SDA_Rst();
    OLED_SCL_Rst();
}

void IIC_Stop()         //停止信号
{
    OLED_SCL_Set();
    OLED_SDA_Rst();
    OLED_SDA_Set();
}

void IIC_Wait_Ack()     //等待ACK
{
    OLED_SCL_Set();
    OLED_SCL_Rst();
}

void Write_IIC_Byte(uint8 IIC_Byte)     //发送数据函数
{
    uint8 i,Temp,Data;

    Data = IIC_Byte;

    OLED_SCL_Rst();

    for(i=0;i<8;i++)        
    {
        Temp = Data;
        Temp =Temp & 0x80;
        if(Temp == 0x80)
            OLED_SDA_Set();
        else
            OLED_SDA_Rst();
        Data <<= 1;
        OLED_SCL_Set();
        OLED_SCL_Rst();
    }
}

void Write_IIC_Command(uint8 IIC_Command)       //写入命令函数
{
    IIC_Start();
    Write_IIC_Byte(0x78);            //从站地址,SA0=0
    IIC_Wait_Ack(); 
    Write_IIC_Byte(0x00);           //写入命令
    IIC_Wait_Ack(); 
    Write_IIC_Byte(IIC_Command); 
    IIC_Wait_Ack(); 
    IIC_Stop();
}

void Write_IIC_Data(uint8 IIC_Data)         //写入数据函数
{
    IIC_Start();
    Write_IIC_Byte(0x78);           //D/C#=0; R/W#=0
    IIC_Wait_Ack(); 
    Write_IIC_Byte(0x40);           //写入数据
    IIC_Wait_Ack(); 
    Write_IIC_Byte(IIC_Data);
    IIC_Wait_Ack(); 
    IIC_Stop();
}

void OLED_WR_Byte(uint8 Data,uint8 cmd)         //命令/数据选择函数
{
    if(cmd)
        Write_IIC_Data(Data);
    else
        Write_IIC_Command(Data);

}

void Fill_Picture(uint8 Fill_Data)              //填充屏幕
{
    uint8 i,j;

    for(i=0;i<8;i++)
    {
        OLED_WR_Byte(0xB0+i,OLED_CMD);      //page0-page1
        OLED_WR_Byte(XLevelL,OLED_CMD);     
        OLED_WR_Byte(XLevelH,OLED_CMD);     
        for(j=0;j<128;j++)
            OLED_WR_Byte(Fill_Data,OLED_DATA);
    }
}

void OLED_Set_Pos(uint8 x,uint8 y)          //设置屏幕位置
{   
    OLED_WR_Byte(0xB0+y,OLED_CMD);                      //通过x坐标定位页
    OLED_WR_Byte((((x+2)&0xF0)>>4)|0x10,OLED_CMD);       //y坐标高4位定位列的高地址
    OLED_WR_Byte(((x+2)&0x0F),OLED_CMD);                //y坐标低4位定位列的低地址
}


void OLED_Clear()           //清屏
{
    Fill_Picture(0x00);
}   

void OLED_Show_Char(uint8 x,uint8 y,uint8 Char,uint8 Char_Size)         //显示一个字符，输入字符的坐标，字符和字符尺寸
{       
    uint8 c=0,i=0;

    c = Char - 32;  //得到偏移后的值

    if(x > Max_Column - 1)
    {
        x = 0;
        y += 2;
    }
    if(Char_Size == 16)     //大尺寸执行下面的程序
    {
        OLED_Set_Pos(x,y);  
        for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
    }
    else            //小尺寸执行下面的程序
    {   
        OLED_Set_Pos(x,y);
        for(i=0;i<6;i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);             
    }
}

void OLED_Show_Chinese(uint8 x,uint8 y,uint8 number) //显示汉字函数，number是自定义的汉字编码
{                   
    uint8 t;

    OLED_Set_Pos(x,y);  
    for(t=0;t<16;t++)
        OLED_WR_Byte(Chinese[2*number][t],OLED_DATA);
    OLED_Set_Pos(x,y+1);    
    for(t=0;t<16;t++)   
        OLED_WR_Byte(Chinese[2*number+1][t],OLED_DATA);                 
}
/*10^n函数*/
/*其实在math.h这个库里面有pow()函数，用于求x的y次方的值，但是该函数的返回值是double类型的，所以自己做一个*/
uint16 Pow(uint8 n)  
{
    uint16 result=1;     
    while(n--)
        result *= 10;    
    return result;
}

void OLED_Show_Number(uint8 x,uint8 y,uint16 number,uint8 len,uint8 Char_size) //显示数字，区别于显示字符，实在不想写一个数字转字符的函数
{
    uint8 i,temp,enshow = 0;

    for(i=0;i<len;i++)
    {
        temp = (number/Pow(len-i-1))%10;
        if(enshow == 0 && i < (len-1))
        {
            if(temp==0)
            {
                OLED_Show_Char(x+(Char_size/2)*i,y,' ',Char_size);
                continue;
            }
            else
                enshow=1;
        }
        OLED_Show_Char(x+(Char_size/2)*i,y,temp+'0',Char_size);
    }

}

void OLED_Init()  //初始化OLED
{   
    OLED_WR_Byte(0xAE,OLED_CMD);//--display off
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
    OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
    OLED_WR_Byte(0x81,OLED_CMD); // contract control
    OLED_WR_Byte(0xFF,OLED_CMD);//--128   
    OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
    OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
    OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);//

    OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
    OLED_WR_Byte(0x80,OLED_CMD);//

    OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);//

    OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
    OLED_WR_Byte(0xF1,OLED_CMD);//

    OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
    OLED_WR_Byte(0x12,OLED_CMD);//

    OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
    OLED_WR_Byte(0x30,OLED_CMD);//

    OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);//

    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}