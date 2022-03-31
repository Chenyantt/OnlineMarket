#include "goods.h"

#include <string>

int Goods::GoodsNum = 0;

Goods::Goods() {
	goods_state = -1;
}

Goods::Goods(string* id, string* name, double p, int n, string* d, string* s,string* time,int state,string mode) {
	GoodsNum += 1;
	goods_id = *id;
	goods_name = *name;
	price = p;
	number = n;
	description = *d;
	seller = *s;
	goods_time = *time;
	goods_state = state;
	accountmode = mode;
}

Goods::Goods(Goods& g) {
	goods_id = g.goods_id;
	goods_name = g.goods_name;
	price = g.price;
	number = g.number;
	description = g.description;
	seller = g.seller;
	goods_time = g.goods_time;
	goods_state = g.goods_state;
	accountmode = g.accountmode;
}

//获取商品列表中的商品数
int Goods::GetNum() {
	return GoodsNum;
}

//更改列表中的商品数
void Goods::ModNum(int n) {
	GoodsNum = n;
	return;
}

//获取商品ID
string Goods::getid() const {
	return goods_id;
}

//获取商品的名字
string Goods::getname() const {
	return goods_name;
}

//获取商品的价格
double Goods::getprice() const {
	return price;
}

//获取商品的数字
int Goods::getnumber() const {
	return number;
}

//获取商品的描述
string Goods::getdes() const {
	return description;
}

//获取商品的卖家
string Goods::getseller() const {
	return seller;
}

//获取商品的上架时间
string Goods::gettime() const {
	return goods_time;
}

//获取商品的状态
int Goods::getstate() const {
	return goods_state;
}

//下架商品
void Goods::remove() {
	goods_state = 0;
	return;
}

//改变商品的价格
void Goods::mod_price(double pri) {
	price=pri;
	return;
}

//改变商品的描述
void Goods::mod_des(string des) {
	description = des;
	return;
}

//改变商品的数量
void Goods::mod_num(int num) {
	number = num;
	return;
}