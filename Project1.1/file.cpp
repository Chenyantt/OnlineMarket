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
	InitTrolley();
	InitBox();
	return;
}

void InitUsers() {
	User::ModNum(0);
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
		Box tmp;
		tmp.owner = &users[i];
		boxes.insert(pair<string, Box>(uid, tmp));
	}
	ifile.close();
	return;
}

void InitGoods() {
	Goods::ModNum(0);
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
	Order::ModNum(0);
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

void InitTrolley() {
	Item tmp[20];
	ifstream ifile;
	ifile.open("trolley.txt", ios::in);
	if (!ifile) {
		cout << "Open File Error." << endl;
		exit(-1);
	}
	char input_c[200];
	ifile.getline(input_c, 200);
	string id = "";
	int j = 0;
	for (int i = 0; ifile.getline(input_c, 200); i++,++j) {
		string input = input_c;
		int pre_index=0, next_index = input.find(',', pre_index);
		if (input[0] == '(') {
			if (id != "") {
				int k;
				for (k = 0; users[k].getstate() != -1; ++k) {
					if (id == users[k].getid()) break;
				}
				Trolley t(tmp, &users[k], j);
				trolleys.insert(pair<string,Trolley>(id, t));
			}
			id = input.substr(1, 4);
			pre_index = 6;
			j = 0;
			if (input.find(',') == -1) {
				j = -1;
				continue;
			}
		}
		string goods_id = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string goods = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string price_s = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string number_s = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string seller = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string time = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find('\n', pre_index);
		string state_s = input.substr(pre_index, next_index - pre_index);
		int number = stoi(number_s);
		double price = stod(price_s);
		int state;
		if (state_s[0] == 's') state = 0;
		else state = 1;
		tmp[j] = Item(goods_id, time, goods, seller, price, number,state);
	}
	if (id != "") {
		int k;
		for (k = 0; users[k].getstate() != -1; ++k) {
			if (id == users[k].getid()) break;
		}
		Trolley t(tmp, &users[k], j);
		trolleys.insert(pair<string, Trolley>(id, t));
	}
	ifile.close();
	return;
}

void InitBox() {
	for (map<string, Box>::iterator iter = boxes.begin(); iter != boxes.end(); iter++) {
		iter->second.num = 0;
		iter->second.messages_num = 0;
	}
	ifstream ifile;
	ifile.open("message.txt", ios::in);
	if (!ifile) {
		cout << "Open File Error." << endl;
		exit(-1);
	}
	char input_c[200];
	ifile.getline(input_c, 200);
	for (int i = 0; ifile.getline(input_c, 200); i++) {
		string input = input_c;
		int pre_index = 0, next_index = input.find(',', pre_index);
		string time = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string sender = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find(',', pre_index);
		string receiver = input.substr(pre_index, next_index - pre_index);
		pre_index = next_index + 1, next_index = input.find('\n', pre_index);
		string content = input.substr(pre_index, next_index - pre_index);
		map<string, Box>::iterator iter = boxes.find(receiver);
		iter->second.messages[iter->second.messages_num].content = content;
		iter->second.messages[iter->second.messages_num].time = time;
		iter->second.messages[iter->second.messages_num].sender = sender;
		iter->second.messages[iter->second.messages_num].receiver = receiver;
		iter->second.messages_num++;
		int flag = 0;
		for (int j = 0; j < iter->second.num; ++j) {
			if (iter->second.talkers[j] == sender) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			iter->second.talkers[iter->second.num] = sender;
			++iter->second.num;
		}
		iter = boxes.find(sender);
		iter->second.messages[iter->second.messages_num].content = content;
		iter->second.messages[iter->second.messages_num].time = time;
		iter->second.messages[iter->second.messages_num].sender = sender;
		iter->second.messages[iter->second.messages_num].receiver = receiver;
		iter->second.messages_num++;
		flag = 0;
		for (int j = 0; j < iter->second.num; ++j) {
			if (iter->second.talkers[j] == receiver) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			iter->second.talkers[iter->second.num] = receiver;
			++iter->second.num;
		}
	}
	for (map<string, Box>::iterator iter = boxes.begin(); iter != boxes.end(); ++iter) {
		for (int j = 0; j + 1 < iter->second.messages_num; ++j) {
			int min_index = j;
			for (int k = j+1; k < iter->second.messages_num; ++k) {
				if (iter->second.messages[k].time < iter->second.messages[min_index].time) {
					min_index = k;
				}
			}
			if (min_index != j) {
				Message tmp(iter->second.messages[j]);
				iter->second.messages[j] = iter->second.messages[min_index];
				iter->second.messages[min_index] = tmp;
			}
		}
	}
	ifile.close();
}

void Save() {
	SaveUsers();
	SaveGoods();
	SaveOrders();
	SaveTrolley();
	SaveBox();
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

void SaveTrolley() {
	ofstream ofile;
	ofile.open("trolley.txt", ios::out);
	ofile << "(userID)commodityID,commodityName,price,number,sellerID,addedDate,state";
	for (map<string, Trolley>::iterator iter = trolleys.begin(); iter != trolleys.end(); iter++) {
		ofile << '\n' << '(' << iter->first << ')' ;
		for (int i = 0; i < iter->second.num; ++i) {
			ofile << '\n' << iter->second.items[i].getid() << ',' << iter->second.items[i].getname() << ','
				<< fixed << setprecision(1) << iter->second.items[i].getprice() << ','
				<< iter->second.items[i].getnum() << ',' << iter->second.items[i].getseller() << ','
				<< iter->second.items[i].gettime() << ',';
			if (iter->second.items[i].getstate() == 0) ofile << "soldout";
			else ofile << "onsale";
		}
	}
	ofile.close();
	return;
}

void SaveBox() {
	ofstream ofile;
	ofile.open("message.txt", ios::out);
	ofile << "time,sender,receiver,content";
	for (map<string, Box>::iterator iter = boxes.begin(); iter != boxes.end(); ++iter) {
		for (int j = 0; j < iter->second.messages_num; ++j) {
			if(iter->second.messages[j].sender== iter->second.owner->getid())
			ofile << '\n' << iter->second.messages[j].time << ','
				<< iter->second.messages[j].sender << ','
				<< iter->second.messages[j].receiver << ','
				<< iter->second.messages[j].content;
		}
	}
	ofile.close();
	return;
}