#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "FloorRequests.h"

void initializeElevator(FloorRequests* requests);

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    FloorRequests requests;
    int lastPosition = 0;
    bool goingUp = true;
    initializeElevator(&requests);


    while(1){
        int floor = elevio_floorSensor();
        printf("Floor: %d\n", floor);
        // printf("Floor: %d, %d, %d, %d\n", requests.floor1,requests.floor2,requests.floor3,requests.floor4);
        // printf("Bool: %d\n", goingUp);
        /*
        
        
        

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }
setFloorRequests(&requests, 0, 0);
        if(floor == N_FLOORS-1){
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
        if (floor >= 0) {
        elevio_floorIndicator(floor);
        lastPosition = floor;
        }

        goingUp = BetterFloorQueue(&requests, floor, lastPosition, goingUp);
        

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            initializeFloorRequests(&requests);
        }

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

void initializeElevator(FloorRequests* requests) {
    initializeFloorRequests(requests);
    while (elevio_floorSensor() != 0) {
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
}