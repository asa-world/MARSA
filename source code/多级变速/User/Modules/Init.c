/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"
u8  First_LCD=1;
/*
 * 函数名：Init_LED
 * 描述  ：流水灯
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Init_LED()
{
  for(int i=0;i<45;i++)
  {
    GPIOB->ODR ^= GPIO_Pin_5;
    Delay_ms(500);
    GPIOD->ODR ^= GPIO_Pin_2;
    Delay_ms(500);
  }
  for(int i=0;i<45;i++)
  {
    GPIOB->ODR ^= GPIO_Pin_5;
    Delay_ms(250);
    GPIOD->ODR ^= GPIO_Pin_2;
    Delay_ms(250);
  }
  LED1_Low;
  LED2_Low;
}

void MENU(int Level,int Mode)
{
  switch(Level)
  {
    case 0:
         if((!Mode)&&(First_LCD))
         {
           lcd_string(0, 0, "    开机        "); //第一行第三格开始，显示文字"开机"
           lcd_string(2, 0, "      初始化... "); //第三行第二格开始，显示文字"初始化..."
           First_LCD=0;
         }
         return;
    case 1:
          switch(Mode)
          {
            case NORMAL:   lcd_string(0,0,"●正常模式      ");
                           lcd_string(1,0,"  红外跟随模式  ");
                           lcd_string(2,0,"  红外循迹模式  ");
                           lcd_string(3,0,"  红外壁障模式  ");
                           return;                                                   //选择项为正常模式
            case FOLLOW:   lcd_string(0,0,"  正常模式      ");
                           lcd_string(1,0,"●红外跟随模式  ");
                           lcd_string(2,0,"  红外循迹模式  ");
                           lcd_string(3,0,"  红外壁障模式  ");
                           return;                                                   //选择项为红外跟随模式                                                  
            case TRACK:   lcd_string(0,0,"  正常模式      ");
                           lcd_string(1,0,"  红外跟随模式  ");
                           lcd_string(2,0,"●红外循迹模式  ");
                           lcd_string(3,0,"  红外壁障模式  ");
                           return;                                                   //选择项为红外循迹模式
            case AVOID:    lcd_string(0,0,"  正常模式      ");
                           lcd_string(1,0,"  红外跟随模式  ");
                           lcd_string(2,0,"  红外循迹模式  ");
                           lcd_string(3,0,"●红外壁障模式  ");
                           return;                                                   //选择项为红外壁障模式
            case WAVEAVOID:lcd_string(0,0,"  红外跟随模式  ");
                           lcd_string(1,0,"  红外循迹模式  ");
                           lcd_string(2,0,"  红外壁障模式  ");
                           lcd_string(3,0,"●超声波壁障模式");
                           return;                                                   //选择项为超声波壁障模式
            case RANG:     lcd_string(0,0,"  红外循迹模式  ");
                           lcd_string(1,0,"  红外壁障模式  ");
                           lcd_string(2,0,"  超声波壁障模式");
                           lcd_string(3,0,"●超声波测距模式");
                           return;                                                   //选择项为超声波测距模式
            case DHT11:    lcd_string(0,0,"  红外壁障模式  ");
                           lcd_string(1,0,"  超声波壁障模式");
                           lcd_string(2,0,"  超声波测距模式");
                           lcd_string(3,0,"●温湿度模式    ");
                           return;                                                   //选择项为温湿度显示模式
          }
          return;
    case 2:
           if(Refresh)
          {
            Refresh = 0;
            lcd_clear();   
          }
          switch(Mode)
          {
            case NORMAL:   lcd_string(1, 0, "    正常模式    ");return;                 //正常模式
            case FOLLOW:   lcd_string(1, 0, "    跟随模式    ");return;                 //跟随模式
            case TRACK:    lcd_string(1, 0, "    循迹模式    ");return;                 //循迹模式
            case AVOID:    lcd_string(1, 0, "  红外壁障模式  ");return;                 //红外避障模式
            case WAVEAVOID:lcd_string(1, 0, "  超声波壁障模式");return;                 //超声波避障模式
            case RANG:     lcd_string(1, 0, "  超声波测距模式");return;                 //超声波测距模式
            case DHT11:    lcd_string(1, 0, "  温湿度显示模式");return;                 //温湿度显示
          }
          return;
    default:return;
  }
}  


/*
 * 函数名：Init_Steer
 * 描述  ：舵机初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Init_Steer()
{
  u8 i,l,r;
  I2C_EEPROM_Init();
  I2C_EEPROM_BufferRead(Angle,0x00,8);//从eeprom读取角度值
  if((Angle[0]==0xff)||(Angle[1]==0xff)||(Angle[2]==0xff)||(Angle[3]==0xff)||(Angle[4]==0xff)||(Angle[5]==0xff)||(Angle[6]==0xff)||(Angle[7]==0xff))//如果从未保存过角度
  {
    for(i=0;i<8;i++)
    {
      Angle[i]=0x3C;//赋初值
    }
     I2C_EEPROM_BufferWrite(Angle,0x00,8);//保存   
  }
    adjust=I2C_EEPROM_ReadByte(0x10);//存储电机校准标志
    if(adjust==0xff)adjust=1;//从未保存过则赋1
    l=I2C_EEPROM_ReadByte(0x09);//从eeprom读取左侧档位数值
    r=I2C_EEPROM_ReadByte(0x0a);//从eeprom读取右侧档位数值
    if((l>100)||(r>100))//判断档位数值是否合理
    {
      l=100;
      r=100;
    }
    speed_left=l*8+200;//档位值换算成速度值
    speed_right=r*8+200;//档位值换算成速度值
    
}


