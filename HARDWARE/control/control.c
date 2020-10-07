#include "control.h"
#include "motor.h"

extern void Turn_Right(void);
extern void Turn_Left(void);

float Position_KP=0.5,Position_KI=0,Position_KD=0;  			//X����PID����
float Position_Kp=-1.5,Position_Ki=-0.18,Position_Kd=0;  	//Y����PID����

void Control_Loop(void)                   
{
	extern int  speed_set , recive_flag ;
	extern float deviationx;
//	int adjust;
	Track();
//	Motor_set(speed_set , 30 , 0);
//	recive_flag = 0;
//	adjust = Position_PID_X (deviationx, 0);
//	printf("%d",adjust);
//	Motor_Adjust(speed_set,adjust);
}

void Track(void)		//ѭ��
{
	extern uint16_t scanresult;
	extern int  speed_set;
	scanresult = ScanLine();
//	printf("%d",scanresult);
	switch (scanresult)
	{
		case 1:Motor_set(speed_set , 0 , 0);break;
		case 2:Motor_set(speed_set , -10 , 10);break;
		case 3:Motor_set(speed_set , 10 , -10);break;
		case 4:Motor_set(speed_set , -15 , 20);break;
		case 5:Motor_set(speed_set , -20 , 30);break;
		case 6:Motor_set(speed_set , 20 , -15);break;
		case 7:Motor_set(speed_set , 30 , -20);break;
		case 8:Motor_set(0 , 0 , 0);break;
		default:Motor_set(0 , 0 , 0);break;
	}
}

int Position_PID_X (float value, float Target)
{
    static float Bias, Pwm, Integral_bias, Last_Bias;
    Bias = value - Target;                                //����ƫ��
    Integral_bias += Bias;	                             //���ƫ��Ļ���
    Pwm = Position_KP * Bias +                            //PID������������
          Position_KI * Integral_bias +                     //PID������������
          Position_KD * (Bias - Last_Bias);                 //PID������΢����
    Last_Bias = Bias;                                     //������һ��ƫ��
    return Pwm;                                           //�������
}

int Position_PID_Y (float value, float Target)
{
    static float Bias, Pwm, Integral_bias, Last_Bias;
    Bias = value - Target;                                //����ƫ��
    Integral_bias += Bias;	                             //���ƫ��Ļ���
    Pwm = Position_Kp * Bias +                            //PID������������
          Position_Ki * Integral_bias +                     //PID������������
          Position_Kd * (Bias - Last_Bias);                 //PID������΢����
    Last_Bias = Bias;                                     //������һ��ƫ��
    return Pwm;                                           //�������
}
