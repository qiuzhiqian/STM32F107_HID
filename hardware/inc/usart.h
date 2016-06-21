#ifndef  _USART2_H_
#define  _USART2_H_

#include "stdio.h"	
#include "stm32f10x.h"

#define USART1_RX_BUF_SIZE  			  1024  	//定义最大接收字节数 200
//#define EN_USART1_RX 			  1		    //使能（1）/禁止（0）串口1接收


void USART1_Init(u32 bdrate);
void USART1_Send_Data(unsigned char *send_buff,unsigned int length); //串口2发送数据函数
void USART1_Send_String(unsigned char *string);                      //串口2发送字符串



#define RS_485_RX_EN 	do{ GPIO_ResetBits(GPIOB , GPIO_Pin_14); GPIO_ResetBits(GPIOC , GPIO_Pin_7);}while(0)	//接收使能
#define RS_485_TX_EN 	do{ GPIO_SetBits(GPIOB , GPIO_Pin_14); GPIO_SetBits(GPIOC , GPIO_Pin_7);}while(0)	//发送使能



#endif
