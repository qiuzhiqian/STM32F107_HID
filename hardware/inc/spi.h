#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
				  	    													  
void SPI3_Init(void);			 //��ʼ��SPI��
void SPI3_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI3_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif

