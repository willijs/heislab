#include "Door.h"



void checkForObstruction(ElevatorState* state) {
    state->obstruction = elevio_obstruction();
    
    if(state->obstruction && state->doorOpen){
        openDoor(state); 
    }
}

void checkCloseDoor(ElevatorState* state) {
     if(time(NULL) - state->startTime  > 3){
        if(state->doorOpen) {
            elevio_doorOpenLamp(0);
            state->doorOpen = 0;
            }
        floorQueue(state); 
    }
}


void openDoor(ElevatorState* state) {
    if(state->floor == -1){
        printf("Prøver å åpne døren mellom etasjer");
        return;
    }
    state->doorOpen = 1;
    elevio_doorOpenLamp(1);
    state->startTime = time(NULL); 
} 

