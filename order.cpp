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

//获取订单列表的订单总数
int Order::GetNum() {
	return OrderNum;
}

//改变订单列表的订单总数
void Order::ModNum(int n) {
	OrderNum = n;
	return;
}

//获取订单ID
string Order::getid() const {
	return order_id;
} 

//获取订单商品
string Order::getgoods() const {
	return goods;
} 

//获取商品单价
double Order::getprice() const {
	return unit_price;
}

//获取商品购买数量
int Order::getnumber() const {
	return order_num;
}

//获取交易时间
string Order::gettime() const {
	return order_time;
}

//获取买家ID
string Order::getbuyer() const {
	return oreder_buyer;
}

//获取卖家ID
string Order::getseller() const {
	return order_seller;
}