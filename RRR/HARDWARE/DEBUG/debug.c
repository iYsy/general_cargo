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
//	//�ж��Ƿ�����ж�
//	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
//	{
//		//������ �����ݴ��� ���ucTemp
//		ucTemp = USART_ReceiveData(DEBUG_USARTx);
//		// �� STM32 �˴�����յ����ֽ�����
//		
//		
////		 rxBuffer[rxBufferIndex++] = USART_ReceiveData(USART2);
////			if (rxBufferIndex >= MAX_DATA_SIZE)
////			{
////					rxBufferIndex = 0; // ���ý��ջ����������Ա������
////			}
////			dataReceived = 1; // ���ݽ��ձ�־��λ
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
//            return (char*)str; // �ҵ��ַ��������ַ����ַ����е�λ��
//        }
//        str++;
//    }
//    return 0; // û���ҵ��ַ������ؿ�ָ��
//}


//int my_strcmp(const char* str1, const char* str2) {
//    while (*str1 && *str2 && *str1 == *str2) {
//        str1++;
//        str2++;
//    }
//    return (*str1 - *str2);
//}

//// �ڴ��ڽ����ж��е��ô˺����������յ����ֽڴ洢�ڻ�������
//void USART_Rx_Handler(uint8_t data) {
//    if (rxIndex < BUFFER_SIZE - 1) {
//        rxBuffer[rxIndex++] = data;
//        rxBuffer[rxIndex] = '\0'; // ȷ���� NULL ��β
//    }
//}

//// ����ѭ���е��ô˺�����������յ�������
//void processReceivedData() {
//    // �����յ��������Ի��з� '\n' ��β
//    char* newline = my_strchr(rxBuffer, '\n');
//    if (newline != 0) {
//        *newline = '\0'; // �� NULL �滻���з����Ա���ʹ���ַ���������������

//        // ������յ�������
//        if (my_strcmp(rxBuffer, "A") == 0) {
//            // �յ����ַ� 'A'��ִ����Ӧ�Ĳ���
//								LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//								LCD_ShowString(24,0,"LCD TEST",BLACK,WHITE,16,0);
//								LCD_ShowPicture(65,80,40,40,gImage_11);
//        } else if (my_strcmp(rxBuffer, "B") == 0) {
//            // �յ����ַ� 'B'��ִ����Ӧ�Ĳ���
//					
//								LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//								LCD_ShowString(24,0,"LCD",BLACK,WHITE,16,0);
//        }
//        
//        // ��ս��ջ�����
//        rxIndex = 0;
//        rxBuffer[0] = '\0';
//    }
//}

