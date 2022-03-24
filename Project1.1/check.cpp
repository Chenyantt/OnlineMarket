#define _CRT_SECURE_NO_WARNINGS
#include "check.h"

#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>

#include "data.h"
#include "color.h"

using namespace std;

void Check(string command, int mode, string name) {
	if (command=="SELECT * FROM user") {
		CheckUser(command, mode, name);
	}
	else if (command.find("SELECT * FROM commodity")!=-1) {
		CheckGoods(command, mode, name);
	}
	else {
		CheckOrder(command, mode, name);
	}
}

void CheckUser(string command, int mode, string name) {
	cout << "********************************************************************************************" << endl;
	cout << setprecision(1) << fixed << left << setw(10) << "用户ID" 
		 << setw(15) << "用户名" << setw(18) << "联系方式" 
		 << setw(25) << "地址" << setw(10) << "钱包余额" 
		 << setw(10) << "用户状态" << endl;
	for (int i = 0; users[i].getstate() != -1; ++i) {
		cout << setw(10) << users[i].getid() << setw(15) << users[i].getname() 
			 << setw(18) << users[i].getphone() << setw(25) << users[i].getaddress() 
			 << setw(10) << users[i].getmoney();
		if (users[i].getstate() == 1) cout << setw(10) << "正常" << endl;
		else cout << setw(10) << "封禁" << endl;
	}
	cout << "********************************************************************************************" << endl;
	time_t rawtime;
	struct tm* info;
	char buffer[80];
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
	ofstream ofile;
	ofile.open("commands.txt", ios::app);
	ofile << buffer << command << '\n';
	ofile.close();
	return;
}

