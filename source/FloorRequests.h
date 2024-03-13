#pragma once
#include "ElevatorState.h"
#include <stdbool.h>

extern int floorButtonMatrix[N_FLOORS][N_BUTTONS];


void HelpFloorQueue(ElevatorState *state, int setFloor);
void FloorQueue( ElevatorState *state);