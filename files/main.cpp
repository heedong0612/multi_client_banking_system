//  Donghee Lee
//  05/30/2019
//
//
//  In this main, a firm is built based on a textfile that contains client
//  information. Then, a transaction is constucted and executed based on
//  a text file that contains transaction information. At the end of execution,
//  it generates a report of all clients' before and after balances.
#include "firm.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    
    // Read in client information txt file
    ifstream clientInfo("clientData.txt");
    if (!clientInfo)  {
        cout << "\"clientData.txt\" File could not be opened." << endl;
        return 1;
    }
    
    // Build an object Firm with the client info
    Firm lose = Firm(clientInfo);

    // Read in transaction information txt file
    ifstream transactions("transactionRequests.txt");
    if (!transactions)  {
        cout << "\"transactionRequests.txt\" File could not be opened." << endl;
        return 1;
    }

    // Build a Transcation object within the Firm and conduct it
    lose.conductTransactions(transactions);
    return 0;
}
