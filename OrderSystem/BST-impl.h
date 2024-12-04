#ifndef __BST_IMPL_SELF_DEF_H__
#define __BST_IMPL_SELF_DEF_H__

#include "BST.h"

template <typename K>
BST<K>::BST() : root(SmartPtr<BSTNode<K>>()) {} // Default constructor: Initialize the root node to be null

template <typename K>
BST<K>::BST(const BST<K>& bst) {
    if (bst.isEmpty()) {
        root = SmartPtr<BSTNode<K>>();
        return;
    }
    root = SmartPtr<BSTNode<K>>(new BSTNode<K>(*bst.root));
}

template <typename K>
BST<K>::~BST() {}

// TODO: Task 3.1
template <typename K>
bool BST<K>::contains(const K& key, SmartPtr<Order> order) const {
    // Return true only if the BST contains the same key and value. order will not contain nullptr.
    // Base case: Return false only if the root node is null
    if (root == SmartPtr<BSTNode<K>>())
        return false;
    // Base case: Return true only if the BST contains the same key and value. 
    if (key == root->key && (root->value).contains(order)) 
        return true;
    // Check the right subtree
    if (key > root->key)
        return (root->right).contains(key, order);
    // Check  the left subtree
    else
        return (root->left).contains(key, order);
}

// TODO: Task 3.2
template <typename K>
int BST<K>::size() const {
// Return the number of Order in the BST.
// It should be a recursive function. 
// Note: We are NOT counting the number of nodes in the BST, but the number of Order in the BST.
// You can assume Order in the BST is unique.
    // Base case: Return 0 if the root node is null
    if (root == SmartPtr<BSTNode<K>>())
        return 0;
    // Root length + left subtree total length + right subtree total length
    return (root->value).length() + (root->left).size() + (root->right).size();
}

// TODO: Task 3.3
template <typename K>
void BST<K>::add(const K& key, SmartPtr<Order> order) {
// Add the SmartPtr<Order> instance to the BST.
// If the key does not exist in the BST, create a new node with the key and value.
// If the key exists in the BST, add the SmartPtr<Order> to the LinkedList in the node.
// Use BSTNode<S>::add(SmartPtr<Order> order) to add the SmartPtr<Order> to the LinkedList.
// order will not contain nullptr.
    // Base case: Create a new node if the BST is empty
    if (root == SmartPtr<BSTNode<K>>()){
        root = SmartPtr<BSTNode<K>>(new BSTNode<K>(key, order));
        return;
    }
    // Add the order to the linked-list if the key is the same
    if (key == root->key){
        (root->value).add(order);
        return;
    }
    // Recursive case: Traverse the left subtree
    if (key < root->key){
        (root->left).add(key, order);
        return;
    }
    // Recursive case: Traverse the right subtree
    if (key > root->key){
        (root->right).add(key, order);
        return;
    }
}

// TODO: Task 3.4
template <typename K>
const BST<K>* BST<K>::find(const K& key) const {
// Return the pointer to the node with the same key.
// If the key does not exist in the BST, return nullptr.
// Note: We do not use SmartPtr here because the BST<K> instance is allocated on the stack.
    // Base case: The recursion hit the leaf == the key doesn't exist in the BST
    if (root == SmartPtr<BSTNode<K>>())
        return nullptr;
    // Return the pointer to the node (BST) with the same key
    if (key == root->key)
        return this;
    // Recursive case: Traverse the left child to find the key
    if (key < root->key)
        return (root->left).find(key);
    // Recursive case: Traverse the right child to the the key
    if (key > root->key)
        return (root->right).find(key);
}

// TODO: Task 3.5
template <typename K>
const BST<K>* BST<K>::findMin() const {
// Return the minimum node of the tree in the BST<K>.
// Note: We do not use SmartPtr here because the BST<K> instance is allocated on the stack.
    // Base case: Return the current node if the left child is null
    if (root->left.isEmpty())
        return this;
    // Recursive case: Traverse the left child to find the minimum node
    return (root->left).findMin();
}


