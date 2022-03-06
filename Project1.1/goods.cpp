#include "goods.h"

#include <string>

int Goods::GoodsNum = 0;

Goods::Goods() {
	goods_state = -1;
}

Goods::Goods(string* id, string* name, double p, int n, string* d, string* s,string* time,int state) {
	GoodsNum += 1;
	goods_id = *id;
	goods_name = *name;
	price = p;
	number = n;
	description = *d;
	seller = *s;
	goods_time = *time;
	goods_state = state;
}

int Goods::GetNum() {
	return GoodsNum;
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