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

#define SPEED_SLOW 200
#define SPEED_FAST 850
#define STATE_MASK 0x006F
#define STATE_OPERATION 0x0027

void DoorStateMashine(struct DoorStateMashine* inst)
{
    INT mag = 0;

    if ((inst->state & STATE_MASK) != STATE_OPERATION) {
        inst->doorState = ST_INIT;
        inst->speed = 0;
        return;
    }

    switch (inst->doorState) {

    case ST_INIT:
        inst->doorState = ST_UNKNOWN;
        break;

    case ST_UNKNOWN:
        if (!inst->direction && inst->s0) inst->doorState = ST_OPEN;
        else if (inst->direction && inst->s3) inst->doorState = ST_CLOSE;
        break;

    case ST_OPEN:
        if (inst->direction) inst->doorState = ST_ACC_POS;
        break;

    case ST_ACC_POS:
        if (!inst->direction) inst->doorState = ST_DEC_NEG;
        else if (inst->s1) inst->doorState = ST_POS;
        break;

    case ST_POS:
        if (!inst->direction) inst->doorState = ST_NEG;
        else if (inst->s2) inst->doorState = ST_DEC_POS;
        break;

    case ST_DEC_POS:
        if (!inst->direction) inst->doorState = ST_ACC_NEG;
        else if (inst->s3) inst->doorState = ST_CLOSE;
        break;

    case ST_CLOSE:
        if (!inst->direction) inst->doorState = ST_ACC_NEG;
        break;

    case ST_ACC_NEG:
        if (inst->direction) inst->doorState = ST_DEC_POS;
        else if (inst->s2) inst->doorState = ST_NEG;
        break;

    case ST_NEG:
        if (inst->direction) inst->doorState = ST_POS;
        else if (inst->s1) inst->doorState = ST_DEC_NEG;
        break;

    case ST_DEC_NEG:
        if (inst->direction) inst->doorState = ST_ACC_POS;
        else if (inst->s0) inst->doorState = ST_OPEN;
        break;

    default:
        inst->doorState = ST_INIT;
        break;
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
}
