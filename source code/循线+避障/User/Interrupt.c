/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"


void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void) 
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**ϵͳ�δ��жϷ�����********
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{  
  TimingDelay_Decrement();
}

/**********************************************************
** ��������EXTI9_5_IRQHandler
** ��������: �����жϷ�����
** �������: ��
** �������: ��
***********************************************************/
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line9) != RESET)		//�ж��Ƿ�Ϊ��8���жϣ�������1�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line9);			//����жϱ�־
		Refresh = 1;
                switch(Level)
                {
                  case 0:Level = 1; Mode = 0;return;
                  case 1:Level = 2;
                         switch(Mode)
                         {
                           case NORMAL:   Cruising_Flag = 0;return;//����ģʽ
                           case FOLLOW:   Cruising_Flag = 1;return;//����ģʽ
                           case TRACK:    Cruising_Flag = 2;return;//ѭ��ģʽ
                           case AVOID:    Cruising_Flag = 3;return;//�������ģʽ
                           case WAVEAVOID:Cruising_Flag = 4;return;//����������ģʽ
                           case RANG:     Cruising_Flag = 5;return;//���������ģʽ
                           case DHT11:    Cruising_Flag = 6;return;//��ʪ����ʾ
                           default:Cruising_Flag = 0;return;
                         }
                  default:Level = 2;return;
                } 
        }
    if(EXTI_GetITStatus(EXTI_Line8) != RESET)		//�ж��Ƿ�Ϊ��9���жϣ�������2�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line8);			//����жϱ�־
		Refresh = 1;
                switch(Level)
                {
                  case 0:return;
                  case 1:Mode++;if (Mode > 6)Mode = 0;return;
                  default:Level = 1;Cruising_Flag = 0;return;
                }
        }
}


/**********************����1�жϷ�����************************************/


void USART1_IRQHandler(void)                	//����1�жϷ������
{
  static u8 i;
  if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==1)
  {
    USART_ClearFlag(USART1,USART_FLAG_RXNE);
    if(rec_flag==0)
    {
      if(USART_ReceiveData(USART1)==0xff)
      {
        rec_flag=1;	
        i=0;
      }			
    }
    else
    {
      if(USART_ReceiveData(USART1)==0xff)
      {
        rec_flag=0;	
        if(i==3)
        {
          Communication_Decode_flag=1;
         //Communication_Decode();		
        }
        i=0;
      }
      else
      {
        buffer[i]=USART_ReceiveData(USART1);
        i++;
      }
    }		
  }
  else
  {
    USART_ClearFlag(USART1,USART_FLAG_LBD);
  }	
} 
/**********************����3�жϷ�����************************************/


void USART3_IRQHandler(void)   
{

  static u8 i;
  if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)==1)
  {
    USART_ClearFlag(USART3,USART_FLAG_RXNE);
    /****************���������Լ��ĺ���*********************/
    //xxxxxx=USART_ReceiveData(USART3); ��ȡ���ڷ��͵�����
    if(rec_flag3==0){  //Ŀǰû�����ڽ������ݣ��˴ο��Խ���
      if(USART_ReceiveData(USART3)==0x55){
        rec_flag3=1;
        i=0; 
      }
    }else{
        buffer3[i]=USART_ReceiveData(USART3);
        i++;  
        if(i==9){
            rec_flag3=0;
            Communication_Decode_flag3=1;
            Communication_Decode3();
            i=0;  
        }
    }
  }else{
    USART_ClearFlag(USART3,USART_FLAG_LBD);
  }	
} 


/**********************��ʱ4�жϷ�����************************************/

void TIM4_IRQHandler(void)   //TIM4�ж�
{
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {
      TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
      overcount++;//�ж��������
    }
}

/**********************��ʱ2�жϷ�����************************************/
static u16 pwmcount = 0;
void TIM2_IRQHandler(void)   //TIM2�ж�
{
  
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
      pwmcount++;
      if(pwmcount == 3600)//20ms����
     { 
          pwmcount = 0;
          
      }
      if(pwmcount == 500)
      {
          Servo1_High;
          Servo2_High;
          Servo3_High;
          Servo4_High;
          Servo5_High;
          Servo6_High;
          Servo7_High;
          Servo8_High;
      }
      
      if(pwmcount == (2*Angle[0]+590)) {Servo1_Low;}
      if(pwmcount == (2*Angle[1]+590)) {Servo2_Low;}
      if(pwmcount == (2*Angle[2]+590)) {Servo3_Low;}
      if(pwmcount == (2*Angle[3]+590)) {Servo4_Low;}
      if(pwmcount == (2*Angle[4]+590)) {Servo5_Low;}
      if(pwmcount == (2*Angle[5]+590)) {Servo6_Low;}
      if(pwmcount == (2*Angle[6]+590)) {Servo7_Low;}
      if(pwmcount == (2*Angle[7]+590)) {Servo8_Low;}
      
    }
}


