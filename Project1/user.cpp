#define _CRT_SECURE_NO_WARNINGS
#include "user.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#include "check.h"
#include "register.h"
#include "update.h"
#include "insert.h"

using namespace std;

User::User(string* id, string* name, string* password, string* phone, string* address) :state(0), money(0) {
	user_id = *id;
	user_name = *name;
	user_password = *password;
	user_address = *address;
	user_phone = *phone;
	ofstream ofile;
	ofile.open("user.txt", ios::app);
	ofile <<'\n' << user_id << ',' << *name << ',' << *password << ',' << *phone <<',' << *address<<',' <<setprecision(1)<<fixed<< money<<',' << "active";
	ofile.close();
}

User::User(string* id, string* name, string* password, string* phone, string* address, double m,int s) {
	user_id = *id;
	user_name = *name;
	user_password = *password;
	user_address = *address;
	user_phone = *phone;
	money = m;
	state = s;
}

User::User() {
	state = -1;
}

void User::menu() {
	while (true) {
		printf("=============================================\n");
		printf(" 1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录\n");
		printf("=============================================\n");
		printf("请输入：");
		string input;
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
			case '4':
				system("cls");
				cout << "--- 退出登录 ---" << endl;
				return;
			case '1':
				buyer_menu();
				break;
			case '2':
				seller_menu();
				break;
			case '3':
				self_menu();
				break;
			default:
				system("cls");
				cout << "输入错误，请重新输入。" << endl << endl;
				break;
			}
		}
	}
	return;
}

string User::getid() {
	return user_id;
}

string User::getname() {
	return user_name;
}

string User::getpassword() {
	return user_password;
}

string User::getphone() {
	return user_phone;
}

string User::getaddress() {
	return user_address;
}

double User::getmoney() {
	return money;
}

int User::getstate() {
	return state;
}

void User::ban() {
	state = 0;
	return;
}

void User::seller_menu() {
	while (true) {
		printf("==============================================================================\n");
		printf("1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回登录主界面\n");
		printf("==============================================================================\n");
		printf("请输入：");
		string input,attribute,value,id,name,des,number;
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
			case '6':
				system("cls");
				cout << "--- 返回主界面 ---" << endl;
				return;
			case '1':
				cout << "请输入商品名称：";
				cin >> name;
				cout << endl << "请输入商品价格：";
				cin >> value;
				cout << endl << "请输入商品数量：";
				cin >> number;
				cout << endl << "请输入商品描述：";
				getchar();
				getline(cin,des);
				cout << endl;
				Insert("INSERT INTO commodity VALUES(" + name + "," + value + "," + number + "," + des + ")", 1, user_id);
				break;
			case '2':
				Check("SELECT * FROM commodity", 2, user_id);
				break;
			case '3':
				cout << "请输入被修改的商品ID：";
				cin >> id;
				back:
				cout << endl<<"请输入被修改的商品属性（1.价格  2.描述）：";
				cin >> attribute;
				if (attribute.length() != 1) {
					cout <<endl<< "输入错误，请重新输入。" << endl;
					goto back;
				}
				else if (attribute == "1") {
					back2:
					cout << endl << "请输入被修改的商品价格：";
					cin >> value;
					attribute = "price";
						int index = value.find('.');
						int length = int(value.length());
						if ((index == -1 && !IsLegal(value, 10, 4)) || (index != -1 && length > index + 2) || index == 0) {
							cout << endl << "输入错误, 请重新输入。" << endl;
							goto back2;
						}
				}
				else if (attribute == "2"){
					back1:
					cout << endl << "请输入被修改的商品描述：";
					getchar();
					getline(cin, value);
					attribute = "description";
					if (IsLegal(value, 200, 3));
					else {
						cout << endl << "输入错误, 请重新输入。" << endl;
						goto back1;
					}
				}
				else {
					cout << endl << "输入错误，请重新输入。" << endl;
					goto back;
				}
				Update("UPDATE commodity SET "+attribute+" = "+value+" WHERE goods_id = " + id, 2, user_id);
				break;
			case '4':
				cout << "请输入要下架的商品ID：";
				cin >> id;
				cout << endl;
				Update("UPDATE commodity SET state = remove WHERE goods_id = " + id, 2, user_id);
				break;
			case '5':
				Check("SELECT * FROM order", 2, user_id);
				break;
			default:
				system("cls");
				cout << "输入错误，请重新输入。" << endl << endl;
				break;
			}
		}
	}
	return;
}

