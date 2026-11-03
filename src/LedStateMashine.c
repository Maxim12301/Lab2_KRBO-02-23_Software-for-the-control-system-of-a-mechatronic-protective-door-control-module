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

/* CYCLE_MS must equal the task cycle time (Software Configuration, Cyclic class).
   Video measurement showed a 0.1 s half period with CYCLE_MS = 10, i.e. a real cycle of about 2 ms. */
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
    case ST_DEC_NEG:
        inst->led1 = 1; inst->led2 = 0; inst->led3 = 0; inst->led4 = 0;
        break;

    case ST_POS:
    case ST_NEG:
        inst->led1 = 1; inst->led2 = 1; inst->led3 = 0; inst->led4 = 0;
        break;

    case ST_ACC_NEG:
    case ST_DEC_POS:
        inst->led1 = 1; inst->led2 = 1; inst->led3 = 1; inst->led4 = 0;
        break;

    case ST_CLOSE:
        inst->led1 = 1; inst->led2 = 1; inst->led3 = 1; inst->led4 = 1;
        break;

    default:
        inst->led1 = 0; inst->led2 = 0; inst->led3 = 0; inst->led4 = 0;
        break;
    }
}
