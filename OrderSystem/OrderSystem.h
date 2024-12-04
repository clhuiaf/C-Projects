#ifndef __ORDER_SYSTEM_SELF_DEF_H__
#define __ORDER_SYSTEM_SELF_DEF_H__

#include "Order.h"
#include "SmartPtr.h"
#include "LinkedList.h"
#include "BST.h"
#include "HashTable.h"

#include <vector>
#include <climits> // modified

class OrderSystem {
    public:
        static int hashFunc(int oid);
        // Constructor & Destructor
        OrderSystem();
        OrderSystem(vector<SmartPtr<Order>> order);
        OrderSystem(const OrderSystem& os) = delete;
        ~OrderSystem();

        void addOrder(SmartPtr<Order> order);
        void removeOrder(SmartPtr<Order> order);
        bool containsOrder(int oid) const;
        SmartPtr<Order> getOrder(int oid) const;

        // Get number of mixian included in that range
        template <typename T>
        int getNumberMixianStat(T start, T end, const BST<T>& tree) const;

        // Get the total revenue of mixian sold in that range
        template <typename T>
        float getPriceSumStat(T start, T end, const BST<T>& tree) const;
        void printOrders() const;
        const BST<int>& getBSTSpiciness() const {
            return this->bst_spciness;
        }
        const BST<Soup>& getBSTSoup() const {
            return this->bst_soup;
        }
    private:
        BST<int> bst_spciness;
        BST<Soup> bst_soup;
        HashTable ht;
};

#include "OrderSystem-impl.h"

#endif // __ORDER_SYSTEM_SELF_DEF_H__