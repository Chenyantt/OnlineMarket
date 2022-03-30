#define _CRT_SECURE_NO_WARNINGS
#include "update.h"

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

#include "data.h"
#include "register.h"
#include "file.h"
#include "user.h"
#include "color.h"

using namespace std;

void Update(string command, int mode, string id) {
	if (command.find("UPDATE commodity SET state = remove WHERE id = ")!=-1) {
		BanSeller(command, mode, id);
	}
	else if(command.find("UPDATE commodity SET state = remove WHERE goods_id = ") != -1) {
		RemoveGoods(command, mode, id);
	}
	else if (command.find("UPDATE commodity SET number = ") != -1) {
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
			goods[i].remove();
		}
	}
	for (map<string, Trolley>::iterator iter = trolleys.begin(); iter != trolleys.end() ; iter++) {
		for (int i = 0; i < iter->second.num; ++i) {
			if (iter->second.items[i].getseller() == user_id)
				iter->second.remove(iter->second.items[i].getid(), iter->second.items[i].getnum());
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
	ofile<< buffer << command << '\n';
	ofile.close();
	return;
}

void RemoveGoods(string command, int mode, string id) {
	string input, goods_id = command.substr(command.find("goods_id = ") + 11);
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if ((mode == 1 && goods[i].getid() == goods_id) || (mode == 2 && goods[i].getid() == goods_id && goods[i].getseller() == id)) {
			if (goods[i].getstate() == 0) {
				cout <<FRONT_RED<< "����Ʒ�Ѵ����¼�״̬�У�" <<RESET<< endl;
				return;
		}
		back:
			cout << "ȷ���¼ܸ���Ʒ��" << endl;
			cout << "**************************************************************************************" << endl;
			cout << setprecision(1) << fixed << left << setw(10) << "��ƷID" << setw(15) << "����" 
				 << setw(8) << "�۸�" << setw(15) << "�ϼ�ʱ��"<< setw(10) << "����" 
				 << setw(10) << "����ID" << setw(10) << "��Ʒ״̬" << endl;
			cout << setw(10) << goods[i].getid() << setw(15) << goods[i].getname() 
				 << setw(8) << goods[i].getprice() << setw(15)<< goods[i].gettime() 
				 << setw(10) << goods[i].getnumber() << setw(10) << goods[i].getseller();
			if (goods[i].getstate() == 1) cout << setw(10) << "������" << endl;
			else cout << setw(10) << "���¼�" << endl;
			cout << "**************************************************************************************" << endl;
			cout << "��ѡ��(y/n)��";
			getline(cin, input);
			while (input == "") getline(cin, input);
			if (input == "y") {
				goods[i].remove();
				for (map<string, Trolley>::iterator iter = trolleys.begin(); iter != trolleys.end(); iter++) {
					for (int i = 0; i < iter->second.num; ++i) {
						if (iter->second.items[i].getid() == goods_id)
							iter->second.remove(goods_id, iter->second.items[i].getnum());
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
				ofile << buffer << command << '\n';
				ofile.close();
				cout << FRONT_GREEN <<"�¼ܳɹ�" <<RESET<< endl;
				return;
			}
			else if (input == "n") {
				cout << FRONT_RED <<"������ȡ��" << RESET << endl;
				return;
			}
			else {
				cout << FRONT_RED <<"�����������������" <<RESET<< endl<<endl;
				goto back;
			}
		}
	}
	cout <<FRONT_RED<<"û�в�ѯ����Ʒ����ȷ��id�Ƿ���ȷ" <<RESET<< endl;
	return;
}

void BuyGoods(string command, int mode,string id) {
	string goods_id = command.substr(command.find("goods_id = ") + 11);
	int number = stoi(command.substr(command.find("number = ") + 9, command.find("WHERE")-1));
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if (goods[i].getid() == goods_id) {
			goods[i].mod_num(number);
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
			if (number == 0) {
				goods[i].remove();
				for (map<string, Trolley>::iterator iter = trolleys.begin(); iter != trolleys.end(); iter++) {
					for (int i = 0; i < iter->second.num; ++i) {
						if (iter->second.items[i].getid() == goods_id)
							iter->second.items[i].mod_state(0);
					}
				}
				ofile.open("commands.txt", ios::app);
				ofile << buffer << "UPDATE commodity SET state = remove WHERE goods_id = "<<goods[i].getid() << '\n';
				ofile.close();
			}
			return;
		}
	}
	return;
}

void UpdateGoods(string command, int mode, string id) {
	cout << setprecision(1) << fixed;
	double price;
	string input, des, goods_id = command.substr(command.find("goods_id") + 11);
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		if (goods[i].getid() == goods_id && goods[i].getseller() == id) {
		back:
			if (command.find("price") != -1) {
				string p = command.substr(command.find("price") + 8, command.find("WHERE") - 9 - command.find("price"));
				if (!IsNumberLegal(p)) {
					cout << FRONT_RED << "������Ч�����Զ����أ���"<<RESET << endl;
					return;
				}
				price = stod(p), des = goods[i].getdes();
			}
			else {
				des = command.substr(command.find("description") + 14, command.find("WHERE") - command.find("description") - 14);
				if (!IsLegal(des, 200, 3)) {
					cout << FRONT_RED << "������Ч�����Զ����أ���"<<RESET << endl;
					return;
				}
				price = goods[i].getprice();
			}
			cout << "��ȷ���޸ĵ���Ϣ����" << endl;
			cout << "*****************************************************************************" << endl;
			cout << "��ƷID: " << goods_id << endl << "��Ʒ����: " << goods[i].getname() << endl
				<< "��Ʒ�۸�" << price << endl << "��Ʒ����: " << des << endl;
			cout << "*****************************************************************************" << endl;
			cout << "��ѡ��(y/n)��";
			getline(cin, input);
			while (input == "") getline(cin, input);
			if (input == "y") {
				goods[i].mod_des(des);
				goods[i].mod_price(price);
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
				cout << FRONT_GREEN <<"�޸ĳɹ�" <<RESET<< endl;
				return;
			}
			else if (input == "n") {
				cout << FRONT_RED << "������ȡ��" << RESET << endl;
				return;
			}
			else {
				cout << FRONT_RED <<"�����������������" <<RESET<< endl <<endl;
				goto back;
			}
		}
	}
	cout << FRONT_RED <<"û�в�ѯ����Ʒ����ȷ��id�Ƿ���ȷ" <<RESET<< endl;
	return;
}

