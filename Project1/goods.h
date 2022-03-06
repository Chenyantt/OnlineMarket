#ifndef _GOODS_
#define _GOODS_

#include <string>

using namespace std;

class Goods
{
public:
	Goods();
	Goods(string* id, string* name, double p,int n, string* d, string* s,string* time,int state);
	string getid(); string getname(); double getprice(); int getnumber(); 
	string getdes(); string getseller(); string gettime(); int getstate();
	void ban(); void mod_price(double pri); void mod_des(string des); void mod_num(int num);
private:
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
