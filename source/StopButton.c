#include "StopButton.h"

void callStopButton(ElevatorState* state) {
    //Turns of all the elevatorbuttons, and sets the stopButton to true, if not alredy pressed
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
    //Opens door if on a floor
    if(state->floor != -1) { 
        openDoor(state);
    }
    elevio_stopLamp(1);
    elevio_motorDirection(DIRN_STOP);
}


void stopLampOff(ElevatorState* state) {
    //Turns off the stopButton if it's alredy on
    if (state->stopButton) { 
        elevio_stopLamp(0);
        state->stopButton = false;
    }
}