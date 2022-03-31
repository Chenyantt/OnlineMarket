#define _CRT_SECURE_NO_WARNINGS
#include "user.h"

#include <iostream>
#include <iomanip>
#include <fstream>

#include "check.h"
#include "register.h"
#include "update.h"
#include "insert.h"
#include "data.h"
#include "calculator.h"
#include "balance.h"
#include "color.h"

using namespace std;

int User::UserNum = 0;

User::User(string* id, string* name, string* password, string* phone, string* address, double m,int s) {
	UserNum++;
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

//获取当前用户总数
int User::GetNum() {
	return UserNum;
}

//更改当前用户总数
void User::ModNum(int n) {
	UserNum = n;
	return;
}

//用户菜单
void User::menu() {
	while (true) {
		cout << "===============================================================" <<endl;
		cout << " 1.我是买家 2.我是卖家 3.个人信息管理 4.留言箱 5.注销登录" << endl;
		cout << "===============================================================" << endl;
		cout << "请输入：";
		string input;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout <<"您的输入是:【" << input << "】" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "输入错误，请重新输入。" <<RESET<< endl << endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				buyer_menu();
				break;
			case '2':
				seller_menu();
				break;
			case '3':
				self_menu();
				break;
			case '4':
				boxes[user_id].menu();
				break;
			case '5':
				cout << FRONT_RED << "--- 退出登录 ---" << RESET << endl;
				return;
			default:
				cout << FRONT_RED << "输入错误，请重新输入。" <<RESET<< endl << endl;
				break;
			}
		}
	}
	return;
}

//获取用户ID
string User::getid() const {
	return user_id;
}

//获取用户名
string User::getname() const {
	return user_name;
}

//获取用户密码
string User::getpassword() const {
	return user_password;
}

//获取用户电话
string User::getphone() const {
	return user_phone;
}

//获取用户地址
string User::getaddress() const {
	return user_address;
}

//获取账户余额
double User::getmoney() const {
	return money;
}

//获取用户状态
int User::getstate() const {
	return state;
}

//查看用户个人信息
void User::check_info() const {
	cout << "***************************" << endl;
	cout << "用户名：" << user_name << endl;
	cout << "联系方式：" << user_phone << endl;
	cout << "地址：" << user_address << endl;
	cout << "**************************" << endl ;
	return;
}

//卖家菜单
void User::seller_menu() {
	while (true) {
		cout << "=====================================================================================================" << endl;
		cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.发布商品优惠 7.返回登录主界面" << endl;
		cout << "=====================================================================================================" << endl;
		cout << "请输入：";
		string input,attribute,value,id,name,des,number;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout <<"您的输入是:【" << input << "】" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "输入错误，请重新输入。" <<RESET<< endl << endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				cout << "请输入商品名称：";
				getline(cin, name);
				while (name == "") getline(cin, name);
				cout <<"请输入商品价格：";
				getline(cin, value);
				while (value == "") getline(cin, value);
				cout <<"请输入商品数量：";
				getline(cin, number);
				while (number == "") getline(cin, number);
				cout <<"请输入商品描述：";
				getline(cin,des);
				while (des == "") getline(cin, des);
				Insert("INSERT INTO commodity VALUES(" + name + "," + value + "," + number + "," + des + ")", 1, user_id);
				break;
			case '2':
				Check("SELECT * FROM commodity", 2, user_id);
				break;
			case '3':
				cout << "请输入被修改的商品ID：";
				getline(cin, id);
				while (id == "") getline(cin, id);
				back:
				cout <<"请输入被修改的商品属性（1.价格  2.描述）：";
				getline(cin, attribute);
				while (attribute == "") getline(cin, attribute);
				if (attribute.length() != 1) {
					cout << FRONT_RED <<"输入错误，请重新输入。" <<RESET<< endl;
					goto back;
				}
				else if (attribute == "1") {
					back2:
					cout <<"请输入被修改的商品价格：";
					getline(cin, value);
					while (value == "") getline(cin, value);
					attribute = "price";
						if (!IsNumberLegal(value)) {
							cout << FRONT_RED <<"输入错误, 请重新输入。" <<RESET<< endl;
							goto back2;
						}
				}
				else if (attribute == "2"){
					back1:
					cout <<"请输入被修改的商品描述：";
					getline(cin, value);
					while (value == "") getline(cin, value);
					attribute = "description";
					if (IsLegal(value, 200, 3));
					else {
						cout << FRONT_RED <<"输入错误, 请重新输入。" <<RESET<< endl;
						goto back1;
					}
				}
				else {
					cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl;
					goto back;
				}
				Update("UPDATE commodity SET "+attribute+" = "+value+" WHERE goods_id = " + id, 2, user_id);
				break;
			case '4':
				cout << "请输入要下架的商品ID：";
				getline(cin,id);
				while (id == "") getline(cin, id);
				Update("UPDATE commodity SET state = remove WHERE goods_id = " + id, 2, user_id);
				break;
			case '5':
				Check("SELECT * FROM order", 2, user_id);
				break;
			case '6':
				Account();
				break;
			case '7':
				cout << FRONT_RED<<"--- 返回主界面 ---"<<RESET << endl;
				return;
			default:
				cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl<< endl;
				break;
			}
			cout << endl;
		}
	}
	return;
}

