//  Donghee Lee
//  05/30/2019
//
//
// this Transaction class stores the type of this transaction, the account id
// of the client who requests the transactions, the account id of the other
// bank of client, and the amount of money involved.

#include <stdio.h>
#include <iomanip>
#include "transaction.h"

using namespace std;

//----------------------------------------------------------------------------
// constructor
// stores the transType, the account id of the client who requests the
// transaction, the otherId involved, and the amount of money.
Transaction::Transaction(char transType, int clientId,
                         int otherId, int amount) {
    this->transType = transType;
    this->clientId = clientId;
    this->otherId = otherId;
    this->amount = amount;
}

//----------------------------------------------------------------------------
// copy contructor
// copies the transType, accountId, other account Id, and the amount of money
// from the other Transaction
Transaction::Transaction(const Transaction & other) {
    this->transType = other.transType;
    this->clientId = other.clientId;
    this->otherId = other.otherId;
    this->amount = other.amount;
}
//----------------------------------------------------------------------------
// destructor
// copies the transType, accountId, other account Id, and the amount of money
// from the other Transaction
Transaction::~Transaction() {

}

//----------------------------------------------------------------------------
// operator<<
// prints out the type of transaction, the amount of money involved, and a
// message that indicates which bank the money is from or being sent to.
ostream& operator<<(ostream &output, const Transaction & clnt) {
    int accType = clnt.getClientId() % 10;
    switch(clnt.getTransType()) {
        case 'D':
            output << "deposit  " << " $" << setw(6) <<
            clnt.getAmount() << " into " << clnt.bankNames(accType)
            << endl;
            break;
        case 'W':
            output << setw(9) << "withdraw " << " $" << setw(6) <<
            clnt.getAmount() << " from " << clnt.bankNames(accType)
            << endl;
            break;
        case 'M' :
            output << "move     " << " $" << setw(6) <<
            clnt.getAmount() << " from " << clnt.bankNames(accType)
            << endl << "                  to " <<
            clnt.bankNames(clnt.getOtherId()%10) <<
            " for client " << clnt.getOtherId()/10 <<endl;
            break;
        case 'H':
            output << setw(9) << "history  " << endl;
            return output;
    }
   
    return output;
}

//----------------------------------------------------------------------------
// bankNames
// returns the string name of n-th bank accounts
string Transaction::bankNames(int n) const{
    switch (n) {
        case 0:
            return "Money Market fund";
        case 1:
            return "Prime Money Market fund";
        case 2:
            return "Long-Term Bond fund";
        case 3:
            return "Short-Term Bond fund";
        case 4:
            return "500 Index fund";
        case 5:
            return "Capital Value fund";
        case 6:
            return "Growth Equity fund";
        case 7:
            return "Growth Index fund";
        case 8:
            return "Value fund";
        case 9:
            return "Value Stock Index";
    }
    return "";
}

//----------------------------------------------------------------------------
// getTransType
// returns the type of the transaction
char Transaction::getTransType() const {
    return transType;
}

//----------------------------------------------------------------------------
// getClientId
// returns the account Id of the client who requested the transaction
int Transaction::getClientId() const {
    return clientId;
}

//----------------------------------------------------------------------------
// getOtherId
// returns the account Id of the other client recepient
int Transaction::getOtherId() const {
    return otherId;
}

//----------------------------------------------------------------------------
// getAmount
// returns the amount of the money involved in this Transaction
int Transaction::getAmount() const {
    return amount;
}

