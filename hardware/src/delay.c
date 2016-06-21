#include "delay.h"
#include "tim.h"

void delay_ms(u16 nms)		//¾«È·ÑÓÊ±
{
	delaycnt=nms;
	while(delaycnt);
}
