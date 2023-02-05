/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/
#include "Include.h"


/*
 * 函数名：Get_distance
 * 描述  ：获得超声波距离
 * 输入  ：无
 * 输出  ：distance(毫米级)
 * 调用  ：外部调用
 */
float Get_distance(void)
{
  float distance=0,sum_distance=0;
  u16 TIM=0;
  u8 i=0;
  /*测5次数据计算一次平均值*/
  while(i!=5)
  {
      GPIO_SetBits(GPIOC,GPIO_Pin_4);//拉高信号，作为触发信号
      Delay_us(12);//高电平信号超过10us
      GPIO_ResetBits(GPIOC,GPIO_Pin_4);//拉低信号
      
      TIM_Cmd(TIM4, ENABLE);
      /*等待回响信号*/
      while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) && overcount==0);
      TIM4->CNT=0;
      while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) && overcount==0);
      TIM_Cmd(TIM4, DISABLE);
      i++;
      if(overcount!=0)//定时器中断溢出
      {
            overcount=0;//清零
            return 0.0;
      }
      TIM=TIM_GetCounter(TIM4);//获取计TIM4数寄存器中的计数值
      distance=(float)sqrt((TIM/10.0*17)*(TIM/10.0*17)-module_interval*module_interval/4.0)+12.0; //12.0为误差补偿//根据计数值算出单次测距距离
      sum_distance=sum_distance+distance;//累加5次
  }
  distance=sum_distance/5;//求5次平均值
  return distance;//返回距离值
}



/*
 * 函数名：Send_Distance
 * 描述  ：向上位机发送超声波距离
 * 输入  ：无
 * 输出  ：distance(毫米级)
 * 调用  ：外部调用
 */
void Send_Distance(void)
{
    USART_SendData(USART1, 0xFF);
    Delay_ms(5);
    USART_SendData(USART1, 0x03);
    Delay_ms(5);
    USART_SendData(USART1, 0x00);
    Delay_ms(5);
    USART_SendData(USART1, (u16)Get_distance()/10);
    Delay_ms(5);
    USART_SendData(USART1, 0xFF);
    Delay_ms(1000);   
}