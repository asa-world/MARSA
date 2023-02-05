#ifndef __MOTOR_H
#define	__MOTOR_H


#define MOTOR_GO_FORWARD   MOTOR_A_CON1_HIGH;MOTOR_A_CON2_LOW;MOTOR_B_CON1_HIGH;MOTOR_B_CON2_LOW; //电机前进	                            
#define MOTOR_GO_BACK	   MOTOR_A_CON1_LOW;MOTOR_A_CON2_HIGH;MOTOR_B_CON1_LOW;MOTOR_B_CON2_HIGH; //电机后退
#define MOTOR_GO_RIGHT	   MOTOR_A_CON1_LOW;MOTOR_A_CON2_HIGH;MOTOR_B_CON1_HIGH;MOTOR_B_CON2_LOW; //电机左转
#define MOTOR_GO_LEFT	   MOTOR_A_CON1_HIGH;MOTOR_A_CON2_LOW;MOTOR_B_CON1_LOW;MOTOR_B_CON2_HIGH; //电机右转
#define MOTOR_GO_STOP	   MOTOR_A_CON1_LOW;MOTOR_A_CON2_LOW;MOTOR_B_CON1_LOW;MOTOR_B_CON2_LOW;   //电机停止 


void Avoiding(void);
void TrackLine(void);
void AvoidByRadar(int distance);
void Follow(void);
void forward(int adjust);
void back(int adjust);
void left(int adjust);
void right(int adjust);
void Route();


extern unsigned long ifstop;
#endif /* __MOTOR_H */