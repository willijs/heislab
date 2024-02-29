#include "Door.h"
#include "driver/elevio.h"
#include <time.h>


// void openDoor(Door* door) {
//     door->open = true;
//     elevio_doorOpenLamp(door->open);
// }
// void closeDoor(Door* door) {
//     door->open = false;
//     elevio_doorOpenLamp(false);
// }

void openDoorSequence() {
        elevio_doorOpenLamp(1);
        // sleep(3);
        elevio_doorOpenLamp(0);
} //sleep er nok en dårlig ide. Kan ikke gjøre noe annet imens
