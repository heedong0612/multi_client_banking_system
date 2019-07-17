//  Donghee Lee
//  05/30/2019
//
//
//  This BSTree class makes a binary search tree of pointers to Client objects
//  Nodes of the tree are ordered in preorder. This class allows inserting,
//  retrieving, displaying, and emptying of the tree.

#include "bst.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------
// constructor
// sets the binary search tree to be empty
BSTree::BSTree() {
    root = nullptr;
}

//----------------------------------------------------------------------------
// destructor
// makes the tree empty
BSTree::~BSTree() {
    makeEmpty();
}

//----------------------------------------------------------------------------
// insert
// inserts a pointer to the client object in this BSTree. Nodes are ordered
// in preorder. returns true after inserting
bool BSTree::insert(Client* cptr) {
    Node* ptr = new Node;
    if (ptr == nullptr) return false;            // out of memory
    ptr->data = cptr;
    ptr->left = ptr->right = nullptr;
    if (isEmpty()) {
        root = ptr;
    }
    else {
        Node* current = root;                           // walking pointer
        bool inserted = false;                          // whether inserted yet
        
        // if item is less than current item, insert in left subtree,
        // otherwise insert in right subtree
        while (!inserted) {
            if (*ptr->data < *current->data) {
                if (current->left == nullptr) {              // insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                    current = current->left;               // one step left
            }
            else {
                if (current->right == nullptr) {             // insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                    current = current->right;              // one step right
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------------
// retrieve
// looks for the given target client in this BSTree and let the holdTarget
// point to the object. Returns true if the target client has been found,
// but returns false otherwise.
bool BSTree::retrieve(const Client & target,
                      Client * & holdTarget) const {
    return retrieveHelper(target, holdTarget, root);
}

//----------------------------------------------------------------------------
// retrieveHelper -- private helper function
// looks for the given target client in this BSTree and let the holdTarget
// point to the object. Returns true if the target client has been found,
// but returns false otherwise.
bool BSTree::retrieveHelper(const Client & target,
                            Client * & holdTarget, Node* root) const {
    if(root == nullptr) {
        return false;
    } else if (target < *root->data) {
        return retrieveHelper(target, holdTarget, root->left);
    } else if (target > *root->data) {
        return retrieveHelper(target, holdTarget, root->right);
    } else {
        holdTarget = root->data;
        return true;
    }
    
}

//----------------------------------------------------------------------------
// display
// displays every nodes of this tree in order
void BSTree::display() const {
    displayHelper(root);
}

//----------------------------------------------------------------------------
// displayHelper -- private Helper function
// displays every nodes of this tree in order
void BSTree::displayHelper(Node * curr) const {
    if (curr != nullptr) {
        displayHelper(curr->left);
        cout << *curr->data;
        displayHelper(curr->right);
    }
}

//----------------------------------------------------------------------------
// makeEmpty
// this empties the current tree by deallocating all memory
void BSTree::makeEmpty() {
    makeEmpty(root);
}

//----------------------------------------------------------------------------
// makeEmpty -- private helper function
// this empties the current tree by deallocating all memory
void BSTree::makeEmpty(Node* curr) {
    if (curr != nullptr) {
        makeEmpty(curr->left);
        makeEmpty(curr->right);
        delete curr->data;
        curr = nullptr;
    }
}

//----------------------------------------------------------------------------
// isEpty
// returns true if this tree is empty
bool BSTree::isEmpty() const {
    return root == nullptr;
}
