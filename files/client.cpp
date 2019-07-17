//  Donghee Lee
//  05/30/2019
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

#include "client.h"

#include <iomanip>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------
// constructor
// Client holds string firstname, string lastname, int accountId, and the
// amountList array for the balances of the clients bank accounts. The client
// also stores its own history of valid(approved) transactions.
Client::Client(string firstName, string lastName,
               int accountId, int amountList []) {
    fname = firstName;
    lname = lastName;
    accId = accountId;

    if (amountList != nullptr) {
        for (int i = 0; i < accSize; i++) {
            accounts.push_back(Account(i, amountList[i]));
        }
    }
  //  delete [] amountList;
    historyLog = History();
}

//----------------------------------------------------------------------------
// copy constructor
// this client copies the name, account ID, and history from the other client's
Client::Client(const Client & other){
    fname = other.fname;
    lname = other.lname;
    accId = other.accId;
    
    for (int i = 0; i < accSize; i++) {
        accounts.push_back(Account(other.accounts[i]));
    }
    historyLog = other.historyLog;
}

//----------------------------------------------------------------------------
// destructor
Client::~Client(){
    
}

//----------------------------------------------------------------------------
// getAccId
// returns the account Id of this client
int Client::getAccId() const {
    return accId;
}

//----------------------------------------------------------------------------
// deposit
// returns true after completing the deposit of int amount of money into
// int accType of bank account of this client
bool Client::deposit(int accType, int amount){
    accounts[accType].setAmount(accounts[accType].getAmount() + amount);
    return true;
}

//----------------------------------------------------------------------------
// withdraw
// returns true if there is enough balance in the int accType of bank account
// to withdraw int amount of money. If it does, then withdraw that amount
// then return true. If it doesn't, check if it has an alternative account
// that can withdraw the rest of the amount that needs to be covered.
// If it does, with draw then return true. If it doesn't, return false.
bool Client::withdraw(int accType, int amount){
    if (accounts[accType].getAmount() >= amount) { // can do it
        accounts[accType].setAmount(accounts[accType].getAmount() - amount);
        return true;
    } else {
        int altType = accounts[accType].getAltAccount();
        if (altType == -1) {
            return false;
        } else {
            int leftover = amount - accounts[accType].getAmount();
            if (accounts[altType].getAmount() >= leftover) {
                accounts[accType].setAmount(0);
                accounts[altType].setAmount(accounts[altType].
                                            getAmount()-leftover);
                return true;
            } else {
                return false;
            }
        }
    }
}
//----------------------------------------------------------------------------
// history
// displays the history of this Client showing its actions such as deposit,
// withdraw, move, history from and to which accounts. returns true
bool Client::history() {
    cout << "History of transactions for client ";
    cout << lname << " " << fname << ", client ID = "
    << accId << endl;
    cout << "Type      Amount  Detail" << endl;
    cout << "--------- ------- --------------------------------------" << endl;
    historyLog.showHistory();
    return true;
}
//----------------------------------------------------------------------------
// move
// moves int amount of money from int fromAccType of bank account of this
// client, to int toAccType of bank account of toClient. it is only executed
// if this client's specific account (or its alternative accoubt) has enough
// balance to be withdrawn.
bool Client::move(int amount, int fromAccType, int toAccType,
                  Client * toClient) {
    bool withdrawSucceed = withdraw(fromAccType, amount);
    if (withdrawSucceed) {
        (*toClient).deposit(toAccType, amount);
    } else {
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------
// operator<<
// displays the account Id of this client, the name of this client, and
// the initial and final balance of all bank accounts it holds.
ostream& operator<<(ostream &output, const Client & clnt) {
    output << clnt.accId << "  " << clnt.lname << " " << clnt.fname << endl;
    output << "Initial Balances: ";
    for (int i = 0; i < accSize; i++) {
        output << setw(6) << to_string(clnt.accounts[i].getOrigAmt());
    }
    output << endl;
    output << "Final Balances:   ";
    for (int i = 0; i < accSize; i++) {
        output << setw(6) << to_string(clnt.accounts[i].getAmount());
    }
    output << endl << endl;
    return output;
}

//----------------------------------------------------------------------------
// addToHistory
// if a transaction is valid, it is added to this client's personal historylog
void Client::addToHistory(Transaction * trn) {
    historyLog.addHistory(trn);
}

//----------------------------------------------------------------------------
// operator<
// returns true if this client's accId is less than the other's
bool Client::operator<(const Client& other) const {
    return accId < other.accId;
}

//----------------------------------------------------------------------------
// operator>
// returns true if this client's accId is bigger than the other's
bool Client::operator>(const Client& other) const {
    return accId > other.accId;
}

//----------------------------------------------------------------------------
// operator<=
// returns true if this client's accId is less than or equal to the other's
bool Client::operator<=(const Client& other) const {
    return accId <= other.accId;
}

//----------------------------------------------------------------------------
// operator>=
// returns true if this client's accId is bigger than or equal to the other's
bool Client::operator>=(const Client& other) const {
    return accId >= other.accId;
}

//----------------------------------------------------------------------------
// operator==
// returns true if this client's accId is equal to the other's
bool Client::operator==(const Client& other) const {
    return accId == other.accId;
}

//----------------------------------------------------------------------------
// operator!=
// returns true if this client's accId is not equal to the other's
bool Client::operator!=(const Client& other) const {
    return accId != other.accId;
}
