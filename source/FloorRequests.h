#pragma once

#include <stdbool.h>

typedef struct {
    bool floor1;
    bool floor2;
    bool floor3;
    bool floor4;
} FloorRequests;

void setFloorRequests(FloorRequests *req, int floor, bool value);
bool getFloorRequests(FloorRequests *req, int floor);

void initializeFloorRequests(FloorRequests *req);

void HelpFloorQueue(FloorRequests *req, int floor, int lastPosition, int setFloor);

// void FloorQueue(FloorRequests *req, int floor, int lastPosition);

bool BetterFloorQueue(FloorRequests *req, int floor, int lastPosition, bool goingUp);