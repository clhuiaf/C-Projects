#include "blockchain.h"
//#include <iostream>

using namespace std;

/**
 * The destructor of the TransactionNode class.
 *
 * As a node, this function destructs the next transaction node in the linked list of transactions.
 * Also, this function destructs the transaction that the node holds.
 */
TransactionNode::~TransactionNode() {
    // TODO: Task 5
    // delete transaction;
    // if (next != nullptr)
    //     delete next;
}

/**
 * The destructor of the Block class.
 *
 * As a linked list, this function triggers the deletion of the linked list of transactions.
 * As a node, this function destructs the next block in the linked list of blocks.
 */
Block::~Block() {
    // TODO: Task 5
    // TransactionNode *current = head; 
    // while (current != nullptr) {
    //     TransactionNode *nextNode = current->next; 
    //     delete current; 
    //     current = nextNode; 
    // }
    
    //delete head;
    //delete next;
}

/**
 * Adds a transaction to the block.
 *
 * This function creates a new transaction node to wrap the given transaction,
 * and appends the new transaction node to the end of the linked list of transactions.
 *
 * @param transaction The transaction to be added.
 */
void Block::addTransaction(const Transaction *transaction) {
    // TODO: Task 4
    // Create a new TransactionNode 
    TransactionNode * new_transaction_node = new TransactionNode;
    new_transaction_node->transaction = transaction; 
    new_transaction_node->next = nullptr; 
   // If no transaction record, set head points to new node
    if (head == nullptr) {
        head = new_transaction_node;
    } 
    // The block already have at least one transaction record
    else {
        // Create a working pointer moving to the end of linked list 
        TransactionNode *current = head;
        // If current->next != nullptr, keep going
        while (current->next) {
            current = current->next; // Move to the next node
        }
        current->next = new_transaction_node; // Append the new node at the end
        //cout << "test" << endl;
    }

}

/**
 * The destructor of the Blockchain class.
 *
 * As a linked list, this function triggers the deletion of the linked list of blocks.
 */
Blockchain::~Blockchain() {
    // TODO: Task 5
    // Block *current = head;  
    // while (current != nullptr) {
    //     Block *nextBlock = current->next;  
    //     delete current;  
    //     current = nextBlock;  
    // }
    
    //delete head;
}

/**
 * Adds a block to the blockchain.
 *
 * This function appends the given block to the end of the linked list of blocks.
 *
 * @param block The block to be added.
 */
void Blockchain::addBlock(Block *block) {
    // TODO: Task 4
    // Check if the block is nullptr
    if (!block){
        return;
    }
    // If the blockchain has no blocks, points the head and tail both to the new block
    if (!head) {
        head = block;
        tail = block;
    } 
    // The blockchain has at least one block, append the block to the end
    else {
        tail->next = block;
        tail = block; 
    }
    block->next = nullptr; 
    length++; 
}


//
// PROVIDED FUNCTIONS
//

TransactionNode *Block::getHead() const {
    return head;
}

Block *Blockchain::getHead() const {
    return head;
}

Block *Blockchain::getTail() const {
    return tail;
}

int Blockchain::getLength() const {
    return length;
}
