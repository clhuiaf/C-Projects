
#include <iostream>

#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() {
    _head = SmartPtr<LLNode>(); // set head to "nulltpr"
    _tail = SmartPtr<LLNode>(); // set tail to "nullptr"
    _size = 0;
}

LinkedList::~LinkedList() {
    SmartPtr<LLNode> curr = _head;
    while (curr) {
        /*
        // Delete the node object, NOT the object inside the node
        SmartPtr<LLNode> next = curr->next;
        // next.unset(); // original
        curr.unset(); // modified
        curr = next;
        */
        curr->prev.unset(); // Break reference cycle, which would otherwise make `SmartPtr` leak memory
        curr = curr->next;
        // unset all node one by one
    }
}

LinkedList::LinkedList(const LinkedList& ll) {
    // Copy constructor that perform deep copy
    _head = SmartPtr<LLNode>();
    _tail = SmartPtr<LLNode>();
    _size = 0;

    // require deep copy
    SmartPtr<LLNode> curr = ll._head;
    while (curr) {
        add(curr->order);
        curr = curr->next;
    }
}

void LinkedList::add(SmartPtr<Order> order) {
    SmartPtr<LLNode> node = SmartPtr<LLNode>{new LLNode(order)}; // ???
    if (!_head) {
        _head = node;
        _tail = node;
    } else {
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }
    _size++;
}

void LinkedList::remove(SmartPtr<Order> order) {
    if (!order) {
        return;
    }
    SmartPtr<LLNode> curr = _head;
    while (curr) {
        if (curr->order == order) {
            if (curr->prev) {
                curr->prev->next = curr->next;
            } else {
                _head = curr->next;
            }
            if (curr->next) {
                curr->next->prev = curr->prev;
            } else {
                _tail = curr->prev;
            }
            curr.unset();
            _size--;
            return;
        }
        curr = curr->next;
    }
}

int LinkedList::length() const{
    return _size;
}

bool LinkedList::isEmpty() const{
    return _size == 0;
}

bool LinkedList::contains(SmartPtr<Order> order) const{
    SmartPtr<LLNode> curr = _head;
    while (curr) {
        if (curr->order == order) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void LinkedList::clear() {
    SmartPtr<LLNode> curr = _head;
    while (curr) {
        /*
        SmartPtr<LLNode> next = curr->next;
        curr.unset();
        curr = next;
        */
        curr->prev.unset(); // Break reference cycle, which would otherwise make `SmartPtr` leak memory
        curr = curr->next;
    }
    _head = SmartPtr<LLNode>();
    _tail = SmartPtr<LLNode>();
    _size = 0;
}

// TODO: Task 2.1
// You only need to implement the accessor for operator[]. 
// It works like a 0-indexed array. Return the element in the linked list if the range is valid. 
// If it is out-of-bound or a negative number, return a SmartPtr instance representing nullptr.
SmartPtr<Order> LinkedList::operator[](int index) const {
    // Within valid range
    if (index >= 0 && index < _size){
        int count = 0;
        SmartPtr<LLNode> curr = _head;
        while (count != index){
            curr = curr->next;
            count++;
        }
        return curr->getOrder();
    }
    // Out of bounds
    else{
        return SmartPtr<Order>();
    }
}


ostream& operator<<(ostream& os, const LinkedList& ll) {
    SmartPtr<LLNode> curr = ll._head;
    os << "Linked List:\t";
    while (curr) {
        os << curr->getOrder() << "\t";
        curr = curr->getNext();
    }
    os << "End of Linked List";
    return os;
}

LinkedList& LinkedList::operator=(const LinkedList& ll) {
    if (this == &ll) {
        return *this;
    }
    clear();
    SmartPtr<LLNode> curr = ll._head;
    while (curr) {
        add(curr->order);
        curr = curr->next;
    }
    return *this;
}