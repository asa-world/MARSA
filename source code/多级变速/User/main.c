/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤���� V3.2�汾
*/

/**************************** WiFi �����˴��⹤���� *******************************
��оƬ��STM32F105RCT6
 ����     ����              I/O             TIMER         ����

�����    ena              PA0             TIMER5/CH1
          enb              PA1             TIMER5/CH2
          IN1              PC6
          IN2              PC7
          IN3              PC8
          IN4              PC9
�����    SER1             PA2             TIMER2
          SER2             PA3             TIMER2

���ڣ�    TXD              PA9
          RXD              PA10

PWM��    ���1/  11~       PA6             TIMER2
         ���2/  2         PA7             TIMER2
         ���3/  4         PB0             TIMER2
         ���4/  3~        PB1             TIMER2

I/O��    A15  /  A5        PC5             ADC12-IN15       Echo
         A14  /  A4        PC4             ADC12-IN14       Trig
         A13  /  A3        PC3             ADC12-IN13       �����
         A12  /  A2        PC2             ADC12-IN12       �Һ���
         A11  /  A1        PC1             ADC12-IN11       �к���
         A10  /  A0        PC0             ADC12-IN10       ����
		             
         A11  /  A1        PC1             ADC12-IN11       �������ǰ         
                           PC10                             ���������                                                                      
                           PC11                             ���������

**********************************************************************************/

#include "Include.h"
/*
 * ��������main
 * ����  ��������ں���
 * ����  ����
 * ���  ����
 * ����  ����
 */
 int speed=3;
 float s_up=1;
 float s_down=3;

void main(void)
{
  /* ����ϵͳʱ��Ϊ72M ;*/
  SystemInit();
  
  
  
  SysTick_Configuration();  //SysTick�ж����ã���Ҫ������ʱ
  
  //LCD_12864_init();//Һ������ʼ��
  
  GPIO_ALL_Config(); //GPIO��ʼ��
  
  //Init_LED();   //��ˮ�Ƶ���ʱ38��ȴ�WIFIģ������
  
  //Init_Steer(); //����Ƕȳ�ʼ��  
    
  //TIM2_PWM_Init(); //��ʱ��2(���PWM��ʼ��)
  
  TIM4_Init(); //��ʱ��4(��ʱ)
    
  TIM5_PWM_Init(); //��ʱ��5(����ٶ�PWM��ʼ��)
  
  USART1_Config();  //���ڳ�ʼ��
  
  ifstop=0; //���������೤ʱ��û�м�⵽����
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

