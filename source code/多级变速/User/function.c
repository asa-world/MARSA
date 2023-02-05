/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"
int Communication_Decode_flag=0;
int Communication_Decode_flag3=0;
float rollx;
float pitchy=0;
float yawz;
float temperature;



/*
 * 函数名：Communication_Decode
 * 描述  ：解析串口数据功能函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在Interrupt.c串口中断1函数中调用
 */

 void Communication_Decode(void)  
{
  if(Communication_Decode_flag)
  {
    Communication_Decode_flag=0;
    if(buffer[0]==0x00)//手动控制
    {
         GPIOB->ODR ^= GPIO_Pin_5;                     //电机指示灯翻转
         switch(buffer[1])
          {
            case 0x00:MOTOR_GO_STOP;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;           //停止
            case 0x01:MOTOR_GO_FORWARD;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;        //前进
            case 0x02:MOTOR_GO_BACK;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;           //后退
            case 0x03:MOTOR_GO_LEFT;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;           //左转
            case 0x04:MOTOR_GO_RIGHT;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;          //右转
            
            case 0x05:MOTOR_GO_FORWARD;Set_Left_Speed(speed_left); Set_Right_Speed(20);return;          //左前
            case 0x06:MOTOR_GO_FORWARD;Set_Left_Speed(20); Set_Right_Speed(speed_right);return;          //右前
            case 0x07:MOTOR_GO_BACK;Set_Left_Speed(speed_left); Set_Right_Speed(20);return;          //左后
            case 0x08:MOTOR_GO_BACK;Set_Left_Speed(20); Set_Right_Speed(speed_right);return;          //右后
            
            default:return;                          //停止
          }
    }
    
   else if(buffer[0]==0x01)//舵机控制
    {      
        GPIOD->ODR ^= GPIO_Pin_2;                      //舵机指示灯翻转
        switch(buffer[1])
        {
            case 0x01:Angle[0]=(buffer[2]); return;   //舵机1号
            case 0x02:Angle[1]=(buffer[2]); return;   //舵机2号
            case 0x03:Angle[2]=(buffer[2]); return;   //舵机3号
            case 0x04:Angle[3]=(buffer[2]); return;   //舵机4号
            case 0x05:Angle[4]=(buffer[2]); return;   //舵机5号  
            case 0x06:Angle[5]=(buffer[2]); return;   //舵机6号  
            case 0x07:Angle[6]=(buffer[2]); return;   //舵机7号
            case 0x08:Angle[7]=(buffer[2]); return;   //舵机8号
            default : return;
        }  
            
    }
    else if(buffer[0]==0x02)
    {
        if(buffer[2]>100)return;     
        if(buffer[1]==0x01)//等于01表示左侧调速
        {
            speed_left=(buffer[2]*8+200);//buffer[2]为档位值最小0最大100
            //将档位值换算左侧速度
            Set_Left_Speed(speed_left);//左边速度
            //I2C_EEPROM_WriteByte(buffer[2],0x09);//把右侧档位存储到EEPROM
        }
        if(buffer[1]==0x02)//等于02表示右侧调速
        {
            speed_right=(buffer[2]*8+200);//buffer[2]为档位值最小0最大100
            //将档位值换算右侧速度
            Set_Right_Speed(speed_right);//右边速度
            //I2C_EEPROM_WriteByte(buffer[2],0x0a);//把右侧档位存储到EEPROM
        }
    }
    
    else if(buffer[0]==0x32)//存储角度
    {
        I2C_EEPROM_BufferWrite(Angle,0x00,8);//把角度存储到EEPROM
    }
    
    
    else if(buffer[0]==0x33)//角度归位
    {
        Init_Steer();
    }
    
    
    else if(buffer[0]==0x40)//电机校准标志，校准功能模式的电机转向方向
    {
        adjust=buffer[1];
        I2C_EEPROM_WriteByte(adjust,0x10);//存储标志	
    }
    
    
    else if(buffer[0]==0x13)//功能模式切换开关
    {
         
        switch(buffer[1])
            {
              case 0x01: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 1;Level = 2;Mode = 1;Refresh = 1; return;//红外跟随
              case 0x02: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 2;Level = 2;Mode = 2;Refresh = 1; return;//红外巡线
              case 0x03: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 3;Level = 2;Mode = 3;Refresh = 1; return;//红外避障
              case 0x04: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 4;Level = 2;Mode = 4;Refresh = 1; return;//超声波雷达避障
              case 0x05: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 5;Level = 2;Mode = 5;Refresh = 1; return;//超声波距离显示
              case 0x06: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 6;Level = 2;Mode = 6;Refresh = 1; return;//温湿度显示
              case 0x07: if(Cruising_Flag !=7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 7;                                return;//路径规划  
              case 0x00: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 0;Level = 2;Mode = 0;Refresh = 1; return;//正常模式
              default: return;//正常模式
            }
    }
    else if(buffer[0]==0xA0)//收到右转
      {
         RevStatus = 2;
         TurnAngle=buffer[1];
         Golength=buffer[2];
      }
      else if(buffer[0]==0xA1)//收到左转
      {
         RevStatus = 1;
         TurnAngle=buffer[1];
         Golength=buffer[2];
      }   
    else if(buffer[0]==0x04)//FF040000FF开灯  FF040100FF关灯
    {
      switch(buffer[1])
      {
        case 0x00:Open_Light;return;//开灯
        case 0x01:Closs_Light;return;//关灯
        default:Closs_Light;return;
      }
    }
 
  }
    
}


/*
 * 函数名：Cruising
 * 描述  ：模式切换函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：main函数中调用
 */
void Cruising(void)
{
      	 if(Pre_Cruising_Flag != Cruising_Flag)
	 {
	     if(Pre_Cruising_Flag != 0)
		 {
		   MOTOR_GO_STOP; 
		 }
    	 Pre_Cruising_Flag =  Cruising_Flag;
	 }	

	switch(Cruising_Flag)
	{
	   case 0x01:Follow();            break;//红外跟随模式
	   case 0x02:TrackLine();         break;//红外巡线模式
	   case 0x03:Avoiding();          break;//红外避障模式
	   case 0x04:AvoidByRadar(15);    break;//超声波壁障模式
           case 0x05:Send_Distance();     break;//超声波距离显示模式 (此功能需要开通WIFI模块数据双向功能，教程参考： http://www.wifi-robots.com/thread-2985-1-1.html)
           case 0x06:Display_Dht11();     break;//温湿度显示模式 (此功能需要开通WIFI模块数据双向功能，教程参考： http://www.wifi-robots.com/thread-2985-1-1.html)
	   case 0x07:Route();             break;//路径规划
           default:break;
	}	
        Communication_Decode();
}

void Communication_Decode3(){
  if(Communication_Decode_flag3){
    Communication_Decode_flag3=0;
    if(buffer3[0]==0x53){ 
       rollx=((buffer3[2]<<8)|buffer3[1])/32768.0*180;
       pitchy=((buffer3[4]<<8)|buffer3[3])/32768.0*180;
       yawz=((buffer3[6]<<8)|buffer3[5])/32768.0*180;
       temperature=((buffer3[8]<<8)|buffer3[7]) /100.0;
  } 
}
}

