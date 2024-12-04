#include "Order.h"
#include <iostream>
ostream& operator<<(ostream& os, const Order& order) {
    // TODO
    os << "Order ID: " << order.getOid() << ", Price: " << order.getPrice();
    return os;
}