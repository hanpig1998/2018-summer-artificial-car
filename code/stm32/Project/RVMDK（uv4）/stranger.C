#include "stranger.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
void stranger_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
      
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void stranger(void)
{
	int i=0;
	while(1)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11))
		{
			i++;
			printf("strangers coming!\n");
			if (i>=30)
			{
				break;
			}
			Delay_ms(5000);
		}
		else
		{
			printf("no stranger\n");
			Delay_ms(5000);
		}
	}
}