int BanUser(string command, int mode, string id) {
	string input, user_id = command.substr(command.find("id") + 5);
	for (int i = 0; users[i].getstate() != -1; ++i) {
		if (users[i].getid() == user_id) {
			if (users[i].getstate() == 0) {
				cout << FRONT_RED << "���û��Ѵ��ڷ��״̬�У�" <<RESET<< endl;
				return 0;
			}
			back:
			cout << "ȷ��������û���" << endl;
			cout << "********************************************************************************************" << endl;
			cout << setprecision(1) << fixed << left << setw(10) << "�û�ID" 
				 << setw(15) << "�û���" << setw(18) << "��ϵ��ʽ" << setw(25) << "��ַ" 
				 << setw(10) << "Ǯ�����" << setw(10)<< endl;
			cout << setw(10) << users[i].getid() << setw(15) << users[i].getname() 
				 << setw(18) << users[i].getphone() << setw(25) << users[i].getaddress() 
				 << setw(10) << users[i].getmoney() << endl;
			cout << "********************************************************************************************" << endl;
			cout << "��ѡ��(y/n)��";
			getline(cin, input);
			while (input == "") getline(cin, input);
			if (input == "y") {
				users[i].ban();
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
				cout <<FRONT_GREEN<<"����ɹ�" <<RESET<< endl;
				return 1;
			}
			else if (input == "n") {
				cout << FRONT_RED <<"������ȡ��" << RESET << endl;
				return 0;
			}
			else {
				cout << FRONT_RED <<"�����������������" <<RESET<< endl <<endl;
				goto back;
			}
		}
	}
	cout << FRONT_RED <<"���޴��ˣ���ȷ��id�Ƿ���ȷ" <<RESET<< endl;
	return 0;
}