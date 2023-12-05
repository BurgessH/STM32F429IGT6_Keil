 
#include "./board.h"


static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  

  NVIC_InitStructure.NVIC_IRQChannel 											= KEY1_INT_EXTI_IRQn;

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 		= 1;
 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority 					= 1;

  NVIC_InitStructure.NVIC_IRQChannelCmd 									= ENABLE;
	
  NVIC_Init(&NVIC_InitStructure);
}




void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_AHB1PeriphClockCmd(KEY1_INT_GPIO_CLK, 		ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	NVIC_Configuration();


	GPIO_InitStructure.GPIO_Pin 	= KEY1_INT_GPIO_PIN;

	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;	    		

	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;

	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure); 
	
	/* Selects the GPIO pin used as EXTI Line */
	SYSCFG_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);

	EXTI_InitStructure.EXTI_Line 				= KEY1_INT_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode 				= EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger 		= EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd 		= ENABLE;
	
	EXTI_Init(&EXTI_InitStructure);

}

