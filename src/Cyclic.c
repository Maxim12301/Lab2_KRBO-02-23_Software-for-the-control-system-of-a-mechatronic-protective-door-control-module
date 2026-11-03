#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
    stateMachine.enable = 1;

    doorSM.state = stateMachine.state;
    DoorStateMashine(&doorSM);

    stateMachine.speed = doorSM.speed;
    stateMachine.speedSet = doorSM.speed;
    DriveStateMashine(&stateMachine);

    ledSM.state = doorSM.doorState;
    LedStateMashine(&ledSM);
}
