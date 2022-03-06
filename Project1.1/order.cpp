#include "order.h"

#include <string>

using namespace std;

int Order::OrderNum = 0;

Order::Order() {
	order_num = -1;
}

Order::Order(string id, string good, double price, int number, string date, string seller, string buyer) {
	OrderNum += 1;
	order_id = id;
	goods = good;
	unit_price = price;
	order_num = number;
	order_time = date;
	order_seller = seller;
	oreder_buyer = buyer;
}

int Order::GetNum() {
	return OrderNum;
}

string Order::getid() const {
	return order_id;
} 

string Order::getgoods() const {
	return goods;
} 

double Order::getprice() const {
	return unit_price;
}

int Order::getnumber() const {
	return order_num;
}

string Order::gettime() const {
	return order_time;
}

string Order::getbuyer() const {
	return oreder_buyer;
}

string Order::getseller() const {
	return order_seller;
}