#include <iostream>
#include "bitcoin.h"

using namespace std;
const int TOTAL_USER_SIZE = 1000;
const int PENDING_POOL_SIZE = 1000;

/**
 * The destructor of the BitcoinSystem class.
 *
 * All the memory allocated for the blockchain, unspent bitcoin batches, users, and pending transactions
 * should be deallocated in this function.
 */

void deleteTransactionList(TransactionNode* node) {
    while (node != nullptr) {
        TransactionNode* temp = node;
        node = node->next; // Move to the next node
        delete temp;       // Delete the current node
    }
}

void deleteBlockList(Block* block) {
    while (block != nullptr) {
        Block* temp = block;
        block = block->next; // Move to the next block
        deleteTransactionList(temp->getHead()); // Delete the transaction list in the block
        delete temp; // Delete the current block
    }
}

void deleteBlockchain(Blockchain* blockchain) {
    deleteBlockList(blockchain->getHead()); // Delete the block list
    delete blockchain; // Delete the blockchain itself
}


BitcoinSystem::~BitcoinSystem() {
    // TODO: Task 5
    for (int i = 0; i < pendingTransactionCount; i++) {
        delete pendingTransactions[i]; // Call Transaction destructor // Del input
    }
    delete [] pendingTransactions;

    for (int i = 0; i < userCount; i++) {
        delete users[i]; // Call Users' destructor  // Del output
    }
    delete [] users; // Del user

    delete unspentBitcoinBatches; 

    deleteBlockchain(blockchain);

    //delete blockchain; // Del records
}


/**
 * Adds a new user with given name to the Bitcoin system.
 *
 * This function re-allocates a larger `users` array
 * and pushes the new user to the end of the new array.
 * This function should also increment the user count.
 *
 * Note that after calling the function, there should be no memory leak.
 *
 * You may assume that the name of the user is unique.
 *
 * @param name The name of the user to be added.
 */
void BitcoinSystem::addUser(const string &name) {
    // TODO: Task 1
    if (users == nullptr)
        users = new User*[TOTAL_USER_SIZE]; // Pre-allocate the array with enough size
    users[userCount] = new User(name); // REMEMBER TO DELETE!!
    userCount++;
}

/**
 * Gets the user with the given name.
 *
 * This function iterates over the user array and returns the user with the given name.
 * If the user with the given name isn't found, the function returns nullptr.
 *
 * You may assume that the name of the user is unique.
 *
 * @param name The name of the user to be found.
 * @return The user with the given name, or nullptr if the user isn't found.
 */
User *BitcoinSystem::getUser(const string &name) const {
    // TODO: Task 2
    for (int i = 0; i < userCount; i++){
        // The user is found
        if (users[i]->getName() == name)
            return users[i];
    }
    // The user is not found
    return nullptr;
}

/**
 * Adds a certain amount of bitcoin to the user with the given name.
 *
 * First, the function finds the user with the given name.
 * If the user isn't found, the function prints "User not found" and returns.
 *
 * Then, the function creates a new bitcoin batch with the user as the owner with the given amount.
 *
 * Last, the function adds the created bitcoin batch to
 * the user's bitcoin batches and also the unspent bitcoin batches.
 *
 * You may assume that the name of the user is unique.
 *
 * @param name The name of the user to add bitcoin.
 * @param amount The amount of bitcoin to be added.
 */
void BitcoinSystem::addBitcoinToUser(const string &name, const int amount) const {
    // TODO: Task 2
    User * user_ptr = getUser(name);
    if (user_ptr == nullptr){
        cout << "User not found" << endl;
        return;
    }
    BitcoinBatch* new_batch = new BitcoinBatch(user_ptr, amount); // Dynamic Object created !!
    user_ptr->addBitcoinBatch(new_batch); // Add to user's bag
    unspentBitcoinBatches->addBatch(new_batch); // Add to unspent pool
}

/**
 * Adds a new transaction to the pending transactions array.
 *
 * This function re-allocates a larger `pendingTransactions` array
 * and pushes the new transaction to the end of the new array.
 * This function should also increment the pending transaction count.
 *
 * Note that after calling the function, there should be no memory leak.
 *
 * @param transaction The transaction to be added.
 */
void BitcoinSystem::addPendingTransaction(Transaction *transaction) {
    // TODO: Task 3
    pendingTransactions[pendingTransactionCount] = transaction;
    pendingTransactionCount++;
}

