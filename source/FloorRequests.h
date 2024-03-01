#pragma once
#include "ElevatorState.h"
#include <stdbool.h>


//Skulle vi byttet til en matrise?
typedef struct {
    bool floor1;
    bool floor2;
    bool floor3;
    bool floor4;
} FloorRequests;

void setFloorRequests(FloorRequests *req, int floor, bool value);
//bool getFloorRequests(FloorRequests *req, int floor);

void initializeFloorRequests(FloorRequests *req);

void HelpFloorQueue(FloorRequests *req, ElevatorState *state, int setFloor);

// void FloorQueue(FloorRequests *req, int floor, int lastPosition);

void BetterFloorQueue(FloorRequests *req, ElevatorState *state);