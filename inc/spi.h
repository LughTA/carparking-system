#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////
//set RFID rc522
/////////////////////////////////////////////////////////////////////
#define MFRC522_CS_GPIO					GPIOA
#define MFRC522_CS_PIN					GPIO_Pin_4
#define MFRC522_CS_RCC					RCC_AHB1Periph_GPIOA	

#define MFRC522_RST_GPIO				GPIOB
#define MFRC522_RST_PIN					GPIO_Pin_11
#define MFRC522_RST_RCC					RCC_AHB1Periph_GPIOB	

#define MFRC522_SPI							SPI1				// SPIx
#define MFRC522_SPI_GPIO				GPIOA			// 
#define MFRC522_SCK_PIN					GPIO_Pin_5		// SCK
#define MFRC522_MISO_PIN				GPIO_Pin_6		// MISO
#define MFRC522_MOSI_PIN				GPIO_Pin_7		// MOSI
#define MFRC522_SPI_GPIO_RCC		RCC_AHB1Periph_GPIOA
#define MFRC522_SPI_RCC					RCC_APB2Periph_SPI1
/////////////////////////////////////////////////////////////////////
//set SD CARD
/////////////////////////////////////////////////////////////////////


#define MICROSD_SPI							SPI2					// SPIx
#define MICROSD_SPI_GPIO				GPIOB					//
#define MICROSD_CS_PIN					GPIO_Pin_12 	// NSS
#define MICROSD_SCK_PIN					GPIO_Pin_13		// SCK
#define MICROSD_MISO_PIN				GPIO_Pin_14		// MISO
#define MICROSD_MOSI_PIN				GPIO_Pin_15		// MOSI
#define MICROSD_SPI_GPIO_RCC		RCC_AHB1Periph_GPIOB
#define MICROSD_SPI_RCC					RCC_APB1Periph_SPI2
/* Exported functions ------------------------------------------------------- */

void SPIRC552_Config();
void SPISD_Config();
uint8_t My_SPI_Exchange(uint8_t u8Data);
#endif /* __SPI_H */
