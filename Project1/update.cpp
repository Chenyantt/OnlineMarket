#define _CRT_SECURE_NO_WARNINGS
#include "update.h"

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "data.h"
#include "register.h"
#include "file.h"

using namespace std;

void Update(string command, int mode, string id) {
	if (mode == 3) {
		BanSeller(command, mode, id);
	}
	else if (command.find("user") != -1) {
		UpdateUser(command, mode, id);
	}
	else if(command.find("state") != -1) {
		RemoveGoods(command, mode, id);
	}
	else if (command.find("number") != -1) {
		BuyGoods(command, mode, id);
	}
	else {
		UpdateGoods(command, mode, id);
	}
	return;
}

void BanSeller(string command, int mode, string id) {
	string user_id = command.substr(command.find("id") + 5);
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if(goods[i].getseller()==user_id){
			goods[i].ban();
		}
	}
	time_t rawtime;
	struct tm* info;
	char buffer[80];
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
	ofstream ofile;
	ofile.open("commands.txt", ios::app);
	ofile << '\n' << buffer << command;
	ofile.close();
	return;
}

void BuyGoods(string command, int mode,string id) {
	string goods_id = command.substr(command.find("goods_id") + 11);
	int number = stoi(command.substr(command.find("number") + 9, command.find("WHERE")-1));
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if (goods[i].getid() == goods_id) {
			goods[i].mod_num(number);
			if (goods[i].getnumber() == 0) {
				goods[i].ban();
				time_t rawtime;
				struct tm* info;
				char buffer[80];
				time(&rawtime);
				info = localtime(&rawtime);
				strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
				ofstream ofile;
				ofile.open("commands.txt", ios::app);
				ofile << '\n' << buffer << "UPDATE commodity SET state = remove WHERE goods_id = "<<goods[i].getid();
				ofile.close();
			}
			time_t rawtime;
			struct tm* info;
			char buffer[80];
			time(&rawtime);
			info = localtime(&rawtime);
			strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
			ofstream ofile;
			ofile.open("commands.txt", ios::app);
			ofile << '\n' << buffer << command;
			ofile.close();
			return;
		}
	}
	return;
}

void RemoveGoods(string command, int mode, string id) {
	cout << setprecision(1);
	cout << fixed;
	cout << left;
	string input;
	string goods_id=command.substr(command.find("goods_id")+11);
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if ((mode==1 && goods[i].getid() == goods_id) || (mode==2 && goods[i].getid() == goods_id && goods[i].getseller() == id)) {
		back:
			cout << "确定下架该商品吗？" << endl;
			cout << "********************************************************************************************" << endl;
			cout << setw(10) << "商品ID" << setw(15) << "名称" << setw(8) << "价格" << setw(15) << "上架时间"
				 <<setw(10) << "数量" << setw(10) << "卖家ID"<< setw(10) << "商品状态" <<endl;
			cout << setw(10) << goods[i].getid() << setw(15) << goods[i].getname() << setw(8) << goods[i].getprice() << setw(15)
				<< goods[i].gettime() << setw(10) << goods[i].getnumber() << setw(10) << goods[i].getseller();
			if (goods[i].getstate() == 1) {
				cout << setw(10) << "销售中";
			}
			else {
				cout << setw(10) << "已下架";
			}
			cout << endl;
			cout << "********************************************************************************************" << endl;
			cout << "请选择（y/n）：";
			cin >> input;
			if (input == "y") {
				time_t rawtime;
				struct tm* info;
				char buffer[80];
				time(&rawtime);
				info = localtime(&rawtime);
				strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
				ofstream ofile;
				ofile.open("commands.txt", ios::app);
				ofile << '\n' << buffer << command;
				ofile.close();
				cout << endl << "下架成功" << endl;
				goods[i].ban();
				return;
			}
			else if (input == "n") {
				cout << endl << "操作已取消" << endl;
				return;
			}
			else {
				cout << endl << "输入错误，请重新输入" << endl;
				goto back;
			}
		}
	}
	cout << endl << "没有查询到商品，请确认id是否正确" << endl;
	return;
}