void User::buyer_menu() {
	while (true) {
		printf("==================================================================================\n");
		printf("1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回登录主界面\n");
		printf("==================================================================================\n");
		printf("请输入：");
		string input,goods_name,number;
		int n;
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
			case '6':
				system("cls");
				cout << "--- 返回主界面 ---" << endl;
				return;
			case '1':
				Check("SELECT * FROM commodity", 3, user_id);
				break;
			case '2':
				cout << "请输入商品ID：";
				cin >> goods_name;
				cout << endl << "请输入商品数量：";
				cin >> number;
				cout << endl;
				n=Insert("INSERT INTO order VALUES(" + goods_name + "," + number,2,user_id);
				if (n != -1) Update("UPDATE commodity SET number = " + to_string(n) + " WHERE goods_id = " + goods_name, 2, user_id);
				break;
			case '3':
				cout << "请输入商品名称：";
				cin >> goods_name;
				cout << endl;
				Check("SELECT * FROM commodity WHERE name CONTAINS " + goods_name, 3, user_id);
				break;
			case '4':
				Check("SELECT * FROM order", 3, user_id);
				break;
			case '5':
				cout << "请输入商品ID：";
				cin >> goods_name;
				cout << endl;
				Check("SELECT * FROM commodity WHERE goods_id CONTAINS " + goods_name, 3, user_id);
				break;
			default:
				system("cls");
				cout << "输入错误，请重新输入。" << endl << endl;
				break;
			}
		}
	}
	return;
}

void User::self_menu() {
	while (true) {
		printf("=============================================\n");
		printf("1.查看信息 2.修改信息 3.充值 4.返回用户主界面\n");
		printf("=============================================\n");
		printf("请输入：");
		string input;
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
			case '4':
				system("cls");
				cout << "--- 返回主界面 ---" << endl;
				return;
			case '1':
				check_info();
				break;
			case '2':
				mod_info();
				break;
			case '3':
				recharge();
				break;
			default:
				system("cls");
				cout << "输入错误，请重新输入。" << endl << endl;
				break;
			}
		}
	}
	return;
}

void User::check_info() {
	cout << "***************************"<< endl;
	cout << "用户名：" << user_name << endl;
	cout << "联系方式：" << user_phone << endl;
	cout << "地址：" << user_address << endl;
	cout << "钱包余额：" << money << endl;
	cout << "**************************" << endl<<endl<<endl;
	return;
}

void User::mod_money(double n) {
	money -= n;
	return;
}

void User::mod_info() {
	string input,name,phone,address;
back:
	cout << "请选择你要修改的属性：（1.用户名  2.电话  3.地址）：";
	cin >> input;
	if (input.length() != 1) {
		system("cls");
		cout << "输入错误，请重新输入。" << endl;
		goto back;
	}
	else {
		char flag = input[0];
		switch (flag)
		{
		case '1':
			back1:
			cout <<endl<< "请选择修改后的用户名：";
			cin >> name;
			if(IsLegal(name, 10, 1) ){
				if (!IsDuplicate(name, 1)) {
					cout <<endl<< "用户名重复，请重新输入。" << endl;
					goto back1;
				}
				else {
					user_name = name;
					cout << "----修改成功----" << endl;
				}
			}
			else {
				cout << "用户名过长或者含有非法字符，请重新输入。" << endl;
				goto back1;
			}
			break;
		case '2':
			back2:
			cout <<endl<< "请选择修改后的电话：";
			cin >> phone;
			if (IsLegal(phone, 20, 4)) {
				user_phone = phone;
				cout << "----修改成功----" << endl;
			}
			else {
				cout <<endl<< "电话号码过长或者含有非法字符，请重新输入。" << endl;
				goto back2;
			}
			break;
		case '3':
			back3:
			cout <<endl<< "请选择修改后的地址：";
			getchar();
			getline(cin,address);
			if (IsLegal(address, 40, 3)) {
				user_address = address;
				cout << "----修改成功----" << endl;
			}
			else {
			cout <<endl<< "地址过长或者含有非法字符，请重新输入。" << endl;
			goto back3;
			}
			break;
		default:
			system("cls");
			cout << "输入错误，请重新输入。" << endl;
			goto back;
			break;
		}
	}
	return;
}

void User::recharge() {
	back:
	cout << "请输入充值金额（小数点后仅能输入一位小数）：";
	string m;
	cin >> m;
	int index = m.find('.');
	int length = int(m.length());
	if ((index == -1 && !IsLegal(m, 10, 4)) || (index != -1 && length > index + 2) || index == 0) {
		cout <<endl<<"输入错误, 请重新输入。" << endl;
		goto back;
	}
	else {
		money += stod(m);
		cout << endl << "---充值成功---" << endl;
	}
	return;
}