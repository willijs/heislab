#include "utilities.h"



void checkButtonPresses() {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed) {
                floorButtonMatrix[f][b] = 1;
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
    }
}

void updateFloorIndicator(ElevatorState* state) {
     if (state->floor >= 0) {
            elevio_floorIndicator(state->floor);
            state->lastPos = state->floor;
    }
}