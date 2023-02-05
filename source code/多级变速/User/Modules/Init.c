/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"
u8  First_LCD=1;
/*
 * ��������Init_LED
 * ����  ����ˮ��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
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
           lcd_string(0, 0, "    ����        "); //��һ�е�����ʼ����ʾ����"����"
           lcd_string(2, 0, "      ��ʼ��... "); //�����еڶ���ʼ����ʾ����"��ʼ��..."
           First_LCD=0;
         }
         return;
    case 1:
          switch(Mode)
          {
            case NORMAL:   lcd_string(0,0,"������ģʽ      ");
                           lcd_string(1,0,"  �������ģʽ  ");
                           lcd_string(2,0,"  ����ѭ��ģʽ  ");
                           lcd_string(3,0,"  �������ģʽ  ");
                           return;                                                   //ѡ����Ϊ����ģʽ
            case FOLLOW:   lcd_string(0,0,"  ����ģʽ      ");
                           lcd_string(1,0,"��������ģʽ  ");
                           lcd_string(2,0,"  ����ѭ��ģʽ  ");
                           lcd_string(3,0,"  �������ģʽ  ");
                           return;                                                   //ѡ����Ϊ�������ģʽ                                                  
            case TRACK:   lcd_string(0,0,"  ����ģʽ      ");
                           lcd_string(1,0,"  �������ģʽ  ");
                           lcd_string(2,0,"�����ѭ��ģʽ  ");
                           lcd_string(3,0,"  �������ģʽ  ");
                           return;                                                   //ѡ����Ϊ����ѭ��ģʽ
            case AVOID:    lcd_string(0,0,"  ����ģʽ      ");
                           lcd_string(1,0,"  �������ģʽ  ");
                           lcd_string(2,0,"  ����ѭ��ģʽ  ");
                           lcd_string(3,0,"��������ģʽ  ");
                           return;                                                   //ѡ����Ϊ�������ģʽ
            case WAVEAVOID:lcd_string(0,0,"  �������ģʽ  ");
                           lcd_string(1,0,"  ����ѭ��ģʽ  ");
                           lcd_string(2,0,"  �������ģʽ  ");
                           lcd_string(3,0,"����������ģʽ");
                           return;                                                   //ѡ����Ϊ����������ģʽ
            case RANG:     lcd_string(0,0,"  ����ѭ��ģʽ  ");
                           lcd_string(1,0,"  �������ģʽ  ");
                           lcd_string(2,0,"  ����������ģʽ");
                           lcd_string(3,0,"���������ģʽ");
                           return;                                                   //ѡ����Ϊ���������ģʽ
            case DHT11:    lcd_string(0,0,"  �������ģʽ  ");
                           lcd_string(1,0,"  ����������ģʽ");
                           lcd_string(2,0,"  ���������ģʽ");
                           lcd_string(3,0,"����ʪ��ģʽ    ");
                           return;                                                   //ѡ����Ϊ��ʪ����ʾģʽ
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
            case NORMAL:   lcd_string(1, 0, "    ����ģʽ    ");return;                 //����ģʽ
            case FOLLOW:   lcd_string(1, 0, "    ����ģʽ    ");return;                 //����ģʽ
            case TRACK:    lcd_string(1, 0, "    ѭ��ģʽ    ");return;                 //ѭ��ģʽ
            case AVOID:    lcd_string(1, 0, "  �������ģʽ  ");return;                 //�������ģʽ
            case WAVEAVOID:lcd_string(1, 0, "  ����������ģʽ");return;                 //����������ģʽ
            case RANG:     lcd_string(1, 0, "  ���������ģʽ");return;                 //���������ģʽ
            case DHT11:    lcd_string(1, 0, "  ��ʪ����ʾģʽ");return;                 //��ʪ����ʾ
          }
          return;
    default:return;
  }
}  


/*
 * ��������Init_Steer
 * ����  �������ʼ��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Init_Steer()
{
  u8 i,l,r;
  I2C_EEPROM_Init();
  I2C_EEPROM_BufferRead(Angle,0x00,8);//��eeprom��ȡ�Ƕ�ֵ
  if((Angle[0]==0xff)||(Angle[1]==0xff)||(Angle[2]==0xff)||(Angle[3]==0xff)||(Angle[4]==0xff)||(Angle[5]==0xff)||(Angle[6]==0xff)||(Angle[7]==0xff))//�����δ������Ƕ�
  {
    for(i=0;i<8;i++)
    {
      Angle[i]=0x3C;//����ֵ
    }
     I2C_EEPROM_BufferWrite(Angle,0x00,8);//����   
  }
    adjust=I2C_EEPROM_ReadByte(0x10);//�洢���У׼��־
    if(adjust==0xff)adjust=1;//��δ�������1
    l=I2C_EEPROM_ReadByte(0x09);//��eeprom��ȡ��൵λ��ֵ
    r=I2C_EEPROM_ReadByte(0x0a);//��eeprom��ȡ�Ҳ൵λ��ֵ
    if((l>100)||(r>100))//�жϵ�λ��ֵ�Ƿ����
    {
      l=100;
      r=100;
    }
    speed_left=l*8+200;//��λֵ������ٶ�ֵ
    speed_right=r*8+200;//��λֵ������ٶ�ֵ
    
}


