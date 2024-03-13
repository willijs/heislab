#include "StopButton.h"

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


void stopLampOff(ElevatorState* state) {
    if (state->stopButton) {
        elevio_stopLamp(0);
        state->stopButton = false;
    }
}