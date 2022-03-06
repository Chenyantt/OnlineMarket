#define _CRT_SECURE_NO_WARNINGS
#include "file.h"

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

#include "data.h"

using namespace std;

void Init() {
	InitUsers();
	InitGoods();
	InitOrders();
	return;
}

void InitUsers() {
	ifstream ifile;
	ifile.open("user.txt", ios::in);
	if (!ifile) {
		cout << "Open File Error." << endl;
		exit(-1);
	}
	char input_c[200];
	ifile.getline(input_c, 200);
	for (int i = 0; ifile.getline(input_c, 200); i++) {
		
		string input = input_c;
		string uid = input.substr(0, 4);
		int pre_index = 5,next_index=input.find(',', pre_index);
		string name=input.substr(pre_index,next_index-pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string password= input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string phone = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string address = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string balance = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find('\n', pre_index);
		string state_s = input.substr(pre_index, next_index - pre_index);
		int state;
		state_s[0] == 'i'? state = 0 : state = 1;
		double money = stod(balance);
		users[i] = User(&uid, &name, &password, &phone, &address, money, state);
	}
	ifile.close();
	return;
}

void InitGoods() {
	ifstream ifile;
	ifile.open("commodity.txt", ios::in);
	if (!ifile) {
		cout << "Open File Error." << endl;
		exit(-1);
	}
	char input_c[300];
	ifile.getline(input_c, 300);
	for (int i = 0; ifile.getline(input_c, 300); i++) {
		string input = input_c;
		string id = input.substr(0, 4);
		int pre_index = 5, next_index = input.find(',', pre_index);
		string name = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string price_s = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string number_s = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string description = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string seller = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string time = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find('\n', pre_index);
		string state_s = input.substr(pre_index, next_index - pre_index);
		int state,number=stoi(number_s);
		state_s[0] == 'o' ? state = 1 : state = 0;
		double price = stod(price_s);
		goods[i] = Goods(&id, &name, price, number, &description, &seller, &time,state);
	}
	ifile.close();
	return;
}

void InitOrders() {
	ifstream ifile;
	ifile.open("order.txt", ios::in);
	if (!ifile) {
		cout << "Open File Error." << endl;
		exit(-1);
	}
	char input_c[200];
	ifile.getline(input_c, 200);
	for (int i = 0; ifile.getline(input_c, 200); i++) {
		string input = input_c;
		string id = input.substr(0, 4);
		int pre_index = 5, next_index = input.find(',', pre_index);
		string goods = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string price_s = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string number_s = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string time = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string seller = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find('\n', pre_index);
		string buyer = input.substr(pre_index, next_index - pre_index);
		int number = stoi(number_s);
		double price = stod(price_s);
		orders[i] = Order(id, goods, price, number, time, seller, buyer);
	}
	ifile.close();
	return;
}

void Save() {
	SaveUsers();
	SaveGoods();
	SaveOrders();
	return;
}

void SaveUsers(){
	ofstream ofile;
	ofile.open("user.txt", ios::out);
	ofile <<"userID, username, password, phoneNumber, address, balance, userState";
	for (int i = 0; users[i].getstate() != -1; ++i) {
		ofile << '\n' << users[i].getid() << ',' << users[i].getname() << ',' 
			  << users[i].getpassword() << ',' << users[i].getphone() << ',' 
			  << users[i].getaddress() << ',' << fixed <<setprecision(1)
			  << users[i].getmoney() << ',';
		if (users[i].getstate() == 1) ofile << "active";
		else ofile << "inactive";
	}
	ofile.close();
	return;
}

void SaveGoods(){
	ofstream ofile;
	ofile.open("commodity.txt", ios::out);
	ofile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state";
	for (int i = 0; goods[i].getstate() != -1; ++i) {
		ofile << '\n' << goods[i].getid() << ',' << goods[i].getname() << ',' 
			  <<fixed << setprecision(1) << goods[i].getprice() << ','
			  << goods[i].getnumber() << ',' << goods[i].getdes() << ',' 
			  << goods[i].getseller()<<',' << goods[i].gettime() << ',';
		if (goods[i].getstate() == 1) ofile << "onsale";
		else ofile << "remove";
	}
	ofile.close();
	return;
}

void SaveOrders(){
	ofstream ofile;
	ofile.open("order.txt", ios::out);
	ofile << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
	for (int i = 0; orders[i].getnumber() != -1; ++i) {
		ofile << '\n' << orders[i].getid() << ',' << orders[i].getgoods() << ',' 
			  <<fixed <<setprecision(1) << orders[i].getprice() << ','
			  << orders[i].getnumber() << ',' << orders[i].gettime() << ',' 
			  << orders[i].getseller() <<',' << orders[i].getbuyer();
	}
	ofile.close();
	return;
}