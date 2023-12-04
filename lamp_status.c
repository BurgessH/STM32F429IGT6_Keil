
#define	LSW_ON					(1)
#define	LSW_OFF					(0)

typedef enum lamp_work_status    //1.左转灯工作状态
{
	Left_lamp_1HZ=0,  			//左转状态

	Left_lamp_4HZ,				//爆闪状态
	
	RL_lamp_1HZ,				//应急状态
	
	Left_lamp_OFF,				//init状态
	
}CAR_WORK_MODE



typedef struct lamp_check_state    		//2.状态检测切换
{
	CAR_WORK_MODE mode;
	
	bool (*ctrlcheck)(void);
	
	CAR_WORK_MODE next_work_mode;
	
}CAR_CHECK_STATE



typedef struct car_work_state			//3.状态功能执行函数
{
	CAR_WORK_MODE work_mode
	
	void(*ctrlLoop)(void);	
}CAR_STATE



CAR_CHECK_STATE car_check_perform[] =
{
	{Left_lamp_OFF, 	Left_lamp_OFF_check, 	Left_lamp_OFF},
	
	{Left_lamp_OFF, 	Left_lamp_4HZ_check, 	Left_lamp_4HZ},
	{Left_lamp_OFF, 	Left_lamp_1HZ_check, 	Left_lamp_1HZ}, 	//转向灯-状态切换
	{Left_lamp_OFF, 	RL_lamp_1HZ_check, 		RL_lamp_1HZ},

	
	{Left_lamp_4HZ, 	Left_lamp_OFF_check, 	Left_lamp_OFF},
	{Left_lamp_4HZ, 	Left_lamp_1HZ_check, 	Left_lamp_1HZ},		//爆闪
	{Left_lamp_4HZ, 	RL_lamp_1HZ_check, 		RL_lamp_1HZ},
	
	{Left_lamp_1HZ, 	Left_lamp_OFF_check, 	Left_lamp_OFF},
	{Left_lamp_1HZ, 	Left_lamp_4HZ_check, 	Left_lamp_4HZ},		//转向
	{Left_lamp_1HZ, 	RL_lamp_1HZ_check, 		RL_lamp_1HZ},	
	
	
	{RL_lamp_1HZ, 		Left_lamp_OFF_check, 	Left_lamp_OFF},
	{RL_lamp_1HZ, 		Left_lamp_4HZ_check, 	Left_lamp_4HZ},
	{RL_lamp_1HZ, 		Left_lamp_1HZ_check, 	Left_lamp_1HZ}, 	//应急
}


CAR_STATE car_work_perform[]=
{
	{Left_lamp_4HZ, 	Left_lamp_4HZ_perform},
	
	{Left_lamp_1HZ, 	Left_lamp_1HZ_perform},
	
	{RL_lamp_1HZ, 		RL_lamp_1HZ_perform},
	
	{Left_lamp_OFF, 	Left_lamp_OFF_perform},
}

#define BrakeSW_status			hal_pin_read(BrakeSW)
#define EmerLSW_status			hal_pin_read(EmerLSW)

#define RTurnLSW_status			hal_pin_read(RTurnLSW)
#define LTurnLSW_status			hal_pin_read(LTurnLSW)

#define LEFT_ON 				hal_pin_write(HSDIN0, PIN_HIGH);
#define RIGHT_ON				hal_pin_write(HSDIN1, PIN_HIGH);
#define TAIL_ON					hal_pin_write(TailL, PIN_HIGH);

#define LEFT_OFF 				hal_pin_write(HSDIN0, PIN_LOW);
#define RIGHT_OFF 				hal_pin_write(HSDIN1, PIN_LOW);
#define TAIL_OFF 				hal_pin_write(TailL, PIN_LOW);



bool Left_lamp_OFF_check(void)
{
	if((BrakeSW_status == LSW_OFF)&&(LTurnLSW_status == LSW_OFF)&&(EmerLSW_status == LSW_OFF))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Left_lamp_4HZ_check(void)		//爆闪
{
	if(((BrakeSW_status == LSW_ON)&&(LTurnLSW_status == LSW_OFF)&&(EmerLSW_status == LSW_OFF)) ||  \
	  ((BrakeSW_status  == LSW_ON)&&(LTurnLSW_status == LSW_OFF)&&(EmerLSW_status == LSW_ON))  ||  \	  
	  ((BrakeSW_status  == LSW_ON)&&(LTurnLSW_status == LSW_ON)&&(EmerLSW_status  == LSW_OFF)) ||  \
	  ((BrakeSW_status  == LSW_ON)&&(LTurnLSW_status == LSW_ON)&&(EmerLSW_status  == LSW_ON)))	
	{
		return true;
	}
	else
	{
		return false;
		
	}

}

bool Left_lamp_1HZ_check(void) 		//转向
{
	if(((BrakeSW_status == LSW_OFF)&&(LTurnLSW_status == LSW_ON)&&(EmerLSW_status == LSW_OFF)) || \
	   ((BrakeSW_status == LSW_OFF)&&(LTurnLSW_status == LSW_ON)&&(EmerLSW_status == LSW_ON)))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool RL_lamp_1HZ_check(void)		//应急
{
	if((BrakeSW_status == LSW_OFF)&&(LTurnLSW_status == LSW_OFF)&&(EmerLSW_status == LSW_ON))
	{
		return true;

	}	
	else
	{
		if(EmerLSW_status == LSW_OFF&&status == LSW_ON)
		{
			LEDS_OFF;
			
			return false;
		}	
		
		return false;	
	}

}


void Left_lamp_OFF_perform(void)
{
		LEDS_OFF;
}

void Left_lamp_4HZ_perform(void)
{
	if(Speed >50Km)
	{
		
	}
	else
	{
		TAIL_ON;
	}
	
	
}

void Left_lamp_1HZ_perform(void)
{
	//执行左转灯功能, 应急灯开关是否有效
	if(EmerLSW_status == LSW_ON)
	{
		TAIL_ON;
		LEFT_ON;
	}
	else{
		LEFT_ON;
	}
	
}

void LR_lamp_1HZ_perform(void)
{
	//执行应急灯功能
	
}


//检索状态更新
static void oled_mode_check_perfrom(void)
{
	unisgned char i=0;
	
	for(int i=0; i<sizeof(car_check_perform)/sizeof(car_check_perform[0]); i++)
	{
		if(g_car_work == car_check_perform[i].work_mode)
		{
			if(car_check_perform[i].ctrlcheck() == true) //Next Mode
			{
				g_car_work = car_check_perform[i].next_work_mode;
				
				break;
			}
		}
	}
}

CAR_WORK_MODE g_car_work 		= Left_lamp_OFF;
//CAR_WORK_MODE g_car_work_old 	= car_turn;



//执行当前状态对应的函数：默认状态Init
void Left_led_work_all_perform(void)
{
	for(int i=0; i<sizeof(car_work_perform)/sizeof(car_work_perform[0]); i++)
	{
		if(g_car_work == car_work_perform[i].work_mode)	
		{
			if(g_car_work_old != g_car_work)
			{
				car_work_perform[i].ctrlinit(); 		
				g_car_work_old = g_car_work;			
			}
			
				car_work_perform[i].ctrlLoop(); 			//执行功能Fun
			
				oled_mode_check_perfrom();					//Next Staus
			
			break;
		}
	}	
}



static uint8_t status = 0;

void Led_blink(void)
{
	if(status == 0)
	{
		LEDS_ON;
		status = 1;
	}
	else
	{
		LEDS_OFF;
		status = 0;
	}
}	 