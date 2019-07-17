//  Donghee Lee
//  05/30/2019
//
//
// this History class holds a queue of pointers to Transactions that has
// been executed thus far.

#include "history.h"
#include <stdio.h>
using namespace std;

//----------------------------------------------------------------------------
// constructor
// holds a queue of pointers to Transactions
History::History() {
    approvedTrns = std::queue<Transaction *>();
}

//----------------------------------------------------------------------------
// destructor
// destructs History
History::~History() {

}

//----------------------------------------------------------------------------
// addHistory
// adds a pointer to a Transaction in the queue
bool History::addHistory(Transaction * trns) {
    approvedTrns.push(trns);
    return true;
}

//----------------------------------------------------------------------------
// showHistory
// diesplays the transactions that have beene saved
void History::showHistory(){
    showHistoryHelper(approvedTrns);
}

//----------------------------------------------------------------------------
// showHistoryHelper
// diesplays the transactions that have beene saved
void History::showHistoryHelper(std::queue<Transaction *> tpr) {
    while (!approvedTrns.empty()) {
        std::cout << *(approvedTrns.front());
        approvedTrns.pop();
    }
}
