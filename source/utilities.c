#include "utilities.h"



void checkButtonPresses() {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed) {
                floorButtonMatrix[f][b] = 1;
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
    }
}

void updateFloorIndicator(ElevatorState* state) {
     if (state->floor >= 0) {
            elevio_floorIndicator(state->floor);
            state->lastPos = state->floor;
    }
}

void checkForObstruction(ElevatorState* state) {
        state->obstruction = elevio_obstruction();
       
        if(state->obstruction && state->doorOpen){
            openDoor(state); 
        }
}

void callStopButton(ElevatorState* state) {
    if(!state->stopButton) {
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                elevio_buttonLamp(f, b, 0);
                floorButtonMatrix[f][b] = 0;
            }
        }
        state->lastDirection = state->goingUp;
        state->stopButton = true;
    }
    if(state->floor != -1) {
        openDoor(state);
    }
    elevio_stopLamp(1);
    elevio_motorDirection(DIRN_STOP);
}

void checkCloseDoor(ElevatorState* state) {
     if(time(NULL) - state->startTime  > 3){
        if(state->doorOpen) {
            elevio_doorOpenLamp(0);
            state->doorOpen = 0;
            }
        FloorQueue(state); 
    }
}

void stopLampOff(ElevatorState* state) {
    if (state->stopButton) {
        elevio_stopLamp(0);
        state->stopButton = false;
    }
}