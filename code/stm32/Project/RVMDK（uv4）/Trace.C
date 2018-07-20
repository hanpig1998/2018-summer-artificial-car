#include "motor_1.h"
#include "Trace.h"
#include "stm32f10x.h"
#include "pwm.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_dht11.h"


void left_sensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOA,&GPIO_InitStructure);
}	

void right_sensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void self_tracing(int a)
{
	int flag=0;
	left_sensor_Init();
	right_sensor_Init();
	straight();
	Motor_1_PRun(a);
	while(1)
	{
		if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)&&(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)))
		{
			right_45();	
			Delay_ms(10);
		}
		else if (!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)&&(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)))
		{
			left_45();
			Delay_ms(10);
		}
		else if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)&&(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)))
		{
			straight();
		}
		else
		{
			Delay_ms(250);
			flag++;
			if (flag==30)
			{
				straight();
				Motor_1_STOP();
				break;
			}
			//straight();
			//Motor_1_STOP();
			//break;
		}
	}
}
			

 
