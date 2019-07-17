//  Donghee Lee
//  05/30/2019
//
//
//
// This Firm class stores all clients in a binary search tree based on their
// accountId. It stores all valid transactions, and executes them if only
// they are valid and can be done. A transaction is valid if the
// transaction type is one of those four options and the client accounId(s)
// involved exist in the Firm. The transaction can be done if there are enough
// balances in the accounts. After execution, it saves the transaction in the
// history log for that client.

#include "firm.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

//----------------------------------------------------------------------------
// constructor
// this Firm takes a ifstream& of text file to build all clients and store
// them in a binary search tree. they are ordered based on their accId.
Firm::Firm(ifstream& clientInfo) {

    transQueue = queue<Transaction>();
    clientTree = BSTree();

    for (;;) {
        string fname;
        string lname;
        int accId;
        clientInfo >> fname;
        if (!clientInfo.eof()) {
            clientInfo >> lname >> accId;
        } else {
            break;
        }
        int amountList [accSize];
        for (int i = 0; i < accSize; i++) {
            clientInfo >> amountList[i];
        }
        Client * clt = new Client(fname, lname, accId, amountList);
        clientTree.insert(clt);
    }
}

//----------------------------------------------------------------------------
// copy constructor
// this firm copies the clients from the other
Firm::Firm(const Firm & other){
    clientTree = BSTree(other.clientTree);
    transQueue = queue<Transaction>();
}

//----------------------------------------------------------------------------
// destructor
Firm::~Firm(){
  //  clientTree.makeEmpty();
}

//----------------------------------------------------------------------------
// conductTransactions
// this builds a queue of valid transactions based on the ifstream transInfo.
// It considers a transaction valid if is type is one of 'D', 'H', 'M' or 'W'.
// It also checks the accId(s) involved to make sure they exist in the Firm.
// After building a queue of valid transactions, it executes them if it can
// be done (if there are enough balances in the accounts). After that, it
// displays a report to show all clients in the firm and their original
// and current balances of their accounts.
void Firm::conductTransactions(ifstream & transInfo){
    char str[15];
    bool legitTrans = true;
   for (;;) {
       
       if (legitTrans) {
           transInfo >> str;
       }
       legitTrans = true;
       char transType = str[0];

        if (transInfo.eof())  {
            break;
        }
        
        int clientId = -1;
        int amount = -1;
        int otherId = -1;
        switch (transType) {
            case 'W' :
                transInfo >> clientId >> amount;
                break;
            case 'D' :
                transInfo >> clientId >> amount;
                break;
            case 'M' :
                transInfo >> clientId >> amount >> otherId;
                break;
            case 'H':
                transInfo >> clientId;
                break;
            default:
                cout << "Unknown transaction type '" << transType
                << "' requested" << endl;
                legitTrans = false;
                break;
        }
       
       if (transType == 'W' || transType == 'D' || transType == 'H') {
           int cId;
           if (transType == 'H') {
               cId = clientId;
           } else {
               cId = clientId/10;
           }
           Client targetClnt = Client("","", cId ,nullptr);
           Client * targetPtr = nullptr;
           if (!clientTree.retrieve(targetClnt, targetPtr)){
               cout << "Unknown client ID " << cId << " requested" << endl;
               legitTrans = false;
           }
       }
       if (transType == 'M') {
           Client targetClnt = Client("","",clientId/10,nullptr);
           Client * targetPtr = nullptr;

           Client targetClnt2 = Client("","",otherId/10,nullptr);
           Client * targetPtr2 = nullptr;
 
           if (!clientTree.retrieve(targetClnt, targetPtr) ||
               !clientTree.retrieve(targetClnt2, targetPtr2)) {
               cout << "Unknown client ID " << clientId/10 <<
               " or " << otherId/10 << " requested" << endl;
               legitTrans = false;
           }
       }
       if (legitTrans) {
            Transaction trn(transType, clientId, otherId, amount);
            transQueue.push(trn);

       } else {
           transInfo >> str;
           while (!transInfo.eof() && isdigit(str[0])) {
               transInfo >> str;
           }
       }

    }
    cout << endl;
    executeTransactions();
    endReport();
}

//----------------------------------------------------------------------------
// executeTransactions
// it execute the queue of transactions, if they can be done. To do that,
// the accountId(s) involved should exists in this Firm. Also for move and
// withdraw, there should be enough amount of balance in their accounts or
// their alternative accounts. After execution of each transaction, they are
// added to the clients history log for reference.
void Firm::executeTransactions() {
    while (!transQueue.empty()) {
        Transaction & t = transQueue.front();
        transQueue.pop();
        Transaction * trn = &t;
        Client * clnt;

        int accId = (*trn).getClientId();
        if((*trn).getTransType() != 'H') {
            accId /= 10;
        }
        Client targetClnt = Client("","", accId, nullptr);
        clientTree.retrieve(targetClnt, clnt);
        if ((*trn).getTransType() == 'H') {
            (*clnt).addToHistory(trn);
            (*clnt).history();
            cout << endl;
        } else {
            int accType = (*trn).getClientId()%10;
            int amount = (*trn).getAmount();
            
            switch ((*trn).getTransType()) {
                case 'W' :
                    if ((*clnt).withdraw(accType, amount)) {
                        (*clnt).addToHistory(trn);
                    } else {
                        cout << "Withdrawal not performed on " <<
                        (*trn).bankNames(accType) << " for client "
                        << accId << ";"  << endl;
                        cout << "     insufficient funds" << endl << endl;
                    }
                    break;
                case 'D' :
                    if ((*clnt).deposit(accType, amount)) {
                        (*clnt).addToHistory(trn);
                    }
                    break;
                case 'M' :
                    int otherClientId = (*trn).getOtherId();
                    Client * otherClntPtr = nullptr;
                    Client targetOther
                            = Client("", "", otherClientId/10, nullptr);
                    clientTree.retrieve(targetOther, otherClntPtr);
                    if((*clnt).move(amount, accType,
                                    otherClientId % 10, otherClntPtr)) {
                        (*clnt).addToHistory(trn);
                        Transaction * deptr
                            = new Transaction('D', otherClientId, -1, amount);
                        (*otherClntPtr).addToHistory(deptr);
                    }
                    break;
            }
        }
    }
}

//----------------------------------------------------------------------------
// endReport
// displays a report to show all clients in the firm and their original
// and current balances of their accounts.
void Firm::endReport(){
    cout << "REPORT" << endl << endl;
    clientTree.display();
}
