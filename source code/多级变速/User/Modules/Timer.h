/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/
#ifndef __TIMER_H
#define __TIMER_H



void TIM2_PWM_Init(void);
void TIM4_Init(void);
void TIM5_PWM_Init(void);
void Set_Left_Speed(u16 Speed_Left);
void Set_Right_Speed(u16 Speed_Right);


#endif /* __TIMER_H */
