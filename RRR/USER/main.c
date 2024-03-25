//////////////////////////////////////////////////////////////////////////////////	 
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : luxban
//  ��������   : 2022-6-01
//  ����޸�   : 
//  ��������   :��ʾ����(STM32F103ϵ��)
//              �ӿ�˵��: 
//              LED:PA8
//   
//              TFT-LCD: 
//              GND   ��Դ��
//              VCC   3.3v��Դ
//              SCL   PB4��SCLK��
//              SDA   PB5��MOSI��
//              RES   PB6
//              DC    PB7
//              CS    PB8
//              BLK   PB9
//              ----------------------------------------------------------------
//******************************************************************************/
#include "delay.h"
#include "sys.h"
#include "led.h"
#include "lcd_init.h"
#include "lcd.h"
//#include "pic.h"
#include "picture.h"
#include "debug.h"
#include "devices_usart01_debug.h"
#include "system_delay.h"
#include "devices_usart02_zigbee.h"
#include "stm32f10x.h"
#include "function.h"
//#include "stm32f10x_it.h"

#include "./uart/bsp_uart.h"
int main(void)
{
	//����һ����λ��temp�����ڽ������� Ϊʲô�ǰ�λ�����ô��ڷ���ʱ����һ���ַ� ��8bit
	uint8_t temp;
	float t=0;
	u8 r_buf[24]={0};
	u8 len=0;
	delay_init();
	LED_Init();//LED��ʼ��
	LCD_Init();//LCD��ʼ��
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	
	
	DEBUG_UART_Config();
	
	//USART_SendData(DEBUG_USARTx, 'A');
	USART_ReceiveData(DEBUG_USARTx);
	
	
	devices_usart01_debug_init(72,115200);
	devices_usart02_zigbee_init(36,9600);
  while(1){
    len=devices_usart02_zigbee_read_buf(24,r_buf);//��������
		//if(len){
		  //���ݷ��� 0xfe fe 00 ff ff len jdID devid xx ff
//		   if(r_buf[0]==0xfe&&r_buf[1]==0xfe&&r_buf[5]>=9&&
//				 r_buf[5]<=12&&r_buf[6]<=0x80){//�ж�ָ��Ϸ�����Э���ʽ
//			   //ָ�����
//					 ansys(len,r_buf);
//			 }  
			if(r_buf[0]==0xAA)
			{
			  LCD_ShowString(24,0,"LCD TEST",BLACK,WHITE,16,0);
				LCD_ShowPicture(65,80,40,40,gImage_11);
			}
			else if(r_buf[0]==0xBB)
			{
				LCD_ShowString(24,0,"AA",BLACK,WHITE,16,0);
			}
		
		
	}	
	//while(1)
	//{
		//temp = USART_ReceiveData(DEBUG_USARTx);
		//processReceivedData(temp);
		
//		switch(temp)
//		{
//			
//			case 'A':
//				LCD_ShowString(24,0,"LCD TEST",BLACK,WHITE,16,0);
//				LCD_ShowPicture(65,80,40,40,gImage_11);
//			break;
//			
//			case 'B':
//				LCD_ShowString(24,10,"LCD TEST",BLACK,WHITE,16,0);
//				//LCD_ShowPicture(65,80,40,40,gImage_21);
//			break;
//			 
//				
//			
//			default:
//				LCD_ShowString(24,0,"LCD TEST",BLACK,WHITE,16,0);
				
		//}
		
		
//		LCD_ShowString(24,0,"LCD TEST",BLACK,WHITE,16,0);
//		LCD_ShowString(24,30,"LCD_W:",RED,WHITE,16,0);
//		LCD_ShowIntNum(72,30,LCD_W,3,RED,WHITE,16);
//		LCD_ShowString(24,50,"LCD_H:",RED,WHITE,16,0);
//		LCD_ShowIntNum(72,50,LCD_H,3,RED,WHITE,16);
//		LCD_ShowFloatNum1(20,80,t,4,RED,WHITE,16);
//		t+=0.11;
//		LCD_ShowPicture(65,80,40,40,gImage_1);
//	  LED=~LED;

}