// TODO: Task 3.6, replace the node with the minimum node in the right subtree
template <typename K>
void BST<K>::_remove(const K& key) {
// Remove the node with the same key in the BST.
// You should follow the rules specified in the lecture slides.
// This function will replace the node with the minimum node from the right side of the BST if its left and right are both not nullptr.
// Check more rules about BST node deletion in the lecture slide.
// Note: We do not use SmartPtr here because the BST<K> instance is allocated on the stack.
    // Base case: Return if the BST is empty
    if (root == SmartPtr<BSTNode<K>>())
        return;
    // Base case: Remove the node if the key is the same
    if (key == root->key){
        // No children
        if (root->left.isEmpty() && root->right.isEmpty()){
            root.unset();
            return;
        }
        // One child: left child is not null while the right child is null
        if (!root->left.isEmpty() && root->right.isEmpty()){
            SmartPtr<BSTNode<K>> temp = root->left.root; // Store the left child
            root.unset();
            root = temp; // Replace the root with the left child
            return;
        }
        // One child: left child is null while the right child is not null
        if (root->left.isEmpty() && !root->right.isEmpty()){
            SmartPtr<BSTNode<K>> temp = root->right.root; // Store the right child
            root.unset();
            root = temp; // Replace the root with the right child
            return;
        }
        // Two children
        if (!root->left.isEmpty() && !root->right.isEmpty()){
            // Find the minimum node from the right side
            const BST<K>* min_ptr = root->right.findMin(); 
            // Replace the key of the root node wtih that of minimum node
            root->key = min_ptr->root->key;
            // Replace the value of the root node with that of minimum node
            root->value = min_ptr->root->value;
            // Remove the minimum node
            root->right._remove(min_ptr->root->key);
            return;
        }
    }
    // Recursive case: Traverse the left child to remove the node
    if (key < root->key){
        root->left._remove(key);
        return;
    }
    // Recursive case: Traverse the right child to remove the node
    if (key > root->key){
        root->right._remove(key);
        return;
    }
}

// TODO: Task 3.7 
template <typename K>
void BST<K>::remove(const K& key, SmartPtr<Order> order) {
// Remove the SmartPtr<Order> in the LinkedList with the same key in the BST.
// If the LinkedList is empty after removing the SmartPtr<Order>, remove the node with the same key from the BST.
// order will not contain nullptr. 
// Note that you might need to call the _remove function (Task 3.6) if necessary.
    // Find the node with the same key
    const BST<K>* key_node = find(key);
    // The node with the same key is found
    if (key_node != nullptr){
        // Check if the linkedlist contains the order
        if ((key_node->root->value).contains(order)){
            (key_node->root->value).remove(order); // Remove the order from the linked-list
            if ((key_node->root->value).isEmpty())
                _remove(key); // Remove the node if the linked-list is now empty
        }
    }    
}


// TODO: Task 3.8
template <typename K>
Pair<K, SmartPtr<Order>> BST<K>::operator[](int index) const {
    // Return a default constructed Pair if the index is out-of-bound
    if (index < 0 && index >= size())
        return Pair<K, SmartPtr<Order>>();
    // Base case: Return the root node if the index is within the range
    if (index >= (root->left).size() && index < (root->value).length() + (root->left).size())
        return Pair<K, SmartPtr<Order>>(root->key, (root->value)[index - (root->left).size()]);
    // Recursive case: Traverse the left subtree
    if (index < (root->left).size())
        return (root->left)[index];
    // Recursive case: Traverse the right subtree
    if (index >= (root->value).length() + (root->left).size())
        return (root->right)[index - (root->value).length() - (root->left).size()];
}

// TODO: Task 3.9
template <typename K>
std::vector<SmartPtr<Order>> BST<K>::rangeSelect(const K& lower, const K& upper, bool reverse) const {
    // Return an empty vector if the BST is empty
    if (isEmpty())
        return std::vector<SmartPtr<Order>>();
    // Initialize the vector to store the orders
    std::vector<SmartPtr<Order>> orders;
    // Traverse the BST to collect the orders
    for (int i = 0; i < size(); i++){
        Pair<K, SmartPtr<Order>> pair = (*this)[i];
        if (pair.first >= lower && pair.first <= upper)
            orders.push_back(pair.second);
    }
    // Reverse the order if the reverse flag is true
    if (reverse)
        // reverse the vector without using the reverse function
        for (int i = 0; i < orders.size() / 2; i++){
            SmartPtr<Order> temp = orders[i];
            orders[i] = orders[orders.size() - 1 - i];
            orders[orders.size() - 1 - i] = temp;
        }
    return orders;
}

template <typename K>
void BST<K>::printTree(int depth) const {
    // Print the tree in the following format:
    //   (key, length of the linked list)
    //     (key, length of the linked list)
    //       (key, length of the linked list)
    //     (key, length of the linked list)
    //   (key, length of the linked list)

    // Base case: Return if the BST is empty
    if (isEmpty()) {
        return;
    }

    root->right.printTree(depth + 1);
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }
    std::cout << "(" << root->key << "," << this->root->value.length() << ")" << std::endl;
    root->left.printTree(depth + 1);
}

#endif // __BST_IMPL_SELF_DEF_H__