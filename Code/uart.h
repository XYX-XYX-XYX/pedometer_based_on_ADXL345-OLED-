#ifndef  UART_H
#define  UART_H
#define uchar unsigned char
/*
void uart_init(void);
void uart_send_char(uchar i);  
void uart_send_str(char *zifu);        //发送 字符串
void uart_send(int num);			    //发送4位数字
*/


/*
晶振11.0592M,波特率9600
定时器模式：T1八位自动重装
串口工作模式：1
中断：开串口中断，关定时器1中断
 */
void uart_init(void)
{
	TMOD&=0x0f;
	TMOD|=0x20;    //设置T1为八位自动重装 SM0=1，SM1=0！，【GATE=0（不受外部中断限制）】，【C/T=0(定时器模式)】
	TH1=0xfd;	//晶振11.0592M,波特率9600
	TL1=0xfd;		
	TR1=1;	//启动定时器1
 
	SM0=0;	//设置串口工作模式为模式1
	SM1=1;	
	EA=1;	//打开总总中断
	ES=1;	//打开串口中断
	REN=1;	//允许串口接收
}
void uart_send_char(uchar i)  
{
	ES=0;  //关闭串口中断
	SBUF=i;
	while(!TI);	//等待发送完毕
	TI=0;
	ES=1;
}
void uart_send_str(char *zifu)        //发送 字符串
{
	int i=0;
	while(zifu[i]!='\0')
	{
		uart_send_char(zifu[i]);
		i++;
	}
}
void uart_send(int num)    //发送4位数字
{
	//uart_send_char(num/10000%10+48);
	uart_send_char(num/1000%10+48);
	uart_send_char(num/100%10+48);
	uart_send_char(num/10%10+48);
	uart_send_char(num%10+48);
	uart_send_char(13);
}

/*
void RX_int(void) interrupt 4     //接收单个字符        对
{
	char i;
        if(RI)
        {
                RI = 0;
                i = SBUF;
			 uart_send_char(i+1); 
			 uart_send_char(13); 
	   }
}
char a[30];    //一定要  char   ！！
void RX_int(void) interrupt 4     //接收整个字符串    待改
{
	char b[]="adc";
	int temp=0,flag=1;
	a[z]=UDR;         //接收
	z++;
	if(a[z-1]==13)   //检测到换行
	{
	a[z-1]='\0';         //    !!!
	while(*(a+temp))
	{
		if(*(a+temp)==*(b+temp))
		{
			temp++;
		}
		else
		{
			flag=0;
			usart_send_str("wrong!");
			break;
		}
	}
	if(flag)
	{
		temp=adc_one();
		usart_send_char(temp/1000%10+48);
		usart_send_char(temp/100%10+48);
		usart_send_char(temp/10%10+48);
		usart_send_char(temp%10+48);
	}
	usart_send_char(13);           //过行
	for(z=0;z<20;z++)a[z]='\0';
	z=0;
	}
}
*/
#endif 