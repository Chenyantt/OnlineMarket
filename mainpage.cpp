#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "register.h"
#include "login.h"
#include "data.h"
#include "file.h"
#include "color.h"

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

//程序入口，交互主界面
int main() {
	Welcome();
	while (true) {
		string input = Menu();
		if (input.length() != 1) {
			cout << FRONT_RED << "输入错误，请重新输入。" <<RESET<< endl;
		}
		else {
			Init();
			char flag = input[0];
			switch (flag)
			{
			case '1':
				admin.Login();
				break;
			case '2':
				Register();
				cout << FRONT_GREEN << "恭喜你！注册成功！" <<RESET<< endl;
				break;
			case '3':
				Login();
				break;
			case '4':
				Goodbye();
				return 0;
			default:
				cout << FRONT_RED << "输入错误，请重新输入。" <<RESET<< endl;
				break;
			}
			Save();
		}
	}
	return 0;
}