//发布打折优惠
void User::Account() {
	string goods_id;
	cout << "请输入要优惠的商品ID：";
	getline(cin, goods_id);
	while (goods_id == "") getline(cin, goods_id);
	int j = 0;
	for (; goods[j].getstate() != -1; ++j) {
		if (goods[j].getid() == goods_id && goods[j].getseller() == getid()) break;
	}
	if (goods[j].getstate() != -1) {
		back:
		string mode;
		cout << "请输入优惠活动的模式(1.满减额活动  2.买赠活动)：";
		getline(cin, mode);
		while (mode == "") getline(cin, mode);
		if (mode == "1") {
			string sum,money;
			cout << "请输入满减金额（每满多少开始减免）:";
			getline(cin, sum);
			while (sum == "") getline(cin, sum);
			if (!IsNumberLegal(sum)) {
				cout << FRONT_RED << "输入错误，请重新输入!!!" << RESET << endl;
				goto back;
			}
			cout << "请输入减免的金额（每满额后减免多少）:";
			getline(cin, money);
			while (money == "") getline(cin, money);
			if (!IsNumberLegal(money) || stod(money) >= stod(sum)) {
				cout << FRONT_RED << "输入错误，请重新输入!!!" << RESET << endl;
				goto back;
			}
			goods[j].accountmode = sum + "-" + money;
			cout << FRONT_GREEN << "发布成功" << RESET << endl;
			return;
		}
		else if (mode == "2") {
			string sum, money;
			cout << "请输入购买数量（每买多少开始送）:";
			getline(cin, sum);
			while (sum == "") getline(cin, sum);
			if (!IsLegal(sum, 10, 4) || !IsNumberLegal(sum)) {
				cout << FRONT_RED << "输入错误，请重新输入!!!" << RESET << endl;
				goto back;
			}
			cout << "请输入赠送的数量（买后送多少）:";
			getline(cin, money);
			while (money == "") getline(cin, money);
			if (!IsLegal(money, 10, 4) || !IsNumberLegal(money)) {
				cout << FRONT_RED << "输入错误，请重新输入!!!" << RESET << endl;
				goto back;
			}
			goods[j].accountmode = sum + "/" + money;
			cout << FRONT_GREEN << "发布成功" << RESET << endl;
			return;
		}else{
			cout << FRONT_RED << "输入错误，请重新输入!!!" << RESET << endl;
			goto back;
		}
	}
	else {
		cout << FRONT_RED << "未查询到该商品ID!!!" << RESET << endl;
		return;
	}
}

