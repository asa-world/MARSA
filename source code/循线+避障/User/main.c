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

void line()
{
    if((TR_L==0)&&(TR_R==0))//两边同时都没有探测到黑线
    {
        MOTOR_GO_FORWARD;
         return;
     } 
                       
    else if((TR_L == 1)&&(TR_R== 0))//右侧遇到障碍  
      {
        MOTOR_GO_LEFT;
        return;
      }
              
    else if((TR_L == 0)&&(TR_R == 1))//左侧遇到障碍 
      {
        MOTOR_GO_RIGHT;
        return;
      }
                       
    else if((TR_L == 1)&&(TR_R == 1))//左右都检测到黑线，就如视频中的那样遇到一道横的胶带 
      {
        MOTOR_GO_STOP;
        return;
      }
}

void shangpo()
{
          MOTOR_GO_STOP;
        //停车
        Angle[0]=0;
        Angle[1]=70;
        Angle[3]=0;
        Delay_ms(500);
        float distance = Get_distance();    //获取超声波传感器距离值
        if((15<distance)||(distance<=0))             //判断超声波传感器距离值大于15小于等于0
        {
            MOTOR_GO_FORWARD;
            Delay_ms(300);
            MOTOR_GO_STOP;
            Angle[0]=180;
            Angle[3]=0;
            Delay_ms(500);
            Angle[1]=0;
            Delay_ms(50);
            MOTOR_GO_FORWARD;
            Delay_ms(500);
            return;
            //forward(adjust,500);
            Delay_ms(500);
        }
        else
        {
          Angle[0]=180;
          Angle[1]=0;
          Angle[3]=0;
          Delay_ms(500);
          MOTOR_GO_BACK;
          Delay_ms(500);
          MOTOR_GO_RIGHT;
          Delay_ms(250);
          MOTOR_GO_STOP;
        }
        return;
}

void main(void)
{
  /* 设置系统时钟为72M */
  SystemInit();
  
  SysTick_Configuration();  //SysTick中断配置，主要用来定时
  
  //LCD_12864_init();//液晶屏初始化
  
  GPIO_ALL_Config(); //GPIO初始化
  
  //Init_LED();   //流水灯等延时38秒等待WIFI模块启动
  
  //Init_Steer(); //舵机角度初始化  
    
  TIM2_PWM_Init(); //定时器2(舵机PWM初始化)
  
  TIM4_Init(); //定时器4(计时)
    
  TIM5_PWM_Init(); //定时器5(电机速度PWM初始化)
  
  //USART1_Config();  //串口初始化
  

  Angle[0]=180;
  Angle[1]=0;
  Angle[3]=0;
  while (1)
  {
    Set_Left_Speed(500+20);
   Set_Right_Speed(500+30);
    line();
   //MOTOR_GO_FORWARD;
      float distance = Get_distance();    //获取超声波传感器距离值
      if(!((8<distance)||(distance<=0)))             //判断超声波传感器距离值大于15小于等于0
      {
         shangpo();
      }
  }
  
}		

