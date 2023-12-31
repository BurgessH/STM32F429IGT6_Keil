#include  "./uart/bsp_uart.h" 

void myuart_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
		
	RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK, ENABLE);

	/* 使能 USART 时钟 */
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);

	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  	= GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	
	/* 配置Tx引脚为复用功能  */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin  	= DEBUG_USART_TX_PIN  ;  
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚为复用功能 */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin  	= DEBUG_USART_RX_PIN;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);

	/*  连接 PXx 到 USARTx__Rx*/
	GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);

	/* 配置串DEBUG_USART 模式 */
	/* 波特率设置：DEBUG_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate 							= DEBUG_USART_BAUDRATE;
	/* 字长(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength 						= USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits 							= USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity 								= USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode 									= USART_Mode_Rx|USART_Mode_Tx;
	
	/* 完成USART初始化配置 */
	USART_Init(DEBUG_USART, &USART_InitStructure); 
	
	/* 嵌套向量中断控制器NVIC配置 */
//	NVIC_Configuration();

	/* 使能串口接收中断 */
//	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);

	/* 使能串口 */
	USART_Cmd(DEBUG_USART, ENABLE);                   //使能串口1 
 
}




