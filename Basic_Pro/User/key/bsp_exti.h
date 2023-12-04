#ifndef __EXTI_H
#define	__EXTI_H

#include "stm32f4xx.h"

//Òý½Å¶¨Òå KEY0
/*******************************************************/
#define KEY1_INT_GPIO_PORT                GPIOH
#define KEY1_INT_GPIO_CLK                 RCC_AHB1Periph_GPIOH
#define KEY1_INT_GPIO_PIN                 GPIO_Pin_3


#define KEY1_INT_EXTI_PORTSOURCE          EXTI_PortSourceGPIOH
#define KEY1_INT_EXTI_PINSOURCE           EXTI_PinSource3
#define KEY1_INT_EXTI_LINE                EXTI_Line3

#define KEY1_INT_EXTI_IRQn					EXTI3_IRQn
#define KEY1_IRQHandler         		 	EXTI3_IRQHandler         

/*******************************************************/


void EXTI_Key_Config(void);

#endif /* __EXTI_H */
