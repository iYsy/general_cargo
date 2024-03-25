
#include "devices_usart01_debug.h"

u8 debug_rx_buf[DEBUG_BUFFER_LEN] = {0};	//���ջ�����
u8 debug_rx_flag = 0;			//�յ����ݱ�־

void devices_usart01_debug_init( u8 sclk, u32 baud)
{
	double temp = (sclk * 1000000.0)/(16*baud);
	u16 mant = (u16) temp;
	u16 frac = (u16) ((temp - mant)*16);
	mant = mant << 4 | frac;
	
	RCC->APB2ENR |= 1<<14 | 1<<2;
	
	//PA9  -> U1.Tx  �����������50MHz
	//PA10 -> U1.Rx  ��������
	GPIOA->CRH &= 0xFFFFF00F;
	GPIOA->CRH |= 0x000008B0;
	GPIOA->ODR |= 1<<10;
	
	//����DMA1��ͨ��
	RCC->AHBENR |= 1<<0;
	
	USART1->BRR = mant;	//���ر��ʼĴ���
	//ʹ�ܴ���  ʹ��IDLE(���߿���)�ж�  ʹ�ܽ���  ʹ�ܷ���
	USART1->CR1 = 1<<13 | 1<<4 | 1<<3 | 1<<2;
	//ʹ��DMA����   ʹ��DMA����
	USART1->CR3 = 1<<6 | 1<<7;
	
	DMA1_Channel4->CCR = 0;
	//Channel Memory Address Reg
	DMA1_Channel4->CMAR = 0;
	//Channel Peripheral Address Reg
	DMA1_Channel4->CPAR = (u32) &USART1->DR;
	DMA1_Channel4->CNDTR = 0;
	DMA1_Channel4->CCR |= 1<<12 | 1<<7 | 1<<4;
	
	DMA1_Channel5->CCR = 0;
	DMA1_Channel5->CMAR = (u32) debug_rx_buf;
	DMA1_Channel5->CPAR = (u32) &USART1->DR;
	//Channel Number Of Data Reg
	DMA1_Channel5->CNDTR = DEBUG_BUFFER_LEN;
	DMA1_Channel5->CCR |= 1<<13 | 1<<7 | 1<<0;
	//ע���ж����ȼ�
    system_option_nvic_priority_set(2,3,USART1_IRQn);
}

void devices_usart01_debug_send_ch(u8 ch)
{
	DMA1_Channel4->CCR &= ~0x01;
	DMA1_Channel4->CMAR = (u32) &ch;
	DMA1_Channel4->CNDTR = 1;
	DMA1_Channel4->CCR |= 0x01;
}

void devices_usart01_debug_send_str(char * str)
{
	u16 len = strlen( str);
	DMA1_Channel4->CCR &= ~0x01;
	DMA1_Channel4->CMAR = (u32) str;
	DMA1_Channel4->CNDTR = len;
	DMA1_Channel4->CCR |= 0x01;
	system_delay_ms(30);
}

void devices_usart01_debug_send_buf(u16 len, u8 * buf)
{
	//�ر�U1.Tx��Ӧ��DMA1.CH4ͨ��
	DMA1_Channel4->CCR &= ~0x01;
	//����Ҫ���͵����ݵ��ڴ��׵�ַ
	DMA1_Channel4->CMAR = (u32) buf;
	//����Ҫ���͵���������
	DMA1_Channel4->CNDTR = len;
	//��ͨ��
	DMA1_Channel4->CCR |= 0x01;
	system_delay_ms(30);
}

void devices_usart01_debug_send_number(double num)
{
	//ȡ����������λС����ֵ��ת��Ϊ�޷�������
	u32 number = num * 100;
	u8 point = 0, i, len;
	u8 buf[30] = {0};
	if( num == 0)
	{
		devices_usart01_debug_send_ch('0');
		return;
	}
	//�����������������������������һ�������
	if( number % 100 != 0)
		point = 1;
	len = 0;
	while( number > 0)	//��������λ��
	{
		len ++;
		number /= 10;
	}
	number = num * 100;
	if( point == 0)
	{
		len -= 2;
		number /= 100;
	}
	//����ֵ��λ��֣�ת��Ϊ�ַ���ʽ���洢��buf��
	for( i = len; i > 0;i --)
	{
		buf[i-1] = number % 10 + '0';
		number /= 10;
	}
	
	//����С����
	number = num * 100;
	if( point != 0)
	{
		buf[len] = number % 10 + '0';
		buf[len-1] = number / 10 % 10 + '0';
		buf[len-2] = '.';
	}
	
	DMA1_Channel4->CCR &= ~0x01;
	DMA1_Channel4->CMAR = (u32) buf;
	DMA1_Channel4->CNDTR = len;
	DMA1_Channel4->CCR |= 0x01;
	system_delay_ms(10);
}

u8 devices_usart01_debug_read_ch(void)
{
	u8 ch;
	if( debug_rx_flag == 0)
		return 0;
	debug_rx_flag = 0;
	DMA1_Channel5->CCR &= ~0x01;
	ch = debug_rx_buf[0];
	DMA1_Channel5->CMAR = (u32) debug_rx_buf;
	DMA1_Channel5->CNDTR = DEBUG_BUFFER_LEN;
	DMA1_Channel5->CCR |= 0x01;
	return ch;
}

u16 devices_usart01_debug_read_buf(u16 size, u8 * buf)
{
	u16 i, len;
	//�ж��Ƿ���յ����ݣ�δ���յ��򷵻�0
	if( debug_rx_flag == 0)
		return 0;
	//������λ
	debug_rx_flag = 0;
	DMA1_Channel5->CCR &= ~0x01;
	//������յ������ݳ���
	len = DEBUG_BUFFER_LEN - DMA1_Channel5->CNDTR;
	if( len > size)
		len = size-1;
	for( i = 0;i < len;i ++)
		buf[i] = debug_rx_buf[i];
	buf[i] = 0;
	DMA1_Channel5->CMAR = (u32) debug_rx_buf;
	DMA1_Channel5->CNDTR = DEBUG_BUFFER_LEN;
	DMA1_Channel5->CCR |= 0x01;
	return len;
}

//==============����1�жϷ�����========
void USART1_IRQHandler(void)
{
	u8 temp;
	if( USART1->SR & (1<<4))
	{
		temp = USART1->DR;
		debug_rx_flag = temp;
		debug_rx_flag = 1;
	}
}
