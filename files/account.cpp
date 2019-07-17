//  Donghee Lee
//  05/30/2019
//
//
//  This Account class stores the bank type of itself and the amount it stores.
//  It keeps track of the original amount and the current amount. It also
//  provides the alternative bank type, if it has one.

#include <stdio.h>
#include "account.h"

//----------------------------------------------------------------------------
// constructor
// saves the bank type and original amount of money of this Account
Account::Account(int type, int amount) {
    this->origAmt = amount;
    this->currAmt = amount;
    this->type = type;          // to figure out the alternative account
}

//----------------------------------------------------------------------------
// copy constructor
// copies the other Accounts' original and curren balance, and the bank type.
Account::Account(const Account & other) {
    this->origAmt = other.origAmt;
    this->currAmt = other.currAmt;
    this->type = other.type;
}

//----------------------------------------------------------------------------
// destructor
// destructs Account
Account::~Account() {

}

//----------------------------------------------------------------------------
// getAltAccount
// returns the possible alternative bank type of int of this Account
// If none, returns -1
int Account::getAltAccount() const {
    if (type < 2) {
        return (type == 0)? 1 : 0;
    } else if (type < 4) {
        return (type == 3)? 4 : 3;
    } else {
        return -1;
    }
}

//----------------------------------------------------------------------------
// getAmount
// returns the current balance of this Account
int Account::getAmount() const {
    return currAmt;
}

//----------------------------------------------------------------------------
// getorigAmt
// reuturns the original balance of this Account
int Account::getOrigAmt() const {
    return origAmt;
}

//----------------------------------------------------------------------------
// setAmount
// sets the current balance of this Account to int amt
bool Account::setAmount(int amt) {
    currAmt = amt;
    return true;
}
