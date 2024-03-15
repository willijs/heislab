#include "ElevatorState.h"



void initializeElevatorState(ElevatorState* state){
    //Initializes all of the states
    state->floor = 0;
    state->lastPos = 0;
    state->goingUp = 1;
    state->doorOpen = 0;
    state->startTime = time(NULL);
    state->obstruction = 0;
    state->stopButton = 0;
    state->lastDirection = 0;
}



void initializeElevator(ElevatorState* state) {
    //Turns of all buttonlamps
     for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
     }
    //Moves the elevator to a defined position (floor 1)
    initializeElevatorState(state);
    while (elevio_floorSensor() != 0) {
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
}