#include "Door.h"



void checkForObstruction(ElevatorState* state) {
    //Checks for obstructions, and keeps the door open if obstructed
    state->obstruction = elevio_obstruction();
    
    if(state->obstruction && state->doorOpen){
        openDoor(state); 
    }
}

void checkCloseDoor(ElevatorState* state) {
    //Checks when the door should close, and requests a new order after door is closed
     if(time(NULL) - state->startTime  > 3){
        if(state->doorOpen) {
            elevio_doorOpenLamp(0);
            state->doorOpen = 0;
            }
        floorQueue(state); 
    }
}


void openDoor(ElevatorState* state) {
    //Opens the door if not between floors, and starts a 3 second timer
    if(state->floor == -1){
        printf("Trying to open the door while between floors!");
        return;
    }
    state->doorOpen = 1;
    elevio_doorOpenLamp(1);
    state->startTime = time(NULL); 
} 

