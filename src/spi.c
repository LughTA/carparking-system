
#include "spi.h"

void SPIRC552_Config(){
		
    /*  clock GPIO,SPIx RC522 */
    RCC_AHB1PeriphClockCmd(MFRC522_SPI_GPIO_RCC | MFRC522_RST_RCC | MFRC522_CS_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(MFRC522_SPI_RCC, ENABLE);

    
		/* configure GPIO_SPIx RC522 */
    GPIO_InitTypeDef GPIO_InitStruct;
		// configure SCK, MOSI, MISO
    GPIO_InitStruct.GPIO_Pin = MFRC522_SCK_PIN | MFRC522_MISO_PIN | MFRC522_MOSI_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(MFRC522_SPI_GPIO, &GPIO_InitStruct);

    // connect GPIO to Alternate Function
    GPIO_PinAFConfig(MFRC522_SPI_GPIO, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(MFRC522_SPI_GPIO, GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig(MFRC522_SPI_GPIO, GPIO_PinSource7, GPIO_AF_SPI1);

    // configure SS (CS) to output
    GPIO_InitStruct.GPIO_Pin = MFRC522_CS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(MFRC522_CS_GPIO, &GPIO_InitStruct);

    // set NSS (CS) to high
    GPIO_SetBits(MFRC522_CS_GPIO,MFRC522_CS_PIN);

    // configure Reset port to output
    GPIO_InitStruct.GPIO_Pin = MFRC522_RST_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(MFRC522_RST_GPIO, &GPIO_InitStruct);

    // set bit Reset to high
    GPIO_SetBits(MFRC522_RST_GPIO,MFRC522_RST_PIN);
		
		
		/* configure SPIx */
    SPI_InitTypeDef SPI_InitStruct;
    SPI_StructInit(&SPI_InitStruct);
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;  
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
		// initialization SPIx
    SPI_Init(MFRC522_SPI, &SPI_InitStruct);
    SPI_Cmd(MFRC522_SPI, ENABLE);
}
void SPISD_Config(){
		/*  clock GPIO,SPIx SD.CARD */
    RCC_AHB1PeriphClockCmd(MICROSD_SPI_GPIO_RCC, ENABLE);
    RCC_APB1PeriphClockCmd(MICROSD_SPI_RCC, ENABLE);

    
		/* configure GPIO_SPIx SD.CARD */
    GPIO_InitTypeDef GPIO_InitStruct;
		// configure SCK, MOSI, MISO
    GPIO_InitStruct.GPIO_Pin = MICROSD_SCK_PIN | MICROSD_MISO_PIN | MICROSD_MOSI_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(MICROSD_SPI_GPIO, &GPIO_InitStruct);

    // connect GPIO Alternate Function
    GPIO_PinAFConfig(MICROSD_SPI_GPIO, GPIO_PinSource13, GPIO_AF_SPI2);
    GPIO_PinAFConfig(MICROSD_SPI_GPIO, GPIO_PinSource14, GPIO_AF_SPI2);
    GPIO_PinAFConfig(MICROSD_SPI_GPIO, GPIO_PinSource15, GPIO_AF_SPI2);

    // configure SS (CS) to output
    GPIO_InitStruct.GPIO_Pin = MICROSD_CS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(MICROSD_SPI_GPIO, &GPIO_InitStruct);

    // set NSS (CS) to high
    GPIO_SetBits(MICROSD_SPI_GPIO,MICROSD_CS_PIN);
		
		/*  SPIx */
    SPI_InitTypeDef SPI_InitStruct;
    SPI_StructInit(&SPI_InitStruct);
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;  
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
		// initialization SPIx
    SPI_Init(MICROSD_SPI, &SPI_InitStruct);
    SPI_Cmd(MICROSD_SPI, ENABLE);
}

uint8_t My_SPI_Exchange(uint8_t u8Data)
{
	SPI_I2S_SendData(MICROSD_SPI, u8Data);
	while (SPI_I2S_GetFlagStatus(MICROSD_SPI, SPI_I2S_FLAG_BSY) == SET) {
	}
	return SPI_I2S_ReceiveData(MICROSD_SPI);
}
