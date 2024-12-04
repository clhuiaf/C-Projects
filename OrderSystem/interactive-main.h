#ifndef __INTERACTIVE_MAIN_SELF_DEF_H__
#define __INTERACTIVE_MAIN_SELF_DEF_H__

#include "OrderSystem.h"
#include "SmartPtr.h"
#include "Order.h"
#include "BST.h"
#include "HashTable.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class InteractiveMain {
    public:
        InteractiveMain(string path);
        ~InteractiveMain() = default;
        void run();
    private:
        string path;
        vector<SmartPtr<Order>> orders;
};

#endif // __INTERACTIVE_MAIN_SELF_DEF_H__
