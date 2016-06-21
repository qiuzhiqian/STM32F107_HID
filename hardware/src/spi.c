#include "spi.h"

 
//¨°???¨º?SPI?¡ê?¨¦¦Ì?3?¨º??¡¥¡ä¨²??¡ê?????3¨¦?¡Â?¨²?¡ê¨º?¡ê?¡¤??¨ºSD Card/W25Q64/NRF24L01						  
//SPI?¨²3?¨º??¡¥
//?a¨¤???¨º???SPI1¦Ì?3?¨º??¡¥

//		SPI_Flash_Init();	     
//	SPI_Flash_Write((u8*)TEXT_Buffer,0,SIZE);//D??¡§¡§?¡§oy?Y
// 	while(1)
//	{
//		SPI_Flash_Read(datatemp,0,SIZE);//?¡§¡é3?¡§oy?Y
//		USART1_Send_String(datatemp);
//		dly_10ms(200);
//	}

void SPI3_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;

//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );//PORTA  SPI1  ¨º¡À?¨®¨º1?¨¹ 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTA  SPI1  ¨º¡À?¨®¨º1?¨¹ 
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE );//PORTA  SPI1  ¨º¡À?¨®¨º1?¨¹ 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);  

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //¨¦¨¨??SPI¦Ì£¤?¨°?¨°?????¨°¦Ì?¨ºy?Y?¡ê¨º?:SPI¨¦¨¨???a???????¨°¨¨???1¡è
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//¨¦¨¨??SPI1¡è¡Á¡Â?¡ê¨º?:¨¦¨¨???a?¡ÂSPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//¨¦¨¨??SPI¦Ì?¨ºy?Y¡ä¨®D?:SPI¡¤¡é?¨ª?¨®¨º?8?????¨¢11
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//¡ä?DD¨ª?2?¨º¡À?¨®¦Ì????D¡Á¡ä¨¬??a??¦Ì???
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//¡ä?DD¨ª?2?¨º¡À?¨®¦Ì?¦Ì¨²?t??¨¬?¡À???¡ê¡§¨¦?¨¦y?¨°???¦Ì¡ê?¨ºy?Y¡À?2¨¦?¨´
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSSD?o?¨®¨¦¨®2?t¡ê¡§NSS1¨¹??¡ê??1¨º?¨¨¨ª?t¡ê¡§¨º1¨®?SSI??¡ê?1¨¹¨¤¨ª:?¨²2?NSSD?o?¨®DSSI??????
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//?¡§¨°?2¡§¨¬??¨º?¡è¡¤??¦Ì¦Ì??¦Ì:2¡§¨¬??¨º?¡è¡¤??¦Ì?¦Ì?a256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//???¡§¨ºy?Y¡ä?¨º?¡ä¨®MSB???1¨º?LSB???a¨º?:¨ºy?Y¡ä?¨º?¡ä¨®MSB???a¨º?
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC?¦Ì????¦Ì??¨¤??¨º?
	SPI_Init(SPI3, &SPI_InitStructure);  //?¨´?YSPI_InitStruct?D???¡§¦Ì?2?¨ºy3?¨º??¡¥¨ªa¨¦¨¨SPIx??¡ä??¡Â
 
	SPI_Cmd(SPI3, ENABLE); //¨º1?¨¹SPI¨ªa¨¦¨¨
	
	SPI3_ReadWriteByte(0xff);//???¡¥¡ä?¨º?		 

}   
//SPI ?¨´?¨¨¨¦¨¨??o¡¥¨ºy
//SpeedSet:
//SPI_BaudRatePrescaler_2   2¡¤??¦Ì   
//SPI_BaudRatePrescaler_8   8¡¤??¦Ì   
//SPI_BaudRatePrescaler_16  16¡¤??¦Ì  
//SPI_BaudRatePrescaler_256 256¡¤??¦Ì 
  
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI3->CR1&=0XFFC7;
	SPI3->CR1|=SPI_BaudRatePrescaler;	//¨¦¨¨??SPI1?¨´?¨¨ 
	SPI_Cmd(SPI3,ENABLE); 

} 

//SPIx ?¨¢D¡ä¨°???¡Á??¨²
//TxData:¨°aD¡ä¨¨?¦Ì?¡Á??¨²
//¡¤¦Ì???¦Ì:?¨¢¨¨?¦Ì?¦Ì?¡Á??¨²
u8 SPI3_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET) //?¨¬2¨¦???¡§¦Ì?SPI¡À¨º????¨¦¨¨??¨®?¡¤?:¡¤¡é?¨ª?o¡ä???¡À¨º????
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI3, TxData); //¨ª¡§1y¨ªa¨¦¨¨SPIx¡¤¡é?¨ª¨°???¨ºy?Y
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) //?¨¬2¨¦???¡§¦Ì?SPI¡À¨º????¨¦¨¨??¨®?¡¤?:?¨®¨º¨¹?o¡ä?¡¤???¡À¨º????
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI3); //¡¤¦Ì??¨ª¡§1ySPIx¡Á??¨¹?¨®¨º?¦Ì?¨ºy?Y					    
}
