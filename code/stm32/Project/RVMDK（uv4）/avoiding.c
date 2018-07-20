#include "stm32f10x.h"
#include "avoiding.h" 
#include "stm32f10x.h"
#include "motor_1.h"  
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_dht11.h"
#include "pwm.h"
void avoid_forwardtrig_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
}	
void avoid_forwardout_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}	
//C1trig,C3receive;  
void avoid_lefttrig_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}	
void avoid_leftout_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
}	
void avoid_righttrig_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_14);
}	
void avoid_rightout_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_15);
}	

int avoiding_forward(void)
{
	int i=0;
	avoid_forwardtrig_Init();
	avoid_forwardout_Init();
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	Delay_us(20);
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3));
	for(i=0;i<=300;i++)
	{
		if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))
		{
					return 1;
		}
	}
	printf("no collison\n");
	return 0;
}
int avoiding_left(void)
{
	int i=0;
	avoid_lefttrig_Init();
	avoid_leftout_Init();
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	Delay_us(20);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2));
	for(i=0;i<=800;i++)
	{
		if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2))
		{
					return 1;
		}
	}
	return 0;
}
int avoiding_right(void)
{
	int i=0;
	avoid_righttrig_Init();
	avoid_rightout_Init();
	GPIO_SetBits(GPIOC,GPIO_Pin_14);
	Delay_us(20);
	GPIO_ResetBits(GPIOC,GPIO_Pin_14);
	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15));
	for(i=0;i<=800;i++)
	{
		if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15))
		{
					return 1;
		}
	}
	return 0;
}

void avoiding(int a)
{
	int i=0;
	Motor_1_PRun(a);
	straight();
	while(1)
	{
		straight();
		Motor_1_PRun(a);
		if (avoiding_forward())
		{
			if (!avoiding_left())
			{
				i=0;
				Motor_1_NRun(a);
				Delay_ms(3000);
				Motor_1_PRun(a);
				left_45();
				while (i<=4)
				{
					i++;
					if (avoiding_left())
					{
						straight();
						Motor_1_NRun(a);
						Delay_ms(1000);
						break;
					}
					else
					{
						Delay_ms(500);
					}
				}
			}
			else
			{
				if (!avoiding_right())
				{
					i=0;
					Motor_1_NRun(a);
					Delay_ms(3000);
					Motor_1_PRun(a);
					right_45();
					while (i<=4)
					{
						i++;
						if (avoiding_right())
						{
							straight();
							Motor_1_NRun(a);
							Delay_ms(1000);
							break;
						}
						else
						{
							Delay_ms(500);
						}
					}
				}
				else
				{
					Motor_1_NRun(a);
					Delay_ms(3000);
					Motor_1_STOP();
					printf("pighan idiot \n");
					break;
				}
			}
		}
	}
}

/*int following_forward(void)
{
	int i=0;
	avoid_forwardtrig_Init();
	avoid_forwardout_Init();
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	Delay_us(20);
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3));
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))
	{
		i++;
	}
	return i;
}*/

	
