//  Donghee Lee
//  05/30/2019
//
//
//
// this History class holds a queue of pointers to Transactions that has
// been executed thus far.

#include "transaction.h"
#include <queue>

#ifndef history_h
#define history_h

class History {
    
public:
    History();                      // constructor
    ~History();                     // destructor   
    
    bool addHistory(Transaction *); // adds transaction pointer to the queue
    void showHistory();             // displays all transactions in the queue
    
private:
    std::queue<Transaction *> approvedTrns; // queue of transaction pointers
    void showHistoryHelper(std::queue<Transaction *>);
};

#endif /* history_h */
