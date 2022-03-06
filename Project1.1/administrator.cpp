#define _CRT_SECURE_NO_WARNINGS
#include "administrator.h"

#include <string>
#include <iostream>
#include <Windows.h>

#include "check.h"
#include "update.h"

Administrator::Administrator() : admin_name("admin"), admin_password("123456") {}

void Administrator::Login() {
	string input;
	cout << "请输入用户名：";
	cin >> input;
	if (input != "admin") {
		system("cls");
		cout << "用户名错误，请重新输入" << endl;
	}
	else {
		cout << endl << "请输入密码：";
		cin >> input;
		if (input != "123456") {
			system("cls");
			cout << "密码错误，请重新输入" << endl;
		}
		else {
			system("cls");
			cout << "-----登录成功-----" << endl;
			this->Menu();
		}
	}
	return;
}


void Administrator::Menu() {
	while (true) {
		cout << "=========================================================================================" << endl;
		cout << "  1.查看所有商品  2.搜索商品  3.下架商品  4.查看所有订单  5.查看所有用户  6.封禁用户  7.注销" << endl;
		cout << "=========================================================================================" << endl;
		cout<<"请输入：";
		string input,name,id;
		cin >> input;
		cout << endl << "您的输入是:【 " << input << " 】" << endl;
		if (input.length() != 1) {
			system("cls");
			cout << "输入错误，请重新输入。" << endl;
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
				cin >> name;
				cout << endl;
				Check("SELECT * FROM commodity WHERE name CONTAINS " + name, 1, "administrator");
				break;
			case '3':
				cout << "请输入要下架的商品ID：";
				cin >> id;
				cout << endl;
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
				cin >> id;
				cout << endl;
				if(BanUser("UPDATE user SET state = inactive WHERE id = " + id, 1, "administrator"))
					Update("UPDATE commodity SET state = remove WHERE id = " + id, 3, "administrator");
				break;
			case '7':
				system("cls");
				cout << "--- 退出登录 ---" << endl;
				return;
			default:
				system("cls");
				cout << "输入错误，请重新输入。" << endl << endl;
				break;
			}
		}
	}
}