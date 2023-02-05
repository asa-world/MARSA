#ifndef __MOTOR_H
#define	__MOTOR_H


#define MOTOR_GO_FORWARD   MOTOR_A_CON1_HIGH;MOTOR_A_CON2_LOW;MOTOR_B_CON1_HIGH;MOTOR_B_CON2_LOW; //���ǰ��	                            
#define MOTOR_GO_BACK	   MOTOR_A_CON1_LOW;MOTOR_A_CON2_HIGH;MOTOR_B_CON1_LOW;MOTOR_B_CON2_HIGH; //�������
#define MOTOR_GO_RIGHT	   MOTOR_A_CON1_LOW;MOTOR_A_CON2_HIGH;MOTOR_B_CON1_HIGH;MOTOR_B_CON2_LOW; //�����ת
#define MOTOR_GO_LEFT	   MOTOR_A_CON1_HIGH;MOTOR_A_CON2_LOW;MOTOR_B_CON1_LOW;MOTOR_B_CON2_HIGH; //�����ת
#define MOTOR_GO_STOP	   MOTOR_A_CON1_LOW;MOTOR_A_CON2_LOW;MOTOR_B_CON1_LOW;MOTOR_B_CON2_LOW;   //���ֹͣ 


void Avoiding(void);
void TrackLine(void);
void AvoidByRadar(int distance);
void Follow(void);
void forward(int adjust,int speed);
void back(int adjust);
void left(int adjust,int speed);
void right(int adjust,int speed);
void Route();

#endif /* __MOTOR_H */