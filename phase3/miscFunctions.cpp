#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "miscFunctions.h"
#include "account.h"
#include "login.h"
#include "accDelete.h"
#include "logout.h"
#include "paybill.h"
#include "changeplan.h"
#include "transfer.h"
#include "disable.h"

void tChooser(vector<string> lType,login session){
	
	if(session.getLoginType()=="Standard"){
		string transaction = lType[session.updateSessionCounter()];
		if(transaction == "Withdrawal"){

		}else if(transaction == "Transfer"){
			transfer trans;
			trans.conductTransfer(lType,session);
		}else if(transaction=="Paybill"){
			payBill p;
			p.paybill(lType,session);
		}else if(transaction == "Deposit"){
			
		}else if(transaction == "Logout"){
			logout account;
			account.accLogout(lType,session);
			
		}else if(transaction == "Create" || transaction == "Delete" || transaction == "Disable" || transaction == "Changeplan"){
			cout<<"Error: User lacks permissions to access this function"<<endl;
			tChooser(lType,session);
			
		}else if(transaction == "Login"){
			cout<<"Error: User cannot login into another account while logged in"<<endl;
			tChooser(lType,session);

		}else{
			exit(0);
		}

	}else if(session.getLoginType()=="Admin"){
		//int temp = session.updateSessionCounter();
		string transaction = lType[session.updateSessionCounter()];
		
		if(transaction == "Create"){
			//callCreate
		}else if(transaction == "Delete"){

			accDelete delAcc;
			delAcc.deleteAccount(lType,session,delAcc);
			

		}else if(transaction=="Paybill"){
			payBill p;
			p.paybill(lType,session);
		}else if(transaction == "Disable"){
			disable dis;
			dis.disableAccount(lType,session);
			
		}else if(transaction == "Changeplan"){
			changePlan c;
			c.ChangePaymentType(lType,session);
			
		}else if(transaction == "Logout"){
			// cout <<"testing" << endl; 
			logout account;
			account.accLogout(lType,session);
			
		}else if(transaction == "Transfer"){
			transfer trans;
			trans.conductTransfer(lType,session);
		}else if(transaction == "Login"){
			cout<<"Error: User cannot login into another account while logged in"<<endl;
			tChooser(lType,session);

		}else{
			exit(0);
		}
	}
};


