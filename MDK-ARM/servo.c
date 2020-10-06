/******************************************************

360�ȶ�����Ƴ��򣬾�ȷ���ƽǶ�

******************************************************/
#include "servo.h"
#include "math.h"

int x_pos,y_pos;		

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
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,speed); 
}

void servo_down_pos(int speed)	//�·����λ��(40~260)
{
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,speed); 
}

void servo_scan(void)					//����Զ���������ɨ��
{
	for(y_pos = 160 ; y_pos < 220 ;)
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

void servo_adjust(int x_now,int y_now,float x_adj,float y_adj)
{
	if( fabs(x_adj)<1)	x_adj = 0;					//С��������
	if( fabs(y_adj)<1)	y_adj = 0;
	
	servo_down_pos(170+x_adj);
	
}