#pragma once
#include "ElevatorState.h"
#include <stdbool.h>


//Skulle vi byttet til en matrise?

extern int floorButtonMatrix[N_FLOORS][N_BUTTONS];


/*

void setFloorRequests(FloorRequests *req, int floor, bool value);
//bool getFloorRequests(FloorRequests *req, int floor);

void initializeFloorRequests(FloorRequests *req);
*/

void HelpFloorQueue(ElevatorState *state, int setFloor);

void FloorQueue( ElevatorState *state);