#include "trolley.h"

#include <iostream>
#include <string>
#include <iomanip>

#include "color.h"
#include "register.h"
#include "user.h"
#include "data.h"
#include "insert.h"
#include "update.h"

using namespace std;

Item::Item() {
	id = "";
	number = 0;
}

Item::Item(string i, string t, string na, string s, double p, int n,int st) {
	id = i;
	price = p;
	number = n;
	name = na;
	seller = s;
	time = t;
	state = st;
}

string Item::getid() const {
	return id;
}

string Item::getname() const {
	return name;
}

string Item::gettime() const {
	return time;
}

double Item::getprice() const {
	return price;
}

int Item::getnum() const {
	return number;
}

int Item::getstate() const {
	return state;
}

string Item::getseller() const {
	return seller;
}

void Item::add_num(int n) {
	number += n;
	return;
}

void Item::mod_state(int n) {
	state = n;
	return;
}


Trolley::Trolley() {
	num = 0;
}

Trolley::Trolley(Item i[], User* id, int j) {
	owner = id;
	num = j;
	for (int k = 0; k < j; ++k) {
		items[k] = i[k];
	}
}

int Trolley::getnum() const {
	return num;
}

void Trolley::check() {
	cout << left;
	if (num == 0) { 
		cout << "购物车为空!!!" << endl;
		return;
	}
	system("cls");
	while (true) {
		cout << "********************************************************************************************" << endl;
		cout << setw(10) << "商品ID" << setw(15) << "名称" << setw(8) << "价格" <<setw(8) <<"数量"
			<< setw(15) << "上架时间" << setw(10) << "卖家ID" << setw(10) << "商品状态" << endl;
		for (int i = 0; i < num; ++i) {
			cout << setw(10) << items[i].getid() << setw(15) << items[i].getname() << fixed << setprecision(1)
				<< setw(8) << items[i].getprice() << setw(8) << items[i].getnum() << setw(15) 
				<< items[i].gettime() << setw(10) << items[i].getseller() ;
			if (items[i].getstate() == 1) cout << setw(10) << "销售中" << endl;
			else cout << setw(10) << "已售罄" << endl;
		}
		cout << "********************************************************************************************" << endl;
	back:
		string input;
		cout << "(可选择商品的排列顺序：a.按商品名称  b.最早发布 c.最近发布 d.价格从低到高 e.价格从高到低 " << endl;
		cout << " 可选择操作： 1.清空购物车 2.购买单件商品 3.将商品移出购物车 4.返回主界面)" << endl;
		cout << " 请输入：";
		getline(cin, input);
		while (input == "") getline(cin, input);
		string goods_name, number;
		if (input.length() != 1) {
			cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl;
			goto back;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case 'a':
				for (int i = 0; i < num - 1; ++i) {
					int min_index = i;
					for (int j = i + 1; j < num; ++j) {
						if (items[min_index].getname() > items[j].getname()) {
							min_index = j;
						}
					}
					if (min_index != i) {
						Item tmp(items[i]);
						items[i] = items[min_index];
						items[min_index] = tmp;
					}
				}
				break;
			case 'b':
				for (int i = 0; i < num - 1; ++i) {
					int min_index = i;
					for (int j = i + 1; j < num; ++j) {
						if (items[min_index].gettime() > items[j].gettime()) {
							min_index = j;
						}
					}
					if (min_index != i) {
						Item tmp(items[i]);
						items[i] = items[min_index];
						items[min_index] = tmp;
					}
				}
				break;
			case 'c':
				for (int i = 0; i < num - 1; ++i) {
					int max_index = i;
					for (int j = i + 1; j < num; ++j) {
						if (items[max_index].gettime() < items[j].gettime()) {
							max_index = j;
						}
					}
					if (max_index != i) {
						Item tmp(items[i]);
						items[i] = items[max_index];
						items[max_index] = tmp;
					}
				}
				break;
			case 'd':
				for (int i = 0; i < num - 1; ++i) {
					int min_index = i;
					for (int j = i + 1; j < num; ++j) {
						if (items[min_index].getprice() > items[j].getprice()) {
							min_index = j;
						}
					}
					if (min_index != i) {
						Item tmp(items[i]);
						items[i] = items[min_index];
						items[min_index] = tmp;
					}
				}
				break;
			case 'e':
				for (int i = 0; i < num - 1; ++i) {
					int max_index = i;
					for (int j = i + 1; j < num; ++j) {
						if (items[max_index].getprice() < items[j].getprice()) {
							max_index = j;
						}
					}
					if (max_index != i) {
						Item tmp(items[i]);
						items[i] = items[max_index];
						items[max_index] = tmp;
					}
				}
				break;
			case '1':
				if (clear()) return;
				break;
			case '2':
				cout << "请输入商品ID：";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				cout << "请输入商品数量：";
				getline(cin, number);
				while (number == "") getline(cin, number);
				if (!IsLegal(number, 10, 4) || !IsNumberLegal(number)) {
					cout << FRONT_RED << "操作失败，输入商品数量错误！！" << RESET << endl;
				}
				else {
					buy(goods_name, stoi(number));
				}
				break;
			case '3':
				cout << "请输入商品ID：";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				cout << "请输入商品数量：";
				getline(cin, number);
				while (number == "") getline(cin, number);
				if (!IsLegal(number, 10, 4) || !IsNumberLegal(number)) {
					cout << FRONT_RED << "操作失败，输入商品数量错误！！" << RESET << endl;
				}
				else {
					int flag = remove(goods_name, stoi(number));
					if (flag == 1)
						cout << FRONT_GREEN << "移出成功" << RESET << endl;
					else if (flag == -1)
						cout << FRONT_RED << "操作失败，未查询到该商品ID!!!" << RESET << endl;
					else cout << FRONT_RED << "操作失败，超出购物车中该商品数量!!!" << RESET << endl;
				}
				break;
			case '4':
				cout << FRONT_GREEN << "----已返回主界面----" << RESET << endl;
				return;
			default:
				cout << FRONT_RED << "输入错误，请重新输入。" << RESET << endl;
				goto back;
				break;
			}
			cout << endl;
		}
	}
	return;
}

