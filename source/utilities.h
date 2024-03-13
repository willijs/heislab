#include <stdio.h>
#include <stdlib.h>

#include "driver/elevio.h"
#include "FloorRequests.h"
#include "ElevatorState.h"


void checkButtonPresses();

void updateFloorIndicator(ElevatorState* state);

void checkForObstruction(ElevatorState* state);

void callStopButton(ElevatorState* state);