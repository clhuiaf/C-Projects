#include "OrderSystem.h"
#include "Order.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int HASH_TABLE_SIZE = 769;

// TODO: Task 5.1
OrderSystem::OrderSystem() {
// The constructor of the Ordersystem Class. 
// Even though it is a default constructor, we need to give the hash table a size and a hash function.
// For the size, Chris decides to use her lucky number 769, and the hash function is OrderSystem::hashFunc.
    this->ht = HashTable(HASH_TABLE_SIZE, OrderSystem::hashFunc);
}

// TODO: Task 5.1
int OrderSystem::hashFunc(int oid) {
// You should also implement OrderSystem::hashFunc using the following formula:
// oid * oid + 13 * oid - 7
// You need to ensure that the function only returns a value in the range [0, INT_MAX - 1], 
// or a non-negative integer. If it exceeds integer representation, use modulo to map back to the range.
// For example, if the hash calculated is INT_MAX, it will return to 0 since INT_MAX % INT_MAX is 0.
// Note: The header file for INT_MAX has been included for you.
// Note that Signed (not unsigned) integer overflow is undefined in C++. 
// The oid will not exceed 100,000,000. 
// Remember to consider small and large order IDs at the same time.
    long long hash = static_cast<long long>(oid) * oid + 13 * static_cast<long long>(oid) - 7;
    hash = hash % INT_MAX; 
    return hash;
}

// TODO: Task 5.2
OrderSystem::OrderSystem(vector<SmartPtr<Order>> order) {
// The conversion constructor of the OrderSystem class. 
// The required hash function and size should follow Task 5.1.
// You should add all orders inside the system using the addOrder function. 
// order will not contain nullptr.
    this->ht = HashTable(HASH_TABLE_SIZE, OrderSystem::hashFunc);
    for (SmartPtr<Order> o : order) {
        this->addOrder(o);
    }
}

// TODO: Task 5.3
OrderSystem::~OrderSystem() {
// The destructor of the OrderSystem class. 
// You should ensure that all the memory allocated in the system is released. 
// You should not have any memory leak.
}

// TODO: Task 5.4
void OrderSystem::addOrder(SmartPtr<Order> order) {
// Add an order to the system if it does not exist. 
// You should add an order record in the hash table and in both BSTs. 
// order will not contain nullptr. Pay attention to duplicate orders.
// Please read BST.h for more information about the add function.
    if (this->containsOrder(order->getOid())) {
        return;
    }
    this->ht.add(order); // add order to hash table
    this->bst_soup.add(order->getSoup(), order); // add order to BST for soup
    this->bst_spciness.add(order->getSpicyLevel(), order); // add order to BST for spiciness
}

// TODO: Task 5.5
void OrderSystem::removeOrder(SmartPtr<Order> order) {
// Remove an order from the system if it contains this record. 
// Remove the record from the hash table, and from both BSTs. 
// order will not contain nullptr.
// Please read BST.h for more information about the remove function.
    if (!this->containsOrder(order->getOid())) {
        return;
    }
    this->ht.remove(order); // remove order from hash table
    this->bst_soup.remove(order->getSoup(), order); // remove order from BST for soup
    this->bst_spciness.remove(order->getSpicyLevel(), order); // remove order from BST for spiciness
}

bool OrderSystem::containsOrder(int oid) const {
    return bool(this->getOrder(oid));
}

// TODO: Task 5.6
SmartPtr<Order> OrderSystem::getOrder(int oid) const {
// Get the order by their oid. 
// If the record does not exist, return a default-constructed SmartPtr. 
// Note that the OrderSystem::containsOrder(int oid), 
// which checks if the system contains an order with the specified oid, is implemented by calling this function.
    if (!this->ht.contains(oid)) {
        return SmartPtr<Order>();
    }
    return this->ht.get(oid);
}


void OrderSystem::printOrders() const {
    this->ht.printTable();
    this->bst_soup.printTree();
    this->bst_spciness.printTree();
}