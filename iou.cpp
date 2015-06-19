#include "iou.h"

IOU::IOU(int numusers,int olddebts, string* s):
	activeNum(0),debtNum(0),userNum(numusers),debtMax(olddebts+100) {
	users = new string[numusers];
	for (int i=0;i<numusers;i++)
		users[i] = s[i];
	matrix = new int* [userNum];
	for (int i=0;i<userNum;i++)
		matrix[i] = new int[userNum]();
	debts = new Debt[olddebts+100];
}

IOU::~IOU() {
	delete[] users;
	for (int i=0;i<userNum;i++)
		delete[] matrix[i];
	delete[] matrix;
	delete[] debts;
}

int* IOU::str2indices(string s) {
	unsigned int i;
	int* out = new int[s.length()/2];
	for (i=0;i<s.length()/2;i++)
		out[i] = 10*(s[2*i]-'0')+(s[2*i+1]-'0');
	return out;
}

string IOU::userarr2str(string* arr) {
	string s = arr[0],sav = "",ret;
	int i = 0,j;
	while (s != "") {
		for (j=0;j<userNum;j++)
			if (users[j] == s)
				break;
		stringstream ss;
		ss << j;
		ss >> ret;
		if (ret.length() == 1)
			ret = "0" + ret;
		sav += ret;
		i++;
		s = arr[i];
	}
	return sav;
}

void IOU::addDebt(string from,string to,int value,string description,bool isnew) {
	if (isnew) {
		debts[debtNum].isactive = true;
		debts[debtNum].from = from;
		debts[debtNum].to = to;
		debts[debtNum].value = value;
		debts[debtNum].description = description;
		debtNum++;
		activeNum++;
	}
	int* fromvec = str2indices(from);
	int* tovec = str2indices(to);
	int amount = value*4/(from.length()*to.length());
	for (unsigned int i=0;i<from.length()/2;i++)
		for (unsigned int j=0;j<to.length()/2;j++) {
			matrix[fromvec[i]][tovec[j]] += amount;
			matrix[tovec[j]][fromvec[i]] -= amount;
		}
	delete fromvec;
	delete tovec;
}

void IOU::addDebtbyUsers(string* from,string* to,int value,string description) {
	addDebt(userarr2str(from),userarr2str(to),value,description);	
}

void IOU::delDebt(int i) {
	debts[i].isactive = false;
	activeNum--;
	addDebt(debts[i].to,debts[i].from,debts[i].value,debts[i].description,false);
}

string IOU::userList() {
	stringstream ss;
	ss << userNum << endl;
	for (int i=0;i<userNum;i++)
		ss << users[i] << endl;
	return ss.str();
}

string IOU::debtList() {
	stringstream ss;
	ss << debtNum << endl;
	for (int i=0;i<debtNum;i++)
		if (debts[i].isactive)
			ss << debts[i].from << " " << debts[i].to << " " << debts[i].value
						<< " " << debts[i].description << endl;
	return ss.str();
}

string int2money(int i) {
	stringstream ss;
	string s;
	ss << setw(3) << setfill('0') << i;
	ss >> s;
	s.insert(s.length()-2,".");
	return s;
}

void IOU::printMatrix() {
	cout << setw(40) << "Debtee" << endl;
	cout << setw(12) << "Debtor";
	for (int k=0;k<userNum;k++)
		cout << setw(12) << users[k];
	cout << endl;
	for (int i=0;i<userNum;i++) {
		cout << setw(12) << users[i];
		
		for (int j=0;j<userNum;j++) {
			if (i==j)
				cout << setw(12) << "XXX" << " ";
			else
				cout << setw(12) << int2money(matrix[i][j]) << " ";
		}
		cout << endl;
	}
}

void IOU::printDebt(int i) {
	int* from = str2indices(debts[i].from);
	int* to = str2indices(debts[i].to);
	unsigned int j;
	for (j=0;j<debts[i].from.length()/2;j++) {
		if (j == debts[i].from.length()/2-1) {
			if (j > 0)
				cout << "and ";
			cout << users[from[j]] << " ";
		}
		else if (j == debts[i].from.length()/2-2)
			cout << users[from[j]] << " ";
		else
			cout << users[from[j]] << ", ";
	}
	if (j == 1)
		cout << "owes ";
	else
		cout << "owe ";
	for (j=0;j<debts[i].to.length()/2;j++)
		if (j == debts[i].to.length()/2-1) {
			if (j > 0)
				cout << "and ";
			cout << users[to[j]] << " ";
		}
		else if (j == debts[i].to.length()/2-2)
			cout << users[to[j]] << " ";
		else
			cout << users[to[j]] << ", ";
	cout << "$" << int2money(debts[i].value) << " for " << debts[i].description << endl;
	
	delete from;
	delete to;
}

void IOU::printAll() {
	for (int i=0;i<debtNum;i++)
		if (debts[i].isactive)
			printDebt(i);
}

bool IOU::isUser(string s) {
	for (int i=0;i<userNum;i++)
		if (s == users[i])
			return true;
	return false;
}

void IOU::printRecent() {

}

void IOU::addUser(string s) {

}

void IOU::delUser(string s) {

}