/**
 * Removes a transaction from the pending transactions.
 *
 * This function may have different implementations.
 * However, the transactions should be removed from the pending transactions,
 * and the pending transaction count should be decremented.
 *
 * Also, it sets the transaction's `pending` flag to false,
 * to indicate that the transaction is no longer pending.
 *
 * If the transaction isn't found in the pending transactions array, the function does nothing.
 *
 * Note that after calling the function, there should be no memory leak.
 *
 * @param transaction The transaction to be removed.
 */
void BitcoinSystem::removePendingTransaction(Transaction *transaction) {
    // TODO: Task 4
    for (int i = 0; i < pendingTransactionCount; i++){
        if (pendingTransactions[i]->pending == false && pendingTransactions[i] == transaction){
            //delete pendingTransactions[i]; // Delete directly
            for (int j = i; j < pendingTransactionCount; j++){
                pendingTransactions[j] = pendingTransactions[j+1];
            }
            pendingTransactions[pendingTransactionCount-1] = nullptr;
            pendingTransactionCount--;
            return;
        }
    }
} // Destructor del

/**
 * Selects one pending transaction with the highest fee.
 *
 * This function is used in the `mineBlock` function to select the transactions with the highest fees.
 *
 * If there are no pending transactions, the function returns nullptr.
 *
 * You may assume that there are no two transactions with the same fee.
 *
 * @return The pending transaction with the highest fee.
 */
Transaction *BitcoinSystem::selectPendingTransaction() const {
    // TODO: Task 4
    // If no pending trasaction, return nullptr
    if (pendingTransactionCount == 0)
        return nullptr;
    Transaction * highest_transaction = nullptr;
    // iterate the pool to find out which has highest fee
    for (int i = 0; i < pendingTransactionCount; i++){
        // Set the first item as the highest trasaction first
        if (highest_transaction == nullptr){
            highest_transaction = pendingTransactions[i];
            continue;
        }
        //See if the latter transactions have higher fee , update the highest_transaction if yes
        if (pendingTransactions[i]->getFee() > highest_transaction->getFee())
            highest_transaction = pendingTransactions[i];
    }
    // Remove the transaction with highest fee from the pending pool
    // removePendingTransaction(highest_transaction); // Since its const member function , no modification
    return highest_transaction;
}

/**
 * Transacts from sender to receiver with the given amount and fee.
 *
 * First, the function finds the users with the given senderName and receiverName.
 * If either of the users isn't found, the function prints "User not found" and returns.
 * Hint: you may make use of the `BitcoinSystem::getUser` function in this step.
 *
 * Then, the function tries to spend the amount and fee from the sender's bitcoin batches.
 * If there aren't enough bitcoin batches from sender to cover the amount and fee,
 * the function prints "Insufficient unspent bitcoin batches" and returns.
 * Hint: you may make use of the `UnspentBitcoinBatches::spend` function in this step.
 * The spent batches become the inputs of the transaction.
 *
 * Then, the function creates two outputs: one for the receiver and one for the sender.
 * For the receiver, the function creates a BitcoinBatch with the receiver user and the amount.
 * For the sender, the function creates a BitcoinBatch with the sender user and the change.
 * You may refer to `UnspentBitcoinBatches::spend` for more information for the change
 * Note that even if the change is zero, the function should still create a BitcoinBatch of amount 0 for the sender.
 *
 * Last, the function creates the transaction with the inputs and the outputs described preceding,
 * and add the transaction to the pending transactions.
 * Hint: you may make use of the `BitcoinSystem::addPendingTransaction` function in this step.
 *
 * After all, the function prints "Transaction added to pending transactions".
 *
 * @param senderName The name of the sender user.
 * @param receiverName The name of the receiver user.
 * @param amount The amount to be sent from the sender to the receiver.
 * @param fee The transaction fee to be paid by the sender.
 */
