#include "ElevatorState.h"



void initializeElevatorState(ElevatorState* state){
    state->floor = 0;
    state->lastPos = 0;
    state->move = 0;
    state->goingUp = 1;
    state->doorOpen = 0;
    state->startTime = time(NULL);
    state->obstruction = 0;
    state->stopButton = 0;
}