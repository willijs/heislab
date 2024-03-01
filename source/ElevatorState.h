#pragma once
#include <time.h>
#include <stdbool.h>

typedef struct  {
    int lastPos;
    int floor;
    bool move;
    bool goingUp;
    bool doorOpen;
    long startTime;
    bool obstruction;
    bool stopButton;
}ElevatorState;

void initializeElevatorState(ElevatorState* state);



