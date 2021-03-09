#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "transfer.h"
#include "login.h"
#include "account.h"
#include "miscFunctions.h"

using namespace std;


transfer::transfer() {}

void transfer::setSession(login session) {

    if (session.getLoginType() == "Admin") {
        this->adminTransaction = true;
    }
    else {
        this->adminTransaction = false;
    }
}

void transfer::setAccountFrom(vector<string> lType, login session, string accountNum, string name) {
    int accountNumber;
    string holderName;

    if (holderName != "") {
        cout << "Please enter the account holder's name:" << endl;
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
            cout << "Error: Name not found" << endl;
            tChooser(lType, session);
        }

        cout << "Please enter the account number: " << endl;
        accountNumber = stoi(accountNum);

        // Seeing if the account exists in the standardAccount vector
        bool foundNum = false;
        for (int i = 0; i < standardAccounts.size(); i++) {
            if ((holderName == standardAccounts[i].getAccountName()) &&
                (accountNumber == standardAccounts[i].getAccountNumber()) &&
                foundName == true) {
                foundNum = true;
                this->accountFrom = &standardAccounts[i];
                cout << "Account number valid" << endl;
            }
        }

        if (foundNum == false) {
            cout << "Error: Account holder’s name does not match with account number" << endl;
            tChooser(lType, session);
        }
    }
    else {
        cout << "Please enter the account number:" << endl;
        accountNumber = stoi(accountNum);

        // Seeing if the account exists in the standardAccount vector
        bool found = false;
        for (int i = 0; i < standardAccounts.size(); i++) {
            if (accountNumber == standardAccounts[i].getAccountNumber()) {
                found = true;
                this->accountFrom = &standardAccounts[i];
                cout << "Account number valid" << endl;
            }
        }

        if (found == false) {
            cout << "Error: Account number invalid" << endl;
            tChooser(lType, session);
        }
    }
}

void transfer::setAccountTo(vector<string> lType, login session, string accountNum) {

    int accountNumber;

    cout << "Please enter the account number:" << endl;
    accountNumber = stoi(accountNum);

    // Checking that the sending and receiving accounts are not the same
    if (accountNumber == accountFrom->getAccountNumber()) {
        cout << "Error: Transferring account and receiving account cannot be the same" << endl;
        tChooser(lType, session);
    }
    else {    
        // Seeing if the account exists in the standardAccount vector
        bool found = false;
        for (int i = 0; i < standardAccounts.size(); i++) {
            if (accountNumber == standardAccounts[i].getAccountNumber()) {
                found = true;
                this->accountTo = &standardAccounts[i];
                cout << "Account number valid" << endl;
            }
        }

        if (found == false) {
            cout << "Error: Account number invalid" << endl;
            tChooser(lType, session);
        }
    }
}

void transfer::setAmount(vector<string> lType, login session, string setAmount) {
    float amount;

    cout << "Please enter the amount to transfer: " << endl;
    amount = stof(setAmount);

    if (adminTransaction == true  && amount > 0.00) {
        this->transferAmount = amount;
        cout << "Valid amount" << endl;
    }
    else if (adminTransaction == false && amount > 0.00 && amount < 1000.00) {
        this->transferAmount = amount;
        cout << "Valid amount" << endl;
    }
    else if (adminTransaction == false && amount > 1000.00) {
        cout << "Error: Selected transfer amount exceeds the $1000 session transfer limit" << endl;
        tChooser(lType, session);
    }
    else if (amount <= 0.00) {
        cout << "Error: Selected transfer amount must be greater than $0.00" << endl;
        tChooser(lType, session);
    }
    else {
        cout << "Error: Cannot transfer set amount" << endl;
        tChooser(lType, session);
    }
}

void transfer::conductTransfer(vector<string> lType, login session) {

    cout << "Transfer selected" << endl;
    //cout << lType[session.getSessionCounter()] << endl;

    setSession(session);
    
    if (lType[session.getSessionCounter()] != "cancelTransfer") {
        if (adminTransaction == true) {
            string name = lType[session.updateSessionCounter()];
            string account = lType[session.getSessionCounter()];
            setAccountFrom(lType, session, account, name);
            session.updateSessionCounter();
        }
        else if (adminTransaction == false){
            setAccountFrom(lType, session, lType[session.updateSessionCounter()], "");
        }
    }

    if (lType[session.getSessionCounter()] != "cancelTransfer") {
        setAccountTo(lType, session, lType[session.updateSessionCounter()]);
    }

    if (lType[session.getSessionCounter()] != "cancelTransfer") {
        setAmount(lType, session, lType[session.updateSessionCounter()]);
    }

    if (lType[session.getSessionCounter()] != "cancelTransfer") {
        if (accountTo->getAccountStatus() != "D" && accountFrom->getAccountStatus() != "D") {
            float accountFromBalance = accountFrom->getBalance();
            float accountToBalance = accountTo->getBalance();

            if ((accountFromBalance - transferAmount) >= 0.00 && (accountToBalance + transferAmount) >= 0.00) {
                accountFrom->setBalance(accountFromBalance - transferAmount);
                accountTo->setBalance(accountToBalance + transferAmount);
                // saveLogs();
                cout << "Transfer successful" << endl;
            }
            else if ((accountFromBalance - transferAmount) < 0.00 && (accountToBalance + transferAmount) >= 0.00) {
                cout << "Error: Transferring account must have a balance of at least $0.00 after interaction" << endl;
            }
            else if ((accountFromBalance - transferAmount) >= 0.00 && (accountToBalance + transferAmount) < 0.00) {
                cout << "Error: Receiving account must have a balance of at least $0.00 after interaction" << endl;
            }
            else {
                cout << "Error: Transfer unsuccessful" << endl;
            }
        }
        else {
            cout << "Error: One or more of the selected accounts are disabled" << endl;
        }

        tChooser(lType,session);
    }
    else {
        cout << "Transfer cancelled" << endl;
        session.updateSessionCounter();
        tChooser(lType,session);
    }
}

/*
void transfer::saveLogs() {
    FILE file = "transfer_" + transactionNumber + ".etf";
    fstream stream;
    stream.open(file, ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "02_" << accountFrom.getAccountName() << "_"
               << accountFrom.getAccountNumber() << "_-" << transferAmount
               << "___"
               
               << endl

               << "02_" << accountTo.getAccountName() << "_"
               << accountTo.getAccountNumber() << "_+" << transferAmount
               << "___" << endl;
    }
    close(file);
}
*/