/******************************************************

360�ȶ�����Ƴ��򣬾�ȷ���ƽǶ�

******************************************************/
#include "servo.h"

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
	static int i,j;
	for(j = 160 ; j < 220 ;)
	{
		servo_up_pos(j);
		if( (j/10)%2 == 0)
		{
			for(i = 40 ; i < 260 ; i++)
			{
				servo_down_pos(i);
				HAL_Delay(20);
			}
		}
		else
		{
			for(i = 260 ; i > 40 ; i--)
			{
				servo_down_pos(i);
				HAL_Delay(20);
			}
		}
		j += 10;
	}
	
}
