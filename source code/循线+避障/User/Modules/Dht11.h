/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
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