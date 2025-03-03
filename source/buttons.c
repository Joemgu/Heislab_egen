#include "../inc/buttons.h"

void check_buttons(ElevatorOrders *orders, Elevator *anElevator)
{
    for(int floor = 0; floor < 4; floor++)
    {
        for(ButtonType button = BUTTON_HALL_UP; button <= BUTTON_CAB; button++)
        {
            int current_state = elevio_callButton(floor,button);
            if(current_state)
            {
                handle_button_pressed(floor,button,orders,anElevator);
            }
        }
    }
}

void handle_button_pressed(int floor, ButtonType button, ElevatorOrders *orders, Elevator *anElevator)
{
    elevio_buttonLamp(floor,button,1);
    update_new_order(orders,floor,button);
    printf("------------------------\n");
    //printf("order: %x\n",orders->inside_orders);
    //trenger logikk for å endre moving_up

    //sets destination_floor in anElevator to the int representation of tha next destination from ElvatorOrders
    uint8_t new_destination_floor_bit_map = get_next_destination_bit_map(orders,get_current_floor(anElevator),get_moving_up(anElevator));
    if(!new_destination_floor_bit_map){
        switch_moving_direction(anElevator);
        new_destination_floor_bit_map = get_next_destination_bit_map(orders,get_current_floor(anElevator),get_moving_up(anElevator));
    }
    printf("button type: %d\n",button);
    printf("highest bit: %d\n",get_highest_bit(new_destination_floor_bit_map));
    printf("bit map: %d\n",new_destination_floor_bit_map);
    set_destination_floor(anElevator,get_highest_bit(new_destination_floor_bit_map));
    set_has_destination(anElevator,true);


    //printf("next dest: %x\n",anElevator->destination_floor);
    return;
}
