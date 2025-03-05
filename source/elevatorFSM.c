#include "../inc/elevatorFSM.h"

/**
 * @file elevatorFSM.c
 * @brief Implementation file for elevatorFSM.h
 */


//Switch case between states, will run in the main while loop of the program
void elevatorFSM(Elevator *anElevator,ElevatorOrders *orders){
//printf("%d\n", get_current_state(anElevator));
    
    switch (get_current_state(anElevator))
    {
    case IDLE:
        handle_IDLE(anElevator);
        break;
    case MOVING:
        handle_MOVING(anElevator);
        break;
    case AT_DESTINATION:
        handle_AT_DESTINATION(anElevator,orders);
        break;
    case EMERGENCY: 
        handle_EMERGENCY(anElevator);
        break;
    default:
        break;
    }
};



//define the triggers from IDLE-state
void handle_IDLE(Elevator *anElevator)
{
    if(!get_has_destination(anElevator))
    {
        return;
    }
    else if(get_has_destination(anElevator))
    {   
        if(get_current_floor(anElevator) == get_destination_floor(anElevator)){
            printf("Hopp dra IDLE til DEST\n");
            set_start_time(anElevator);
            set_current_state(anElevator,AT_DESTINATION);
        }
        else if(get_current_floor(anElevator) < get_destination_floor(anElevator))
        {
            printf("Hopp dra IDLE til MOVE up\n");
            elevio_motorDirection(DIRN_UP);
            set_moving_up(anElevator,true);
            
            set_current_state(anElevator, MOVING);
        }
        else if(get_current_floor(anElevator) > get_destination_floor(anElevator))
        {
            printf("Hopp dra IDLE til MOVE down\n");
            elevio_motorDirection(DIRN_DOWN);
            set_moving_up(anElevator,false);
            set_current_state(anElevator, MOVING);  
        }
        return;
    }   
    else if(elevio_stopButton())
    {
        printf("Hopp dra IDLE til DEST\n");
        elevio_doorOpenLamp(1);
        set_start_time(anElevator);
        set_current_state(anElevator, AT_DESTINATION);
    }
};

//define the triggers from Moving-state
void handle_MOVING(Elevator *anElevator)
{
    if(elevio_floorSensor() != -1)
    {
        //set the floor indicator
        elevio_floorIndicator(elevio_floorSensor());
        //update the current floor
        set_current_floor(anElevator, elevio_floorSensor());
    
        if(get_current_floor(anElevator)==get_destination_floor(anElevator))
        {
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
            set_start_time(anElevator);
            printf("Hopp fra MOVE til DEST\n");
            set_current_state(anElevator, AT_DESTINATION);
            return;
        }
    }
    return;
};

//define the triggers from Handle_AT_DESTINATION-state
void handle_AT_DESTINATION(Elevator *anElevator, ElevatorOrders *orders)
{
    mark_order_served(orders,get_current_floor(anElevator));
    elevio_buttonLamp(get_current_floor(anElevator),BUTTON_HALL_UP,0);
    elevio_buttonLamp(get_current_floor(anElevator),BUTTON_HALL_DOWN,0);
    elevio_buttonLamp(get_current_floor(anElevator),BUTTON_CAB,0);


    if(elevio_obstruction())
    {
        set_start_time(anElevator);
        return;
    }
    else if(get_time_difference(anElevator)>= 3)
    {

        if(!orders->unserved_orders)
        {
            set_has_destination(anElevator,false);
        } 
        else 
        {
            uint8_t new_destination_floor_bit_map = get_next_destination_bit_map(orders,get_current_floor(anElevator),get_moving_up(anElevator),get_is_moving(anElevator));
            if(!new_destination_floor_bit_map)
            {
                switch_moving_direction(anElevator);
                new_destination_floor_bit_map = get_next_destination_bit_map(orders,get_current_floor(anElevator),get_moving_up(anElevator),get_is_moving(anElevator));
            }
        set_destination_floor(anElevator,get_highest_bit(new_destination_floor_bit_map));
        }
        elevio_doorOpenLamp(0);
        printf("Hopp fra at DEST til IDLE\n");
        set_current_state(anElevator, IDLE);
        return;
    }
};


void handle_EMERGENCY(Elevator *anElevator)
{
    
};