//买家菜单
void User::buyer_menu() {
	while (true) {
		cout << "======================================================================================================================" << endl;
		cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.加入购物车 7. 查看购物车 8.返回登录主界面" << endl;
		cout << "======================================================================================================================" << endl;
		cout << "请输入：";
		string input,goods_name,number;
		int n,j;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout <<"您的输入是:【" << input << "】" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl << endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				Check("SELECT * FROM commodity", 3, user_id);
				break;
			case '2':
				cout << "请输入商品ID：";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				cout <<"请输入商品数量：";
				getline(cin, number);
				while (number == "") getline(cin, number);
				n=Insert("INSERT INTO order VALUES(" + goods_name + "," + number + ")",2,user_id);
				if (n != -1) Update("UPDATE commodity SET number = " + to_string(n) + " WHERE goods_id = " + goods_name, 2, user_id);
				break;
			case '3':
				cout << "请输入商品名称：";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				Check("SELECT * FROM commodity WHERE name CONTAINS " + goods_name, 3, user_id);
				break;
			case '4':
				Check("SELECT * FROM order", 3, user_id);
				break;
			case '5':
				cout << "请输入商品ID：";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				Check("SELECT * FROM commodity WHERE goods_id CONTAINS " + goods_name, 3, user_id);
				break;
			case '6':
				cout << "请输入商品ID：";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				for (j = 0; goods[j].getstate() != -1; ++j) {
					if (goods[j].getid() == goods_name) break;
				}
				if (goods[j].getstate() == -1 || goods[j].getstate() == 0) {
					cout << FRONT_RED << "未查询到该商品ID!!!" << RESET << endl;
					
				}
				else {
					cout << "请输入商品数量：";
					getline(cin, number);
					while (number == "") getline(cin, number);
					if (!IsLegal(number, 10, 4) || !IsNumberLegal(number)) {
						cout << FRONT_RED << "输入商品数量错误！！" << RESET << endl;
					}
					else {
						trolleys[user_id].add(goods_name,goods[j].getname(),goods[j].gettime(),goods[j].getseller(), goods[j].getprice(), stoi(number));
						cout << FRONT_GREEN << "加入成功" << RESET << endl;
					}
				}
				break;
			case '7':
				trolleys[user_id].check();
				break;
			case '8':
				cout << FRONT_RED<<"--- 返回主界面 ---" <<RESET<< endl;
				return;
			default:
				cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl << endl;
				break;
			}
			cout << endl;
		}
	}
	return;
}

//个人信息中心菜单
void User::self_menu() {
	while (true) {
		cout << "==========================================================================" << endl;
		cout << "1.查看信息 2.修改信息 3.充值 4.查看余额 5.启动计算器 6.返回用户主界面" << endl;
		cout << "==========================================================================" << endl;
		cout << "请输入：";
		string input;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout <<"您的输入是:【" << input << "】" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl << endl;
		}
		else {
			string str,output;
			char flag = input[0];
			switch (flag)
			{
			case '1':
				check_info();
				break;
			case '2':
				mod_info();
				break;
			case '3':
				recharge();
				break;
			case '4':
				cout<<"您的余额是："<<fixed<<setprecision(1)<<money<<endl;
				break;
			case '5':
				cout << "请输入算式：";
				getline(cin, str);
				while (str=="") getline(cin, str);
				output = Calculator(str);
				if ((output[0] < '0' || output[0]>'9') && output[0] != '-')
					cout  << FRONT_RED <<output << RESET << endl;
				else cout <<"计算的结果为：" << output << endl;
				break;
			case '6':
				cout << FRONT_RED << "--- 返回主界面 ---" <<RESET<< endl;
				return;
			default:
				cout << FRONT_RED << "输入错误, 请重新输入。" << RESET << endl << endl;
				break;
			}
			cout << endl;
		}
	}
	return;
}

//封禁用户
void User::ban() {
	state = 0;
	return;
}

//改变余额
void User::mod_money(double n) {
	money -= n;
	return;
}

