#define _CRT_SECURE_NO_WARNINGS

#include "login.h"
#include "data.h"
#include "user.h"

#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

void Login() {	
	string name, password;
back:	
	cout << "请输入用户名：" ;
	cin >> name;
	cout << endl << "请输入密码：";
	cin >> password;
	for (int i = 0; users[i].getstate()!= -1; i++) {
		if (users[i].getname() == name && users[i].getpassword() == password && users[i].getstate()==1) {
			system("cls");
			cout << endl << "-----登录成功-----" << endl;
			users[i].menu();
			return;
		}
		else if (users[i].getname() == name && users[i].getpassword() == password && users[i].getstate() == 0) {
			cout << endl << "该用户已被封禁无法登录" << endl;
			return;
		}
	}
	system("cls");
	cout << endl << "用户名或者密码错误，请重新登录" << endl;
	goto back;
}
