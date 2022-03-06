#define _CRT_SECURE_NO_WARNINGS
#include "insert.h"

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <iomanip>

#include "register.h"
#include "file.h"
#include "data.h"
#include "order.h"

using namespace std;

int Insert(string command, int mode, string id) {
	if (command.find("INSERT INTO commodity VALUES(") != -1) {
		return Insert_goods(command, mode, id);
	}
	else {
		return Insert_order(command, mode, id);
	}
}

int Insert_goods(string command, int mode, string id) {
	int pre_index = command.find(",");
	string name = command.substr(command.find("(") + 1, pre_index - 1 - command.find("("));
	int now_index = command.find(",", pre_index + 1);
	string price = command.substr(pre_index + 1, now_index - 1 - pre_index);
	pre_index = now_index, now_index = command.find(",", now_index + 1);
	string number = command.substr(pre_index + 1, now_index - 1 - pre_index);
	string des = command.substr(now_index + 1, command.find(")") - now_index - 1);
	if (IsLegal(name, 20, 1) && IsLegal(des, 200, 3) && IsLegal(number,20,4) && stoi(number)>0) {
		int index = price.find('.');
		int length = int(price.length());
		if ((index==-1 && !IsLegal(price,10,4))||(index!=-1 && length > index + 2) || index == 0) {
			cout<< "输入无效，已自动返回！！" << endl;
			return 0;
		}
		string mid = BuildUid('M');
		back:
		cout << "请确认商品信息无误！" << endl;
		cout << "********************************************************************************************" << endl;
		cout << "商品名称: " << name << endl << "商品价格:" << price << endl
			<< "商品数量：" << number << endl << "商品描述: " << des << endl;
		cout << "********************************************************************************************" << endl;
		string input;
		cout << "您确认要发布该商品吗？(y/n) ";
		cin >> input;
		if (input == "y") {
			time_t rawtime;
			struct tm* info;
			char buffer[80];
			time(&rawtime);
			info = localtime(&rawtime);
			strftime(buffer, 80, "%Y-%m-%d", info);
			string buffer_s = buffer;
			goods[Goods::GetNum() - 1] = Goods(&mid, &name, stod(price), stoi(number), &des, &id, &buffer_s, 1);
			strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
			ofstream ofile;
			ofile.open("commands.txt", ios::app);
			ofile << '\n' << buffer << command;
			ofile.close();
			return 1;
		}
		else if (input == "n") {
			cout << endl << "操作已取消" << endl;
			return 0;
		}
		else {
			cout << endl << "输入错误，请重新输入" << endl;
			goto back;
		}
	}
	else {
		cout << "输入无效，已自动返回！！" << endl;
		return 0;
	}
}

int Insert_order(string command, int mode, string id) {
	cout << setprecision(1) << fixed;
	string goods_id = command.substr(command.find("(") + 1, command.find(",") - 1 - command.find("("));
	int number = stoi(command.substr(command.find(",") + 1, command.find(")") - 1 - command.find(",")));
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if (goods[i].getid() == goods_id && goods[i].getstate()!=0) {
			if (number > goods[i].getnumber()) {
				cout << "商品存货不足，交易失败！" << endl;
				return -1;
			}
			double price = goods[i].getprice();
			string seller = goods[i].getseller();
			for (int j = 0; users[j].getstate() != -1; ++j) {
				if (users[j].getid() == id) {
					double balance = users[j].getmoney();
					if (balance < price * number) {
						cout << "余额不足，交易失败！" << endl;
						return -1;
					}
					if (users[j].getid() == goods[i].getseller()) {
						cout << "不能购买自己发布的商品！" << endl;
						return -1;
					}
					for (int k = 0; users[k].getstate() != -1; ++k) {
						if (users[k].getid() == goods[i].getseller()) {
							users[k].mod_money(-1*price * number);
							break;
						}
					}
					time_t rawtime;
					struct tm* info;
					char buffer[80];
					time(&rawtime);
					info = localtime(&rawtime);
					strftime(buffer, 80, "%Y-%m-%d", info);
					users[j].mod_money(price * number);
					string tid = BuildUid('T'),buffer_s=buffer;
					orders[Order::GetNum() - 1] = Order(tid,goods_id,price,number,buffer_s,goods[i].getseller(),id);
					cout << "********************************************************************************************" << endl;
					cout << "交易提醒！" << endl;
					cout << "交易时间: " << buffer << endl << "交易单价:" << price << endl
						<< "交易数量：" << number << endl <<"交易状态：交易成功"<<endl << "您的余额: " << users[j].getmoney() << endl;
					cout << "********************************************************************************************" << endl;
					ofstream ofile;
					strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
					ofile.open("commands.txt", ios::app);
					ofile << '\n' << buffer << "INSERT INTO order VALUES("<<tid<<','<<goods[i].getid()
						<<',' << fixed << setprecision(1) << price <<','<<number<<',' << buffer_s 
						<<','<<goods[i].getseller()<<','<<id<<')';
					ofile.close();
					return goods[i].getnumber()-number;
				}
			}
		}
	}
	cout << "查无此商品，交易失败！" << endl;
	return -1;
}