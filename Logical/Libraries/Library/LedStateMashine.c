
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
#define ST_INIT 0
#define ST_UNKNOWN 1
#define ST_OPEN 2
#define ST_CLOSE 3
#define ST_ACC_POS 4
#define ST_ACC_NEG 5
#define ST_POS 6
#define ST_NEG 7
#define ST_DEC_POS 8
#define ST_DEC_NEG 9
#define ST_WAIT 10

#define CYCLE_MS 2
#define HALF_CYCLES (500 / CYCLE_MS)

void LedStateMashine(struct LedStateMashine* inst)
{
	if (inst->state == ST_UNKNOWN) {
		inst->timer++;
		if (inst->timer >= HALF_CYCLES) {
			inst->timer = 0;
			inst->blinkOn = !inst->blinkOn;
		}
	} else {
		inst->timer = 0;
		inst->blinkOn = 0;
	}

	switch (inst->state) {

		case ST_UNKNOWN:
			inst->led1 = inst->blinkOn; inst->led2 = inst->blinkOn;
			inst->led3 = inst->blinkOn; inst->led4 = inst->blinkOn;
			break;

		case ST_ACC_POS:
			inst->led1 = 1; inst->led2 = 0; inst->led3 = 0; inst->led4 = 0;
			break;

		case ST_POS:
			inst->led1 = 1; inst->led2 = 1; inst->led3 = 0; inst->led4 = 0;
			break;

		case ST_DEC_POS:
			inst->led1 = 1; inst->led2 = 1; inst->led3 = 1; inst->led4 = 0;
			break;

		case ST_ACC_NEG:
			inst->led1 = 0; inst->led2 = 0; inst->led3 = 0; inst->led4 = 1;
			break;

		case ST_NEG:
			inst->led1 = 0; inst->led2 = 0; inst->led3 = 1; inst->led4 = 1;
			break;

		case ST_DEC_NEG:
			inst->led1 = 0; inst->led2 = 1; inst->led3 = 1; inst->led4 = 1;
			break;

		case ST_CLOSE:
		case ST_OPEN:
			inst->led1 = 1; inst->led2 = 1; inst->led3 = 1; inst->led4 = 1;
			break;

		default:
			inst->led1 = 0; inst->led2 = 0; inst->led3 = 0; inst->led4 = 0;
			break;
	}
}