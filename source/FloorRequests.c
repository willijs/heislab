#include "FloorRequests.h"


int floorButtonMatrix[N_FLOORS][N_BUTTONS] = {0};


void executeOrder(ElevatorState *state, int setFloor) {
     if (state->floor == setFloor) {
        elevio_motorDirection(DIRN_STOP);
        for (int i = 0; i < 3; i++) {
            floorButtonMatrix[setFloor][i] = 0;
            elevio_buttonLamp(state->floor, i, 0);
        }
        openDoor(state);
    }
    else if (state->lastPos > setFloor) { 
        elevio_motorDirection(DIRN_DOWN);
        state->goingUp = false;
    }
    else if (state->lastPos < setFloor) {
        elevio_motorDirection(DIRN_UP);
        state->goingUp = true;
    }
    else{
        if (state->lastDirection) {
                elevio_motorDirection(DIRN_DOWN);

        }
        else {
                elevio_motorDirection(DIRN_UP);
        }
     }
}



void floorQueue(ElevatorState* state) {

    if (state->goingUp) {
        for (int i = state->lastPos; i < 4; i++) {
            if ((floorButtonMatrix[i][0] || floorButtonMatrix[i][2])) {
                if (i == state->lastPos && state->floor == -1) {
                    continue;
                }
                executeOrder(state, i);
                return;
            }
        }
        for (int i = 3; i > -1 ; i--) {
            if ((floorButtonMatrix[i][1] || floorButtonMatrix[i][2])) {
                executeOrder(state, i);
                return;
            }
        }
        for (int i = 0; i < 4; i++) {
            if ((floorButtonMatrix[i][0])) {
                executeOrder(state, i);
                return;
            }
        }
    }

    else {
        for (int i = state->lastPos; i >= 0; i--) {
            if ((floorButtonMatrix[i][1] || floorButtonMatrix[i][2])) {
                if (i == state->lastPos && state->floor == -1) {
                    continue;
                }
                executeOrder(state, i);
                return;
            }
        }
        for (int i = 0; i <= 3 ; i++) {
            if ((floorButtonMatrix[i][0] || floorButtonMatrix[i][2])) {
                executeOrder(state, i);
                return;
            }
        }
        for (int i = 3; i >= 0 ; i--) {
            if ((floorButtonMatrix[i][1] || floorButtonMatrix[i][2])) {
                executeOrder(state, i);
                return;
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
