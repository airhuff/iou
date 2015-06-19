#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "iou.h"

using namespace std;

const char file[] = "iou.dat";

IOU* getData() {
	int userNum,debtNum;
	ifstream inp;
	inp.open(file);
	if (!inp.is_open()) {
		cout << "Error: Unable to open file." << endl;
		return 0;
	}
	inp >> userNum;
	string* users = new string[userNum];
	for (int i=0;i<userNum;i++)
		inp >> users[i];
	inp >> debtNum;
	IOU* obj = new IOU(userNum,debtNum,users);	

	string from,to,description;
	int value;
	for (int i=0;i<debtNum;i++) {
		inp >> from >> to >> value >> description;
		obj->addDebt(from,to,value,description);
	}

	inp.close();
	return obj;
}

void saveData(IOU* obj) {
	ofstream out;
	out.open(file);
	out << obj->userList() << obj->debtList();
	out.close();
}

string prompt(string query) {
	string out;
	cout << query << ">>> ";
	getline(cin,out);
	return out;
}

int dollars2cents(string dol) {
	if (dol[dol.length()-3] != '.')
		return -1;
	dol.erase(dol.length()-3,1);
	for (unsigned int i=0;i<dol.length();i++)
		if (!isdigit(dol[i]))
			return -1;
	stringstream ss;
	unsigned int i;
	ss << dol;
	ss >> i;
	return i;
}

void getNew(IOU* obj) {
	int userlistnum = 0,userlistnum2 = 0,dol;
	string input,value;
	string userlist[100],userlist2[100];
	input = prompt("Who owes money?\n");
	while (input != "") {
		if (!obj->isUser(input)) {
			cout << "ERROR: Unrecognized user. Try again.\n";
			input = prompt("");
			continue;
		}
		userlist[userlistnum] = input;
		userlistnum++;
		input = prompt("");
	}
	input = prompt("Who is owed money?\n");
	while (input != "") {
		if (!obj->isUser(input)) {
			cout << "ERROR: Unrecognized user. Try again.\n";
			input = prompt("");
			continue;
		}
		userlist2[userlistnum2] = input;
		userlistnum2++;
		input = prompt("");
	}
	cout << "What amount of money is owed?" << endl << ">>> $";
	while (true) {
		cin >> value;
		cin.get();
		dol = dollars2cents(value);
		if (dol != -1)
			break;
		cout << "ERROR: Invalid format. Try again.\n>>> $";
		
	}
	input = prompt("Give a description of the debt.\n");

	obj->addDebtbyUsers(userlist,userlist2,dollars2cents(value),input);

}

void Repay(IOU* obj) {
	string user1[100],user2[100],value;
	user1[0] = prompt("Who is paying?\n");
	user2[0] = prompt("Who is being paid?\n");
	cout << "What amount of money is being paid?" << endl << ">>> $";
	cin >> value;
	cin.get();
	obj->addDebtbyUsers(user2,user1,dollars2cents(value),"Repayment");
}

int main() {
	IOU* obj = getData();
	string input;
	while (true) {
		input = prompt("");
		if (input == "new")
			getNew(obj);
		else if (input == "repay")
			Repay(obj);
		else if (input == "show debts")
			obj->printAll();
		else if (input == "show grid")
			obj->printMatrix();
		else if (input == "save")
			saveData(obj);
		else if (input == "help")
			cout << "sorry";
		else if (input == "quit" || input == "exit")
			break;
		else
			cout << "ERROR: Invalid command.\n";
	}


	saveData(obj);

	delete obj;
	return 0;
}
