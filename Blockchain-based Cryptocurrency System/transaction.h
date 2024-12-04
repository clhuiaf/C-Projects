#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "user.h"

using namespace std;

class User;

/**
 * A class representing a batch of bitcoins.
 *
 * A batch is the smallest unit of bitcoins that can be transferred in a transaction.
 *
 * A batch is created if and only if one of the following happens:
 * - The bitcoin system adds some amount of bitcoin to a user directly
 *   via the `BitcoinSystem::addBitcoinToUser` function.
 * - A pending transaction has been created, and new batches are created as the output of the transaction,
 *   via the `BitcoinSystem::transact` function.
 */
class BitcoinBatch {
public:
    BitcoinBatch(User *owner, int amount);

    /**
    * The owner of the batch.
    *
    * A user owns a batch if the user has received the batch in a transaction as output,
    * or if some amount of bitcoin is added to the user directly by the bitcoin system.
    */
    User *const owner; // Address is fixed

    /**
    * The amount of bitcoin in the batch.
    *
    * To transfer another amount of bitcoin, they must transfer the whole batch,
    * and during the transaction, the bitcoin system creates a new batch as the change back to the sender.
    */
    const int amount;
};

/**
 * A class representing a transaction in the Bitcoin system.
 *
 * A transaction has a sender and a receiver.
 * The sender sends bitcoins to the receiver.
 *
 * A transaction sends bitcoins in batches.
 * It has a list of input bitcoin batches.
 * The term "input" refers to the batch of bitcoins that the sender sends.
 * It has an output bitcoin batch for the receiver,
 * and the amount of bitcoin in the batch is the amount that the sender wants to send to the receiver.
 * It has another output bitcoin batch for the sender,
 * and the amount of bitcoin in the batch is the change back to the sender.
 */
class Transaction {
public:
    Transaction(
        const string &sender,
        const string &receiver,
        const BitcoinBatch **inputs,
        int inputCount,
        const BitcoinBatch *outputForReceiver,
        const BitcoinBatch *outputForSender
    );

    ~Transaction();

    int getFee() const;


    // PROVIDED FUNCTIONS

    string getSender() const;

    string getReceiver() const;

    const BitcoinBatch **getInputs() const;

    int getInputCount() const;

    const BitcoinBatch *getOutputForReceiver() const;

    const BitcoinBatch *getOutputForSender() const;

    /**
     * The boolean flag indicating whether the transaction is pending.
     *
     * Hint: the flag is useful for the destructor.
     */
    bool pending = true;

private:
    /**
     * The name of the sender of the transaction.
     */
    const string sender;
    /**
     * The name of the receiver of the transaction.
     */
    const string receiver;

    /**
     * The input bitcoin batches of the transaction.
     */
    const BitcoinBatch **const inputs; // The pointer itselt cannot change address , but we can add elements 
    /**
     * The number of input bitcoin batches of the transaction.
     *
     * It's equal to the *effective* size of the `inputs` array.
     */
    const int inputCount; // Length of inputs

    /**
     * The output of the transaction for the transaction receiver.
     *
     * The amount of bitcoin in the batch is the amount that the sender wants to send to the receiver.
     */
    const BitcoinBatch *const outputForReceiver;
    /**
     * The output of the transaction for the transaction sender.
     *
     * The amount of bitcoin in the batch is the change back to the sender.
     */
    const BitcoinBatch *const outputForSender;
};

/**
 * The class representing the unspent bitcoin batches of the Bitcoin system.
 *
 * A bitcoin batch is unspent if it hasn't been used as an input in any transaction.
 * Equivalently, a bitcoin batch is unspent if it can be used as an input in a transaction.
 *
 * A bitcoin batch becomes "unspent" if and only if one of the following happens:
 *  - The bitcoin batch is added to the user directly by the bitcoin system
 *    via the `BitcoinSystem::addBitcoinToUser` function.
 *  - The bitcoin batch is received by the user in a "confirmed" transaction as the output
 *    via the `BitcoinSystem::mineBlock` function.
 *
 * A bitcoin batch is spent (becomes "not unspent") if it's used as an input in a transaction
 * via the `BitcoinSystem::transact` function.
 */
class UnspentBitcoinBatches {
public:
    ~UnspentBitcoinBatches();

    bool isSpent(const BitcoinBatch *batch) const;

    void addBatch(const BitcoinBatch *batch);

    void spendBatch(const BitcoinBatch *batch);

    int spend(
        const User *user,
        int amount,
        const BitcoinBatch **spentBatches,
        int &spentBatchCount
    );

private:
    /**
     * The unspent bitcoin batches.
     *
     * This is a dynamic array, and it's re-allocated whenever the number of unspent transaction bitcoin batches increases.
     */
    const BitcoinBatch **unspentBitcoinBatches = nullptr;
    /**
     * The number of unspent transaction bitcoin batches.
     *
     * It's always equal to the *effective* size of the `unspentBitcoinBatches` array.
     */
    int unspentBitcoinBatchesCount = 0;
};

#endif
