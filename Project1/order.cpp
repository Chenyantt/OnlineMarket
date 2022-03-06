#include "order.h"

#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

Order::Order() {
	order_num = -1;
}

Order::Order(string id, string g, double price, int number, string date, string s, string b) {
	order_id = id;
	goods = g;
	unit_price = price;
	order_num = number;
	order_time = date;
	order_seller = s;
	oreder_buyer = b;
}

string Order::getid() {
	return order_id;
} 

string Order::getgoods() {
	return goods;
} 

double Order::getprice() {
	return unit_price;
}

int Order::getnumber() {
	return order_num;
}

string Order::gettime() {
	return order_time;
}

string Order::getbuyer() {
	return oreder_buyer;
}

string Order::getseller() {
	return order_seller;
}