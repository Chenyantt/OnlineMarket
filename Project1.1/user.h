#ifndef _USER_H_
#define _USER_H_

#include <string>

using namespace std;

class User {
public:
	User();
	User(string* id, string* name, string* password, string* phone, string* address, double m,int state);
	static int GetNum(); static void ModNum(int n);
	void menu(); void seller_menu(); void buyer_menu(); void self_menu();
	string getid() const; string getname() const; 
	string getpassword() const; string getphone() const;
	string getaddress() const; double getmoney() const;
	int getstate() const; void check_info() const; 
	void mod_info(); void recharge();
	void ban(); void mod_money(double n);
	void Account();
private:
	static int UserNum;
	string user_id;
	string user_name;
	string user_password;
	string user_phone;
	string user_address;
	double money;
	int state;
};

int IsNumberLegal(string s);

#endif