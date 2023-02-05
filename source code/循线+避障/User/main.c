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

void line()
{
    if((TR_L==0)&&(TR_R==0))//����ͬʱ��û��̽�⵽����
    {
        MOTOR_GO_FORWARD;
         return;
     } 
                       
    else if((TR_L == 1)&&(TR_R== 0))//�Ҳ������ϰ�  
      {
        MOTOR_GO_LEFT;
        return;
      }
              
    else if((TR_L == 0)&&(TR_R == 1))//��������ϰ� 
      {
        MOTOR_GO_RIGHT;
        return;
      }
                       
    else if((TR_L == 1)&&(TR_R == 1))//���Ҷ���⵽���ߣ�������Ƶ�е���������һ����Ľ��� 
      {
        MOTOR_GO_STOP;
        return;
      }
}

void shangpo()
{
          MOTOR_GO_STOP;
        //ͣ��
        Angle[0]=0;
        Angle[1]=70;
        Angle[3]=0;
        Delay_ms(500);
        float distance = Get_distance();    //��ȡ����������������ֵ
        if((15<distance)||(distance<=0))             //�жϳ���������������ֵ����15С�ڵ���0
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
  /* ����ϵͳʱ��Ϊ72M */
  SystemInit();
  
  SysTick_Configuration();  //SysTick�ж����ã���Ҫ������ʱ
  
  //LCD_12864_init();//Һ������ʼ��
  
  GPIO_ALL_Config(); //GPIO��ʼ��
  
  //Init_LED();   //��ˮ�Ƶ���ʱ38��ȴ�WIFIģ������
  
  //Init_Steer(); //����Ƕȳ�ʼ��  
    
  TIM2_PWM_Init(); //��ʱ��2(���PWM��ʼ��)
  
  TIM4_Init(); //��ʱ��4(��ʱ)
    
  TIM5_PWM_Init(); //��ʱ��5(����ٶ�PWM��ʼ��)
  
  //USART1_Config();  //���ڳ�ʼ��
  

  Angle[0]=180;
  Angle[1]=0;
  Angle[3]=0;
  while (1)
  {
    Set_Left_Speed(500+20);
   Set_Right_Speed(500+30);
    line();
   //MOTOR_GO_FORWARD;
      float distance = Get_distance();    //��ȡ����������������ֵ
      if(!((8<distance)||(distance<=0)))             //�жϳ���������������ֵ����15С�ڵ���0
      {
         shangpo();
      }
  }
  
}		

