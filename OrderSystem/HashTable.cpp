#include "HashTable.h"

// Note: In this stage, to verify your implementations of HashTable with the public test cases, 
// we suggest you to first implement the OrderSystem::hashFunc hash function in Task 5.1
// TODO: Task 4.1
HashTable::HashTable( int size,  int (*hash)(int)) {
// The constructor of the HashTable class takes size, which is the number of cells in the hash table, 
// and hash, which is the hash function. 
// You should initialize the std::vector<LinkedList> hashTable with size cells. 
// You can assume that the hash function will always return [0, INT_MAX - 1].
// Note: HashTable definitely cannot have SmartPtr<Order> that contains nullptr, otherwise we cannot hash its order ID.
    hashTable.resize(size); // Resize the hashTable
    this->size = size; // Set the size of the hash table
    this->hash = hash; // Set the hash function
}

// TODO: Task 4.2
HashTable::HashTable(const HashTable& ht) {
// The copy constructor of the HashTable class should deep copy every content in the object ht.
    // Deep copy the hashTable
    hashTable.resize(ht.hashTable.size()); // Resize the hashTable
    for (int i = 0; i < ht.hashTable.size(); ++i) {
        hashTable[i] = ht.hashTable[i]; // Copy the linked list
    }
    size = ht.size; // Copy the size
    hash = ht.hash; // Copy the hash function
}

// TODO: Task 4.3
void HashTable::add(SmartPtr<Order> order) {
//Add the order to the hash table if it does not already exist in the table. 
// You should use the oid of the Order as the key to find the cell in the table. 
// Add the order to the corresponding LinkedList. 
// The index of the hash table is determined by the hash result % size of the table. 
// Note that there should be no duplicated orders in the hash table. order will not contain nullptr.
    int key = order->getOid(); // Get the key of the order
    int index = hash(key) % size; // Get the index of the hash table
    if (!hashTable[index].contains(order)) { // Check if the order is already in the hash table
        hashTable[index].add(order); // Add the order to the linked list
    }
}

// TODO: Task 4.4
SmartPtr<Order> HashTable::get(int key) const {
// Get the order with the same key (i.e., order ID) in the hash table. 
// If the key does not exist in the hash table, return a default-constructed SmartPtr<Order> object.
// Note the HashTable::contains(int key), 
// which checks whether this is an order in the hash table containing the specified key, is implemented by calling this function.
    int index = hash(key) % size; // Get the index of the hash table
    // Iterate through the linked list, to check if any order with the same key i.e order ID exists
    for (int i = 0; i < hashTable[index].length(); ++i) {
        SmartPtr<Order> order = hashTable[index][i]; // Get the order
        if (order->getOid() == key) { // Check if the order ID is the same as the key
            return order; // Return the order
        }
    }
    // The key does not exist in the hash table
    return SmartPtr<Order>(); // Return a default-constructed SmartPtr<Order> object
}

// TODO: Task 4.5
void HashTable::remove(SmartPtr<Order> order) {
// Remove the order with the same key in the hash table. 
// order will not contain nullptr. 
// You do not have to delete empty LinkedLists after removing the specified order.
    int key = order->getOid(); // Get the key of the order
    int index = hash(key) % size; // Get the index of the hash table
    // check if the order is in the hash table 
    if (!hashTable[index].contains(order)) { // Check if the order is in the hash table
        return; // Return if the order is not in the hash table
    }
    hashTable[index].remove(order); // Remove the order from the linked list
}

bool HashTable::contains(int key) const {
    return bool(this->get(key));
}

// TODO: Task 4.6
SmartPtr<Order> HashTable::operator[](int key) const {
// Return the order record if the corresponding oid exists. 
// If it does not exist in the hash table, return a default-constructed SmartPtr<Order> instance.
    return this->get(key); // Return the order with the same key
}

void HashTable::printTable() const {
    // Print the table
    std::cout << "HashTable:" << std::endl;
    for (int i = 0; i < hashTable.size(); ++i) {
        std::cout << "Index: " << i << ": ";
        std::cout << hashTable[i] << std::endl;
    }
}

