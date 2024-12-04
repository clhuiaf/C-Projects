#ifndef __HASHTABLE_SELF_DEF_H__
#define __HASHTABLE_SELF_DEF_H__

#include "LinkedList.h"
#include "SmartPtr.h"
#include "Order.h"

#include <vector>

class HashTable {
    public:
        HashTable() : hashTable(), size(), hash() {}
        HashTable(int size, int (*hash)(int));
        HashTable(const HashTable& ht);
        ~HashTable() = default;

        void add(SmartPtr<Order> order);
        void remove(SmartPtr<Order> order);
        bool contains(int key) const;

        SmartPtr<Order> get(int key) const;
        SmartPtr<Order> operator[](int key) const;
        void printTable() const;
    private:
        std::vector<LinkedList> hashTable;
        int size;
        int (*hash)(int);
};

#endif // __HASHTABLE_SELF_DEF_H__