#define _CRT_SECURE_NO_WARNINGS
#include "check.h"

#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>

#include "data.h"

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
	cout << setprecision(1) << fixed << left << setw(10) << "�û�ID" 
		 << setw(15) << "�û���" << setw(18) << "��ϵ��ʽ" 
		 << setw(25) << "��ַ" << setw(10) << "Ǯ�����" 
		 << setw(10) << "�û�״̬" << endl;
	for (int i = 0; users[i].getstate() != -1; ++i) {
		cout << setw(10) << users[i].getid() << setw(15) << users[i].getname() 
			 << setw(18) << users[i].getphone() << setw(25) << users[i].getaddress() 
			 << setw(10) << users[i].getmoney();
		if (users[i].getstate() == 1) cout << setw(10) << "����" << endl;
		else cout << setw(10) << "���" << endl;
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
	ofile << '\n' << buffer << command;
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
			cout << "��ƷID: " << id << endl << "��Ʒ����: " << goods[j].getname() << endl
				<< "��Ʒ�۸�:" << goods[j].getprice() << endl << "�ϼ�ʱ��: " << goods[j].gettime() << endl
				<< "��Ʒ����: " << goods[j].getdes() << endl << "��Ʒ����: " << goods[j].getseller() << endl;
		}
		else {
			cout << "������ƷID����!!!" << endl;
		}
		return;
	}
	int flag = 0;
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		string goods_name = command.substr(command.find("CONTAINS") + 9);
		if (command.find("CONTAINS")==-1 || goods[i].getname().find(goods_name) != -1) {
			if (mode == 1 || (mode == 2 && goods[i].getseller() == name) || (mode==3 && goods[i].getstate()!=0)) {
				if (flag == 0) {
					cout << "********************************************************************************************" << endl;
					cout << setw(10) << "��ƷID" << setw(15) << "����" << setw(8) << "�۸�" 
						 << setw(15) << "�ϼ�ʱ��";
					if (mode != 2) cout << setw(10) << "����ID";
					if (mode != 3) cout << setw(10) << "����" << setw(10) << "��Ʒ״̬";
					cout << endl;
					flag = 1;
				}
				cout << setw(10) << goods[i].getid() << setw(15) << goods[i].getname() 
					 <<setw(8) << goods[i].getprice() << setw(15) << goods[i].gettime();
				if (mode != 2) cout << setw(10) << goods[i].getseller();
				if (mode != 3) {
					cout << setw(10)<<goods[i].getnumber();
					if (goods[i].getstate() == 1) cout << setw(10) << "������";
					else cout << setw(10) << "���¼�";
				}
				cout << endl;
			}
		}
	}
	if (flag == 0) {
		if (mode != 2) cout << "δ��ѯ����Ʒ����" << endl;
		else cout << "��δ������Ʒ��" << endl;
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
	ofile << '\n' << buffer << command;
	ofile.close();
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
				cout << setw(10) << "����ID" << setw(10) << "��ƷID" 
					 << setw(15) << "���׵���" << setw(10) << "����" << setw(15) << "ʱ��";
				if (mode != 2) cout << setw(10) << "����";
				if (mode != 3) cout << setw(10) << "���";
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
		cout << "������ʷ��������" << endl;
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
	ofile << '\n' << buffer << command;
	ofile.close();
	return;
}