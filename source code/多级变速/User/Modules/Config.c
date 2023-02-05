/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"


/*
 * 函数名：GPIO_ALL_Config
 * 描述  ：所有功能引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：初始化中调用
 */
void GPIO_ALL_Config(void)     //所有功能引脚初始化
{  
      Wave_GPIO_Config();       //超声波引脚初始化
      Infrared_GPIO_Config();   //跟随、避障红外引脚初始化
      MOTOR_GPIO_Config();      //电机引脚初始化
      Light_Config();           //车灯引脚初始化
      Fllow_GPIO_Config();      //循迹红外引脚初始化
      TIM2_Servo_GPIO_Config(); //定时器2(舵机引脚初始化)
      LED_GPIO_Config();        //初始化LED1、LED2流水灯
      Key_Configuration();      //按键GPIO及中断响应设置
}

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：流水灯引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void LED_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOD, &GPIO_InitStructure);
      LED1_Low;
      LED2_Low;
}

/*
 * 函数名：Key_Configuration
 * 描述  ：按键初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void Key_Configuration(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      EXTI_InitTypeDef EXTI_InitStructure;		//定义一个中断结构体变量
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
      GPIO_Init(GPIOB, &GPIO_InitStructure);
      
      //PB8中断
      GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);  	//PB8设为中断输入引脚
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//设置为中断模式
      EXTI_InitStructure.EXTI_Line = EXTI_Line8;	//中断线8
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //设置为下降沿触发方式
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;							//使能中断
      EXTI_Init(&EXTI_InitStructure);			//配置中断
      EXTI_ClearITPendingBit(EXTI_Line0);//清除中断标志
      
      //PB9中断
      GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);  	//PB9设为中断输入引脚
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//设置为中断模式
      EXTI_InitStructure.EXTI_Line = EXTI_Line9;	//中断线9
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //设置为下降沿触发方式
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;							//使能中断
      EXTI_Init(&EXTI_InitStructure);			//配置中断
      EXTI_ClearITPendingBit(EXTI_Line0);//清除中断标志
      
      NVIC_InitTypeDef NVIC_InitStructure;
      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //采用组别1
      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
}

/*
 * 函数名：TIM2_Servo_GPIO_Config
 * 描述  ：定时器2(舵机引脚初始化)
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM2_Servo_GPIO_Config(void) //定时器2(舵机引脚初始化)
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
 * 函数名：Wave_GPIO_Config
 * 描述  ：超声波引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void  Wave_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;  
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
      
      /*Echo pin define*/
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//悬浮模式
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      
      /*Trigle pin define*/
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOC,GPIO_Pin_4);
      GPIO_ResetBits(GPIOC,GPIO_Pin_5);
}

/*
 * 函数名：Infrared_GPIO_Config
 * 描述  ：跟随、避障红外引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
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
 * 函数名：Infrared_GPIO_Config
 * 描述  ：电机引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
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
 * 函数名：Light_Config
 * 描述  ：车灯初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
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
 * 函数名：Fllow_GPIO_Config
 * 描述  ：红外循迹引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
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

