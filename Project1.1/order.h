#ifndef _ORDER_
#define _ORDER_

#include <string>

using namespace std;

class Order {
public:
	Order();
	Order(string id, string goods, double price, int number, string date, string seller, string buyer);
	static int GetNum();
	string getid() const; string getgoods() const;
	double getprice() const; int getnumber() const;
	string gettime() const; string getbuyer() const;
	string getseller() const;
private:
	static int OrderNum;
	string order_id;
	string goods;
	double unit_price;
	int order_num;
	string order_time;
	string oreder_buyer;
	string order_seller;
};

# endif