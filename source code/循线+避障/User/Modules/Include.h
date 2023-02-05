/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
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

#define INIT      0     //初始化
#define NORMAL    0     //正常模式
#define FOLLOW    1     //跟随模式
#define TRACK     2     //循迹模式
#define AVOID     3     //红外避障模式
#define WAVEAVOID 4     //超声波避障模式
#define RANG      5     //超声波测距模式
#define DHT11     6     //温湿度显示

#define module_interval 25    //定义超声波模块接收发射端间距(单位：mm)
#define object_distance 100.0   //检测物体的距离


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
extern int overcount;               //用于检测是否定时器已经溢出
extern float result;
extern u16 speed_left;//左侧速度初值
extern u16 speed_right;//右侧速度初值

extern u8 RevStatus;
extern u8 TurnAngle;
extern u8 Golength;

#endif /* __INCLUDE_H */