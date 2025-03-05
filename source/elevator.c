#include "../inc/elevator.h"

void set_current_state(Elevator *anElevator, Elevator_state_t a_current_state)
{
    anElevator->current_state = a_current_state;
}

Elevator_state_t get_current_state(Elevator *anElevator)
{
    return anElevator->current_state;
}


void set_destination_floor(Elevator *anElevator,int destination_floor)
{
    if(destination_floor < 0 || destination_floor > N_FLOORS)
    {
        //later implent interupt
        //prints "Floor out of bound"
        printf("Floor out of bound\n");
    }
    anElevator->destination_floor = destination_floor;
    return;
};


int get_destination_floor(Elevator *anElevator)
{
    return anElevator->destination_floor;
}

void set_current_floor(Elevator *anElevator, int a_current_floor)
{
    anElevator->current_floor = a_current_floor;
}

int get_current_floor(Elevator *anElevator)
{
    return anElevator->current_floor;
}

void set_has_destination(Elevator *anElevator, bool has_a_destination)
{
    anElevator->has_destination = has_a_destination;
}

bool get_has_destination(Elevator *anElevator)
{
    return anElevator->has_destination;
}

void set_moving_up(Elevator *anElevator, bool moving_up)
{
    anElevator->moving_up = moving_up;
}

bool get_moving_up(Elevator *anElevator){
    return anElevator->moving_up;
}

void switch_moving_direction(Elevator *anElevator)
{
    if(anElevator->moving_up){
        anElevator->moving_up = false;
    } 
    else 
    {
        anElevator->moving_up = true;
    }
    return;
}

void set_start_time(Elevator *anElevator)
{
    anElevator->start_time = time(NULL);
}

int get_time_difference(Elevator *anElevator)
{
    return (int)time(NULL) - anElevator->start_time;
}

bool get_is_moving(Elevator *anElevator) 
{
    if ((anElevator->current_state) == MOVING)
    {
        return true;
    } 
    else
    {
        return false;
    } 
}