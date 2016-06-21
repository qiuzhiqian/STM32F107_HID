#include "usart.h"

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 0
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
        USART_SendData(USART2,(uint8_t)ch);   
        return ch;
}
#endif 


void USART1_Init(u32 bdrate)
{ 
  
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 

	/********************以下为USART2配置**************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
	/*
	*  USART1_TX -> PA9 , USART1_RX -> PA10
	*/	 
    //初始化PA9和PA10	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);		   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bdrate;                                    //波特率115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                             //无校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //发送和接受使能
	USART_Init(USART1, &USART_InitStructure);                                       //初始化串口2
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                  //接收中断使能
	USART_Cmd(USART1, ENABLE);                                                      //使能时串口2                     
	USART_ClearITPendingBit(USART1, USART_IT_TC);                                   //清除中断TC位
	
	{
		NVIC_InitTypeDef   NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	         //串口2中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//3;    //抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//1;	         //子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           	 //IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);                              //根据指定的参数初始化VIC寄存器
	}
	
	RS_485_RX_EN;
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 ch;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{
		ch =USART_ReceiveData(USART1);
  }
} 

void USART1_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	RS_485_TX_EN;
	for(i = 0;i < length;i ++)
	{			
		USART1->DR = send_buff[i];
		while((USART1->SR&0X40)==0);	
	}	
	RS_485_RX_EN;
}

void USART1_Send_String(unsigned char *string)
{
	RS_485_TX_EN;
	while(*string!='\0')
	{
					USART1->DR=*string;
					while(!(USART1->SR&0x40));
					string++;
	}
	RS_485_RX_EN;
}
