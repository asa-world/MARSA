/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

/******************************************************************************
                                  硬件连接
                          + ------------VCC
                          - ------------GND
                          out------------GPIOC_0(A0)
********************************************************************************/                         
#include "Dht11.h"
#include "SysTick.h"
#include "usart1.h"
#define Pin GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define Pout_high GPIO_SetBits(GPIOC,GPIO_Pin_0)
#define Pout_low GPIO_ResetBits(GPIOC,GPIO_Pin_0)
                                    

/*
 * 函数名：DHT11_IN_Init
 * 描述  ：初始化DHT11总线为输入模式
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void DHT11_IN_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	/*温湿度传感器控制线浮空输入*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_0);
}


/*
 * 函数名：DHT11_OUT_Init
 * 描述  ：初始化DHT11总线为输出模式
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void DHT11_OUT_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	/*温湿度传感器控制线模拟输入*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_0);
}


/*
 * 函数名：DHT11_Rst
 * 描述  ：发送响应信号
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void DHT11_Rst(void)
{
	DHT11_OUT_Init();  //设置引脚为输出模式
	Pout_low;  
	Delay_ms(20);////拉低至少18ms
	Pout_high; //总线拉高20~40us,DHT11会返回一个低电平
	Delay_us(35);
	DHT11_IN_Init();
	//设置管脚为输入模式，用于读取DHT11的值,此时Pin(1)为高电平
}


/*
 * 函数名：DHT11_Read_Byte
 * 描述  ：读取数据
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static u8 DHT11_Read_Byte(void)
{
	u8 i,temp,Redata;
	for(i=0;i<8;i++) 
    {     
		while(!Pin);//表示读取的高电位延时大于20多微秒，则读取的是1否则为0	
		Delay_us(35);        	
		temp=0;       
		if(Pin)       
		temp=1;        
		while(Pin);      
		Redata<<=1;        
		Redata|=temp;
    }                             
	return Redata;	
}


/*
 * 函数名：Get_TempRH
 * 描述  ：获取温湿度值
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
u8 Get_TempRH(u8 flag)
{
  /**************************************************************
                  Data_Buff[0]  8Bit湿度整数数据
                  Data_Buff[1]  8Bit湿度小数数据
                  Data_Buff[2]  8Bit温度整数数据
                  Data_Buff[3]  8Bit温度小数数据
  **************************************************************/
        u8 i;
        u8 Data_Buff[5];
        DHT11_Rst();
	if(!Pin)  //响应信号,总线被拉低  
	{       
		while(!Pin); //等待80ms低电平过去             
		while(Pin);  //等待80ms高电平过去 
                for(i=0;i<5;i++)
                {
		   Data_Buff[i]=DHT11_Read_Byte();  //读取数据     
                }
                DHT11_OUT_Init();
		Pout_high;    
		Delay_ms(100);  
        } 
       if(flag) return Data_Buff[2];//等于1时返回温度
       else return Data_Buff[0];//等于0时返回湿度
         
}

/*
 * 函数名：Display_Dht11
 * 描述  ：PC端温湿度显示
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Display_Dht11()
{
           TIM_Cmd(TIM2, DISABLE);
           uint16_t temp = 0;
           temp = Get_TempRH(0);
           Delay_ms(5);
           USART_SendData(USART1,0xFF);
           Delay_ms(5);
	   USART_SendData(USART1,0x3D);
           Delay_ms(5);
           USART_SendData(USART1,0x00);
           Delay_ms(5);
	   USART_SendData(USART1,temp);//发送湿度度   湿度量程是20%到90%   
           Delay_ms(5);
	   USART_SendData(USART1,0xFF);
	   Delay_ms(1000); 
           temp = Get_TempRH(1);
           Delay_ms(5);
	   USART_SendData(USART1,0xFF);
           Delay_ms(5);
	   USART_SendData(USART1,0x3F);
           Delay_ms(5);
           USART_SendData(USART1,0x00);
           Delay_ms(5);
	   USART_SendData(USART1,temp);//发送温度    温度量程是0°到50°
           Delay_ms(5);	   
	   USART_SendData(USART1,0xFF);
           TIM_Cmd(TIM2, ENABLE);
	   Delay_ms(1000);
           
}