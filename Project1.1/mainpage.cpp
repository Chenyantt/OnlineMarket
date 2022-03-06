#define _CRT_SECURE_NO_WARNINGS
#include "administrator.h"
#include "goods.h"
#include "order.h"
#include "menu.h"
#include "user.h"
#include "register.h"
#include "login.h"
#include "data.h"
#include "file.h"
#include "check.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>

using namespace std;

int main() {
	Welcome();
	while (true) {
		string input = Menu();
		if (input.length() != 1) {
			system("cls");
			cout << "输入错误，请重新输入。" << endl;
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
				system("cls");
				cout << "恭喜你！注册成功！" << endl;
				break;
			case '3':
				Login();
				break;
			case '4':
				Goodbye();
				return 0;
			default:
				cin.clear();
				cin.sync();
				system("cls");
				cout << "输入错误，请重新输入。" << endl;
				break;
			}
			Save();
		}
	}
	return 0;
}