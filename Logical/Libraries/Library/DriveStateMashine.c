
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define CMD_SHUTDOWN 0x0006
#define CMD_SWITCH_ON 0x0007
#define CMD_ENABLE 0x000F
#define STATE_MASK 0x006F
#define STATE_SWITCHED_ON 0x0021
#define STATE_READY 0x0023
#define STATE_OPERATION 0x0027

/* TODO: Add your comment here */
void DriveStateMashine(struct DriveStateMashine* inst)
{
	UINT st = inst->state & STATE_MASK;

	if (!inst->enable) {
		inst->command = CMD_SHUTDOWN;
		inst->speed = 0;
		return;
	}

	switch (inst->command) {

		case CMD_SWITCH_ON:
			inst->speed = 0;
			if (st == STATE_READY) inst->command = CMD_ENABLE;
			else if (st != STATE_SWITCHED_ON) inst->command = CMD_SHUTDOWN;
			break;

		case CMD_ENABLE:
			inst->speed = (st == STATE_OPERATION) ? inst->speedSet : 0;
			if (st != STATE_READY && st != STATE_OPERATION) inst->command = CMD_SHUTDOWN;
			break;

		default:
			inst->command = CMD_SHUTDOWN;
			inst->speed = 0;
			if (st == STATE_SWITCHED_ON) inst->command = CMD_SWITCH_ON;
			break;
	}
}	

