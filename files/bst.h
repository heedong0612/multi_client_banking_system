//  Donghee Lee
//  05/30/2019
//
//
//  This BSTree class makes a binary search tree of pointers to Client objects
//  Nodes of the tree are ordered in preorder. This class allows inserting,
//  retrieving, displaying, and emptying of the tree.

#ifndef bst_h
#define bst_h
#include "client.h"

class BSTree {
public:
    BSTree();
    ~BSTree(); // calls makeEmpty which deallocates all memory
    // insert object into the tree, parameter holds pointer to object to insert
    bool insert(Client*);
    
    // retrieve object, first parameter is object to retrieve
    // second parameter holds pointer to found object, nullptr if not found
    bool retrieve(const Client & , Client*&)const;
    void display()const; //displays the contents of a tree to cout
    void makeEmpty(); //empties the current tree, deallocates all memory
    bool isEmpty()const; //returns true if tree is empty
    
private:
    struct Node{ 
        Client* data;
        Node* right;
        Node* left;
    };
    Node* root;                                 // root of the tree
    bool retrieveHelper(const Client & , Client*&, Node*)const;
    void makeEmpty(Node*);
    void displayHelper(Node*) const;
};

#endif /* bst_h */
