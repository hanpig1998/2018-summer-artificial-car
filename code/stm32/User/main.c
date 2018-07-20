/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   dht11温湿度传感器测试实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_dht11.h"
#include "bsp_usart1.h"
#include "motor_1.h"
#include "pwm.h"
#include "Trace.h"
#include "avoiding.h"
#include "stranger.h"


DHT11_Data_TypeDef DHT11_Data;

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	char command[20];
	int a=1;
	SysTick_Init();

	USART1_Config();

	DHT11_GPIO_Config();
	while(1)
	{
	printf("please command the car:\n");
  scanf("%s",command);
	if (command[0]=='F')
	{
		printf("%s",command);
		straight();
		Motor_1_PRun(a);	
	}
	else if (command[0]=='R')
	{
		printf("%s",command);
		right_45();
	}
	else if (command[0]=='L')
	{
		printf("%s",command);
		left_45();
	}
	else if (command[0]=='S')
	{
		Motor_1_STOP();
	}
	else if (command[0]=='B')
	{
		straight();
		Motor_1_NRun(a);
	}
	else if (command[0]=='D')
	{
		if( Read_DHT11(&DHT11_Data)==SUCCESS)
		{
		printf("\r\nhumidity%d.%d RH temperature %d.%d C\r\n",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		//printf("\r\n 湿度:%d,温度:%d \r\n" ,DHT11_Data.humi_int,DHT11_Data.temp_int);
		}
		else
		{
		printf("\r\n");
		}
	}
	else if (command[0]=='A')
	{
		avoiding(a);
	}
	else if (command[0]=='T')
	{
		self_tracing(a);
	}
	else if (command[0]=='C')
	{
		printf("choose your speed:\n");
		scanf("%d",&a);
	}
	else if (command[0]=='Z')
	{
		stranger();
	}
}

}
