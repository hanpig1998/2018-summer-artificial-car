#include "motor_1.h"  
#include "stm32f10x.h"
 
void TIM4_PWM_INIT(u16 arr,u16 psc)  
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);
}
void TIM5_PWM_INIT(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM5, ENABLE);
}

 
void Motor_1_STOP(void)
{
	TIM4_PWM_INIT(9999,147);
	TIM_SetCompare2(TIM4,0);
	TIM5_PWM_INIT(9999,147);
	TIM_SetCompare2(TIM5,0);
}
 
 
void Motor_1_PRun(int a)
{
	TIM4_PWM_INIT(9999,147);
	if (a==1)
	{
		TIM_SetCompare2(TIM4,699);
	}
	else if (a==2)
	{
		TIM_SetCompare2(TIM4,1299);
	}
	else if (a==3)
	{
		TIM_SetCompare2(TIM4,1999);
	}
	TIM5_PWM_INIT(9999,147);
	TIM_SetCompare2(TIM5,0);
}

void Motor_1_NRun(int b)
{
	TIM4_PWM_INIT(9999,147);
	TIM_SetCompare2(TIM4,0);
	TIM5_PWM_INIT(9999,147);
	if (b==1)
	{
		TIM_SetCompare2(TIM5,699);
	}
	else if (b==2)
	{
		TIM_SetCompare2(TIM5,1599);
	}
	else if (b==3)
	{
		TIM_SetCompare2(TIM5,2499);
	}
}
 


