#include "transaction.h"
#include <iostream>

using namespace std;
const int TOTAL_UNSPENT_SIZE = 1000;

/**
 * Constructs a BitcoinBatch with the given owner and amount.
 *
 * Initialize the fields according to the parameters.
 *
 * @param owner The owner of the batch.
 * @param amount The amount of bitcoin in the batch.
 */
BitcoinBatch::BitcoinBatch(User *owner, const int amount) : owner(owner), amount(amount){
    // TODO: Task 1
}

/**
 * Constructs a Transaction with the parameters.
 *
 * Initialize the fields according to the parameters.
 */
Transaction::Transaction(
    const string &sender,
    const string &receiver,
    const BitcoinBatch **inputs,
    const int inputCount,
    const BitcoinBatch *outputForReceiver,
    const BitcoinBatch *outputForSender
) : sender(sender), receiver(receiver), inputs(inputs), 
    inputCount(inputCount),outputForReceiver(outputForReceiver),outputForSender(outputForSender)
{
    // TODO: Task 1
}

/**
 * Destructs a Transaction.
 *
 * This function should de-allocate either inputs or outputs depending on whether the transaction is pending.
 * If the transaction is pending,
 * it means that the output batches aren't yet added to the receiver and the sender's bitcoin batches.
 * If the transaction isn't pending,
 * it means that the input batches are already removed from the sender's bitcoin batches.
 * Referring to `User::~User`, think about which batches should be de-allocated in each case.
 *
 * Note that the `Transaction::pending` flag is useful to determine whether the transaction is pending or not.
 */
Transaction::~Transaction() {
    //TODO: Task 5
    // If the transaction is pended
    if (!pending) {
        const BitcoinBatch** input = getInputs();
        for (int i = 0; i < getInputCount(); i++){
            delete input[i];
        }
        delete[] inputs; 
    }
    // Inputs elements is removed by mineBlock function
    // So we just deallocate the contiguous boxes 
    else{
        delete outputForReceiver; 
        delete outputForSender;   
    } 
}

/**
 * Calculates the fee of the transaction.
 *
 * The fee of the transaction is the difference between the sum of the input amounts and the sum of the output amounts.
 *
 * The term "fee" refers to the amount of bitcoin that the system charges for the transaction.
 * See `BitcoinSystem::transact` for more information about the fee.
 *
 * @return The fee of the transaction.
 */
int Transaction::getFee() const {
    // TODO: Task 4
    const BitcoinBatch** input_array = getInputs();
    const BitcoinBatch* output_batch_receiver = getOutputForReceiver();
    const BitcoinBatch* output_batch_sender = getOutputForSender();
    int input_amount = 0, output_amount = output_batch_receiver->amount, 
                          change = output_batch_sender->amount, fee;
    int input_count = getInputCount();
    for (int i = 0; i < input_count; i++){
        input_amount += input_array[i]->amount;
    }
    fee = input_amount - output_amount - change;
    return fee;
}

/**
 * Destructs a UnspentBitcoinBatches.
 *
 * It should de-allocate the `unspentBitcoinBatches` array.
 * However, it shouldn't de-allocate the batches in the array.
 * Think of the ownership of the batches,
 * refer to `User::~User` and `Transaction::~Transaction` for more information.
 */
UnspentBitcoinBatches::~UnspentBitcoinBatches() {
    // TODO: Task 5
    // for (int i = 0; i < unspentBitcoinBatchesCount; i++){
    //     delete unspentBitcoinBatches[i];
    // }
}

/**
 * Determines whether the given bitcoin batch is spent.
 *
 * A bitcoin batch is spent if it's not in the `unspentBitcoinBatches` array.
 * Otherwise, it's unspent.
 *
 * @param batch The bitcoin batch to check whether it's spent.
 * @return true if the bitcoin batch is spent, false otherwise.
 */
bool UnspentBitcoinBatches::isSpent(const BitcoinBatch *batch) const {
    // TODO: Task 3
    for (int i = 0; i < unspentBitcoinBatchesCount; i++){
        // Found the bitcoin and it is not spent
        if (unspentBitcoinBatches[i] == batch)
            return false; 
    }
    // The coin is spent
    return true;
}


/**
 * Adds the given bitcoin batch to the unspent bitcoin batches.
 *
 * This function re-allocates a larger `unspentBitcoinBatches` array
 * and pushes the new bitcoin batch to the end of the new array.
 * This function should also increment the unspent bitcoin batch count.
 *
 * Note that after calling the function, there should be no memory leak.
 *
 * @param batch The bitcoin batch to be added.
 */
void UnspentBitcoinBatches::addBatch(const BitcoinBatch *batch) {
    // TODO: Task 2
    if (unspentBitcoinBatches == nullptr) // Dynamic array creation !!
        unspentBitcoinBatches = new const BitcoinBatch* [TOTAL_UNSPENT_SIZE];
    unspentBitcoinBatches[unspentBitcoinBatchesCount] = batch; // Append to the end of the unspent pool
    unspentBitcoinBatchesCount++;
}

/**
 * Spends a given bitcoin batch from the unspent bitcoin batches.
 *
 * This function may have different implementations.
 * However, the bitcoin batch should be removed from the unspent bitcoin batches,
 * and the unspent bitcoin batch count should be decremented.
 *
 * Note that after calling the function, there should be no memory leak.
 *
 * If the bitcoin batch isn't in the unspent bitcoin batches, this function should do nothing.
 *
 * @param batch The bitcoin batch to be spent.
 */
