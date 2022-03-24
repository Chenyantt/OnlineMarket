#define _CRT_SECURE_NO_WARNINGS
#include "administrator.h"

#include <string>
#include <iostream>
#include <map>

#include "check.h"
#include "update.h"
#include "color.h"
#include "data.h"

Administrator::Administrator() : admin_name("admin"), admin_password("123456") {}

void Administrator::Login() {
	string input;
	cout << "请输入用户名：";
	getline(cin, input);
	while (input == "") getline(cin, input);
	if (input != "admin") {
		system("cls");
		cout << FRONT_RED << "用户名错误，请重新输入" <<RESET<< endl;
	}
	else {
		cout << "请输入密码：";
		getline(cin, input);
		while (input == "") getline(cin, input);
		if (input != "123456") {
			system("cls");
			cout << FRONT_RED << "密码错误，请重新输入" <<RESET<< endl;
		}
		else {
			system("cls");
			cout << FRONT_GREEN << "------登录成功------" <<RESET<< endl << endl;
			this->Menu();
		}
	}
	return;
}


void Administrator::Menu() {
	while (true) {
		cout << "========================================================================================================================" << endl;
		cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看订单 5.查看用户 6.封禁用户 7.查看所有用户留言 8.查看指定用户留言 9.注销" << endl;
		cout << "========================================================================================================================" << endl;
		cout<<"请输入：";
		string input,name,id;
		getline(cin, input);
		while(input=="") getline(cin, input);
		cout << "您的输入是:【" << input << "】" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "输入错误，请重新输入。" <<RESET<< endl<< endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				Check("SELECT * FROM commodity", 1, "administrator");
				break;
			case '2':
				cout << "请输入商品名称：";
				getline(cin, name);
				while (name == "") getline(cin, name);
				Check("SELECT * FROM commodity WHERE name CONTAINS " + name, 1, "administrator");
				break;
			case '3':
				cout << "请输入要下架的商品ID：";
				getline(cin, id);
				while (id == "") getline(cin, id);
				Update("UPDATE commodity SET state = remove WHERE goods_id = " + id, 1, "administrator");
				break;
			case '4':
				Check("SELECT * FROM order", 1, "administrator");
				break;
			case '5':
				Check("SELECT * FROM user", 1, "administrator");
				break;
			case '6':
				cout << "请输入要封禁的用户ID：";
				getline(cin, id);
				while (id == "") getline(cin, id);
				if(BanUser("UPDATE user SET state = inactive WHERE id = " + id, 1, "administrator"))
					Update("UPDATE commodity SET state = remove WHERE id = " + id, 3, "administrator");
				break;
			case '7':
				CheckMessage();
				break;
			case '8':
				SearchMessage();
				break;
			case '9':
				system("cls");
				cout << FRONT_RED <<"--- 退出登录 ---" <<RESET<< endl;
				return;
			default:
				cout << FRONT_RED << "输入错误，请重新输入。" <<RESET<< endl;
				break;
			}
			cout << endl;
		}
	}
}

void CheckMessage() {
	int flag = 0;
	for (map<string, Box>::iterator iter = boxes.begin(); iter != boxes.end(); ++iter) {
		for (int j = 0; j < iter->second.messages_num; ++j) {
			if(flag==0) cout << "*******************************************" << endl;
			flag = 1;
			if(iter->second.messages[j].sender== iter->second.owner->getid())
			cout << REVERSE << FRONT_GREEN << iter->second.messages[j].sender << "发送给" << iter->second.messages[j].receiver
				<< ':' <<RESET<<REVERSE <<iter->second.messages[j].content  <<RESET<< '('
				<< iter->second.messages[j].time<<')' << endl;
		}
	}
	if (!flag) cout << "查无历史消息" << endl;
	else cout << "*******************************************" << endl;
	return;
}

void SearchMessage() {
	cout << "请输入查找的用户：";
	string input;
	int flag = 0;
	getline(cin, input);
	while (input == "") getline(cin, input);
	map<string, Box>::iterator iter = boxes.find(input);
	if (iter == boxes.end())
	{
		cout << FRONT_RED << "查无该用户" << RESET << endl;
		return;
	}
	if (iter->second.num == 0) {
		cout << "查无历史消息" << endl;
		return;
	}
	cout << "*******************************************" << endl;
	cout << "该用户的历史消息：" << endl;
	for (int i = 0; i < iter->second.messages_num; ++i) {
		if (iter->second.messages[i].sender == input) {
			cout << REVERSE << FRONT_GREEN << "发送给" << iter->second.messages[i].receiver << "："
				<<RESET <<REVERSE<< iter->second.messages[i].content <<RESET<<'('<< iter->second.messages[i].time
				<<')' << endl;
		}
		else {
			cout << REVERSE << FRONT_RED << "来自于" << iter->second.messages[i].receiver << "："
				<< RESET << REVERSE << iter->second.messages[i].content << RESET << '(' << iter->second.messages[i].time
				<< ')' << endl;
		}
	}
	cout << "******************************************" << endl;
	return;
}