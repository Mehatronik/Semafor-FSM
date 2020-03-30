#include "fsmSemafor.h"

extern uint16_t msTicker;		//iz stm32f1xx_it.c fajla
extern uint8_t msTickerEnable;


uint8_t check_Timer_Elapsed(void)
{
	
	if (msTicker == 0)
		return 1;
	else
		return 0;

	 //0 - osttani u trenutnom stanu
	 //1 - idi u naredno stanje
}



static void resetAllLights(void)
{
	HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(yellow1_GPIO_Port, yellow1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(yellow2_GPIO_Port, yellow2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_RESET);
}

static void go1Lights(void)
{
	resetAllLights();
	HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_SET);
	
	//reset timer, tj. start tajmera
//	msTicker = 10000;				//10 sek.
//	msTickerEnable = 1;
	HAL_Delay(10000);
}

static void go2Lights(void)
{
	resetAllLights();
	HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_SET);
	
//	msTicker = 10000;				//10 sek.
//	msTickerEnable = 1;
	HAL_Delay(10000);
}

static void go2BlinkLights(void)
{
	uint8_t i;
	
	resetAllLights();
	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_SET);
	
	for(i=0; i<10; i++)
	{
		HAL_GPIO_TogglePin(green2_GPIO_Port, green2_Pin);
		HAL_Delay(200);
	}
	
}

static void go1BlinkLights(void)
{
	uint8_t i;
	
	resetAllLights();
	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_SET);
	
	for(i=0; i<10; i++)
	{
		HAL_GPIO_TogglePin(green1_GPIO_Port, green1_Pin);
		HAL_Delay(200);
	}
	
}

static void yellow1Lights(void)
{
	resetAllLights();
	HAL_GPIO_WritePin(yellow1_GPIO_Port, yellow1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_SET);
	
//	msTicker = 3000;				
//	msTickerEnable = 1;
	HAL_Delay(3000);
}

static void yellow2Lights(void)
{
	resetAllLights();
	HAL_GPIO_WritePin(yellow2_GPIO_Port, yellow2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_SET);
	
//	msTicker = 3000;				
//	msTickerEnable = 1;
	HAL_Delay(3000);
}

static void bothStopLights(void)
{
	resetAllLights();
	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_SET);
	
//	msTicker = 2000;				
//	msTickerEnable = 1;
	HAL_Delay(2000);
}

static void prepareToGo1Lights(void)
{
	resetAllLights();
	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(yellow1_GPIO_Port, yellow1_Pin, GPIO_PIN_SET);
	
//	msTicker = 3000;				
//	msTickerEnable = 1;
	HAL_Delay(3000);
}

static void prepareToGo2Lights(void)
{
	resetAllLights();
	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(yellow2_GPIO_Port, yellow2_Pin, GPIO_PIN_SET);
	
//	msTicker = 3000;				
//	msTickerEnable = 1;
	HAL_Delay(3000);
}


FSMType fsm_Semafor[NUMBER_OF_STATES] = 
{
	{ &go2Lights,           {GO2, GO_BLINK2}             },					//GO2, GO_BLINK2, YELLOW2, BOTH_STOP_I, PREPARE_GO1, GO1, GO_BLINK1, YELLOW1, BOTH_STOP_II, PREPARE_GO2
	{ &go2BlinkLights,      {GO_BLINK2, YELLOW2}         },
	{ &yellow2Lights,       {YELLOW2, BOTH_STOP_I}       },
	{ &bothStopLights,      {BOTH_STOP_I, PREPARE_GO1}   },
	{ &prepareToGo1Lights,  {PREPARE_GO1, GO1}           },
	{ &go1Lights,           {GO1, GO_BLINK1}             },
	{ &go1BlinkLights,      {GO_BLINK1, YELLOW1}         },
	{ &yellow1Lights,       {YELLOW1, BOTH_STOP_II}      },
	{ &bothStopLights,      {BOTH_STOP_II, PREPARE_GO2}  },
	{ &prepareToGo2Lights,  {PREPARE_GO2, GO2}           }
		
};
