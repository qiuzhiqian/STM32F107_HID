#include "delay.h"
#include "tim.h"

void delay_ms(u16 nms)		//��ȷ��ʱ
{
	delaycnt=nms;
	while(delaycnt);
}
