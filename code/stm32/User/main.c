/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   dht11��ʪ�ȴ���������ʵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
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
  * @brief  ������
  * @param  ��  
  * @retval ��
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
		//printf("\r\n ʪ��:%d,�¶�:%d \r\n" ,DHT11_Data.humi_int,DHT11_Data.temp_int);
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
