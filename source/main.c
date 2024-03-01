#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "FloorRequests.h"
#include "ElevatorState.h"

void initializeElevator(FloorRequests* requests, ElevatorState* state);

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    FloorRequests requests;
    ElevatorState state;
    initializeElevator(&requests, &state);


    while(1){
        state.floor = elevio_floorSensor();
        printf("Floor: %d\n", state.floor);
        // printf("Floor: %d, %d, %d, %d\n", requests.floor1,requests.floor2,requests.floor3,requests.floor4);
        // printf("Bool: %d\n", goingUp);
        /*
        
        
        

        if(state.floor == 0){
            elevio_motorDirection(DIRN_UP);
        }ce/ElevatorState.h:13:20: warning: expected ';' at end of declaration list
    bool stopButton
setFloorRequests(&requests, 0, 0);
        if(state.floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }*/
        

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed) {
                    setFloorRequests(&requests, f, 1);
                    elevio_buttonLamp(f, b, btnPressed);
                }
            }
        }
        if (state.floor >= 0) {
        elevio_floorIndicator(state.floor);
        state.lastPos = state.floor;
        }
        //if (state.startTime +3 < time(NULL))
        BetterFloorQueue(&requests, &state);
        

        if(elevio_obstruction()){
        } else {
        }
        
        if(elevio_stopButton()){
            elevio_stopLamp(1);
            elevio_motorDirection(DIRN_STOP);
            initializeFloorRequests(&requests);
        }
        else {
            elevio_stopLamp(0);
        }
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

void initializeElevator(FloorRequests* requests, ElevatorState* state) {
    initializeElevatorState(state);
    initializeFloorRequests(requests);
    while (elevio_floorSensor() != 0) {
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
}