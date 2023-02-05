/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/
#ifndef __INCLUDE_H
#define __INCLUDE_H

#include "stm32f10x.h"
#include "Interrupt.h"
#include "SysTick.h"
#include "usart1.h"
#include "usart3.h"
#include "Timer.h"
#include "function.h"
#include "i2c_eeprom.h"
#include "Config.h"
#include "Motor.h"
#include "Ultrasonic.h"
#include "Init.h"
#include "DHT11.h"
#include "12864.h"
#include <stdarg.h>
#include <math.h>
#include <stdio.h>

#define INIT      0     //��ʼ��
#define NORMAL    0     //����ģʽ
#define FOLLOW    1     //����ģʽ
#define TRACK     2     //ѭ��ģʽ
#define AVOID     3     //�������ģʽ
#define WAVEAVOID 4     //����������ģʽ
#define RANG      5     //���������ģʽ
#define DHT11     6     //��ʪ����ʾ

#define module_interval 25    //���峬����ģ����շ���˼��(��λ��mm)
#define object_distance 100.0   //�������ľ���


extern u8 adjust;
extern u8 buffer[3];
extern u8 buffer3[10];
extern u8 rec_flag;
extern u8 rec_flag3;
extern u8 Angle[8];
extern int Level;
extern int Mode;
extern int Refresh;
extern int Cruising_Flag;
extern int Pre_Cruising_Flag;
extern int overcount;               //���ڼ���Ƿ�ʱ���Ѿ����
extern float result;
extern u16 speed_left;//����ٶȳ�ֵ
extern u16 speed_right;//�Ҳ��ٶȳ�ֵ

extern u8 RevStatus;
extern u8 TurnAngle;
extern u8 Golength;

#endif /* __INCLUDE_H */