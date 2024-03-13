#include "FloorRequests.h"
#include "driver/elevio.h"
#include <stdio.h>
#include "ElevatorState.h"


int floorButtonMatrix[N_FLOORS][N_BUTTONS] = {0};


void HelpFloorQueue(ElevatorState *state, int setFloor) {
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



void FloorQueue(ElevatorState* state) {

    if (state->goingUp) {
        for (int i = state->lastPos; i < 4; i++) {
            if ((floorButtonMatrix[i][0] || floorButtonMatrix[i][2])) {
                if (i == state->lastPos && state->floor == -1) {
                    continue;
                }
                HelpFloorQueue(state, i);
                return;
            }
        }
        for (int i = 3; i > -1 ; i--) {
            if ((floorButtonMatrix[i][1] || floorButtonMatrix[i][2])) {
                HelpFloorQueue(state, i);
                return;
            }
        }
        for (int i = 0; i < 4; i++) {
            if ((floorButtonMatrix[i][0])) {
                HelpFloorQueue(state, i);
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
                HelpFloorQueue(state, i);
                return;
            }
        }
        for (int i = 0; i <= 3 ; i++) {
            if ((floorButtonMatrix[i][0] || floorButtonMatrix[i][2])) {
                HelpFloorQueue(state, i);
                return;
            }
        }
        for (int i = 3; i >= 0 ; i--) {
            if ((floorButtonMatrix[i][1] || floorButtonMatrix[i][2])) {
                HelpFloorQueue(state, i);
                return;
            }
        }
        
    }
}

