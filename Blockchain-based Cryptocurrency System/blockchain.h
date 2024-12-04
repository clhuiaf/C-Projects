#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "transaction.h"

using namespace std;

/**
 * A class representing a node in the linked list of transactions.
 */
class TransactionNode {
public:
    ~TransactionNode();

    /**
     * The transaction that the node holds.
     */
    const Transaction *transaction;

    /**
     * The next transaction node in the linked list of transactions.
     */
    TransactionNode *next;
};

/**
 * A class representing a block in a blockchain.
 *
 * A block is a node of the blockchain linked list.
 * Meanwhile, a block is also a linked list of transactions.
 */
class Block {
public:
    ~Block();

    // Add transaction to the node linked-list in the block
    void addTransaction(const Transaction *transaction);


    /**
     * The next block in the linked list of blocks.
     */
    Block *next = nullptr;


    // PROVIDED FUNCTIONS

    TransactionNode *getHead() const; // Get the TransactionNode head

private:
    /**
     * The head of the linked list of transactions.
     */
    TransactionNode *head = nullptr; // points to TransactionNode linked-list
};

/**
 * A class representing a blockchain.
 *
 * A blockchain is a linked list of blocks.
 */
class Blockchain {
public:
    ~Blockchain();

    void addBlock(Block *block); 


    // PROVIDED FUNCTIONS

    Block *getHead() const;

    Block *getTail() const;

    int getLength() const;

private:
    /**
     * The head of the linked list of blocks.
     */
    Block *head = nullptr;

    /**
     * The tail of the linked list of blocks.
     */
    Block *tail = nullptr;

    /**
     * The length of the linked list of blocks.
     */
    int length = 0;
};

#endif