void Trolley::add(string id, string name, string time, string seller,double p, int n) {
	for (int i = 0; i < num; ++i) {
		if (id == items[i].getid()) {
			items[i].add_num(n);
			return;
		}
	}
	items[num] = Item(id, time, name, seller, p, n,1);
	++num;
}

int Trolley::remove(string id, int n) {
	for (int i = 0; i < num; ++i) {
		if (id == items[i].getid()) {
			if (items[i].getnum() < n) {
				return 0;
			}
			else if (items[i].getnum() == n) {
				for (int j = i; j < num - 1; j++) {
					items[j] = items[j + 1];
				}
				items[num - 1].id = "";
				items[num - 1].number = 0;
				--num;
				return 1;
			}
			else {
				items[i].add_num(-n);
				return 1;
			}
		}
	}
	return -1;
}

int Trolley::buy(string id, int n) {
	for (int i = 0; i < num; ++i) {
		if (id == items[i].id) {
			if (n > items[i].number) {
				cout << FRONT_RED << "交易失败，商品数量超出购物车中该商品数量！" << RESET << endl;
				return 0;
			}
			if (items[i].seller == owner->getid()) {
				cout << FRONT_RED << "不能购买自己发布的商品" << RESET << endl;
				return 0;
			}
			if (items[i].state == 0) {
				cout << FRONT_RED << "交易失败，该商品已售罄！！" << RESET << endl;
				return 0;
			}
			int j;
			for (j = 0; goods[j].getstate() != -1; ++j) {
				if (items[i].id == goods[j].getid()) break;
			}
			if (goods[j].getnumber() < items[i].number) {
				string input;
				back:
				cout << "以下商品存货不足，请确认是否购买(1. 购买全部剩余商品 2.取消购买)"<< endl;
				cout << "请输入：";
				getline(cin, input);
				while (input == "") getline(cin, input);
				if (input != "2" && input != "1") {
					cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl;
					goto back;
				}
				else if (input == "2") {
					cout << FRONT_RED << "操作已取消" << RESET << endl;
					return 0;
				}
				if (items[i].price * goods[j].getnumber() > owner->getmoney()) {
					cout << FRONT_RED << "余额不足，购买失败" << RESET << endl;
					return 0;
				}
				int n = Insert("INSERT INTO order VALUES(" + id + "," + to_string(goods[j].getnumber()) + ")", 2, owner->getid());
				if (n != -1) Update("UPDATE commodity SET number = 0 WHERE goods_id = " + id, 2, owner->getid());
			}
			else {
				if (items[i].price * items[i].number > owner->getmoney()) {
					cout << FRONT_RED << "余额不足，购买失败" << RESET << endl;
					return 0;
				}
				int n = Insert("INSERT INTO order VALUES(" + id + "," + to_string(items[i].number) + ")", 2, owner->getid());
				if (n != -1) Update("UPDATE commodity SET number = " + to_string(n) + " WHERE goods_id = " + id, 2, owner->getid());
			}
			remove(id, items[i].number);
			return 1;
		}
	}
	cout << FRONT_RED << "购物车中查无该商品，交易失败！" << RESET << endl;
	return 0;
}