void UnspentBitcoinBatches::spendBatch(const BitcoinBatch *batch) { // Delete?
    // TODO: Task 3
    // The batch is not in the unspent pool -> not found and spent
    for (int i = 0; i < unspentBitcoinBatchesCount; i++){
        if (unspentBitcoinBatches[i] == batch){
            //delete unspentBitcoinBatches[i]; // Delete directly
            //Replace the removed one by moving all element one step forward
            for (int j = i; j < unspentBitcoinBatchesCount-1; j++){ 
                unspentBitcoinBatches[j] = unspentBitcoinBatches[j+1]; 
            }
            // Assign nullptr to the duplicated one (the last one)
            unspentBitcoinBatches[unspentBitcoinBatchesCount-1] = nullptr;
            unspentBitcoinBatchesCount--;
            return;
        }
    }
    // Basically, remove a unspent batch from the pool
}

/**
 * Spend the given amount of bitcoin (of a user) from the unspent bitcoin batches of a user.
 *
 * This function iterates over the unspent bitcoin batches of the user and spends the given amount of bitcoin.
 *
 * If there aren't enough amount of bitcoin of the user to be spent, the function doesn't spend anything and returns -1.
 *
 * If there are enough bitcoins to spend, the function spends the bitcoins batch by batch until the given amount is spent.
 * The function returns the amount of bitcoin left in the last batch, which is effectively the change. 
 *
 * Meanwhile,
 * the spent batches are stored in the `spentBatches` array;
 * the count of spent batches is stored in spentBatchCount.
 *
 * For example, assume there are three batches for a certain user:
 *
 * - Batch 1: 100 bitcoins
 * - Batch 2: 50 bitcoins
 * - Batch 3: 50 bitcoins
 *
 * Since there are three batches for the user, `spentBatches` should be at least the size of 3. // Total size assumption
 *
 * If we spend 125 bitcoins, batch 1 and 2 will be spent, and the remaining amount 25 (= 100 + 50 - 125) will be returned.
 * We don't touch batch 3, because spending batch 1 and 2 is enough for 125 bitcoins.
 *
 * spentBatches will be {Batch 1, Batch 2}, and spentBatchCount will be 2.
 * Note that the order of elements in `spentBatches` should be the same as the order of batches in the user's bitcoin batches.
 *
 * Hint: you can use `UnspentBitcoinBatches::isSpent` to check whether a specific batch is spent.
 * Hint: you can use `UnspentBitcoinBatches::spendBatch` to spend a specific batch.
 *
 * This function is different from `UnspentBitcoinBatches::spendBatch`.
 * This function spends a specific amount of bitcoin from a specific user,
 * while `UnspentBitcoinBatches::spendBatch` spends a specific bitcoin batch.
 *
 * @param user The user from which this function spends the bitcoin.
 * @param amount The amount of which this function spends the bitcoin.
 * @param spentBatches The array to store the batches spent by this function,
 *   should be at least the size of `user->getBitcoinBatchCount()`.
 *   After the function call, the spent batches will be stored in this array.
 * @param spentBatchCount The count reference to store the count of batches spent by this function.
 *   After the function call, the count of spent batches will be stored in this variable.
 * @return The amount of the remaining bitcoin in the last batch spent (change), possibly 0;
 *   or -1 if there aren't enough bitcoins to spend.
 */
int UnspentBitcoinBatches::spend(
    const User *user,
    const int amount,
    const BitcoinBatch **spentBatches,
    int &spentBatchCount
) {
    // TODO: Task 3
    // Count = enough amount to settle output amount + fee
    int count = 0;
    // // Check if the amount is sufficient
    // Check if the user has enough amount (from the pool)
    for (int i = 0; i < unspentBitcoinBatchesCount; i++){
        if (count >= amount)
            break;
        if ((unspentBitcoinBatches[i]->owner == user)){
            count += unspentBitcoinBatches[i]->amount;
        }
    }
    // If the amount is not enought (or not enought for the fee), then leave the function and return -1
    if (count < amount){ // 
        return -1;
    }
    // Since count >= amount , can be zero change
    int change = count - amount;
    /* Loop through the user's batches array to add batches to the spentbaches array
        until the count is <= 0 
    */
    for (int i = 0; count > 0 && i < unspentBitcoinBatchesCount; ){
        if (unspentBitcoinBatches[i]->owner == user){
            spentBatches[spentBatchCount] = unspentBitcoinBatches[i];
            spentBatchCount++;
            count -= unspentBitcoinBatches[i]->amount;
            //problematic
            if (!isSpent(unspentBitcoinBatches[i]))
                spendBatch(unspentBitcoinBatches[i]);
        }
        else{
            i++;
        }

   }   
    return change; // The remaining value in the count is the change
}


//
// PROVIDED FUNCTIONS
//

string Transaction::getSender() const {
    return sender;
}

string Transaction::getReceiver() const {
    return receiver;
}

const BitcoinBatch **Transaction::getInputs() const {
    return inputs;
}

int Transaction::getInputCount() const {
    return inputCount;
}

const BitcoinBatch *Transaction::getOutputForReceiver() const {
    return outputForReceiver;
}

const BitcoinBatch *Transaction::getOutputForSender() const {
    return outputForSender;
}
