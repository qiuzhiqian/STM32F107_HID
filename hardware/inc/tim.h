#ifndef __TIM_H
#define __TIM_H

#include "includes.h"
#include "usart.h"
#include "main.h"
#include "huawei4G_client_demo.h"
#include "led.h"

extern u16 delaycnt;

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_forCnt_Init(u16 arr,u16 psc);
	
#endif
