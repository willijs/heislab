#include "FloorRequests.h"
#include "driver/elevio.h"
#include <stdio.h>
#include "ElevatorState.h"


int floorButtonMatrix[N_FLOORS][N_BUTTONS] = {0};

/*
void setFloorRequests(FloorRequests *req, int floor, bool value) {
    switch(floor){
        case 0:{
            req->floor1 = value;
            break;
        }
         case 1:{
            req->floor2 = value;
            break;
        }
         case 2:{
            req->floor3 = value;
            break;
        }
         case 3:{
            req->floor4 = value;
            break;
        }
    }
}

bool getFloorRequests(FloorRequests *req, int floor) {
    switch(floor){
        case 0:{
            return req->floor1;
        }
         case 1:{
            return req->floor2;
        }
         case 2:{
            return req->floor3;
        }
         case 3:{
            return req->floor4;
        }
    }

void initializeFloorRequests(FloorRequests *req){
    req->floor1 = 0;
    req->floor2 = 0;
    req->floor3 = 0;
    req->floor4 = 0;
}

*/
void HelpFloorQueue(ElevatorState *state, int setFloor) {
     if (state->floor == setFloor) {
        elevio_motorDirection(DIRN_STOP);
        for (int i = 0; i < 3; i++) {
            floorButtonMatrix[setFloor][i] = 0;
            elevio_buttonLamp(state->floor, i, 0);
        }
        openDoor(state);
    }
    else if (state->lastPos > setFloor) { // add a check to see if the door is open
        elevio_motorDirection(DIRN_DOWN);
    }
    else if (state->lastPos < setFloor) {
        elevio_motorDirection(DIRN_UP);
    }
    else{
        printf("Something is wrong with the floors");
        elevio_motorDirection(DIRN_STOP);
    }
}


// void FloorQueue(FloorRequests *req, int floor, int lastPosition) {
//     if (req->floor1) {
//         HelpFloorQueue(req, floor,lastPosition, 0);
//     }
//     else if (req->floor2) {
//         HelpFloorQueue(req, floor,lastPosition, 1);
//     }
//     else if (req->floor3) {
//         HelpFloorQueue(req, floor,lastPosition, 2);
//     }
//     else if (req->floor4) {
//         HelpFloorQueue(req, floor,lastPosition, 3);
//     }
// }


void FloorQueue(ElevatorState* state) {
    if (state->goingUp) {
        if (state->floor == 0 && (floorButtonMatrix[0][0] || floorButtonMatrix[0][2])){
            HelpFloorQueue(state, 0);
        }
        else if ((state->lastPos == 0 || state->floor == 1) && (floorButtonMatrix[1][0] || floorButtonMatrix[1][2])) {
            HelpFloorQueue(state, 1);
        }
        else if ((state->lastPos <= 1 || state->floor == 2) && (floorButtonMatrix[2][0] || floorButtonMatrix[2][2])) {
            HelpFloorQueue(state, 2);
        }
        else if ((state->lastPos <= 2 || state->floor == 3) && (floorButtonMatrix[3][0] || floorButtonMatrix[3][2])) {
            HelpFloorQueue(state, 3);
        }
        else {
            state->goingUp = false;
        }

    }
    else {
        if (state->floor == 3 && (floorButtonMatrix[3][1] || floorButtonMatrix[3][2])){
            HelpFloorQueue(state, 3);
        }
        else if ((state->lastPos == 3 || state->floor == 2) && (floorButtonMatrix[2][1] || floorButtonMatrix[2][2])) {
            HelpFloorQueue(state, 2);
        }
        else if ((state->lastPos >= 2 || state->floor == 1) && (floorButtonMatrix[1][1] || floorButtonMatrix[1][2])) {
            HelpFloorQueue(state, 1);
        }
        else if ((state->lastPos >= 1 || state->floor == 0) && (floorButtonMatrix[0][1] || floorButtonMatrix[0][2])) {
            HelpFloorQueue(state, 0);
        }
        else {
            state->goingUp = true;
        }
    }
}