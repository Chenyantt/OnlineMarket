#include "goods.h"

#include <string>

Goods::Goods() {
	goods_state = -1;
}

Goods::Goods(string* id, string* name, double p, int n, string* d, string* s,string* time,int state) {
	goods_id = *id;
	goods_name = *name;
	price = p;
	number = n;
	description = *d;
	seller = *s;
	goods_time = *time;
	goods_state = state;
}
string Goods::getid(){
	return goods_id;
}
string Goods::getname() {
	return goods_name;
}
double Goods::getprice() {
	return price;
}
int Goods::getnumber() {
	return number;
}
string Goods::getdes() {
	return description;
}
string Goods::getseller() {
	return seller;
}
string Goods::gettime() {
	return goods_time;
}
int Goods::getstate() {
	return goods_state;
}

void Goods::ban() {
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