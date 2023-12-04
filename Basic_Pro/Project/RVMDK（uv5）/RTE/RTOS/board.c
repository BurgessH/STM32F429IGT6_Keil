/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-24                  the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "stm32f4xx.h"
#include  "./uart/bsp_uart.h" 



#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */
#define RT_HEAP_SIZE (15*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];

RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

void rt_os_tick_callback(void)
{
    rt_interrupt_enter();
    
    rt_tick_increase();

    rt_interrupt_leave();
}

/**
 * This function will initial your board.
 */
void rt_hw_board_init(void)
{
//#error "TODO 1: OS Tick Configuration."
    /* 
     * TODO 1: OS Tick Configuration
     * Enable the hardware timer and call the rt_os_tick_callback function
     * periodically with the frequency RT_TICK_PER_SECOND. 
     */
	uint32_t msCnt;     		// count value of 1ms
	SystemCoreClockUpdate();
	
	msCnt = SystemCoreClock/RT_TICK_PER_SECOND;
	SysTick_Config(msCnt);
	
	myuart_init();
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

#ifdef RT_USING_CONSOLE

static int uart_init(void)
{
//#error "TODO 2: Enable the hardware uart and config baudrate."
    return 0;
}
INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
//#error "TODO 3: Output the string 'str' through the uart."
	
	 /* �����ٽ�� */  
	 //��ֹ����ϵͳ�ĵ��ȣ������ٽ�εĴ��벻�����ϣ���rt_scheduler_lock_nest>=1ʱ��������ֹͣ���ȡ� 
	rt_enter_critical();
	
	while(*str!='\0')
	{
		 /* ���� */
		if (*str == '\n')//RT-Thread ϵͳ�����еĴ�ӡ���� \n ��β�������� \r\n���������ַ����ʱ����Ҫ����� \n ֮ǰ��� \r����ɻس��뻻�У�����ϵͳ��ӡ��������Ϣ��ֻ�л���
		{
		   USART_SendData(USART1, '\r');
			 while(USART_GetFlagStatus(USART1, USART_FLAG_TC)== RESET);
		}
		
		USART_SendData(USART1, *(str++));
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)== RESET);	 //�ñ�־λʹ��TCʱ�ᵼ��finsh����г���Ŀ���
	}
	 /* �˳��ٽ�� */  
    //ע�⣺ʹ�ý����ٽ�����rt_enter_critical(); һ��Ҫʹ���˳��ٽ����� rt_exit_critical();�����������ס���޷����е���
	rt_exit_critical(); 
}

/*finsh����̨��Ϊһ���߳�Ҳ�ڲ��ϵ�ִ��,Ĭ�����ȼ�Ϊ21,���̵߳ĺ������ȼ������21(����С��21),������޷���Ӧ���߳�*/
char rt_hw_console_getchar(void)
{
    /* Note: the initial value of ch must < 0 */
    int ch = -1;
 
//#error "TODO 4: Read a char from the uart and assign it to 'ch'."
		
		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
		{
			ch = (char)USART_ReceiveData(USART1);
		}
		else
		{
			if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
			{
				USART_ClearFlag(USART1, USART_FLAG_TC);
			}
		}
    return ch;
}




#endif

