#ifndef _USER_
#define _USER_

#include <string>

using namespace std;

class User {
public:
	User(string* id, string* name, string* password, string* phone, string* address);
	User(string* id, string* name, string* password, string* phone, string* address, double m,int state);
	User();
	void menu(); void seller_menu(); void buyer_menu(); void self_menu();
	string getid(); string getname(); string getpassword(); string getphone();
	string getaddress(); double getmoney(); int getstate();
	void check_info(); void mod_info(); void recharge();
	void ban(); void mod_money(double n);
private:
	string user_id;
	string user_name;
	string user_password;
	string user_phone;
	string user_address;
	double money;
	int state;
};

#endif

