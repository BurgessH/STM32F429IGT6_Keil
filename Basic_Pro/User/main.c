#include "./board.h"

/* 声明线程1、2入口函数 */
static void led1_thread_entry(void *parameter);
static void led2_thread_entry(void *parameter);



/* 定义线程控制块 */
static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t led2_thread = RT_NULL;


static void led1_thread_entry(void *parameter)
{
	while(1)
	{
		LED1_ON;
		rt_thread_delay(500);
		
		LED1_OFF;
		rt_thread_delay(500);
	}
}

static void led2_thread_entry(void *parameter)
{
	while(1)
	{
		LED2_OFF;
		rt_thread_delay(500);
		
		LED2_ON;
		rt_thread_delay(500);
	}
}


int main(void)
{
  	
		/* 创建线程 */
	led1_thread = rt_thread_create("led1",	/* 线程名字 */
									led1_thread_entry, 			/* 线程入口函数 */ 
									RT_NULL, 								/* 线程入口函数参数 */ 
									512, 										/* 线程栈大小 */ 
									3, 											/* 线程的优先级 */
									10); 										/* 线程时间片 */
	
	led2_thread = rt_thread_create("led2",	/* 线程名字 */
									led2_thread_entry, 			/* 线程入口函数 */ 
									RT_NULL, 								/* 线程入口函数参数 */ 
									512, 										/* 线程栈大小 */ 
									3, 											/* 线程的优先级 */
									10); 										/* 线程时间片 */

		/* 启动线程 */
	if(led1_thread != RT_NULL)
	{
		rt_thread_startup(led1_thread);
		rt_kprintf("led1_thread success...\r\n");
	}
	else
	{
			return RT_ERROR;
	}

	
	if(led2_thread != RT_NULL)
	{
			rt_thread_startup(led2_thread);
			rt_kprintf("led2_thread success...\r\n");
	}
	else
	{
			return RT_ERROR;
	}


//	while(1)                            
//	{	
//		LED2_ON;	
//		LED1_ON;
//		rt_thread_mdelay(1000);	
//		//rt_kprintf("LED1_ON blink...\r\n");
//		
//		LED1_OFF;	//hight 灭
//		LED2_OFF;	//hight 
//		rt_thread_mdelay(1000);
//		
//		//rt_kprintf("LED1_OFF blink...\r\n");
//	}
}






