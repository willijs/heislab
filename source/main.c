#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "FloorRequests.h"
#include "ElevatorState.h"


void initializeElevator(ElevatorState* state);


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    ElevatorState state;
    initializeElevator(&state);


    while(1){
        state.floor = elevio_floorSensor();
        //printf("Floor: %d\n", state.floor);
        //printf("Floor: %d, %d, %d, %d\n", requests.floor1,requests.floor2,requests.floor3,requests.floor4);
        // printf("Bool: %d\n", goingUp);
        
        if(elevio_stopButton()){
            if(!state.stopButton) {
                for(int f = 0; f < N_FLOORS; f++){
                    for(int b = 0; b < N_BUTTONS; b++){
                    elevio_buttonLamp(f, b, 0);
                    floorButtonMatrix[f][b] = 0;
                    }
                }
            }
            if(state.floor != -1) {
                openDoor(&state);
            }
            elevio_stopLamp(1);
            elevio_motorDirection(DIRN_STOP);
            state.stopButton = true;
        }
        else {
            if (state.stopButton) {
            elevio_stopLamp(0);
            state.stopButton = false;
            }
        

        for(int f = 0; f < N_FLOORS; f++){
            printf("\n");
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                printf("%d",floorButtonMatrix[f][b]);
                if (btnPressed) {
                    floorButtonMatrix[f][b] = 1;
                    elevio_buttonLamp(f, b, btnPressed);
                }
            }
        }
        printf("\n");
        printf("\n");
        if (state.floor >= 0) {
            elevio_floorIndicator(state.floor);
            state.lastPos = state.floor;
        }
        
        state.obstruction = elevio_obstruction();
       
        if(state.obstruction && state.doorOpen){
            openDoor(&state); 
        }
        if(time(NULL) - state.startTime  > 3){ //så lenge det ikke har gått tre sekunder kaller vi på å utføre neste i køen
            if(state.doorOpen) {
            elevio_doorOpenLamp(0);
            state.doorOpen = 0;
            }
            FloorQueue(&state); 
        }
        
        }
        //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

void initializeElevator(ElevatorState* state) {
    initializeElevatorState(state);
    while (elevio_floorSensor() != 0) {
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
}