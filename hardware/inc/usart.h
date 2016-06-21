#ifndef  _USART2_H_
#define  _USART2_H_

#include "stdio.h"	
#include "stm32f10x.h"

#define USART1_RX_BUF_SIZE  			  1024  	//�����������ֽ��� 200
//#define EN_USART1_RX 			  1		    //ʹ�ܣ�1��/��ֹ��0������1����


void USART1_Init(u32 bdrate);
void USART1_Send_Data(unsigned char *send_buff,unsigned int length); //����2�������ݺ���
void USART1_Send_String(unsigned char *string);                      //����2�����ַ���



#define RS_485_RX_EN 	do{ GPIO_ResetBits(GPIOB , GPIO_Pin_14); GPIO_ResetBits(GPIOC , GPIO_Pin_7);}while(0)	//����ʹ��
#define RS_485_TX_EN 	do{ GPIO_SetBits(GPIOB , GPIO_Pin_14); GPIO_SetBits(GPIOC , GPIO_Pin_7);}while(0)	//����ʹ��



#endif
