#pragma once

typedef struct  {
    int move;
    int position;
    int lastPosition;
}ElevatorState;

void checkValid(ElevatorState* state); //gi false dersom position == -1

void updatePosition(ElevatorState* state); //update position og last position

void updateMove(ElevatorState* state); // -1 = ned, 0 = stille, 1 = opp

//MotorDirection gjør dette allerede

//oppstart?


