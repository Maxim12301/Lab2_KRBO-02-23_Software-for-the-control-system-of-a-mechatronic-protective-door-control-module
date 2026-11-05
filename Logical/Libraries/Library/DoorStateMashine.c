#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
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

#define SPEED_SLOW 200
#define SPEED_FAST 850
#define STATE_MASK 0x006F
#define STATE_OPERATION 0x0027

void DoorStateMashine(struct DoorStateMashine* inst)
{
	INT mag = 0;
	BOOL e0, e1, e2, e3;

	e0 = (inst->s0 != inst->s0Prev);
	e1 = (inst->s1 != inst->s1Prev);
	e2 = (inst->s2 != inst->s2Prev);
	e3 = (inst->s3 != inst->s3Prev);

	if ((inst->state & STATE_MASK) != STATE_OPERATION) {
		inst->doorState = ST_INIT;
	}
	else {
		switch (inst->doorState) {

			case ST_INIT:
				inst->doorState = ST_UNKNOWN;
				break;

			case ST_UNKNOWN:
			case ST_WAIT:
				if (inst->direction && e0) inst->doorState = ST_ACC_POS;
				else if (!inst->direction && e3) inst->doorState = ST_ACC_NEG;
				break;

			case ST_ACC_POS:
				if (!inst->direction) inst->doorState = ST_WAIT;
				else if (e1) inst->doorState = ST_POS;
				break;

			case ST_POS:
				if (!inst->direction) inst->doorState = ST_WAIT;
				else if (e2) inst->doorState = ST_DEC_POS;
				break;

			case ST_DEC_POS:
				if (!inst->direction) inst->doorState = ST_WAIT;
				else if (e3) inst->doorState = ST_CLOSE;
				break;

			case ST_CLOSE:
				if (!inst->direction) inst->doorState = ST_WAIT;
				break;

			case ST_ACC_NEG:
				if (inst->direction) inst->doorState = ST_WAIT;
				else if (e2) inst->doorState = ST_NEG;
				break;

			case ST_NEG:
				if (inst->direction) inst->doorState = ST_WAIT;
				else if (e1) inst->doorState = ST_DEC_NEG;
				break;

			case ST_DEC_NEG:
				if (inst->direction) inst->doorState = ST_WAIT;
				else if (e0) inst->doorState = ST_OPEN;
				break;

			case ST_OPEN:
				if (inst->direction) inst->doorState = ST_WAIT;
				break;

			default:
				inst->doorState = ST_INIT;
				break;
		}
	}

	switch (inst->doorState) {
		case ST_UNKNOWN:
		case ST_ACC_POS:
		case ST_ACC_NEG:
		case ST_DEC_POS:
		case ST_DEC_NEG:
			mag = SPEED_SLOW;
			break;
		case ST_POS:
		case ST_NEG:
			mag = SPEED_FAST;
			break;
		default:
			mag = 0;
			break;
	}

	inst->speed = inst->direction ? -mag : mag;

	inst->s0Prev = inst->s0;
	inst->s1Prev = inst->s1;
	inst->s2Prev = inst->s2;
	inst->s3Prev = inst->s3;
}