#ifndef _GOODS_
#define _GOODS_

#include <string>

using namespace std;

class Goods
{
public:
	Goods();
	Goods(string* id, string* name, double p,int n, string* d, string* s,string* time,int state);
	static int GetNum();
	string getid() const; string getname() const; 
	double getprice() const; int getnumber() const;
	string getdes() const; string getseller() const; 
	string gettime() const; int getstate() const;
	void remove(); void mod_price(double pri); 
	void mod_des(string des); void mod_num(int num);
private:
	static int GoodsNum;
	string goods_id;
	string goods_name;
	double price;
	int number;
	string description;
	string seller;
	string goods_time;
	int goods_state;
};

#endif