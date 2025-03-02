#include "../inc/startup_sequence.h"


void startup_sequence(Elevator *anElevator)
{
    while(elevio_floorSensor() == -1)
    {
        elevio_motorDirection(DIRN_UP);
    }
    elevio_motorDirection(DIRN_STOP);
    printf("Startup til IDLE\n");
    set_current_state(anElevator, IDLE);
    set_current_floor(anElevator, elevio_floorSensor());
    set_has_destination(anElevator, false);
    elevio_floorIndicator(elevio_floorSensor());
    return;
}