int Trolley::clear() {
	string tmp1 = "", tmp2 = "";
	double sum = 0;
	for (int i = 0; i < num; ++i) {
		string goods_id = items[i].getid();
		int number = items[i].getnum();
		if (items[i].getstate() == 0) {
			if (items[i].getseller() == owner->getid()) {
				cout << FRONT_RED << "不能购买自己发布的商品！" << RESET << endl;
				return 0;
			}
			if (tmp2 == "") tmp1 = goods_id;
			else tmp2 += "," + goods_id;
			continue;
		}
		for (int j = 0; goods[j].getstate() != -1; ++j) {
			if (goods_id == goods[j].getid()) {
				if (items[i].getseller() == owner->getid()) {
					cout << FRONT_RED << "不能购买自己发布的商品！" << RESET << endl;
					return 0;
				}
				if (number > goods[j].getnumber()) {
					if (tmp1 == "") tmp1 = goods_id;
					else tmp1 += "," + goods_id;
					sum += items[i].getprice() * goods[j].getnumber();
					break;
				}
				else {
					sum += items[i].getprice() * number;
					break;
				}
			}
		}
	}
	if (sum > owner->getmoney()) {
		cout << FRONT_RED  << "余额不足，购买失败" << RESET << endl;
		return 0;
	}
	string input;
	if (tmp2 != "") {
	back:
		cout << "以下商品已售罄，请确认是否购买(1. 购买其余商品 2. 取消清空购物车)：" << tmp2 <<endl;
		cout << "请输入：";
		getline(cin, input);
		while (input == "") getline(cin, input);
		if (input != "2" && input != "1") {
			cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl;
			goto back;
		}
		else if (input == "2") {
			cout << FRONT_RED << "操作已取消" << RESET << endl;
			return 0;
		}
	}
	if (tmp1 != "") {
	back1:
		cout << "以下商品存货不足，请确认是否购买(1. 购买全部剩余商品 2.取消清空购物车)：" << tmp1 << endl;
		cout << "请输入：";
		getline(cin, input);
		while (input == "") getline(cin, input);
		if (input != "2" && input != "1") {
			cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl;
			goto back1;
		}
		else if (input == "2") {
			cout << FRONT_RED << "操作已取消" << RESET << endl;
			return 0;
		}
	}
	for (int i = 0; i < num;) {
		string goods_id = items[i].getid();
		int number = items[i].getnum();
		if (items[i].getstate() == 0) {
			continue;
		}
		for (int j = 0; goods[j].getstate()!=-1 ;j++) {
			if (goods_id == goods[j].getid()) {
				if (number > goods[j].getnumber()) {
					int n = Insert("INSERT INTO order VALUES(" + goods_id + "," + to_string(goods[j].getnumber()) + ")", 2, owner->getid());
					if (n != -1) Update("UPDATE commodity SET number = 0 WHERE goods_id = " + goods_id, 2, owner->getid());
				}
				else {
					int n = Insert("INSERT INTO order VALUES(" + goods_id + "," + to_string(number) + ")", 2, owner->getid());
					if (n != -1) Update("UPDATE commodity SET number = " + to_string(n) + " WHERE goods_id = " + goods_id, 2, owner->getid());
				}
				remove(goods_id, number);
				break;
			}
		}
	}
	cout <<endl<< FRONT_GREEN << "购物车已清空" << RESET;
	return 1;
}