#include "FloorRequests.h"






void setFloorRequests(FloorRequests *req, int floor, bool value) {
    switch(floor){
        case 0:{
            req->floor1 = value;
            break;
        }
         case 1:{
            req->floor2 = value;
            break;
        }
         case 2:{
            req->floor3 = value;
            break;
        }
         case 3:{
            req->floor4 = value;
            break;
        }
    }
}

void initializeFloorRequests(FloorRequests *req){
    req->floor1 = 0;
    req->floor2 = 0;
    req->floor3 = 0;
    req->floor4 = 0;
}