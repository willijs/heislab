#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "FloorRequests.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    FloorRequests requests;
    int lastPosition = 1;
    initializeFloorRequests(&requests);

    while(1){
        int floor = elevio_floorSensor();
        printf("Floor: %d, %d, %d, %d\n", requests.floor1,requests.floor2,requests.floor3,requests.floor4);
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
                //elevio_buttonLamp(f, b, btnPressed);
                if (btnPressed) {
                    setFloorRequests(&requests, f, 1);
                }
            }
        }
        if (floor >= 0) {
        elevio_floorIndicator(floor);
        lastPosition = floor;
        }

        if (requests.floor1) {
            if (floor == 0) {
                elevio_motorDirection(DIRN_STOP);
                setFloorRequests(&requests, 0, 0);
            }
            else {
                elevio_motorDirection(DIRN_DOWN);
            }
        }
        else if (requests.floor2) {
            if (floor == 1) {
                elevio_motorDirection(DIRN_STOP);
                setFloorRequests(&requests, 1, 0);
            }
            else if (lastPosition > 1) {
                elevio_motorDirection(DIRN_DOWN);
            }
             else if (lastPosition < 1) {
                elevio_motorDirection(DIRN_UP);
            }


        }
        else if (requests.floor3) {
            if (floor == 2) {
                elevio_motorDirection(DIRN_STOP);
                setFloorRequests(&requests, 2, 0);
            }
            else if (lastPosition > 2) {
                elevio_motorDirection(DIRN_DOWN);
            }
             else if (lastPosition < 2) {
                elevio_motorDirection(DIRN_UP);
            }

        }
        else if (requests.floor4) {
            if (floor == 3) {
                elevio_motorDirection(DIRN_STOP);
                setFloorRequests(&requests, 3, 0);
            }
            else {
                elevio_motorDirection(DIRN_UP);
            }
        }
        else {
            elevio_motorDirection(DIRN_STOP);
        }
        
        
       

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
