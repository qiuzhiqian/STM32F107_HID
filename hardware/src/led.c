#include "led.h" 
		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_6;//LED 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��ת����50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //���������ʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure);             //��ʼ��PB8.9.14.15
}





