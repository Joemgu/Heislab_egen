#pragma once 
#include <stdbool.h>
#include <stdio.h>
#include "order_handler.h"
#include "elevatorFSM.h"
#include "../source/driver/elevio.h"

void check_buttons(ElevatorOrders *orders, Elevator *anElevator);

void handle_button_pressed(int floor, ButtonType button,ElevatorOrders *orders, Elevator *anElevator);
