/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/
#ifndef __DHT11_H
#define	__DHT11_H

#include "Include.h"
#include "stm32f10x.h"


static void DHT11_IN_Init(void);
static void DHT11_OUT_Init(void);
static void DHT11_Rst(void);
static u8 DHT11_Read_Byte(void);
u8 Get_TempRH(u8 flag);
void Display_Dht11();

#endif /*  __MOTOR_H  */