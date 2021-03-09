#include <string>
#include <cstdlib>
#include <vector>
#include "login.h"
#include "account.h"
#include "accDelete.h"
#include "miscFunctions.h"
#include "accDelete.h"


using namespace std; 

void accDelete::setDbPosition(int dbPosition){
	 this->dbPosition = dbPosition;
}

void accDelete::setANumber(string aNumber){

	this->aNumber = aNumber;
};

void accDelete::setAName(string aName){
	this->aName = aName;
};


int accDelete::getDbPosition(){
	return this->dbPosition;
}


string accDelete::getANumber(){
	return this->aNumber;
};

string accDelete::getAName(){
	return this->aName;
};



void accDelete::deleteAccount(vector<string> lType,login session, accDelete delAcc){
	string aName;
	string aNumber;
	if(session.getLoginType() == "Admin"){
		cout << "Enter Account Holders Name"<< endl;
		aName = lType[session.updateSessionCounter()];
		delAcc.setAName(aName);
		cout << "Enter Account Number" << endl;
		aNumber =lType[session.updateSessionCounter()];
		delAcc.setANumber(aNumber);
		bool verify = false;
		for(int i =0; i<standardAccounts.size();i++){
			if(stoi(delAcc.getANumber())==standardAccounts[i].getAccountNumber()){

				delAcc.setDbPosition(i);
				verify = true;

			}			


		}
		if(verify==true){
			int temp = delAcc.getDbPosition();
			if(delAcc.getAName()==standardAccounts[temp].getAccountName()){
				cout<<"Verification Successful"<<endl;
				standardAccounts.erase(standardAccounts.begin()+temp);
				cout<<"Account Successfully Deleted"<<endl;
			}else{
				cout<<"Error: Account holder name does not match"<<endl;
			}
		}else{
			cout <<"Error: Account does not exist"<<endl;
		}
		tChooser(lType,session);

	}else {
		exit(0);
	}
};
