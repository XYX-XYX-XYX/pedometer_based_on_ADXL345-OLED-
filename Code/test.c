#include"reg52.h"
#include"adxl345.h"
#include"oled.h"

void main(){
	
	uint8 devid;
  uint16 i;
  uint16 cal_temp = 0;
  delay(100);  
	
	CS=0;
	DC=0;
  Init_ADXL345(); 	//???ADXL345
  devid = Single_Read_ADXL345(0X00);      //??????0XE5,????
	OLED_Init();
	delay(1000);
	OLED_Clear();
	
 for (i = 0; i < average_all_times; i++) //???  ???????????
  {
    Multiple_read_ADXL345();
    average_all_temp += (uint16)(ADXL345_xyz() / average_all_times);
    average_all_num++;
    if (average_all_num >= average_all_times) {  //????  ????????????
      average_all_num = 0;
      average_all = average_all_temp;
      average_all_temp = 0;
    }
    delay(80);
  }
	while(1){
	Multiple_read_ADXL345();
		calculate_xyz();
	//delay(100);
		OLED_ShowCHinese(28,2,0);//?
		OLED_ShowCHinese(60,2,1);
		OLED_ShowCHinese(92,2,2);
		OLED_ShowNum(40,6,step_all,4,16);
		
	delay(50);
	}
 }