void CheckGoods(string command, int mode, string name) {
	cout << setprecision(1) << fixed << left;
	if (command.find("goods_id")!=-1) {
		string id = command.substr(command.find("CONTAINS") + 9);
		int j = 0;
		for (; goods[j].getstate() != -1; ++j) {
			if (goods[j].getid() == id) break;
		}
		if (goods[j].getstate() != -1 && goods[j].getstate()!=0) {
			cout << endl << "*****************************"<< endl;
			cout << "商品ID: " << id << endl << "商品名称: " << goods[j].getname() << endl
				<< "商品价格：" << goods[j].getprice() << endl << "上架时间: " << goods[j].gettime() << endl
				<< "商品描述: " << goods[j].getdes() << endl << "商品卖家: " << goods[j].getseller() << endl;
			cout << "*****************************"<< endl;
		}
		else {
			cout << FRONT_RED << "未查询到该商品ID!!!" <<RESET<< endl;
		}
		time_t rawtime;
		struct tm* info;
		char buffer[80];
		time(&rawtime);
		info = localtime(&rawtime);
		strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
		ofstream ofile;
		ofile.open("commands.txt", ios::app);
		ofile << buffer << command << '\n';
		ofile.close();
		return;
	}
	int flag = 0;
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		string goods_name = command.substr(command.find("CONTAINS") + 9);
		if (command.find("CONTAINS")==-1 || goods[i].getname().find(goods_name) != -1) {
			if (mode == 1 || (mode == 2 && goods[i].getseller() == name) || (mode==3 && goods[i].getstate()!=0)) {
				if (flag == 0) {
					cout << "********************************************************************************************" << endl;
					cout << setw(10) << "商品ID" << setw(15) << "名称" << setw(8) << "价格" 
						 << setw(15) << "上架时间";
					if (mode != 2) cout << setw(10) << "卖家ID";
					if (mode != 3) cout << setw(10) << "数量" << setw(10) << "商品状态";
					cout << endl;
					flag = 1;
				}
				cout << setw(10) << goods[i].getid() << setw(15) << goods[i].getname() 
					 <<setw(8) << goods[i].getprice() << setw(15) << goods[i].gettime();
				if (mode != 2) cout << setw(10) << goods[i].getseller();
				if (mode != 3) {
					cout << setw(10)<<goods[i].getnumber();
					if (goods[i].getstate() == 1) cout << setw(10) << "销售中";
					else cout << setw(10) << "已下架";
				}
				cout << endl;
			}
		}
	}
	if (flag == 0) {
		if (mode != 2) cout << "未查询到商品！！" << endl;
		else cout << "暂未发布商品！" << endl;
	}
	else {
		cout << "********************************************************************************************" << endl;
	}
	time_t rawtime;
	struct tm* info;
	char buffer[80];
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
	ofstream ofile;
	ofile.open("commands.txt", ios::app);
	ofile << buffer << command << '\n';
	ofile.close();
	while (flag != 0 && command.find("CONTAINS") == -1) {
	back:
		string input;
		cout << "可选择商品的排列顺序：（1.按商品名称  2.最早发布 3.最近发布 4.价格从低到高 5.价格从高到低 6.返回）：";
		getline(cin, input);
		while (input == "") getline(cin, input);
		if (input.length() != 1) {
			cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl;
			goto back;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				for (int i = 0; goods[i + 1].getstate() != -1; ++i) {
					int min_index = i;
					for (int j = i + 1; goods[j].getstate() != -1; ++j) {
						if (goods[min_index].getname() > goods[j].getname()) {
							min_index = j;
						}
					}
					if (min_index != i) {
						Goods tmp(goods[i]);
						goods[i] = goods[min_index];
						goods[min_index] = tmp;
					}
				}
				break;
			case '2':
				for (int i = 0; goods[i + 1].getstate() != -1; ++i) {
					int min_index = i;
					for (int j = i + 1; goods[j].getstate() != -1; ++j) {
						if (goods[min_index].gettime() > goods[j].gettime()) {
							min_index = j;
						}
					}
					if (min_index != i) {
						Goods tmp(goods[i]);
						goods[i] = goods[min_index];
						goods[min_index] = tmp;
					}
				}
				break;
			case '3':
				for (int i = 0; goods[i + 1].getstate() != -1; ++i) {
					int max_index = i;
					for (int j = i + 1; goods[j].getstate() != -1; ++j) {
						if (goods[max_index].gettime() < goods[j].gettime()) {
							max_index = j;
						}
					}
					if (max_index != i) {
						Goods tmp(goods[i]);
						goods[i] = goods[max_index];
						goods[max_index] = tmp;
					}
				}
				break;
			case '4':
				for (int i = 0; goods[i + 1].getstate() != -1; ++i) {
					int min_index = i;
					for (int j = i + 1; goods[j].getstate() != -1; ++j) {
						if (goods[min_index].getprice() > goods[j].getprice()) {
							min_index = j;
						}
					}
					if (min_index != i) {
						Goods tmp(goods[i]);
						goods[i] = goods[min_index];
						goods[min_index] = tmp;
					}
				}
				break;
			case '5':
				for (int i = 0; goods[i + 1].getstate() != -1; ++i) {
					int max_index = i;
					for (int j = i + 1; goods[j].getstate() != -1; ++j) {
						if (goods[max_index].getprice() < goods[j].getprice()) {
							max_index = j;
						}
					}
					if (max_index != i) {
						Goods tmp(goods[i]);
						goods[i] = goods[max_index];
						goods[max_index] = tmp;
					}
				}
				break;
			case '6':
				cout << FRONT_GREEN << "----已返回----" << RESET << endl;
				return;
			default:
				cout << FRONT_RED << "输入错误，请重新输入。" << RESET << endl;
				goto back;
				break;
			}
			cout << "********************************************************************************************" << endl;
			cout << setw(10) << "商品ID" << setw(15) << "名称" << setw(8) << "价格"
				<< setw(15) << "上架时间";
			if (mode != 2) cout << setw(10) << "卖家ID";
			if (mode != 3) cout << setw(10) << "数量" << setw(10) << "商品状态";
			cout << endl;
			for (int i = 0; goods[i].getstate() != -1; ++i) {
				if (mode == 1 || (mode == 2 && goods[i].getseller() == name) || (mode == 3 && goods[i].getstate() != 0)) {
					cout << setw(10) << goods[i].getid() << setw(15) << goods[i].getname()
						<< setw(8) << goods[i].getprice() << setw(15) << goods[i].gettime();
					if (mode != 2) cout << setw(10) << goods[i].getseller();
					if (mode != 3) {
						cout << setw(10) << goods[i].getnumber();
						if (goods[i].getstate() == 1) cout << setw(10) << "销售中";
						else cout << setw(10) << "已下架";
					}
					cout << endl;
				}
			}
			cout << "********************************************************************************************" << endl;
		}
	}
	return;
}

//administrator mode 1; seller mode2 ;buyer mode 3;
void CheckOrder(string command, int mode, string name) {
	cout << setprecision(1) << fixed << left;
	int flag = 0;
	for (int i = 0; orders[i].getnumber() != -1; ++i) {
		if (mode==1 || (mode==2 && orders[i].getseller()==name) || (mode==3 && orders[i].getbuyer()==name)) {
			if (flag == 0) {
				cout << "********************************************************************************************" << endl;
				cout << setw(10) << "订单ID" << setw(10) << "商品ID" 
					 << setw(15) << "交易单价" << setw(10) << "数量" << setw(15) << "时间";
				if (mode != 2) cout << setw(10) << "卖家";
				if (mode != 3) cout << setw(10) << "买家";
				flag = 1;
				cout << endl;
			}
			cout << setw(10) << orders[i].getid() << setw(10) << orders[i].getgoods() 
				 << setw(15) << orders[i].getprice() << setw(10) << orders[i].getnumber()
				 << setw(15) << orders[i].gettime();
			if (mode != 2) cout << setw(10) << orders[i].getseller();
			if (mode != 3) cout << setw(10) << orders[i].getbuyer();
			cout << endl;
		}
	}
	if (flag == 0) {
		cout << "暂无历史订单！！" << endl;
	}
	else {
		cout << "********************************************************************************************" << endl;
	}
	time_t rawtime;
	struct tm* info;
	char buffer[80];
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
	ofstream ofile;
	ofile.open("commands.txt", ios::app);
	ofile << buffer << command << '\n';
	ofile.close();
	return;
}