#ifndef __MOTOR1_H
#define __MOTOR1_H
 
 
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
 
void TIM4_PWM_INIT(u16 arr,u16 psc);
void TIM5_PWM_INIT(u16 arr,u16 psc);

 
void Motor_1_STOP(void);
void Motor_1_PRun(int a);
void Motor_1_NRun(int b);


#endif
