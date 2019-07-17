//  Donghee Lee
//  05/30/2019
//
//
// This Firm class stores all clients in a binary search tree based on their
// accountId. It stores all valid transactions, and executes them if only
// they are valid and can be done. A transaction is valid if the
// transaction type is one of those four options and the client accounId(s)
// involved exist in the Firm. The transaction can be done if there are enough
// balances in the accounts. After execution, it saves the transaction in the
// history log for that client.

#include "client.h"
#include "history.h"
#include "bst.h"

#include <queue>
#include <fstream>
#include <iostream>

#ifndef firm_h
#define firm_h

class Firm {
   
public:
    Firm(std::ifstream &);              // builds clients based on given file
    Firm(const Firm &);                 // copy constructor
    ~Firm();

    void conductTransactions(std::ifstream &);  // conducts valid transactions

private:
    std::queue<Transaction> transQueue;   // stores valid transactions requests
    BSTree clientTree;                // stores clients ordered by their accId
    
    void endReport();                   // displays all clients accounts
    void executeTransactions();         // executes possible transactions
};

#endif /* firm_h */
