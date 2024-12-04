#ifndef USER_H
#define USER_H

#include "transaction.h"

using namespace std;

class BitcoinBatch;

/**
 * Represents a user in the Bitcoin system.
 */
class User {
public:
    explicit User(const string &name); //str:name to User

    ~User(); // Destructor


    int getBalance() const; // get the total balance

    void addBitcoinBatch(const BitcoinBatch *batch); // Add a ptr to a batch to the dynamic batch ptrs array

    void spend(const BitcoinBatch *batch); // Remove a ptr to a batch from the dynamic batch ptrs array


    // PROVIDED FUNCTIONS

    string getName() const; // name getter function

    const BitcoinBatch **getBitcoinBatches() const; // BitcoinBatch dynamic ptrs array getter

    int getBitcoinBatchCount() const; // number of bitcoin batches getter

private:
    /**
    * The name of the user.
    *
    * You may assume that the name is unique.
    */
    const string name;

    /**
    * The bitcoin batches of the user.
    *
    * This is a dynamic array, and it's re-allocated whenever the number of the bitcoin batches increases.
    */
    const BitcoinBatch **bitcoinBatches; // Dynamic array that stores pointers to const BitcoinBatch objects
    /**
    * The number of bitcoin batches of the user.
    *
    * It's always equal to the *effective* size of the `bitcoinBatches` array.
    */
    int bitcoinBatchCount;
};

#endif
