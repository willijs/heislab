#pragma once
#include "Door.h"
#include "driver/elevio.h"
#include <stdbool.h>

void callStopButton(ElevatorState* state);
void stopLampOff(ElevatorState* state);