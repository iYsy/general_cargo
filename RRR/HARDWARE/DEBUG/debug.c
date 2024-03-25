#include "debug.h"
#include "lcd.h"
#include "lcd_init.h"
#include "picture.h"
#include "./uart/bsp_uart.h"
#include "debug.h"
//#include "stm32f10x_it.h"

uint32_t i;
u8 rxBuffer[MAX_DATA_SIZE];
u8 rxBufferIndex = 0;
u8 dataReceived = 0;


//void DEBUG_USART_IRQHandler(void)
//{
//	uint8_t ucTemp;
//	u8 r_buf[24]={0};
//	//判断是否产生中断
//	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
//	{
//		//若产生 则将数据传入 则给ucTemp
//		ucTemp = USART_ReceiveData(DEBUG_USARTx);
//		// 在 STM32 端处理接收到的字节数组
//		
//		
////		 rxBuffer[rxBufferIndex++] = USART_ReceiveData(USART2);
////			if (rxBufferIndex >= MAX_DATA_SIZE)
////			{
////					rxBufferIndex = 0; // 重置接收缓冲区索引以避免溢出
////			}
////			dataReceived = 1; // 数据接收标志置位
//				
//				
//		//processReceivedData();
//		
//		switch(ucTemp)
//		{
//			
//			case 0x41:
//				LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//				LCD_ShowString(24,0,"11111",BLACK,WHITE,16,0);
//				LCD_ShowPicture(65,80,40,40,gImage_11);
//			break;
//			
//			case 0x42:
//				LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//				LCD_ShowString(24,0,"222222",BLACK,WHITE,16,0);
//				//LCD_ShowPicture(65,80,40,40,gImage_21);
//			break;
//			 
//				
//			
//			default:
//				LCD_ShowString(24,10,"999",BLACK,WHITE,16,0);
//				//LCD_ShowString(24,0,"LCD TEST",BLACK,WHITE,16,0);
//				
//		}
//		USART_SendData(DEBUG_USARTx,ucTemp);
//	
//	
//	}

//}



void processReceivedData(uint8_t temp)
{
	

   switch(temp)
		{
			
			case 'A':
				LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
				LCD_ShowString(24,0,"11111",BLACK,WHITE,16,0);
				LCD_ShowPicture(65,80,40,40,gImage_11);
			break;
			
			case 'B':
				LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
				LCD_ShowString(24,10,"222222",BLACK,WHITE,16,0);
				//LCD_ShowPicture(65,80,40,40,gImage_21);
			break;
			 
				
			
			default:
				LCD_ShowString(24,10,"999",BLACK,WHITE,16,0);
				//LCD_ShowString(24,0,"LCD TEST",BLACK,WHITE,16,0);
				
		}
		USART_SendData(DEBUG_USARTx,temp);
}

//#define BUFFER_SIZE 128

//char rxBuffer[BUFFER_SIZE];
//int rxIndex = 0;


//char* my_strchr(const char* str, char ch) {
//    while (*str != '\0') {
//        if (*str == ch) {
//            return (char*)str; // 找到字符，返回字符在字符串中的位置
//        }
//        str++;
//    }
//    return 0; // 没有找到字符，返回空指针
//}


//int my_strcmp(const char* str1, const char* str2) {
//    while (*str1 && *str2 && *str1 == *str2) {
//        str1++;
//        str2++;
//    }
//    return (*str1 - *str2);
//}

//// 在串口接收中断中调用此函数，将接收到的字节存储在缓冲区中
//void USART_Rx_Handler(uint8_t data) {
//    if (rxIndex < BUFFER_SIZE - 1) {
//        rxBuffer[rxIndex++] = data;
//        rxBuffer[rxIndex] = '\0'; // 确保以 NULL 结尾
//    }
//}

//// 在主循环中调用此函数，处理接收到的数据
//void processReceivedData() {
//    // 假设收到的数据以换行符 '\n' 结尾
//    char* newline = my_strchr(rxBuffer, '\n');
//    if (newline != 0) {
//        *newline = '\0'; // 用 NULL 替换换行符，以便于使用字符串函数处理数据

//        // 处理接收到的数据
//        if (my_strcmp(rxBuffer, "A") == 0) {
//            // 收到了字符 'A'，执行相应的操作
//								LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//								LCD_ShowString(24,0,"LCD TEST",BLACK,WHITE,16,0);
//								LCD_ShowPicture(65,80,40,40,gImage_11);
//        } else if (my_strcmp(rxBuffer, "B") == 0) {
//            // 收到了字符 'B'，执行相应的操作
//					
//								LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//								LCD_ShowString(24,0,"LCD",BLACK,WHITE,16,0);
//        }
//        
//        // 清空接收缓冲区
//        rxIndex = 0;
//        rxBuffer[0] = '\0';
//    }
//}