void BitcoinSystem::transact(const string &senderName, const string &receiverName, const int amount, const int fee) {
    // TODO: Task 3
    // Get users' pointers
    User* sender = getUser(senderName);
    User* receiver = getUser(receiverName);
    // User not found and return 
    if (sender == nullptr || receiver == nullptr){
        cout << "User not found" << endl;
        return;
    }
    // Using the spent batches of the sender to create input array (At least his/her total batch size)
    const BitcoinBatch **input = new const BitcoinBatch*[sender->getBitcoinBatchCount()]; // Dynamic object !!
    int inputCount = 0;
    // Calculate the change for sender while removing the spent batches from the pool
    int change = unspentBitcoinBatches->spend(sender,(amount+fee),input,inputCount);
    // If the sender doesn't have enought money to cover both amount and fee, then return the program
        // if (fee == 3)
        // cout << "test" << endl;
    if (change == -1){
        cout << "Insufficient unspent bitcoin batches" << endl;
        //delete [] input; // Deletion // needa edit
        return;
    }
    // Create output batch and change batch for the receiver and sender respectively
    const BitcoinBatch * output = new BitcoinBatch(receiver,amount); // Dynamic Object!!
    const BitcoinBatch * change_for_sender = new BitcoinBatch(sender,change); // Dynamic Object!!
    // Create new transaction object
    // Pending status of a transaction object is by default pending
    Transaction * new_transaction = new Transaction(senderName,receiverName,input, // Dynamic Object!!
                                                    inputCount,output,change_for_sender); // Input and output will remember the dynamic objs
    // Add the newly created transaction object to the pending pool waiting for mining
    if (pendingTransactions == nullptr)
        pendingTransactions = new Transaction*[PENDING_POOL_SIZE];
    pendingTransactions[pendingTransactionCount] = new_transaction; // New dynamic transaction object is recorded in the pending pool;
    pendingTransactionCount++;
    cout << "Transaction added to pending transactions" << endl;
}

/**
 * Mines a block with the three transactions with the highest fees.
 *
 * The term "mine" refers to the process of converting the pending transactions into a block,
 * that is, effectively confirming a pending transaction.
 * The block is then added to the blockchain to record the transactions in the blockchain.
 *
 * First, the function selects the three transactions with the highest fees from the pending transactions.
 * If there are less than three pending transactions, the function selects all the pending transactions.
 * If there are no pending transactions, the function prints "No pending transactions" and returns.
 * You may assume that there are no two transactions with the same fee.
 * Hint: you may make use of the `BitcoinSystem::selectPendingTransaction` function in this step.
 * Hint: you may make use of the `BitcoinSystem::removePendingTransaction` function in this step.
 *
 * Then, the function creates a block with the selected transactions and adds the block to the blockchain.
 *
 * Last, the function updates the user's bitcoin batches.
 * This is because the transaction is now confirmed from the blockchain,
 * so the inputs of the transaction are spent from the user (owner), // Remove the money from sender's bag
 * and the outputs of the transaction are added to the user (owner)'s bitcoin batches. // Add money to receiver's bag
 *
 * That is, for each transaction:
 *
 * - The function iterates over the inputs and spends them from the inputs' owners.
 * - The function adds the output to the receivers' bitcoin batches.
 * - The function adds the output (change) to the sender's bitcoin batches.
 *
 * Since the outputs are now confirmed, which means the user can now spend them,
 * the function also adds the outputs to the unspent bitcoin batches.
 *
 * After all, the function prints "Block mined".
 */
