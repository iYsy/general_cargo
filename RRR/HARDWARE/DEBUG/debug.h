#ifndef __DEBUG_H
#define __DEBUG_H


#include "stm32f10x.h"


#define MAX_DATA_SIZE 100


//char* my_strchr(const char* str, char ch);
//int my_strcmp(const char* str1, const char* str2);
//void USART_Rx_Handler(uint8_t data) ;
//void processReceivedData();

void DEBUG_USART_IRQHandler(void);
void processReceivedData(uint8_t temp);
	

//void processReceivedData(uint8_t* data, uint32_t length);

#endif 


