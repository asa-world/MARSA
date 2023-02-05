/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
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

/**系统滴答中断服务函数********
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{  
  TimingDelay_Decrement();
}

/**********************************************************
** 函数名：EXTI9_5_IRQHandler
** 功能描述: 按键中断服务函数
** 输入参数: 无
** 输出参数: 无
***********************************************************/
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line9) != RESET)		//判断是否为第8线中断，即按键1中断
	{
		EXTI_ClearITPendingBit(EXTI_Line9);			//清除中断标志
		Refresh = 1;
                switch(Level)
                {
                  case 0:Level = 1; Mode = 0;return;
                  case 1:Level = 2;
                         switch(Mode)
                         {
                           case NORMAL:   Cruising_Flag = 0;return;//正常模式
                           case FOLLOW:   Cruising_Flag = 1;return;//跟随模式
                           case TRACK:    Cruising_Flag = 2;return;//循迹模式
                           case AVOID:    Cruising_Flag = 3;return;//红外避障模式
                           case WAVEAVOID:Cruising_Flag = 4;return;//超声波避障模式
                           case RANG:     Cruising_Flag = 5;return;//超声波测距模式
                           case DHT11:    Cruising_Flag = 6;return;//温湿度显示
                           default:Cruising_Flag = 0;return;
                         }
                  default:Level = 2;return;
                } 
        }
    if(EXTI_GetITStatus(EXTI_Line8) != RESET)		//判断是否为第9线中断，即按键2中断
	{
		EXTI_ClearITPendingBit(EXTI_Line8);			//清除中断标志
		Refresh = 1;
                switch(Level)
                {
                  case 0:return;
                  case 1:Mode++;if (Mode > 6)Mode = 0;return;
                  default:Level = 1;Cruising_Flag = 0;return;
                }
        }
}


/**********************串口1中断服务函数************************************/


void USART1_IRQHandler(void)                	//串口1中断服务程序
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
/**********************串口3中断服务函数************************************/


void USART3_IRQHandler(void)   
{

  static u8 i;
  if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)==1)
  {
    USART_ClearFlag(USART3,USART_FLAG_RXNE);
    /****************下面增加自己的函数*********************/
    //xxxxxx=USART_ReceiveData(USART3); 读取串口发送的数据
    if(rec_flag3==0){  //目前没有正在接收数据，此次可以接收
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


/**********************定时4中断服务函数************************************/

void TIM4_IRQHandler(void)   //TIM4中断
{
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
    {
      TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
      overcount++;//中断溢出计数
    }
}

/**********************定时2中断服务函数************************************/
static u16 pwmcount = 0;
void TIM2_IRQHandler(void)   //TIM2中断
{
  
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
    {
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
      pwmcount++;
      if(pwmcount == 3600)//20ms周期
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


