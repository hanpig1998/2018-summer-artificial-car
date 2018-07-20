#ifndef __avoiding_H
#define __avoiding_H
 
 
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void avoid_forwardtrig_Init(void);
void avoid_forwardout_Init(void);
void avoid_lefttrig_Init(void);
void avoid_leftout_Init(void);
void avoid_righttrig_Init(void);
void avoid_rightout_Init(void);
int avoiding_forward(void);
int avoiding_left(void);
int avoiding_right(void);
void avoiding(int a);
//void following(void);


#endif
