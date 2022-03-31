#define _CRT_SECURE_NO_WARNINGS

#include "login.h"

#include <iostream>
#include <string>

#include "data.h"
#include "user.h"
#include "color.h"

using namespace std;

//登录，并检查账号密码的正确性
void Login() {	
	string name, password;
	back:	
	cout << "请输入用户名：" ;
	getline(cin, name);
	while (name == "") getline(cin, name);
	cout <<"请输入密码：";
	getline(cin, password);
	while (password == "") getline(cin, password);
	for (int i = 0; users[i].getstate()!= -1; i++) {
		if (users[i].getname() == name && users[i].getpassword() == password && users[i].getstate()==1) {
			cout <<FRONT_GREEN<<"-----登录成功-----" <<RESET<< endl;
			users[i].menu();
			return;
		}
		else if (users[i].getname() == name && users[i].getpassword() == password && users[i].getstate() == 0) {
			cout <<"该用户已被封禁无法登录" << endl;
			return;
		}
	}
	cout << FRONT_RED <<"用户名或者密码错误，请重新登录" <<RESET<< endl;
	goto back;
}
