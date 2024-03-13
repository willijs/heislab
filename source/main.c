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
        
        if(elevio_stopButton()){
            callStopButton(&state);
        }
        else {
            stopLampOff(&state);
            checkButtonPresses();
            updateFloorIndicator(&state);
            checkForObstruction(&state);
            checkCloseDoor(&state);
        
        }
    }
    return 0;
}

