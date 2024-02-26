#include "usart.h"

void UART1_Config(void)
{
	
	/*Cap xung clock cho USARTx va GPIO_USART*/
	RCC_APB2PeriphClockCmd(UART_HERCULES_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(UART_HERCULES_GPIO_RCC, ENABLE);
	
	/*Khoi tao GPIO_USART*/
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Pin = UART_HERCULES_TX|UART_HERCULES_RX;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIOInitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(UART_HERCULES_GPIO, &GPIOInitStruct);
	
	// Lien Ket chân GPIO voi chuc nang AF (Alternate Function)
	GPIO_PinAFConfig(UART_HERCULES_GPIO,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(UART_HERCULES_GPIO,GPIO_PinSource10,GPIO_AF_USART1);
	
	/*Khoi tao USARTx*/
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART_HERCULES, &USART_InitStruct);
	USART_Cmd(UART_HERCULES,ENABLE);
}

void USART_SendChar(char data){
	USART1->DR = 0x00;
	USART_SendData(UART_HERCULES, data);
	while ((USART_GetFlagStatus(UART_HERCULES, USART_FLAG_TXE))== RESET);

}
void USART_SendString(char *str) {
  while (*str) {
		USART_SendChar(*str);
		str++;
  }
}