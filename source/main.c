#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "FloorRequests.h"
#include "ElevatorState.h"
#include "utilities.h"




int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    ElevatorState state;
    initializeElevator(&state);

    while(1){

        state.floor = elevio_floorSensor();
        printf("Bool: %d\n", state.goingUp);
        
        if(elevio_stopButton()){
            callStopButton(&state);
        }
        else {
            if (state.stopButton) {
            elevio_stopLamp(0);
            state.stopButton = false;
            }

            checkButtonPresses();
            updateFloorIndicator(&state);
            checkForObstruction(&state);

    
        if(time(NULL) - state.startTime  > 3){ //så lenge det ikke har gått tre sekunder kaller vi på å utføre neste i køen
            if(state.doorOpen) {
            elevio_doorOpenLamp(0);
            state.doorOpen = 0;
            }
            FloorQueue(&state); 
        }
        
        }
    }

    return 0;
}

