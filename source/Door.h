#pragma once
#include "FloorRequests.h"
#include "ElevatorState.h"
#include "driver/elevio.h"
#include <stdbool.h>


void checkForObstruction(ElevatorState* state);
void checkCloseDoor(ElevatorState* state);
void openDoor(ElevatorState* state);

