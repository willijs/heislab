#include "FloorRequests.h"
#include "driver/elevio.h"
#include <stdio.h>






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
            break;
        }
         case 3:{
            return req->floor4;
            break;
        }
    }
}

void initializeFloorRequests(FloorRequests *req){
    req->floor1 = 0;
    req->floor2 = 0;
    req->floor3 = 0;
    req->floor4 = 0;
}

void HelpFloorQueue(FloorRequests *req, int floor, int lastPosition, int setFloor) {
     if (floor == setFloor) {
        elevio_motorDirection(DIRN_STOP);
        setFloorRequests(req, setFloor, 0);
        for (int i = 0; i < 3; i++) {
            elevio_buttonLamp(floor, i, 0);
        }
        openDoorSequence();
    }
    else if (lastPosition > setFloor) {
        elevio_motorDirection(DIRN_DOWN);
    }
    else if (lastPosition < setFloor) {
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


bool BetterFloorQueue(FloorRequests *req, int floor, int lastPosition, bool goingUp) {
    if (goingUp) {
        if (floor == 0 && req->floor1){
            HelpFloorQueue(req, floor,lastPosition, 0);
        }
        else if ((lastPosition == 0 || floor == 1) && req->floor2) {
            HelpFloorQueue(req, floor,lastPosition, 1);
        }
        else if ((lastPosition <= 1 || floor == 2) && req->floor3) {
            HelpFloorQueue(req, floor,lastPosition, 2);
        }
        else if ((lastPosition <= 2 || floor == 3) && req->floor4) {
            HelpFloorQueue(req, floor,lastPosition, 3);
        }
        else {
            goingUp = false;
        }

    }
    else {
        if (floor == 3 && req->floor4){
            HelpFloorQueue(req, floor,lastPosition, 3);
        }
        else if ((lastPosition == 3 || floor == 2) && req->floor3) {
            HelpFloorQueue(req, floor,lastPosition, 2);
        }
        else if ((lastPosition >= 2 || floor == 1) && req->floor2) {
            HelpFloorQueue(req, floor,lastPosition, 1);
        }
        else if ((lastPosition >= 1 || floor == 0) && req->floor1) {
            HelpFloorQueue(req, floor,lastPosition, 0);
        }
        else {
            goingUp = true;
        }
    }
    return goingUp;
}