void BitcoinSystem::mineBlock() {
    // TODO: Task 4
    // Create a new dynamic block
    Block * new_block = new Block;
    // Return if no pending transaction 
    if (pendingTransactionCount == 0){
        cout << "No pending transactions" << endl;
        delete new_block;
        return;
    }
    // less than three pending transaction 
    else if (pendingTransactionCount < 3){
        while (pendingTransactionCount > 0){
            // Ranging from the highest to low pay
            Transaction * highest_transaction = selectPendingTransaction();
            highest_transaction->pending = false; // Change the transaction status
            new_block->addTransaction(highest_transaction);
            removePendingTransaction(highest_transaction); // Remove from the pending pool
        }
    }
    else{
        // At least three pending transaction // Loop three time the process
        for (int i = 0; i < 3; i++){
            Transaction * highest_transaction = selectPendingTransaction();
            //cout << highest_transaction->getFee() << endl;
            highest_transaction->pending = false; // Change the transaction status
            new_block->addTransaction(highest_transaction);
            removePendingTransaction(highest_transaction); // Remove from the pending pool
        }
    }
    // The transaction chain is done and added to the block
    // Now add the block to the blockchain
    blockchain->addBlock(new_block);
    // Update users batches by referring the transaction records
    TransactionNode * transaction_ll_head = new_block->getHead(); // getTail()?
    for (TransactionNode * p = transaction_ll_head; p != nullptr; p = p->next){
        // The transaction recorded users' information so that we can create new batch for them using these info.
        // Get sender and receiver names 
        string sender = p->transaction->getSender();
        string receiver = p->transaction->getReceiver();
        // Get sender and receiver pointers
        User* sender_ptr = getUser(sender);
        User* receiver_ptr = getUser(receiver);
        // Get amounts for their batches respectively
        int sender_output_amount = p->transaction->getOutputForSender()->amount;
        int receiver_output_amount = p->transaction->getOutputForReceiver()->amount;
        // Get the input batches array and its count
        const BitcoinBatch ** input_array = p->transaction->getInputs();
        int input_count = p->transaction->getInputCount();
        // Remove money from sender's bag
        for (int i = 0; i < input_count; i++){ // Delete User's inputs
            sender_ptr->spend(input_array[i]); // Really can delete since no others hold it I guess
        }
        // Transfer money to their accounts
        addBitcoinToUser(sender,sender_output_amount); // Create dynamic batch in this function
        addBitcoinToUser(receiver,receiver_output_amount);
        // Get the addresses of the new batches
        // const BitcoinBatch* new_batch_sender = sender_ptr->getBitcoinBatches()[sender_ptr->getBitcoinBatchCount()];
        // const BitcoinBatch* new_batch_receiver = receiver_ptr->getBitcoinBatches()[receiver_ptr->getBitcoinBatchCount()];
        // // Add the new batches to the unspent pool
        // unspentBitcoinBatches->addBatch(new_batch_sender);
        // unspentBitcoinBatches->addBatch(new_batch_receiver);
    }
    // cout << pendingTransactionCount << endl;
    cout << "Block mined" << endl;
}

//
// PROVIDED FUNCTIONS
//

void BitcoinSystem::printUsers() const {
    cout << "------------ Users ------------" << endl;
    for (int i = 0; i < userCount; i++) {
        cout << "User: " << users[i]->getName() << "\t";
        cout << "Balance: " << users[i]->getBalance() << endl;
    }
    cout << "-------------------------------" << endl;
}

void BitcoinSystem::printBlockchain() const {
    cout << "------------ Blockchain ------------" << endl;
    cout << "Blockchain length: " << blockchain->getLength() << endl;
    Block *current = blockchain->getHead();
    while (current != nullptr) {
        cout << "Block" << endl;
        TransactionNode *transactionNode = current->getHead();
        while (transactionNode != nullptr) {
            const Transaction *transaction = transactionNode->transaction;
            cout << "Transaction from " << transaction->getSender() << " to " << transaction->getReceiver() << endl;
            for (int i = 0; i < transaction->getInputCount(); i++) {
                    //cout << transaction->getSender() << "TEST" << endl;
                cout << "Input " << i << ": " << transaction->getInputs()[i]->owner->getName() << " " << transaction->
                        getInputs()[i]->amount << endl;
            }
            cout << "Output " << 0 << ": " << transaction->getOutputForReceiver()->owner->getName() << " " <<
                    transaction->
                    getOutputForReceiver()->amount << endl;
            cout << "Output " << 1 << ": " << transaction->getOutputForSender()->owner->getName() << " " << transaction
                    ->
                    getOutputForSender()->amount << endl;
            transactionNode = transactionNode->next;
        }
        current = current->next;
    }
    cout << "-----------------------------------" << endl;
}

void BitcoinSystem::printPendingTransactions() const {
    cout << "------------ Pending Transactions ------------" << endl;
    for (int i = 0; i < pendingTransactionCount; i++) {
        const Transaction *transaction = pendingTransactions[i];
        cout << "Transaction from " << transaction->getSender() << " to " << transaction->getReceiver() << endl;
        for (int j = 0; j < transaction->getInputCount(); j++) {
            cout << "Input " << j << ": " << transaction->getInputs()[j]->owner->getName() << " " << transaction->
                    getInputs()[j]->amount << endl;
        }
        cout << "Output " << 0 << ": " << transaction->getOutputForReceiver()->owner->getName() << " " << transaction->
                getOutputForReceiver()->amount << endl;
        cout << "Output " << 1 << ": " << transaction->getOutputForSender()->owner->getName() << " " << transaction->
                getOutputForSender()->amount << endl;
    }
    cout << "---------------------------------------------" << endl;
}
