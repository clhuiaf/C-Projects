#include "user.h"

using namespace std;
const int TOTAL_BATCH_SIZE = 1000;

/**
 * Constructs a new user with the given name.
 *
 * Initially, the user has no bitcoin batches.
 *
 * @param name The name of the user.
 */
User::User(const string &name) : name(name), bitcoinBatches(new const BitcoinBatch* [TOTAL_BATCH_SIZE]), bitcoinBatchCount(0){
    // TODO: Task 1
}

/**
 * Destructs the user.
 *
 * This function should de-allocate all the bitcoin batches of the user.
 */
User::~User() {
    //TODO: Task 5
    for (int i = 0; i < bitcoinBatchCount; i++){
        delete bitcoinBatches[i]; // This call the destructor of BitcoinBatch;
        bitcoinBatches[i] = nullptr;
    }
    delete[] bitcoinBatches;
}


/**
 * Gets the total amount of bitcoin that the user owns.
 *
 * This is the sum of the amounts of all the bitcoin batches of the user.
 *
 * See the documentation of User::bitcoinBatches for more information of user's bitcoin batches.
 *
 * @return The total amount of bitcoin that the user owns.
 */
int User::getBalance() const {
    // TODO: Task 1
    int balance = 0;
    for (int i = 0; i < bitcoinBatchCount; i++){
        balance += bitcoinBatches[i]->amount;
    }
    return balance;
}

/**
 * Adds a bitcoin batch to the user's bitcoin batches.
 *
 * This function re-allocates a larger `bitcoinBatches` array
 * and pushes the new bitcoin batch to the end of the new array.
 * This function should also increment the bitcoin batch count.
 *
 * Note that after calling the function, there should be no memory leak.
 *
 * @param batch The bitcoin batch to be added.
 */
void User::addBitcoinBatch(const BitcoinBatch *batch) { 
    // TODO: Task 2
    bitcoinBatches[bitcoinBatchCount] = batch;
    bitcoinBatchCount++;
}

/**
 * Spend a bitcoin batch from the user's bitcoin batches.
 *
 * This function may have different implementations.
 * However, the bitcoin batch should be removed from the user's bitcoin batches,
 * and the bitcoin batch count should be decremented.
 *
 * Note that after calling the function, there should be no memory leak.
 *
 * If the bitcoin batch isn't in the user's bitcoin batches, this function should do nothing.
 *
 * @param batch The bitcoin batch to be spent.
 */
void User::spend(const BitcoinBatch *batch) {
    // TODO: Task 4
    for (int i = 0; i < bitcoinBatchCount; i++){
        if (bitcoinBatches[i] == batch){
            //delete bitcoinBatches[i]; // Delete the batch directly // Maybe
            for (int j = i; j < bitcoinBatchCount-1; j++){
                bitcoinBatches[j] = bitcoinBatches[j+1];
            }
            bitcoinBatches[bitcoinBatchCount-1] = nullptr;
            bitcoinBatchCount--;
        }
    }
}

//
// PROVIDED FUNCTIONS
//

string User::getName() const {
    return name;
}

const BitcoinBatch **User::getBitcoinBatches() const {
    return bitcoinBatches;
}

int User::getBitcoinBatchCount() const {
    return bitcoinBatchCount;
}
