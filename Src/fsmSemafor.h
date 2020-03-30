#include "main.h"

extern uint8_t check_Timer_Elapsed(void);

enum Stanja
{
	GO2, GO_BLINK2, YELLOW2, BOTH_STOP_I, PREPARE_GO1, GO1, GO_BLINK1, YELLOW1, BOTH_STOP_II, PREPARE_GO2, NUMBER_OF_STATES
};


typedef const struct sFSM
{
	void(*fncPtr)(void);
	//uint16_t delay;
	uint8_t nextState[2];
	
}FSMType;

extern FSMType fsm_Semafor[NUMBER_OF_STATES]; 		//trikic u enumeraciji



