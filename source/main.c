#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "ElevatorState.h"
#include "StopButton.h"
#include "Door.h"




int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    ElevatorState state;
    initializeElevator(&state);

    while(1){
        //Retrieves the current floor
        state.floor = elevio_floorSensor();
        
        //Checks if the stopbutton is called, and stops normal operation if it is
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

