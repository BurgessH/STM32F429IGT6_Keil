#include "stm32f4xx.h"
#include <rtthread.h>

#include "./led/bsp_led.h"
#include "./key/bsp_exti.h"

void Delay(__IO u32 nCount); 


int main(void)
{
	/* LED ¶Ë¿Ú³õÊ¼»¯ */
	LED_GPIO_Config();
  	

	EXTI_Key_Config(); 
	
	
	while(1)                            
	{	
		LED2_ON;	
		LED1_ON;
		rt_thread_mdelay(1000);	
		//rt_kprintf("LED1_ON blink...\r\n");
		
		LED1_OFF;	//hight Ãð
		LED2_OFF;	//hight Ãð
		rt_thread_mdelay(1000);
		
		//rt_kprintf("LED1_OFF blink...\r\n");
	}
}










/*********************END OF FILE*************************/