int UpdateUser(string command, int mode, string id) {
	string input;
	cout << setprecision(1);
	cout << fixed;
	cout << left;
	string user_id = command.substr(command.find("id") + 5);
	for (int i = 0; users[i].getstate() != -1; ++i) {
		if (users[i].getid() == user_id) {
			if (users[i].getstate() == 0) {
				cout << "该用户已被封禁！！！" << endl;
				return 0;
			}
			back:
			cout << "确定封禁该用户吗？" << endl;
			cout << "********************************************************************************************" << endl;
			cout << setw(10) << "用户ID" << setw(15) << "用户名" << setw(18) << "联系方式" << setw(25) << "地址" << setw(10) << "钱包余额" << setw(10)<< endl;
			cout << setw(10) << users[i].getid() << setw(15) << users[i].getname() << setw(18) << users[i].getphone() << setw(25) << users[i].getaddress() << setw(10)
				<< users[i].getmoney() << endl;
			cout << "********************************************************************************************" << endl;
			cout << "请选择（y/n）：";
			cin >> input;
			if (input == "y") {
				time_t rawtime;
				struct tm* info;
				char buffer[80];
				time(&rawtime);
				info = localtime(&rawtime);
				strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
				ofstream ofile;
				ofile.open("commands.txt", ios::app);
				ofile << '\n' << buffer << command;
				ofile.close();
				cout << endl << "封禁成功" << endl;
				users[i].ban();
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
	}
	cout << endl << "查无此人，请确认id是否正确" << endl;
	return 0;
}

void UpdateGoods(string command, int mode, string id) {
	cout << setprecision(1);
	cout << fixed;
	cout << left;
	string input;
	string pre_des;
	double pre_price;
	string goods_id = command.substr(command.find("goods_id") + 11);
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if (goods[i].getid() == goods_id && goods[i].getseller() == id) {
		back:
			pre_des = goods[i].getdes(), pre_price = goods[i].getprice();
			if (command.find("price") != -1) {
				string p = command.substr(command.find("price") + 8,command.find("WHERE")-9- command.find("price"));
				int index = p.find('.');
				int length = int(p.length());
				if ((index == -1 && !IsLegal(p, 10, 4)) || (index != -1 && length > index + 2) || index == 0) {
					cout << "输入无效，已自动返回！！" << endl;
					return;
				}
				goods[i].mod_price(stod(command.substr(command.find("price") + 8)));
			}
			else {
				if (!IsLegal(command.substr(command.find("description") + 14, command.find("WHERE") - command.find("description") - 14), 200, 3)) {
					cout << "输入无效，已自动返回！！" << endl;
					return;
				}
				goods[i].mod_des(command.substr(command.find("description") + 14, command.find("WHERE") - command.find("description") - 15));
			}
			cout << "请确认修改的信息无误！" << endl;
			cout << "********************************************************************************************" << endl;
			cout << "商品ID: " << id << endl << "商品名称: " << goods[i].getname() << endl
				<< "商品价格:" << goods[i].getprice() << endl<< "商品描述: " << goods[i].getdes() << endl;
			cout << "********************************************************************************************" << endl;
			cout << "请选择（y/n）：";
			cin >> input;
			if (input == "y") {
				time_t rawtime;
				struct tm* info;
				char buffer[80];
				time(&rawtime);
				info = localtime(&rawtime);
				strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
				ofstream ofile;
				ofile.open("commands.txt", ios::app);
				ofile << '\n' << buffer << command;
				ofile.close();
				cout << endl << "修改成功" << endl;
				return;
			}
			else if (input == "n") {
				cout << endl << "操作已取消" << endl;
				goods[i].mod_des(pre_des);
				goods[i].mod_price(pre_price);
				return;
			}
			else {
				cout << endl << "输入错误，请重新输入" << endl;
				goto back;
			}
		}
	}
	cout << endl << "没有查询到商品，请确认id是否正确" << endl;
	return;
}