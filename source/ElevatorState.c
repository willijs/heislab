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
    state->lastDirection = 0;
}

void openDoor(ElevatorState* state) {
    if(state->floor == -1){
        printf("Prøver å åpne døren mellom etsajer");
        return;
    }

    state->doorOpen = 1;
    elevio_doorOpenLamp(1);
    state->startTime = time(NULL);
        
} 