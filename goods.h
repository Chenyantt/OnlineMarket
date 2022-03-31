#ifndef _GOODS_H_
#define _GOODS_H_

#include <string>

using namespace std;

//商品类
class Goods
{
public:
	Goods();
	Goods(string* id, string* name, double p,int n, string* d, string* s,string* time,int state,string mode);
	Goods(Goods& g);
	static int GetNum(); //获取商品列表中的商品数
	static void ModNum(int n);//更改列表中的商品数
	string getid() const; //获取商品ID
	string getname() const; //获取商品的名字
	double getprice() const; //获取商品的价格
	int getnumber() const;//获取商品的数字
	string getdes() const;//获取商品的描述
    string getseller() const; //获取商品的卖家
	string gettime() const; //获取商品的上架时间
	int getstate() const;//获取商品的状态
	void remove();//下架商品
	void mod_price(double pri); //改变商品的价格
	void mod_des(string des);//改变商品的描述 
	void mod_num(int num);//改变商品的数量
	string accountmode;
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