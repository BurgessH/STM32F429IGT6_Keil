
#include  "./uart/bsp_uart.h" 


void myuart_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
		
	RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK, ENABLE);

	/* ʹ�� USART ʱ�� */
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);

	/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  	= GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	
	/* ����Tx����Ϊ���ù���  */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin  	= DEBUG_USART_TX_PIN  ;  
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx����Ϊ���ù��� */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin  	= DEBUG_USART_RX_PIN;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);

	/*  ���� PXx �� USARTx__Rx*/
	GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);

	/* ���ô�DEBUG_USART ģʽ */
	/* ���������ã�DEBUG_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate 				= DEBUG_USART_BAUDRATE;
	/* �ֳ�(����λ+У��λ)��8 */
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_Parity 				= USART_Parity_No;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
	USART_InitStructure.USART_Mode 					= USART_Mode_Rx | USART_Mode_Tx;
	
	
	
	/* ���USART��ʼ������ */
	USART_Init(DEBUG_USART, &USART_InitStructure); 
	
	/* Ƕ�������жϿ�����NVIC���� */
//	NVIC_Configuration();

	/* ʹ�ܴ��ڽ����ж� */
//	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);

	/* ʹ�ܴ��� */
	USART_Cmd(DEBUG_USART, ENABLE);                   //ʹ�ܴ���1 
 
}




