/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"

unsigned long ifstop;  //��һ��ʱ��û�м�⵽���ߺ������ֹͣ


/*
 * ��������forward
 * ����  ��У׼���ǰ������
 * ����  ��adjust
 * ���  ����
 * ����  �����ܺ����е���
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
 * ��������back
 * ����  ��У׼��ĺ��˷���
 * ����  ��adjust
 * ���  ����
 * ����  �����ܺ����е���
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
 * ��������left
 * ����  ��У׼�����ת����
 * ����  ��adjust
 * ���  ����
 * ����  �����ܺ����е���
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
 * ��������right
 * ����  ��У׼�����ת����
 * ����  ��adjust
 * ���  ����
 * ����  �����ܺ����е���
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
 * ��������Avoiding
 * ����  ���������ģʽ
 * ����  ����
 * ���  ����
 * ����  ��function�е���
 */
void Avoiding(void)
{
  if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)//����м���ⱻ��ס
  {
    MOTOR_GO_STOP;return;//ֹͣ
  }
}

/*
 * ��������TrackLine
 * ����  ������ѭ��ģʽ
 * ����  ����
 * ���  ����
 * ����  ��function�е���
 */
void TrackLine()//ѭ��,��û�м�⵽���ߵ�һ��ʱ�����Զ�ֹͣ(��ֹ����)
{   


    if((TR_L==0)&&(TR_R==0))//����ͬʱ��û��̽�⵽����
    {    
         ifstop++;
         MOTOR_GO_FORWARD;

         return;
     } 
                       
    if((TR_L == 1)&&(TR_R== 0))//�Ҳ��⵽����
      {
        ifstop=0;
        MOTOR_GO_RIGHT;
        return;
      }
              
    if((TR_L == 0)&&(TR_R == 1))//����⵽���� 
      {
       ifstop=0;
       MOTOR_GO_LEFT;
        return;
      }
                       
    if((TR_L == 1)&&(TR_R == 1))//���Ҷ���⵽���ߣ�������Ƶ�е���������һ����Ľ��� 
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
 * ��������AvoidByRadar
 * ����  ������������ģʽ
 * ����  ��distance
 * ���  ����
 * ����  ��function�е���
 */
void AvoidByRadar(int distance)
{
    result = Get_distance();              //��ó�������þ���
    if(distance*10<100)distance = 10;         //�޶���С���Ͼ���Ϊ10cm
    if((result>10)&&(result < distance*10))   //���Ͼ���ֵ(��λcm)������1��Ϊ�˱��ⳬ������ä��
    {
       while((Get_distance()>10)&&(Get_distance() < distance*10))
       {
          back(adjust);
        }
        MOTOR_GO_STOP;
    }   
}



/*
 * ��������Follow
 * ����  ���������ģʽ
 * ����  ����
 * ���  ����
 * ����  ��function�е���
 */
void Follow(void)
{
      if(IR== 1)	//�м䴫����OK
      {
      
            if((FR_L == 0)&& (FR_R == 0)) //����ͬʱ̽�⵽�ϰ���
            {
            
                MOTOR_GO_STOP//ֹͣ
            } 
             
            if((FR_L == 0)&& (FR_R == 1))//����ϰ���
            {
            
                left(adjust);//��ת
            }
    
            if((FR_L == 1)&& (FR_R == 0))//�Ҳ��ϰ���
            {
                right(adjust);//��ת
            }
             
            if((FR_L == 1)&& (FR_R == 1))//���κ��ϰ���
            {
                forward(adjust);//ǰ��
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
      GPIOB->ODR ^= GPIO_Pin_5;                     //���ָʾ�Ʒ�ת
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
      GPIOB->ODR ^= GPIO_Pin_5;                     //���ָʾ�Ʒ�ת
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

