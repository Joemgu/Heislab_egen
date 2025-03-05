#include "../inc/order_handler.h"


void ElevatorOrders_init(ElevatorOrders *orders)
{
    orders->inside_orders = 0;
    orders->unserved_orders = 0; 
    orders->up_orders = 0;
    orders->down_orders = 0;
}

void update_new_order(ElevatorOrders *orders, int floor, Order_type_t order_type) {
    orders->unserved_orders |= (1 << floor) & UINT4_MASK;
    
    if (order_type == ORDER_UP) {
        orders->up_orders |= (1 << floor) & UINT4_MASK;
    } else if (order_type == ORDER_DOWN) {
        orders->down_orders |= (1 << floor) & UINT4_MASK;
    }
    else if (order_type == ORDER_CAB) {
        orders->inside_orders |= (1 << floor) & UINT4_MASK;
    }
    print_elevator_orders_bitwise(orders);
}

void mark_order_served(ElevatorOrders *orders, int floor) {
    orders->unserved_orders &= ~(1 << floor) & UINT4_MASK;
    orders->inside_orders &= ~(1 << floor) & UINT4_MASK;
    orders->up_orders &= ~(1 << floor) & UINT4_MASK;
    orders->down_orders &= ~(1 << floor) & UINT4_MASK;
}

uint8_t get_next_destination_bit_map(ElevatorOrders *orders, int current_floor, bool moving_up, bool elevator_is_moving) {
        // First, check for orders in the current moving direction
    if((!elevator_is_moving)) {
        if(orders->unserved_orders & (1 << current_floor)){
            return (1 << current_floor);
        }
    }
    if (moving_up) {
        // Check upwards from the current floor
        for (int floor = current_floor+1; floor <= 3; floor++) {
            if (orders->unserved_orders & (1 << floor)) {
                if (orders->up_orders & (1 << floor) || orders->inside_orders & (1 << floor)) {
                    return (1 << floor);  // Return the next destination bit
                }
            }
        }
        
        // Now check for any "down" or "up" orders below while still moving up
        for (int floor = current_floor+1; floor <=3; floor++) {
            if (orders->unserved_orders & (1 << floor)) {
                if (orders->down_orders & (1 << floor) || orders->up_orders & (1 << floor) || orders->inside_orders & (1 << floor)) {
                    return (1 << floor);  // Return the next destination bit
                }
            }
        }
    } else {
        // Check downwards from the current floor
        for (int floor = current_floor+-1; floor >= 0; floor--) {
            if (orders->unserved_orders & (1 << floor)) {
                if (orders->down_orders & (1 << floor) || orders->inside_orders & (1 << floor)) {
                    return (1 << floor);  // Return the next destination bit
                }
            }
        }

        // Now check for any "up" or "down" orders above while still moving down
        for (int floor = current_floor-1; floor >= 0; floor--) {
            if (orders->unserved_orders & (1 << floor)) {
                if (orders->up_orders & (1 << floor) || orders->down_orders & (1 << floor) || orders->inside_orders & (1 << floor)) {
                    return (1 << floor);  // Return the next destination bit
                }
            }
        }
    }

    return 0x00;  // No more orders
}



int get_highest_bit(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        if (value & (1 << i)) {
            return i;  // Return the index of the highest bit set
        }
    }
    return -1; // Return -1 if no bits are set
}

void print_bitwise(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);  // Print each bit, starting from the most significant bit
    }
    printf("\n");
}

void print_elevator_orders_bitwise(ElevatorOrders *orders) {
    printf("Unserved orders bitmask: ");
    print_bitwise(orders->unserved_orders);

    printf("Up orders bitmask:       ");
    print_bitwise(orders->up_orders);

    printf("Down orders bitmask:     ");
    print_bitwise(orders->down_orders);

    printf("Inside orders bitmask:   ");
    print_bitwise(orders->inside_orders);
}

