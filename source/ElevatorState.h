#pragma once
#include <time.h>
#include <stdbool.h>
#include "driver/elevio.h"
#include <stdio.h>

typedef struct  {
    int lastPos;
    int floor;
    bool move;
    bool goingUp;
    bool doorOpen;
    long startTime;
    bool obstruction;
    bool stopButton;
    int lastDirection;
}ElevatorState;


void initializeElevatorState(ElevatorState* state);
void openDoor(ElevatorState* state);





