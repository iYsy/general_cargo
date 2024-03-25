#include "./uart/bsp_uart.h"


static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStucture;
	
	//嵌套向量中断控制器组选择
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//配置usart为中断源
	NVIC_InitStucture.NVIC_IRQChannel = DEBUG_USART_IRQ;
	//抢断优先级
	NVIC_InitStucture.NVIC_IRQChannelPreemptionPriority = 1;
	//子优先级
	NVIC_InitStucture.NVIC_IRQChannelSubPriority = 1;
	
	//使能中断
	NVIC_InitStucture.NVIC_IRQChannelCmd = ENABLE;
	//初始化配置NVIC
	NVIC_Init(&NVIC_InitStucture);

}
void DEBUG_UART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	USART_InitTypeDef USART_InitStructure;
	
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK,ENABLE);
	
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAURATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAURATE;
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	//串口中断优先级配置
	NVIC_Configuration();
	
	//使能串口接收中断
	USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);
	//使能串口
	USART_Cmd(DEBUG_USARTx,ENABLE);
	

}