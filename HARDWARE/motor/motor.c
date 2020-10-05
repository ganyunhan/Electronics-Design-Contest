#include "motor.h"

void Motor_init(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
}

void Motor_Left_speed(int speed)			//左动力电机速度设置
{
//	if(speed >= 0)
//	{
//		HAL_GPIO_WritePin(Push_Motor_L_Direct_GPIO_Port, Push_Motor_L_Direct_Pin, GPIO_PIN_RESET);
//	}
//	else
//	{
//		speed = -speed;
//		HAL_GPIO_WritePin(Push_Motor_L_Direct_GPIO_Port, Push_Motor_L_Direct_Pin, GPIO_PIN_SET);
//	}
	if(speed >= 100)
				speed = 100;
	else if(speed <= -100)
		speed = -100;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,speed);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,speed);
//	printf("%d",speed);
}

void Motor_Right_speed(int speed)			//右动力电机速度设置
{
//	if(speed >=0)
//	{
//		HAL_GPIO_WritePin(Push_Motor_R_Direct_GPIO_Port, Push_Motor_R_Direct_Pin, GPIO_PIN_SET);
//	}
//	else
//	{
//		speed = -speed;
//		HAL_GPIO_WritePin(Push_Motor_R_Direct_GPIO_Port, Push_Motor_R_Direct_Pin, GPIO_PIN_RESET);
//	}
	if(speed >= 100)
				speed = 100;
	else if(speed <= -100)
		speed = -100;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,speed);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,speed); 
//	printf("%d",speed);
}

void Motor_set(int speed , int l_speed , int r_speed)
{
	Motor_Left_speed(speed + l_speed);
	Motor_Right_speed(speed + r_speed);
}

void Turn_Right(void)
{
	Motor_Left_speed(100);
	Motor_Right_speed(0);
}

void Turn_Left(void)
{
	Motor_Left_speed(0);
	Motor_Right_speed(100);
}

void Motor_Stop(void)
{
	Motor_Right_speed(0);
	Motor_Left_speed(0);
}

void Motor_Adjust(int speed , int adjust)			//传入基准前进速度和OpenMV的偏差pid，重新设定PWM
{
	int RightSpeed,LeftSpeed;
	RightSpeed = speed;
	LeftSpeed = speed;
	
	/*偏移调整量adjust限幅*/
	if(adjust >= 100 - speed) adjust = 100-speed;
	else if(adjust <= speed - 100) adjust = speed - 100;
	
	/*偏移调整量adjust输入定时器*/
	if(adjust >= 0)		//正值为即将向右走，即当前路径偏左
	{
		RightSpeed = LeftSpeed + adjust;
	}
	else if(adjust < 0)		//负值为即将向左走，即当前路径偏右
	{
		LeftSpeed = RightSpeed - adjust;
	}
	Motor_Right_speed(RightSpeed);
	Motor_Left_speed(LeftSpeed);
}
