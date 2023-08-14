#ifndef  UART_H
#define  UART_H
#define uchar unsigned char
/*
void uart_init(void);
void uart_send_char(uchar i);  
void uart_send_str(char *zifu);        //���� �ַ���
void uart_send(int num);			    //����4λ����
*/


/*
����11.0592M,������9600
��ʱ��ģʽ��T1��λ�Զ���װ
���ڹ���ģʽ��1
�жϣ��������жϣ��ض�ʱ��1�ж�
 */
void uart_init(void)
{
	TMOD&=0x0f;
	TMOD|=0x20;    //����T1Ϊ��λ�Զ���װ SM0=1��SM1=0������GATE=0�������ⲿ�ж����ƣ�������C/T=0(��ʱ��ģʽ)��
	TH1=0xfd;	//����11.0592M,������9600
	TL1=0xfd;		
	TR1=1;	//������ʱ��1
 
	SM0=0;	//���ô��ڹ���ģʽΪģʽ1
	SM1=1;	
	EA=1;	//�������ж�
	ES=1;	//�򿪴����ж�
	REN=1;	//�����ڽ���
}
void uart_send_char(uchar i)  
{
	ES=0;  //�رմ����ж�
	SBUF=i;
	while(!TI);	//�ȴ��������
	TI=0;
	ES=1;
}
void uart_send_str(char *zifu)        //���� �ַ���
{
	int i=0;
	while(zifu[i]!='\0')
	{
		uart_send_char(zifu[i]);
		i++;
	}
}
void uart_send(int num)    //����4λ����
{
	//uart_send_char(num/10000%10+48);
	uart_send_char(num/1000%10+48);
	uart_send_char(num/100%10+48);
	uart_send_char(num/10%10+48);
	uart_send_char(num%10+48);
	uart_send_char(13);
}

/*
void RX_int(void) interrupt 4     //���յ����ַ�        ��
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
char a[30];    //һ��Ҫ  char   ����
void RX_int(void) interrupt 4     //���������ַ���    ����
{
	char b[]="adc";
	int temp=0,flag=1;
	a[z]=UDR;         //����
	z++;
	if(a[z-1]==13)   //��⵽����
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
	usart_send_char(13);           //����
	for(z=0;z<20;z++)a[z]='\0';
	z=0;
	}
}
*/
#endif 