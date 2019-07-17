//  Donghee Lee
//  05/30/2019
//
//
//  This Account class stores the bank type of itself and the amount it stores.
//  It keeps track of the original amount and the current amount. It also
//  provides the alternative bank type, if it has one.

#include <iostream>
#ifndef account_h
#define account_h
class Account {
    
public:
    Account(int type, int amount);      // constructor
    Account(const Account &);           // copy constructor
    ~Account();                         // destructor
    
    int getAmount() const;              // returns current balance
    int getOrigAmt() const;             // returns original balance
    int getAltAccount() const;          // returns alternative account
    bool setAmount(int);                // sets the current balance

private:
    int origAmt;
    int currAmt;
    int type;                           // bank type
};

#endif /* account_h */
