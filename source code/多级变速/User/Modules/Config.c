/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"


/*
 * ��������GPIO_ALL_Config
 * ����  �����й������ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  ����ʼ���е���
 */
void GPIO_ALL_Config(void)     //���й������ų�ʼ��
{  
      Wave_GPIO_Config();       //���������ų�ʼ��
      Infrared_GPIO_Config();   //���桢���Ϻ������ų�ʼ��
      MOTOR_GPIO_Config();      //������ų�ʼ��
      Light_Config();           //�������ų�ʼ��
      Fllow_GPIO_Config();      //ѭ���������ų�ʼ��
      TIM2_Servo_GPIO_Config(); //��ʱ��2(������ų�ʼ��)
      LED_GPIO_Config();        //��ʼ��LED1��LED2��ˮ��
      Key_Configuration();      //����GPIO���ж���Ӧ����
}

/*
 * ��������LED_GPIO_Config
 * ����  ����ˮ�����ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
 */
void LED_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOD, &GPIO_InitStructure);
      LED1_Low;
      LED2_Low;
}

/*
 * ��������Key_Configuration
 * ����  ��������ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
 */
void Key_Configuration(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      EXTI_InitTypeDef EXTI_InitStructure;		//����һ���жϽṹ�����
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
      GPIO_Init(GPIOB, &GPIO_InitStructure);
      
      //PB8�ж�
      GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);  	//PB8��Ϊ�ж���������
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//����Ϊ�ж�ģʽ
      EXTI_InitStructure.EXTI_Line = EXTI_Line8;	//�ж���8
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //����Ϊ�½��ش�����ʽ
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;							//ʹ���ж�
      EXTI_Init(&EXTI_InitStructure);			//�����ж�
      EXTI_ClearITPendingBit(EXTI_Line0);//����жϱ�־
      
      //PB9�ж�
      GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);  	//PB9��Ϊ�ж���������
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//����Ϊ�ж�ģʽ
      EXTI_InitStructure.EXTI_Line = EXTI_Line9;	//�ж���9
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //����Ϊ�½��ش�����ʽ
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;							//ʹ���ж�
      EXTI_Init(&EXTI_InitStructure);			//�����ж�
      EXTI_ClearITPendingBit(EXTI_Line0);//����жϱ�־
      
      NVIC_InitTypeDef NVIC_InitStructure;
      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //�������1
      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
}

/*
 * ��������TIM2_Servo_GPIO_Config
 * ����  ����ʱ��2(������ų�ʼ��)
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM2_Servo_GPIO_Config(void) //��ʱ��2(������ų�ʼ��)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_Init(GPIOB,&GPIO_InitStructure);
 
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_Init(GPIOA,&GPIO_InitStructure);

}
/*
 * ��������Wave_GPIO_Config
 * ����  �����������ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
 */
void  Wave_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;  
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
      
      /*Echo pin define*/
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//����ģʽ
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      
      /*Trigle pin define*/
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOC,GPIO_Pin_4);
      GPIO_ResetBits(GPIOC,GPIO_Pin_5);
}

/*
 * ��������Infrared_GPIO_Config
 * ����  �����桢���Ϻ������ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
 */
void Infrared_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      GPIO_SetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);	
}

/*
 * ��������Infrared_GPIO_Config
 * ����  ��������ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
 */
void MOTOR_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |GPIO_Pin_9;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |GPIO_Pin_9);	
}



/*
 * ��������Light_Config
 * ����  �����Ƴ�ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
 */
void Light_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOC, GPIO_Pin_0);	
}


/*
 * ��������Fllow_GPIO_Config
 * ����  ������ѭ�����ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
 */
void Fllow_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14; 	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      GPIO_SetBits(GPIOC,GPIO_Pin_13|GPIO_Pin_14);	
}

