/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"
int Communication_Decode_flag=0;
int Communication_Decode_flag3=0;
float rollx;
float pitchy=0;
float yawz;
float temperature;



/*
 * ��������Communication_Decode
 * ����  �������������ݹ��ܺ���
 * ����  ����
 * ���  ����
 * ����  ����Interrupt.c�����ж�1�����е���
 */

 void Communication_Decode(void)  
{
  if(Communication_Decode_flag)
  {
    Communication_Decode_flag=0;
    if(buffer[0]==0x00)//�ֶ�����
    {
         GPIOB->ODR ^= GPIO_Pin_5;                     //���ָʾ�Ʒ�ת
         switch(buffer[1])
          {
            case 0x00:MOTOR_GO_STOP;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;           //ֹͣ
            case 0x01:MOTOR_GO_FORWARD;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;        //ǰ��
            case 0x02:MOTOR_GO_BACK;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;           //����
            case 0x03:MOTOR_GO_LEFT;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;           //��ת
            case 0x04:MOTOR_GO_RIGHT;Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);return;          //��ת
            
            case 0x05:MOTOR_GO_FORWARD;Set_Left_Speed(speed_left); Set_Right_Speed(20);return;          //��ǰ
            case 0x06:MOTOR_GO_FORWARD;Set_Left_Speed(20); Set_Right_Speed(speed_right);return;          //��ǰ
            case 0x07:MOTOR_GO_BACK;Set_Left_Speed(speed_left); Set_Right_Speed(20);return;          //���
            case 0x08:MOTOR_GO_BACK;Set_Left_Speed(20); Set_Right_Speed(speed_right);return;          //�Һ�
            
            default:return;                          //ֹͣ
          }
    }
    
   else if(buffer[0]==0x01)//�������
    {      
        GPIOD->ODR ^= GPIO_Pin_2;                      //���ָʾ�Ʒ�ת
        switch(buffer[1])
        {
            case 0x01:Angle[0]=(buffer[2]); return;   //���1��
            case 0x02:Angle[1]=(buffer[2]); return;   //���2��
            case 0x03:Angle[2]=(buffer[2]); return;   //���3��
            case 0x04:Angle[3]=(buffer[2]); return;   //���4��
            case 0x05:Angle[4]=(buffer[2]); return;   //���5��  
            case 0x06:Angle[5]=(buffer[2]); return;   //���6��  
            case 0x07:Angle[6]=(buffer[2]); return;   //���7��
            case 0x08:Angle[7]=(buffer[2]); return;   //���8��
            default : return;
        }  
            
    }
    else if(buffer[0]==0x02)
    {
        if(buffer[2]>100)return;     
        if(buffer[1]==0x01)//����01��ʾ������
        {
            speed_left=(buffer[2]*8+200);//buffer[2]Ϊ��λֵ��С0���100
            //����λֵ��������ٶ�
            Set_Left_Speed(speed_left);//����ٶ�
            //I2C_EEPROM_WriteByte(buffer[2],0x09);//���Ҳ൵λ�洢��EEPROM
        }
        if(buffer[1]==0x02)//����02��ʾ�Ҳ����
        {
            speed_right=(buffer[2]*8+200);//buffer[2]Ϊ��λֵ��С0���100
            //����λֵ�����Ҳ��ٶ�
            Set_Right_Speed(speed_right);//�ұ��ٶ�
            //I2C_EEPROM_WriteByte(buffer[2],0x0a);//���Ҳ൵λ�洢��EEPROM
        }
    }
    
    else if(buffer[0]==0x32)//�洢�Ƕ�
    {
        I2C_EEPROM_BufferWrite(Angle,0x00,8);//�ѽǶȴ洢��EEPROM
    }
    
    
    else if(buffer[0]==0x33)//�Ƕȹ�λ
    {
        Init_Steer();
    }
    
    
    else if(buffer[0]==0x40)//���У׼��־��У׼����ģʽ�ĵ��ת����
    {
        adjust=buffer[1];
        I2C_EEPROM_WriteByte(adjust,0x10);//�洢��־	
    }
    
    
    else if(buffer[0]==0x13)//����ģʽ�л�����
    {
         
        switch(buffer[1])
            {
              case 0x01: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 1;Level = 2;Mode = 1;Refresh = 1; return;//�������
              case 0x02: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 2;Level = 2;Mode = 2;Refresh = 1; return;//����Ѳ��
              case 0x03: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 3;Level = 2;Mode = 3;Refresh = 1; return;//�������
              case 0x04: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 4;Level = 2;Mode = 4;Refresh = 1; return;//�������״����
              case 0x05: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 5;Level = 2;Mode = 5;Refresh = 1; return;//������������ʾ
              case 0x06: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 6;Level = 2;Mode = 6;Refresh = 1; return;//��ʪ����ʾ
              case 0x07: if(Cruising_Flag !=7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 7;                                return;//·���滮  
              case 0x00: if(Cruising_Flag ==7){Set_Left_Speed(speed_left); Set_Right_Speed(speed_right);}Cruising_Flag = 0;Level = 2;Mode = 0;Refresh = 1; return;//����ģʽ
              default: return;//����ģʽ
            }
    }
    else if(buffer[0]==0xA0)//�յ���ת
      {
         RevStatus = 2;
         TurnAngle=buffer[1];
         Golength=buffer[2];
      }
      else if(buffer[0]==0xA1)//�յ���ת
      {
         RevStatus = 1;
         TurnAngle=buffer[1];
         Golength=buffer[2];
      }   
    else if(buffer[0]==0x04)//FF040000FF����  FF040100FF�ص�
    {
      switch(buffer[1])
      {
        case 0x00:Open_Light;return;//����
        case 0x01:Closs_Light;return;//�ص�
        default:Closs_Light;return;
      }
    }
 
  }
    
}


/*
 * ��������Cruising
 * ����  ��ģʽ�л�����
 * ����  ����
 * ���  ����
 * ����  ��main�����е���
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
	   case 0x01:Follow();            break;//�������ģʽ
	   case 0x02:TrackLine();         break;//����Ѳ��ģʽ
	   case 0x03:Avoiding();          break;//�������ģʽ
	   case 0x04:AvoidByRadar(15);    break;//����������ģʽ
           case 0x05:Send_Distance();     break;//������������ʾģʽ (�˹�����Ҫ��ͨWIFIģ������˫���ܣ��̳̲ο��� http://www.wifi-robots.com/thread-2985-1-1.html)
           case 0x06:Display_Dht11();     break;//��ʪ����ʾģʽ (�˹�����Ҫ��ͨWIFIģ������˫���ܣ��̳̲ο��� http://www.wifi-robots.com/thread-2985-1-1.html)
	   case 0x07:Route();             break;//·���滮
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

