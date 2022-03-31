#ifndef _TROLLEY_H_
#define _TROLLEY_H_

#include <string>
#include "user.h"

using namespace std;

class Trolley;

//购物车中的商品类
class Item {
public:
	friend Trolley;
	Item();
	Item(string i, string t, string na, string s, double p, int n, int st);
	string getid() const; //获取物品ID
	string getname() const; //获取物品名称
	string gettime() const;//获取上架时间
	int getnum() const; //获取物品价格
	double getprice() const; //获取购物车中该物品数量
	string getseller() const;//获取物品状态
	int getstate() const; //获取物品卖家
	void add_num(int n); //增加购物车中物品数量
	void mod_state(int n);//改变物体状态
private:
	string id;
	string name;
	string time;
	string seller;
	double price;
	int number;
	int state;
};

//购物车类
class Trolley {
public:
	friend void InitTrolley();
	friend void SaveTrolley();
	friend void BanSeller(string command, int mode, string id);
	friend void RemoveGoods(string command, int mode, string id);
	friend void BuyGoods(string command, int mode, string id);
	Trolley();
	Trolley(Item i[], User* id, int j);
	int getnum() const;//获取购物车中商品总数
	void check();//查看购物车中的商品并展示
	void add(string id, string name, string time, string seller, double p, int n);//加入购物车
	int remove(string id, int n);//移出购物车
	int buy(string id, int n);//购买单件商品
	int clear();//清空购物车
private:
	Item items[20];
	int num;
	User* owner;
};

#endif

