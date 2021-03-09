#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "disable.h"
#include "login.h"
#include "account.h"
#include "miscFunctions.h"

using namespace std;


disable::disable() {}

void disable::setSession(login session) {

    if (session.getLoginType() == "Admin") {
        this->adminTransaction = true;
    }
    else {
        this->adminTransaction = false;
    }
}

void disable::setSelectedAccount(vector<string> lType, login session, string accountNum, string name) {
    if (adminTransaction == true) {
        string holderName;
        int accountNumber;

        cout << "Please enter bank account holder's name:" << endl;
        holderName = name;

        // Seeing if the name exists in the standardAccount vector
        bool foundName = false;
        for (int i = 0; i < standardAccounts.size(); i++) {
            if (holderName == standardAccounts[i].getAccountName()) {
                foundName = true;
                cout << "Valid account holder" << endl;
            }
        }

        if (foundName == false) {
            cout << "Error: Account holder's name could not be found" << endl;
            tChooser(lType, session);
        }

        if (lType[session.getSessionCounter()] != "cancelDisable") {
            
            cout << "Please enter the account number:" << endl;
            accountNumber = stoi(accountNum);

            // Seeing if the account exists in the standardAccount vector
            bool foundNum = false;
            for (int i = 0; i < standardAccounts.size(); i++) {
                if ((holderName == standardAccounts[i].getAccountName()) &&
                    (accountNumber == standardAccounts[i].getAccountNumber()) &&
                    foundName == true) {
                    foundNum = true;
                    this->selectedAccount = &standardAccounts[i];
                    cout << "Account number valid" << endl;
                }
            }

            if (foundNum == false) {
                cout << "Error: Account number is not under the holder’s name" << endl;
                session.updateSessionCounter();
                tChooser(lType, session);
            }
        }
        else {
            cout << "Account disable cancelled" << endl;
            session.updateSessionCounter();
            tChooser(lType,session);
        }
    }
    else {
        cout << "Error: You can only disable an account in admin mode" << endl;
        tChooser(lType, session);
    }
}

void disable::disableAccount(vector<string> lType, login session) {

    cout << "Disable account selected" << endl;

    setSession(session);

    if (lType[session.getSessionCounter()] != "cancelDisable") {
        string name = lType[session.updateSessionCounter()];
        string account = lType[session.getSessionCounter()];
        setSelectedAccount(lType, session, account, name);
        session.updateSessionCounter();
    }

    if (lType[session.getSessionCounter()] != "cancelDisable") {
        if (selectedAccount->getAccountNumber() != 0 && selectedAccount->getAccountStatus() == "A" && adminTransaction == true) {
            selectedAccount->setAccountStatus("D");
            // saveLogs();
            cout << "Account successfully disabled" << endl;
        }
        else {
            cout << "Account could not be disabled" << endl;
        }
        
        //cout << lType[session.getSessionCounter()] << endl;
        tChooser(lType,session);
    }
    else {
        cout << "Account disable cancelled" << endl;
        session.updateSessionCounter();
        tChooser(lType,session);
    }
}

/*
void disable::saveLogs() {
    FILE file = "disable_" + transactionNumber + ".etf";
    fstream stream;
    stream.open(file, ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "07_" << selectedAccount.getAccountName() << "_"
               << selectedAccount.getAccountNumber() << "_00000.00"
               << "__D" << endl;
    }
    close(file);
}
*/