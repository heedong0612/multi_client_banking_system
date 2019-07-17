//  Donghee Lee
//  05/30/2019
//
//
//
// this Transaction class stores the type of this transaction, the account id
// of the client who requests the transactions, the account id of the other
// bank of client, and the amount of money involved.
#include <fstream>
#include <iostream>

#ifndef transaction_h
#define transaction_h
class Transaction {
    friend std::ostream& operator<<(std::ostream&, const Transaction&);

public:
    Transaction(char transType, int clientId, int otherId, int amount);
    Transaction(const Transaction &);   // Transaction information
    ~Transaction();
    
    char getTransType() const;          // returns the type of transacftion
    int getClientId() const;            // returns the accId of the client
    int getOtherId() const;             // returns the accId of the recipient
    int getAmount() const;              // returns the money involved
    std::string bankNames(int) const;   // returns name of the bank
    
private:
    char transType;                     // one of H,W,M,D
    int clientId;                       // accId of the client
    int otherId;                        // the accId of the recipient
    int amount;                         // the money involved
    
};

#endif /* transaction_h */
