#ifndef _ORDER_H_
#define _ORDER_H_

#include <string>

using namespace std;

//订单类 
class Order {
public:
	Order();
	Order(string id, string goods, double price, int number, string date, string seller, string buyer);
	static int GetNum(); //获取订单列表的订单总数
	static void ModNum(int n);//改变订单列表的订单总数
	string getid() const; //获取订单ID
	string getgoods() const;//获取订单商品
	double getprice() const; //获取商品单价
	int getnumber() const;//获取商品购买数量
	string gettime() const; //获取交易时间
	string getbuyer() const;//获取买家ID
	string getseller() const;//获取卖家ID
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