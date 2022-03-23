#define _CRT_SECURE_NO_WARNINGS
#include "register.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "user.h"
#include "data.h"
#include "color.h"

using namespace std;

void Register() {
	string user_name;
back:
	cout << "请设置用户名（不超过10个字符，仅可使用英文字母）：";
	getline(cin, user_name);
	while (user_name == "") getline(cin, user_name);
	if (IsLegal(user_name, 10, 1)) {
		if (!IsDuplicate(user_name,1)) {
			cout <<FRONT_RED<< "用户名重复，请重新输入。" <<RESET<< endl;
			goto back;
		}
		else {
			BuildCount(user_name);
			return;
		}
	}
	else {
		cout << FRONT_RED << "用户名过长或者含有非法字符，请重新输入。" <<RESET<< endl;
		goto back;
	}
}

//username address mode 1;password mode 2;desciption  mode 3;phone mode 4;
bool IsLegal(string name, int max_length, int mode) {
	int length = name.length();
	if (length > max_length) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		if (( mode != 1 && name[i] >= 48 && name[i] <= 57) || (mode == 3 && name[i] >= 0 && name[i] <= 127) || 
			(mode == 1 && name[i] >= 65 && name[i] <= 90) || (mode!=4 && name[i] >= 97 && name[i] <= 122)) {
			continue;
		}
		return false;
	}
	return true;
}

bool IsDuplicate(string name,int mode) {
	if (mode == 'M') {
		for (int i = 0; goods[i].getstate() != -1; ++i) {
			if(goods[i].getid()==name) return false;
		}
		return true;
	}
	else if (mode == 'T') {
		for (int i = 0; orders[i].getnumber() != -1; ++i) {
			if (name == orders[i].getid()) return false;
		}
		return true;
	}
	else {
		for (int i = 0; users[i].getstate() != -1; ++i) {
			if (mode == 1) {
				if (name == users[i].getname()) return false;
			}
			else if (mode == 'U') {
				if (name == users[i].getid()) return false;
			}
		}
		return true;
	}
}

void BuildCount(string name) {
	string password, address, phone;
back1:
	cout << "请设置密码（不超过20个字符，只可有小写字母和数字组成）：";
	getline(cin,password);
	while (password == "") getline(cin, password);
	if (IsLegal(password, 20, 2)) {
	back2:
		cout <<"请填写地址（不超过40个字符，仅可使用英文字母）：";
		getline(cin, address);
		while (address == "") getline(cin, address);
		if (IsLegal(address, 40, 1)) {
		back3:
			cout <<"请填写手机号码（不超过20个字符，仅可使用数字）：";
			getline(cin, phone);
			while (phone == "") getline(cin, phone);
			if (IsLegal(phone, 20, 4)) {
				string uid = BuildUid('U');
				users[User::GetNum()-1] = User(&uid, &name, &password, &phone, &address, 0, 1);
				Box tmp;
				tmp.owner = &users[User::GetNum() - 1];
				boxes.insert(pair<string, Box>(uid, tmp));
				return;
			}
			else {
				cout <<FRONT_RED<< "电话号码过长或者含有非法字符，请重新输入。" <<RESET<< endl;
				goto back3;
			}
		}
		else {
			cout << FRONT_RED << "地址过长或者含有非法字符，请重新输入。" <<RESET<< endl;
			goto back2;
		}
	}
	else {
		cout << FRONT_RED << "密码过长或者含有非法字符，请重新输入。" <<RESET<< endl;
		goto back1;
	}
}

string BuildUid(char c) {
	char ch[5] = {0};
	ch[0] = c;
	srand(unsigned(time(0)));
	while (true)
	{
		int a = rand() % 10, b = rand() % 10, c = rand() % 10;
		ch[1] = a + 48, ch[2] = b + 48, ch[3] = c + 48;
		string id = ch;
		if (IsDuplicate(id, c)) return id;
	}
}