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
#include "user.h"
#include "color.h"

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
	if (IsLegal(name, 20, 1) && IsLegal(des, 200, 3) && IsLegal(number,20,4) 
		&& IsNumberLegal(number) && stoi(number)>0) {
		if (!IsNumberLegal(price)) {
			cout<< FRONT_RED << "������Ч�����Զ����أ���"<<RESET << endl;
			return 0;
		}
		string mid = BuildUid('M');
		back:
		cout << "��ȷ����Ʒ��Ϣ����" << endl;
		cout << "********************************************************************************************" << endl;
		cout << "��Ʒ����: " << name << endl << "��Ʒ�۸�" << price << endl
			<< "��Ʒ������" << number << endl << "��Ʒ����: " << des << endl;
		cout << "********************************************************************************************" << endl;
		string input;
		cout << "��ȷ��Ҫ��������Ʒ��(y/n) ";
		getline(cin, input);
		while (input == "") getline(cin, input);
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
			ofile << buffer << command << '\n';
			ofile.close();
			cout <<FRONT_GREEN<< "�����ɹ�" << RESET << endl;
			return 1;
		}
		else if (input == "n") {
			cout <<FRONT_RED << "������ȡ��" << RESET << endl;
			return 0;
		}
		else {
			cout << FRONT_RED << "�����������������" <<RESET<< endl;
			goto back;
		}
	}
	else {
		cout << FRONT_RED << "������Ч�����Զ����أ���"<<RESET << endl;
		return 0;
	}
}

int Insert_order(string command, int mode, string id) {
	cout << setprecision(1) << fixed;
	string goods_id = command.substr(command.find("(") + 1, command.find(",") - 1 - command.find("("));
	string num = command.substr(command.find(",") + 1, command.find(")") - 1 - command.find(","));
	if(!IsLegal(num,10,4) || !IsNumberLegal(num)){
		cout << FRONT_RED << "������Ʒ�������󣡣�" <<RESET<< endl;
		return -1;
	}
	int number = stoi(num);
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if (goods[i].getid() == goods_id && goods[i].getstate()!=0) {
			if (number > goods[i].getnumber()) {
				cout << FRONT_RED << "��Ʒ������㣬����ʧ�ܣ�" <<RESET<< endl;
				return -1;
			}
			double price = goods[i].getprice();
			string seller = goods[i].getseller();
			for (int j = 0; users[j].getstate() != -1; ++j) {
				if (users[j].getid() == id) {
					double balance = users[j].getmoney();
					if (balance < price * number) {
						cout << FRONT_RED << "���㣬����ʧ�ܣ�" <<RESET<< endl;
						return -1;
					}
					if (users[j].getid() == goods[i].getseller()) {
						cout <<FRONT_RED<< "���ܹ����Լ���������Ʒ��" <<RESET<< endl;
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
					cout <<FRONT_GREEN<< "********************************************************************************************" << endl;
					cout << "�������ѣ�" << endl;
					cout << "����ʱ��: " << buffer << endl << "���׵���:" << price << endl
						<< "����������" << number << endl <<"����״̬�����׳ɹ�"<<endl << "�������: " << users[j].getmoney() << endl;
					cout << "********************************************************************************************"<<RESET << endl;
					ofstream ofile;
					strftime(buffer, 80, "%Y-%m-%d %H:%M:%S: ", info);
					ofile.open("commands.txt", ios::app);
					ofile << buffer << "INSERT INTO order VALUES("<<tid<<','<<goods[i].getid()
						<<',' << fixed << setprecision(1) << price <<','<<number<<',' << buffer_s 
						<<','<<goods[i].getseller()<<','<<id<<')' << '\n';
					ofile.close();
					return goods[i].getnumber()-number;
				}
			}
		}
	}
	cout << FRONT_RED << "���޴���Ʒ������ʧ�ܣ�" <<RESET<< endl;
	return -1;
}