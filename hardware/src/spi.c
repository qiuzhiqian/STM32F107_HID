#include "spi.h"

 
//��???��?SPI?��?����?3?��??���䨲??��?????3��?��?��?�꨺?��?��??��SD Card/W25Q64/NRF24L01						  
//SPI?��3?��??��
//?a��???��???SPI1��?3?��??��

//		SPI_Flash_Init();	     
//	SPI_Flash_Write((u8*)TEXT_Buffer,0,SIZE);//D??����?��oy?Y
// 	while(1)
//	{
//		SPI_Flash_Read(datatemp,0,SIZE);//?����3?��oy?Y
//		USART1_Send_String(datatemp);
//		dly_10ms(200);
//	}

void SPI3_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;

//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );//PORTA  SPI1  ����?����1?�� 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTA  SPI1  ����?����1?�� 
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE );//PORTA  SPI1  ����?����1?�� 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);  

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����??SPI�̣�?��?��?????����?��y?Y?�꨺?:SPI����???a???????����???1��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����??SPI1�����?�꨺?:����???a?��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����??SPI��?��y?Y�䨮D?:SPI����?��?����?8?????��11
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//��?DD��?2?����?����????D���䨬??a??��???
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//��?DD��?2?����?����?�̨�?t??��?��???�ꡧ��?��y?��???�̡�?��y?Y��?2��?��
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSSD?o?������2?t�ꡧNSS1��??��??1��?����?t�ꡧ��1��?SSI??��?1������:?��2?NSSD?o?��DSSI??????
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//?����?2����??��?�衤??�̦�??��:2����??��?�衤??��?��?a256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//???����y?Y��?��?�䨮MSB???1��?LSB???a��?:��y?Y��?��?�䨮MSB???a��?
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC?��????��??��??��?
	SPI_Init(SPI3, &SPI_InitStructure);  //?��?YSPI_InitStruct?D???����?2?��y3?��??����a����SPIx??��??��
 
	SPI_Cmd(SPI3, ENABLE); //��1?��SPI��a����
	
	SPI3_ReadWriteByte(0xff);//???����?��?		 

}   
//SPI ?��?������??o����y
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��??��   
//SPI_BaudRatePrescaler_8   8��??��   
//SPI_BaudRatePrescaler_16  16��??��  
//SPI_BaudRatePrescaler_256 256��??�� 
  
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI3->CR1&=0XFFC7;
	SPI3->CR1|=SPI_BaudRatePrescaler;	//����??SPI1?��?�� 
	SPI_Cmd(SPI3,ENABLE); 

} 

//SPIx ?��D�䨰???��??��
//TxData:��aD�䨨?��?��??��
//����???��:?����?��?��?��??��
u8 SPI3_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET) //?��2��???����?SPI����????����??��?��?:����?��?o��???����????
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI3, TxData); //����1y��a����SPIx����?����???��y?Y
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) //?��2��???����?SPI����????����??��?��?:?������?o��?��???����????
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI3); //����??����1ySPIx��??��?����?��?��y?Y					    
}
