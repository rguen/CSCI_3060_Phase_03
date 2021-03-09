#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "account.h"
#include "login.h"

// New
#include <sstream>
#include <cstring>

using namespace std;

// Global Variables
vector<account> adminAccounts;
vector<account> standardAccounts;

// vector<string> loginType(std::vector<string> lType){
//     cout << "Select Session Type: Admin or Standard"<< endl;
//     cout<< lType[0];
//     if(lType[0] == "Admin"){
//         //setLoginType(lType);
//         // adminLogin(userInput);
//         cout << "Admin" << endl;
//     }else if(lType[0] == "Standard"){
//         //setLoginType(lType);
//         // standardLogin(userInput);
//     }else{
//         exit(0);
//     }
//     return lType;
// };




vector<string> readFile(string file) {
    std::vector<string> vec;
    string line;
    ifstream fin(file);
    if (!fin) cout << "Can not read file: " << file << endl;
    if (fin.is_open()) {
        while (getline(fin,line)) vec.push_back(line.substr(0,line.size()-1)); 
    }

    return vec;
}

int main(int argc, char *argv[]) { 
    //We need to create an input to take in the command line e.g bank-atm loginAccount1.txt transactionLoginAccount.Atf...
    // compareFiles("base.txt", "second.txt");
    
    std::vector<string> testVec = readFile(argv[1]);
   


    std::vector<string> testAccounts = readFile(argv[2]);
    for (int i = 0; i < testAccounts.size(); i++) {
        
        // Using stringstream to parse each line by the commas
        std::istringstream parseAccountInfo(testAccounts[i]);
        std::string token;
        std::vector<string> accountInfoVec;
        while(getline(parseAccountInfo, token, ',')) {
            accountInfoVec.push_back(token);
        }
        
        account newAccount(accountInfoVec[0], accountInfoVec[1],
                           stoi(accountInfoVec[2]), stof(accountInfoVec[3]),
                           accountInfoVec[4], accountInfoVec[5],accountInfoVec[6]);

        if (newAccount.getType() == "Admin") {
            adminAccounts.push_back(newAccount);
        }
        else {
            standardAccounts.push_back(newAccount);
        }

    }

 

    login session;
    session.setSessionCounter(0);

    session.loginType(testVec,session);



    return 0;
}