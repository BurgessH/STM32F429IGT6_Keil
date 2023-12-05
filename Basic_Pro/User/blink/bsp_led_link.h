#ifndef __BSP_LEN_LINK
#define __BSP_LEN_LINK

#include "stdint.h"

typedef enum lamp_work_status    
{
	Left_lamp_1HZ=0,  	
	
	Left_lamp_4HZ,				
	
	RL_lamp_1HZ,			
	
	Left_lamp_OFF			
	
}CAR_WORK_MODE;


typedef struct lamp_check_state    		
{
	CAR_WORK_MODE mode;
	
	uint8_t (*ctrlcheck)(void);
	
	CAR_WORK_MODE next_work_mode;
	
}CAR_CHECK_STATE;


typedef struct car_work_state			
{
	CAR_WORK_MODE work_mode;
	
	uint8_t (*ctrlLoop)(void);	
}CAR_STATE;









#endif

