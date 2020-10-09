/******************************************************

360�ȶ�����Ƴ��򣬾�ȷ���ƽǶ�

******************************************************/
#include "servo.h"
#include "math.h"
#include "control.h"

extern int x_pos,y_pos;
extern int scan_flag,servo_flag;
extern float deviationx,deviationy;

void servo_init(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	servo_up_reset();
	servo_down_reset();
}

void servo_up_reset(void)		//�Ϸ��������
{
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,200); 
}

void servo_down_reset(void)	//�·��������
{
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,170); 
}

void servo_up_pos(int speed)		//�Ϸ����λ��(140~220)
{
	if(speed<=140)	speed = 140;			//�޷�
	if(speed>=200)	speed = 200;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,speed); 
}

void servo_down_pos(int speed)	//�·����λ��(40~260)
{
	if(speed<=40)	speed = 40;			//�޷�
	if(speed>=260)	speed = 260;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,speed); 
}

void servo_scan(void)					//����Զ���������ɨ��
{
	if(scan_flag == 1)
	{
		for(y_pos = 160 ; y_pos < 200 ;)
		{
			servo_up_pos(y_pos);
			if( (y_pos/10)%2 == 0)
			{
				for(x_pos = 40 ; x_pos < 260 ; x_pos++)
				{
					servo_down_pos(x_pos);
					HAL_Delay(20);
				}
			}
			else
			{
				for(x_pos = 260 ; x_pos > 40 ; x_pos--)
				{
					servo_down_pos(x_pos);
					HAL_Delay(20);
				}
			}
			y_pos += 10;
		}
	}
}

void servo_adjust(float x_adj,float y_adj)
{
	extern float servo_x,servo_y;
	if( fabs(x_adj)<0.5)	x_adj = 0;					//С��������
	if( fabs(y_adj)<0.5)	y_adj = 0;
	servo_x += x_adj;
	servo_y += y_adj;
	servo_down_pos(servo_x);
	servo_up_pos(servo_y);
	printf("x:%.2f  y:%.2f   %.2f   %.2f\n",servo_x,servo_y,x_adj,y_adj);
}
