#ifndef __LINKEDLIST_SELF_DEF_H__
#define __LINKEDLIST_SELF_DEF_H__

#include "SmartPtr.h"
#include "Order.h"

#include <iostream>
#include <stdexcept>

using namespace std;
// Store Order Pointer in each node
class LLNode {
    public:
        LLNode(SmartPtr<Order> order) {
            if (!order) {
                throw invalid_argument{"You are providing a nullptr order!"};
            }
            this->order = order;
            this->next = SmartPtr<LLNode>();
            this->prev = SmartPtr<LLNode>();
        }
        ~LLNode() = default;
        
        SmartPtr<Order> getOrder() {
            return this->order;
        }
        SmartPtr<LLNode> getNext() {
            return this->next;
        }
        SmartPtr<LLNode> getPrev() {
            return this->prev;
        }
        
        void setNext(SmartPtr<LLNode> next) {
            this->next = next;
        }
        void setPrev(SmartPtr<LLNode> prev) {
            this->prev = prev;
        }
    
    private:
        SmartPtr<Order> order;
        SmartPtr<LLNode> next;
        SmartPtr<LLNode> prev;
        friend class LinkedList;
        friend class SmartPtr<LLNode>;
};

// LinkedList container for Order pointers
class LinkedList {
    public:
        LinkedList();
        LinkedList(const LinkedList& ll);
        ~LinkedList();
        void add(SmartPtr<Order> order);
        void remove(SmartPtr<Order> order);
        int length() const;
        bool isEmpty() const;
        bool contains(SmartPtr<Order> order) const;
        void clear();

        // TODO: Implement this two functions
        SmartPtr<Order> operator[](int index) const;


        friend std::ostream& operator<<(std::ostream& os, const LinkedList& ll);
        LinkedList& operator=(const LinkedList& ll);


    private:
        SmartPtr<LLNode> _head;
        SmartPtr<LLNode> _tail;
        int _size;
        SmartPtr<LLNode> find(SmartPtr<Order> order) {
            SmartPtr<LLNode> cur = this->_head;
            while (cur) {
                if (cur->getOrder() == order) {
                    return cur;
                }
                cur = cur->getNext();
            }
            return SmartPtr<LLNode>();
        }
};

#endif // __LINKEDLIST_SELF_DEF_H__