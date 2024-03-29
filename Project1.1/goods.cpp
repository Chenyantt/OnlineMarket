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

int Goods::GetNum() {
	return GoodsNum;
}

void Goods::ModNum(int n) {
	GoodsNum = n;
	return;
}

string Goods::getid() const {
	return goods_id;
}

string Goods::getname() const {
	return goods_name;
}

double Goods::getprice() const {
	return price;
}

int Goods::getnumber() const {
	return number;
}

string Goods::getdes() const {
	return description;
}
string Goods::getseller() const {
	return seller;
}

string Goods::gettime() const {
	return goods_time;
}

int Goods::getstate() const {
	return goods_state;
}

void Goods::remove() {
	goods_state = 0;
	return;
}

void Goods::mod_price(double pri) {
	price=pri;
	return;
}

void Goods::mod_des(string des) {
	description = des;
	return;
}

void Goods::mod_num(int num) {
	number = num;
	return;
}