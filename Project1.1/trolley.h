#ifndef _TROLLEY_H_
#define _TROLLEY_H_

#include <string>
#include "user.h"

using namespace std;

class Trolley;

class Item {
public:
	friend Trolley;
	Item();
	Item(string i, string t, string na, string s, double p, int n, int st);
	string getid() const; string getname() const; string gettime() const;
	int getnum() const; double getprice() const; string getseller() const;
	int getstate() const; void add_num(int n); void mod_state(int n);
private:
	string id;
	string name;
	string time;
	string seller;
	double price;
	int number;
	int state;
};

class Trolley {
public:
	friend void InitTrolley();
	friend void SaveTrolley();
	friend void BanSeller(string command, int mode, string id);
	friend void RemoveGoods(string command, int mode, string id);
	friend void BuyGoods(string command, int mode, string id);
	Trolley();
	Trolley(Item i[], User* id, int j);
	int getnum() const;
	void check();
	void add(string id, string name, string time, string seller, double p, int n);
	int remove(string id, int n);
	int buy(string id, int n);
	int clear();
private:
	Item items[20];
	int num;
	User* owner;
};

#endif

