#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define UINT4_MASK 0x0F

typedef enum {
    ORDER_UP,
    ORDER_DOWN,
    ORDER_CAB
} Order_type_t;

typedef struct {
    uint8_t unserved_orders;  // Bitmask for unserved orders on each floor
    uint8_t up_orders;
    uint8_t down_orders;        // Bitmask for orders going up
    uint8_t inside_orders;    // Bitmask for orders from inside the cab
} ElevatorOrders;


//initialize an order_matirx
void ElevatorOrders_init(ElevatorOrders *orders);

//updates the order matrix with a new order
void update_new_order(ElevatorOrders *orders, int destination_floor, Order_type_t anOrder_type);

//updates the order matrix when a order is served (set the served floor to 0)
void mark_order_served(ElevatorOrders *orders, int served_floor);

//returns the next destination floor based on where the elevator is, which direction the elvator is moving and the order_matrix
uint8_t get_next_destination_bit_map(ElevatorOrders *orders, int current_floor, bool moving_up, bool elevator_is_moving);

int get_highest_bit(uint8_t value);



// Function to print uint8_t bitwise
void print_bitwise(uint8_t value);

// Function to print the ElevatorOrders struct bitwise
void print_elevator_orders_bitwise(ElevatorOrders *orders);