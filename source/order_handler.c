#include "../inc/order_handler.h"

void ElevatorOrders_init(ElevatorOrders *orders)
{
    orders->inside_orders = 0;
    orders->unserved_orders = 0; 
    orders->up_orders = 0;
}

void update_new_order(ElevatorOrders *orders, int floor, Order_type_t order_type) {
    // Check if an order for the floor already exists
    if ((orders->unserved_orders & (1 << floor)) != 0) {
        return;  // No need to update if an order already exists
    }

    orders->unserved_orders |= (1 << floor) & UINT4_MASK;
    
    if (order_type == ORDER_UP) {
        orders->up_orders |= (1 << floor) & UINT4_MASK;
    } else if (order_type == ORDER_DOWN) {
        orders->up_orders &= ~(1 << floor) & UINT4_MASK;  // Clear UP flag
    }

    if (order_type == ORDER_CAB) {
        orders->inside_orders |= (1 << floor) & UINT4_MASK;
    }
}

void mark_order_served(ElevatorOrders *orders, int floor) {
    orders->unserved_orders &= ~(1 << floor) & UINT4_MASK;
    orders->inside_orders &= ~(1 << floor) & UINT4_MASK;
    orders->up_orders &= ~(1 << floor) & UINT4_MASK;
}

uint8_t get_next_destination_bit_map(ElevatorOrders *orders, int current_floor, bool moving_up) {

    if (moving_up) {
        for (int floor = current_floor; floor < 4; ++floor) {
            if (orders->unserved_orders & (1 << floor)) {
                if (orders->up_orders & (1 << floor) || orders->inside_orders & (1 << floor)) {
                    return (1 << floor);
                }
            }
        }
    } else {
        for (int floor = current_floor; floor >= 0; --floor) {
            if (orders->unserved_orders & (1 << floor)) {
                if (!(orders->up_orders & (1 << floor)) || orders->inside_orders & (1 << floor)) {
                    return (1 << floor);
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
