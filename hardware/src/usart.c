#include "usart.h"

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 0
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
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

	/********************����ΪUSART2����**************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
	/*
	*  USART1_TX -> PA9 , USART1_RX -> PA10
	*/	 
    //��ʼ��PA9��PA10	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);		   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bdrate;                                    //������115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                             //��У��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //���ͺͽ���ʹ��
	USART_Init(USART1, &USART_InitStructure);                                       //��ʼ������2
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                  //�����ж�ʹ��
	USART_Cmd(USART1, ENABLE);                                                      //ʹ��ʱ����2                     
	USART_ClearITPendingBit(USART1, USART_IT_TC);                                   //����ж�TCλ
	
	{
		NVIC_InitTypeDef   NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	         //����2�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//3;    //��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//1;	         //�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           	 //IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);                              //����ָ���Ĳ�����ʼ��VIC�Ĵ���
	}
	
	RS_485_RX_EN;
}

void USART1_IRQHandler(void)                	//����1�жϷ������
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
