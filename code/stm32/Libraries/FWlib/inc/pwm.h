#ifndef __PWM_H
#define __PWM_H
 
 
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
 
//#define High    1
//#define Low     0
 
 
void TIM3_PWM_INIT(u16 arr,u16 psc);
 
void left_90(void);
void left_45(void);
void straight(void);
void right_45(void);
void right_90(void);

 

#endif
