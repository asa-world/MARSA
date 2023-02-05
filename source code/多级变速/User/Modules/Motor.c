/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"

unsigned long ifstop;  //在一段时间没有检测到黑线后就让它停止


/*
 * 函数名：forward
 * 描述  ：校准后的前进方向
 * 输入  ：adjust
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void forward(int adjust)
{
        Set_Left_Speed(speed_left);
        Set_Right_Speed(speed_right);
	switch(adjust)
	{
            case 1:MOTOR_GO_FORWARD;return;
            case 2:MOTOR_GO_FORWARD;return;
            case 3:MOTOR_GO_BACK;return;
            case 4:MOTOR_GO_BACK;return;
            case 5:MOTOR_GO_LEFT;return;
            case 6:MOTOR_GO_LEFT;return;
            case 7:MOTOR_GO_RIGHT;return;
            case 8:MOTOR_GO_RIGHT;return;
            default:return;		
	}
}

/*
 * 函数名：back
 * 描述  ：校准后的后退方向
 * 输入  ：adjust
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void back(int adjust)
{
        Set_Left_Speed(speed_left);
        Set_Right_Speed(speed_right);
	switch(adjust)
	{
            case 1:MOTOR_GO_BACK;return;
            case 2:MOTOR_GO_BACK;return;
            case 3:MOTOR_GO_FORWARD;return;
            case 4:MOTOR_GO_FORWARD;return;
            case 5:MOTOR_GO_RIGHT;return;
            case 6:MOTOR_GO_RIGHT;return;
            case 7:MOTOR_GO_LEFT;return;
            case 8:MOTOR_GO_LEFT;return;
            default:return;		
	}
}

/*
 * 函数名：left
 * 描述  ：校准后的左转方向
 * 输入  ：adjust
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void left(int adjust)
{
        Set_Left_Speed(speed_left);
        Set_Right_Speed(speed_right);
	switch(adjust)
	{
            case 1:MOTOR_GO_LEFT;return;
            case 2:MOTOR_GO_RIGHT;return;
            case 3:MOTOR_GO_LEFT;return;
            case 4:MOTOR_GO_RIGHT;return;
            case 5:MOTOR_GO_FORWARD;return;
            case 6:MOTOR_GO_BACK;return;
            case 7:MOTOR_GO_FORWARD;return;
            case 8:MOTOR_GO_BACK;return;
            default:return;	
        }
}

/*
 * 函数名：right
 * 描述  ：校准后的右转方向
 * 输入  ：adjust
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void right(int adjust)
{
        Set_Left_Speed(speed_left);
        Set_Right_Speed(speed_right);
	switch(adjust)
	{
            case 1:MOTOR_GO_RIGHT;return;
            case 2:MOTOR_GO_LEFT;return;
            case 3:MOTOR_GO_RIGHT;return;
            case 4:MOTOR_GO_LEFT;return;
            case 5:MOTOR_GO_BACK;return;
            case 6:MOTOR_GO_FORWARD;return;
            case 7:MOTOR_GO_BACK;return;
            case 8:MOTOR_GO_FORWARD;return;	
            default:return;
	}
}




/*
 * 函数名：Avoiding
 * 描述  ：红外避障模式
 * 输入  ：无
 * 输出  ：无
 * 调用  ：function中调用
 */
void Avoiding(void)
{
  if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)//检查中间红外被挡住
  {
    MOTOR_GO_STOP;return;//停止
  }
}

/*
 * 函数名：TrackLine
 * 描述  ：红外循迹模式
 * 输入  ：无
 * 输出  ：无
 * 调用  ：function中调用
 */
void TrackLine()//循迹,在没有检测到黑线的一段时间后会自动停止(防止乱跑)
{   


    if((TR_L==0)&&(TR_R==0))//两边同时都没有探测到黑线
    {    
         ifstop++;
         MOTOR_GO_FORWARD;

         return;
     } 
                       
    if((TR_L == 1)&&(TR_R== 0))//右侧检测到黑线
      {
        ifstop=0;
        MOTOR_GO_RIGHT;
        return;
      }
              
    if((TR_L == 0)&&(TR_R == 1))//左侧检测到黑线 
      {
       ifstop=0;
       MOTOR_GO_LEFT;
        return;
      }
                       
    if((TR_L == 1)&&(TR_R == 1))//左右都检测到黑线，就如视频中的那样遇到一道横的胶带 
      {  
        ifstop=0;
        MOTOR_GO_FORWARD;
        Delay_ms(100);
        MOTOR_GO_RIGHT;
        Delay_ms(300);
        MOTOR_GO_STOP;
        return;
      }
}


/*
 * 函数名：AvoidByRadar
 * 描述  ：超声波避障模式
 * 输入  ：distance
 * 输出  ：无
 * 调用  ：function中调用
 */
void AvoidByRadar(int distance)
{
    result = Get_distance();              //获得超声波测得距离
    if(distance*10<100)distance = 10;         //限定最小避障距离为10cm
    if((result>10)&&(result < distance*10))   //避障距离值(单位cm)，大于1是为了避免超声波的盲区
    {
       while((Get_distance()>10)&&(Get_distance() < distance*10))
       {
          back(adjust);
        }
        MOTOR_GO_STOP;
    }   
}



/*
 * 函数名：Follow
 * 描述  ：红外跟随模式
 * 输入  ：无
 * 输出  ：无
 * 调用  ：function中调用
 */
void Follow(void)
{
      if(IR== 1)	//中间传感器OK
      {
      
            if((FR_L == 0)&& (FR_R == 0)) //俩边同时探测到障碍物
            {
            
                MOTOR_GO_STOP//停止
            } 
             
            if((FR_L == 0)&& (FR_R == 1))//左侧障碍物
            {
            
                left(adjust);//左转
            }
    
            if((FR_L == 1)&& (FR_R == 0))//右侧障碍物
            {
                right(adjust);//右转
            }
             
            if((FR_L == 1)&& (FR_R == 1))//无任何障碍物
            {
                forward(adjust);//前进
            }
      }
      else
      {
           MOTOR_GO_STOP;
      }
}


void Route()
{
  if (RevStatus == 0)
  {
    USART1_sned_char(0xff);
    USART1_sned_char(0xA8);
    USART1_sned_char(0x00);
    USART1_sned_char(0x00);
    USART1_sned_char(0xff);
    Delay_ms(500);
  }
  while (RevStatus)
  {
    if (RevStatus == 1)
    {
      GPIOB->ODR ^= GPIO_Pin_5;                     //电机指示灯翻转
      RevStatus = 0;
      MOTOR_GO_LEFT;
      Delay_ms((int)(TurnAngle * 1.8));
      MOTOR_GO_STOP;
      MOTOR_GO_FORWARD;
      Delay_ms(Golength * 2);
      MOTOR_GO_STOP;
      break;
    }
    if (RevStatus == 2)
    {
      GPIOB->ODR ^= GPIO_Pin_5;                     //电机指示灯翻转
      RevStatus = 0;
      MOTOR_GO_RIGHT;
      Delay_ms((int)(TurnAngle * 1.8));
      MOTOR_GO_STOP;
      MOTOR_GO_FORWARD;
      Delay_ms(Golength * 2);
      MOTOR_GO_STOP;
      break;
    }
  }
}

