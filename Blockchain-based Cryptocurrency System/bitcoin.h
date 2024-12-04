#ifndef BITCOIN_H
#define BITCOIN_H

#include "blockchain.h"

using namespace std;

/**
 * A class representing the Bitcoin system.
 *
 * See the implementation file for more details.
 */
class BitcoinSystem {
public:
    ~BitcoinSystem();

    void addUser(const string &name);

    User *getUser(const string &name) const;


    void addBitcoinToUser(const string &name, int amount) const;


    void addPendingTransaction(Transaction *transaction);

    void removePendingTransaction(Transaction *transaction);

    Transaction *selectPendingTransaction() const;


    void transact(const string &senderName, const string &receiverName, int amount, int fee);

    void mineBlock();


    // PROVIDED FUNCTIONS

    void printBlockchain() const;

    void printUsers() const;

    void printPendingTransactions() const;

private:
    /**
    * The blockchain of the Bitcoin system.
    *
    * After blocks are mined, they're added to the blockchain.
    */
    Blockchain *blockchain = new Blockchain;

    /**
    * The unspent bitcoin batches of the Bitcoin system.
    */
    UnspentBitcoinBatches *unspentBitcoinBatches = new UnspentBitcoinBatches;

    /**
    * The users of the Bitcoin system.
    *
    * This is a dynamic array, and it's re-allocated whenever the number of users increases.
    */
    User **users = nullptr;
    /**
    * The number of users in the Bitcoin system.
    *
    * It's always equal to the *effective* size of the `users` array.
    */
    int userCount = 0;

    /**
    * The pending transactions of the Bitcoin system.
    *
    * A pending transaction is a transaction that has yet to be mined by `mineBlock`.
    *
    * This is a dynamic array, and it's re-allocated whenever the number of pending transactions increases.
    */
    Transaction **pendingTransactions = nullptr;
    /**
    * The number of pending transactions in the Bitcoin system.
    *
    * It's always equal to the *effective* size of the `pendingTransactions` array.
    */
    int pendingTransactionCount = 0;
};

#endif
