#ifndef _ORDER_
#define _ORDER_

#include <string>

using namespace std;

class Order {
public:
	Order();
	Order(string id, string goods, double price, int number, string date, string seller, string buyer);
	string getid(); string getgoods(); double getprice(); int getnumber(); string gettime(); string getbuyer();
	string getseller();
private:
	string order_id;
	string goods;
	double unit_price;
	int order_num;
	string order_time;
	string oreder_buyer;
	string order_seller;
};

# endif
