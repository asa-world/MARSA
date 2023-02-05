/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室 V3.2版本
*/

/**************************** WiFi 机器人创意工作室 *******************************
主芯片：STM32F105RCT6
 功能     名称              I/O             TIMER         功能

电机：    ena              PA0             TIMER5/CH1
          enb              PA1             TIMER5/CH2
          IN1              PC6
          IN2              PC7
          IN3              PC8
          IN4              PC9
舵机：    SER1             PA2             TIMER2
          SER2             PA3             TIMER2

串口：    TXD              PA9
          RXD              PA10

PWM：    舵机1/  11~       PA6             TIMER2
         舵机2/  2         PA7             TIMER2
         舵机3/  4         PB0             TIMER2
         舵机4/  3~        PB1             TIMER2

I/O：    A15  /  A5        PC5             ADC12-IN15       Echo
         A14  /  A4        PC4             ADC12-IN14       Trig
         A13  /  A3        PC3             ADC12-IN13       左红外
         A12  /  A2        PC2             ADC12-IN12       右红外
         A11  /  A1        PC1             ADC12-IN11       中红外
         A10  /  A0        PC0             ADC12-IN10       车灯
		             
         A11  /  A1        PC1             ADC12-IN11       跟随红外前         
                           PC10                             跟随红外左                                                                      
                           PC11                             跟随红外右

**********************************************************************************/

#include "Include.h"
/*
 * 函数名：main
 * 描述  ：程序入口函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：无
 */
 int speed=3;
 float s_up=1;
 float s_down=3;

void main(void)
{
  /* 设置系统时钟为72M ;*/
  SystemInit();
  
  
  
  SysTick_Configuration();  //SysTick中断配置，主要用来定时
  
  //LCD_12864_init();//液晶屏初始化
  
  GPIO_ALL_Config(); //GPIO初始化
  
  //Init_LED();   //流水灯等延时38秒等待WIFI模块启动
  
  //Init_Steer(); //舵机角度初始化  
    
  //TIM2_PWM_Init(); //定时器2(舵机PWM初始化)
  
  TIM4_Init(); //定时器4(计时)
    
  TIM5_PWM_Init(); //定时器5(电机速度PWM初始化)
  
  USART1_Config();  //串口初始化
  
  ifstop=0; //用来计数多长时间没有检测到黑线
  USART3_Config();
  

  Set_Right_Speed(500);
  Set_Left_Speed(500);
  while (1)
  { 
    if(ifstop<150000){
       TrackLine();
    }
    if(pitchy>190){
       Set_Right_Speed((u16)(speed+(pitchy-180)*s_up));
       Set_Left_Speed((u16)(speed+(pitchy-180)*s_up));
     }
   else if(pitchy<170){
      Set_Right_Speed((u16)(speed+(180-pitchy)*s_down));
      Set_Left_Speed((u16)(speed+(180-pitchy)*s_down));
    } 
   else{
     Set_Right_Speed(speed);
     Set_Left_Speed(speed);
   }
  }
}		