//更改个人信息
void User::mod_info() {
	string input, name, phone, address, password1,password2;
	back:
	cout << "请选择你要修改的属性：（1.用户名  2.电话  3.地址 4. 密码）：";
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
			back1:
			cout << "请选择修改后的用户名：";
			getline(cin, name);
			while (name == "") getline(cin, name);
			if (getname() == name) {
				cout <<FRONT_RED<< "新用户名不可与旧用户名相同。" <<RESET<< endl;
				goto back1;
			}
			if(IsLegal(name, 10, 1) ){
				if (!IsDuplicate(name, 1)) {
					cout <<FRONT_RED<< "用户名重复，请重新输入。" <<RESET<< endl;
					goto back1;
				}
				else {
					user_name = name;
					cout << FRONT_GREEN << "----修改成功----" << RESET << endl;
				}
			}
			else {
				cout << FRONT_RED << "用户名过长或者含有非法字符，请重新输入。" <<RESET<< endl;
				goto back1;
			}
			break;
		case '2':
			back2:
			cout << "请选择修改后的电话：";
			getline(cin, phone);
			while (phone == "") getline(cin, phone);
			if (IsLegal(phone, 20, 4)) {
				user_phone = phone;
				cout << FRONT_GREEN << "----修改成功----" << RESET << endl;
			}
			else {
				cout <<FRONT_RED << "电话号码过长或者含有非法字符，请重新输入。" <<RESET<< endl;
				goto back2;
			}
			break;
		case '3':
			back3:
			cout <<"请选择修改后的地址：";
			getline(cin,address);
			while (address == "") getline(cin, address);
			if (IsLegal(address, 40, 1)) {
				user_address = address;
				cout << FRONT_GREEN << "----修改成功----" << RESET << endl;
			}
			else {
			cout << FRONT_RED << "地址过长或者含有非法字符，请重新输入。" <<RESET<< endl;
			goto back3;
			}
			break;
		case '4':
		back4:
			cout << "请填写修改后的密码：";
			getline(cin, password1);
			while (password1 == "") getline(cin, password1);
			if (IsLegal(password1, 20, 2)) {
				cout << "请再次输入修改后的密码：";
				getline(cin, password2);
				while (password2 == "") getline(cin, password2);
				if (password1 == password2) {
					user_password = password1;
					cout << FRONT_GREEN << "----修改成功----" << RESET << endl;
				}
				else {
					cout << FRONT_RED << "两次输入的密码不一致，请重新输入。" << RESET << endl;
					goto back4;
				}
			}
			else {
				cout << FRONT_RED << "密码过长或者含有非法字符，请重新输入。" << RESET << endl;
				goto back4;
			}
			break;
		default:
			cout << FRONT_RED << "输入错误，请重新输入。" <<RESET<< endl;
			goto back;
			break;
		}
	}
	return;
}

//充值
void User::recharge() {
	back:
	cout << "请输入充值金额（小数点后仅能输入一位小数）：";
	string m;
	getline(cin, m);
	while (m == "") getline(cin, m);
	if (!IsNumberLegal(m)) {
		cout << FRONT_RED <<"输入错误, 请重新输入。" <<RESET<< endl;
		goto back;
	}
	else {
		ofstream ofile;
		ofile.open("recharge.txt", ios::app);
		ofile << '\n' << user_id << ',' << m;
		ofile.close();
		money += stod(m);
		cout << FRONT_GREEN << "---充值成功---" << RESET << endl;
	}
	return;
}

//判断数字是否合法
int IsNumberLegal(string s) {
	if ((s[0]== '0'&& s[1]!= '.') || s[0] == '.' || s[s.length() - 1] == '.') return 0;
	if (s.find('.') != -1 && s.length() > s.find('.') + 2) {
		return 0;
	}
	int cnt = 0;
	for (int i = 0; i<(int)s.length(); ++i) {
		if (s[i] == '.' ) {
			cnt++;
		}
		else if (s[i]<'0' || s[i]>'9') {
			return 0;
		}
	}
	if (cnt >= 2) return 0;
	if(stod(s)<=0) return 0;
	return 1;
}