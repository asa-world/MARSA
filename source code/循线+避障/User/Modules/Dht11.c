/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

/******************************************************************************
                                  Ӳ������
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
 * ��������DHT11_IN_Init
 * ����  ����ʼ��DHT11����Ϊ����ģʽ
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void DHT11_IN_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	/*��ʪ�ȴ����������߸�������*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_0);
}


/*
 * ��������DHT11_OUT_Init
 * ����  ����ʼ��DHT11����Ϊ���ģʽ
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void DHT11_OUT_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	/*��ʪ�ȴ�����������ģ������*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_0);
}


/*
 * ��������DHT11_Rst
 * ����  ��������Ӧ�ź�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void DHT11_Rst(void)
{
	DHT11_OUT_Init();  //��������Ϊ���ģʽ
	Pout_low;  
	Delay_ms(20);////��������18ms
	Pout_high; //��������20~40us,DHT11�᷵��һ���͵�ƽ
	Delay_us(35);
	DHT11_IN_Init();
	//���ùܽ�Ϊ����ģʽ�����ڶ�ȡDHT11��ֵ,��ʱPin(1)Ϊ�ߵ�ƽ
}


/*
 * ��������DHT11_Read_Byte
 * ����  ����ȡ����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static u8 DHT11_Read_Byte(void)
{
	u8 i,temp,Redata;
	for(i=0;i<8;i++) 
    {     
		while(!Pin);//��ʾ��ȡ�ĸߵ�λ��ʱ����20��΢�룬���ȡ����1����Ϊ0	
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
 * ��������Get_TempRH
 * ����  ����ȡ��ʪ��ֵ
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
u8 Get_TempRH(u8 flag)
{
  /**************************************************************
                  Data_Buff[0]  8Bitʪ����������
                  Data_Buff[1]  8Bitʪ��С������
                  Data_Buff[2]  8Bit�¶���������
                  Data_Buff[3]  8Bit�¶�С������
  **************************************************************/
        u8 i;
        u8 Data_Buff[5];
        DHT11_Rst();
	if(!Pin)  //��Ӧ�ź�,���߱�����  
	{       
		while(!Pin); //�ȴ�80ms�͵�ƽ��ȥ             
		while(Pin);  //�ȴ�80ms�ߵ�ƽ��ȥ 
                for(i=0;i<5;i++)
                {
		   Data_Buff[i]=DHT11_Read_Byte();  //��ȡ����     
                }
                DHT11_OUT_Init();
		Pout_high;    
		Delay_ms(100);  
        } 
       if(flag) return Data_Buff[2];//����1ʱ�����¶�
       else return Data_Buff[0];//����0ʱ����ʪ��
         
}

/*
 * ��������Display_Dht11
 * ����  ��PC����ʪ����ʾ
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
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
	   USART_SendData(USART1,temp);//����ʪ�ȶ�   ʪ��������20%��90%   
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
	   USART_SendData(USART1,temp);//�����¶�    �¶�������0�㵽50��
           Delay_ms(5);	   
	   USART_SendData(USART1,0xFF);
           TIM_Cmd(TIM2, ENABLE);
	   Delay_ms(1000);
           
}