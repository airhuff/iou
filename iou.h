#ifndef IOU_H
#define IOU_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

struct Debt {
	bool isactive;
	string from;
	string to;
	int value;
	string description;
};

class IOU {
public:
	IOU(int numusers,int olddebts, string* s);
	~IOU();
	void addDebt(string from,string to,int value,string description,bool isnew=true);
	void addDebtbyUsers(string* from,string* to, int value, string description);
	void delDebt(int i);
	void printAll();
	void printRecent();
	void addUser(string s);
	void delUser(string s);
	bool isUser(string s);
	int numUsers() { return userNum;}
	int numDebts() { return activeNum;}
	string userList();
	string debtList();
	void printMatrix();
private:
	int activeNum;
	int debtNum;
	int userNum;
	int debtMax;
	string* users;
	int** matrix;
	Debt* debts;
	void printDebt(int i);
	int* str2indices(string s);
	string userarr2str(string* arr);
};




#endif
