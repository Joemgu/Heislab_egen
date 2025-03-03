#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include <unistd.h>
#include "../inc/elevatorFSM.h"
#include "../inc/startup_sequence.h"
#include "../inc/buttons.h"
#include "../inc/order_handler.h"



int main(){
    elevio_init();
    
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    Elevator T;
    ElevatorOrders O;
    ElevatorOrders_init(&O);

    startup_sequence(&T);
    printf("Curremt state: %d\n current floor: %d\n destination floor: %d\n", get_current_state(&T),get_current_floor(&T),get_destination_floor(&T));

    while(1){
        check_buttons(&O,&T);
        //printf("order: %x\n",O.inside_orders);
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        elevatorFSM(&T,&O);
    }

    return 0;
}






/*int floor = elevio_floorSensor();
        if(elevio_floorSensor()==1)
        {
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
            Elevator test;
            set_time(&test);
            sleep(3);
            int a = get_time_difference(&test);
            printf("%d\n", a);
            elevio_doorOpenLamp(0);
            elevio_motorDirection(DIRN_UP);
        }
        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }*/