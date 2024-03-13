#pragma once
#include "ElevatorState.h"
#include "Door.h"
#include <stdbool.h>
#include "driver/elevio.h"
#include <stdio.h>


extern int floorButtonMatrix[N_FLOORS][N_BUTTONS];


void executeOrder(ElevatorState *state, int setFloor);
void floorQueue( ElevatorState *state);

void updateFloorIndicator(ElevatorState* state);

void checkButtonPresses();
