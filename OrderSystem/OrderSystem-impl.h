#ifndef __ORDERSYSTEM_IMPL_SELF_DEF_H__
#define __ORDERSYSTEM_IMPL_SELF_DEF_H__

#include "OrderSystem.h"

// TODO: Task 5.7
template <typename T>
int OrderSystem::getNumberMixianStat(T start, T end, const BST<T>& tree) const {
// Aggregate the number of mixian orders in the specified range [start, end] in the BST tree, including both start and end.
// You CANNOT introduce extra header files.
// range selection from BST
// The range is inclusive, i.e., if start = 1 and end = 3, you should count the number of mixian orders with key 1, 2, and 3.
// If the range is empty, return 0.
// If the range is invalid, return -1.
    if (start > end) {
        return -1;
    }
    return tree.rangeSelect(start, end).size();
}

// TODO: Task 5.8
template <typename T>
float OrderSystem::getPriceSumStat(T start, T end, const BST<T>& tree) const {
// Aggregate the total revenue of the mixian orders specified in the range [start, end] in the BST tree, including both start and end.
// You CANNOT introduce extra header files.
// range selection from BST
// The range is inclusive, i.e., if start = 1 and end = 3, you should count the number of mixian orders with key 1, 2, and 3.
// If the range is empty, return 0.
// If the range is invalid, return -1.
    if (start > end) {
        return -1;
    }
    float sum = 0;
    for (SmartPtr<Order> order : tree.rangeSelect(start, end)) {
        sum += order->getPrice();
    }
    return sum;
}


#endif // __ORDERSYSTEM_IMPL_SELF_DEF_H__