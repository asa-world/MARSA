/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"

/**************·���滮����*****************/
u8 RevStatus=0;
u8 TurnAngle;
u8 Golength;

/**************12864����*****************/
int Level = 0;
int Mode = 0;
int Refresh = 0;

u8 adjust; //������У׼��־
u8 buffer[3]; //���崮�ڻ����������
u8 buffer3[10];
u8 rec_flag=0; //���崮�ڽ��ձ�־
u8 rec_flag3=0; //���崮��3�Ľ��ձ�־
u8 Angle[8]={0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c}; //�������Ƕ�����
int Cruising_Flag=0x00; 
int Pre_Cruising_Flag=0x00;
int overcount=0;               //���ڼ���Ƿ�ʱ���Ѿ����
float result = 0;
u16 speed_left=1000;//����ٶȳ�ֵ
u16 speed_right=1000;//�Ҳ��ٶȳ�ֵ

//**************���´���Ϊ�ض���printf����*****************
#ifdef __GNUC__ 
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)   
#else 
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f) 
#endif /* __GNUC__ */ 
PUTCHAR_PROTOTYPE 
{ 
  USART_SendData(USART1, (u16) ch); 
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) 
  { 
  } 
  return ch; 
}
//**************���ϴ���Ϊ�ض���printf����*****************
