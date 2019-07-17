//  Donghee Lee
//  05/30/2019
//
//
//
// This Client class stores the data of client such as their name, their
// account id, and the balances of their different bank accounts. It
// also stores its own history of valid(approved) transactions. This also
// allows clients to deposit, withdraw, move (from one account to another),
// and view history of the client. Clients can be compared by their accID.
// It is assumed that only valid transactions are requested. (A transaction is
// valid if the transaction type is one of those four options and the
// client accounId(s) involved exist in the Firm.)

#ifndef client_h
#define client_h

#include "account.h"
#include "history.h"

#include <vector>
#include <iostream>
#include <fstream>

int const accSize = 10;

class Client {
    friend std::ostream& operator<<(std::ostream&, const Client&);
    
public:
    Client(std::string firstName, std::string lastName,
           int accountId, int []);                  // client constructor
    Client(const Client &);                         // copy constructor
    ~Client();                                      // destructor
    
    // comparison operators -- clients are compared by their accountId
    bool operator<(const Client&) const;
    bool operator<=(const Client&) const;
    bool operator>(const Client&) const;
    bool operator>=(const Client&) const;
    bool operator==(const Client&) const;
    bool operator!=(const Client&) const;
    
    bool deposit(int accType, int amount);      // deposits money
    bool withdraw(int accType, int amount);     // withdraws money
    bool history();                             // displayes history
    bool move(int amount, int fromAccType, int toAccType, Client * toClient);
                                // moves money from one account to another
    int getAccId() const;                       // returns accountId
    void addToHistory(Transaction *);       // add transactions to history Log
    
private:
    std::vector<Account> accounts;
    std::string fname;
    std::string lname;
    int accId;
    History historyLog;
};

#endif /* client_h */
