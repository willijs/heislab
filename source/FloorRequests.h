#pragma once

#include <stdbool.h>

typedef struct {
    bool floor1;
    bool floor2;
    bool floor3;
    bool floor4;
} FloorRequests;


void setFloorRequests(FloorRequests *req, int floor, bool value);

void initializeFloorRequests(FloorRequests *req);