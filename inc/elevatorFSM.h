#pragma once
#include "order_handler.h"
#include "../source/driver/elevio.h"
#include <stdbool.h>
#include <stdio.h>
#include "elevator.h"


/**
 * @file elevatorFSM.h 
 * @brief Header file for elevatorFSM.c 
 */


//The main FSM loop, decides which handle function will run depending on the state of the elevator
void elevatorFSM(Elevator *anElevator,ElevatorOrders *orders);

//Handler functions for the different states 
void handle_IDLE(Elevator *anElevator);
void handle_MOVING(Elevator *anElevator);
void handle_AT_DESTINATION(Elevator *anElevator, ElevatorOrders *orders);
void handle_EMERGENCY(Elevator *anElevator);







