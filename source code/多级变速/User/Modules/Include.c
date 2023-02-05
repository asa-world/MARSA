/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"

/**************路径规划参数*****************/
u8 RevStatus=0;
u8 TurnAngle;
u8 Golength;

/**************12864参数*****************/
int Level = 0;
int Mode = 0;
int Refresh = 0;

u8 adjust; //定义电机校准标志
u8 buffer[3]; //定义串口缓冲接收数组
u8 buffer3[10];
u8 rec_flag=0; //定义串口接收标志
u8 rec_flag3=0; //定义串口3的接收标志
u8 Angle[8]={0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c}; //定义舵机角度数组
int Cruising_Flag=0x00; 
int Pre_Cruising_Flag=0x00;
int overcount=0;               //用于检测是否定时器已经溢出
float result = 0;
u16 speed_left=1000;//左侧速度初值
u16 speed_right=1000;//右侧速度初值

//**************以下代码为重定义printf函数*****************
#ifdef __GNUC__ 
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)   
#else 
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f) 
#endif /* __GNUC__ */ 
PUTCHAR_PROTOTYPE 
{ 
  USART_SendData(USART1, (u16) ch); 
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) 
  { 
  } 
  return ch; 
}
//**************以上代码为重定义printf函数*****************
