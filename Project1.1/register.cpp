#define _CRT_SECURE_NO_WARNINGS
#include "register.h"
#include "user.h"
#include "data.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

void Register() {
	string user_name;
back:
	printf("�������û�����������10���ַ�������ʹ��Ӣ����ĸ����");
	cin >> user_name;
	if (IsLegal(user_name, 10, 1)) {
		if (!IsDuplicate(user_name,1)) {
			cout << "�û����ظ������������롣" << endl;
			goto back;
		}
		else {
			getchar();
			BuildCount(user_name);
			return;
		}
	}
	else {
		cout << "�û����������ߺ��зǷ��ַ������������롣" << endl;
		goto back;
	}
}

//username mode 1;password mode 2;desciption & address mode 3;phone mode 4;
bool IsLegal(string name, int max_length, int mode) {
	int length = name.length();
	if (length > max_length) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		if ((name[i] >= 48 && name[i] <= 57) || (mode == 3 && name[i] >= 0 && name[i] <= 127) || 
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
	cout << "���������루������20���ַ���ֻ����Сд��ĸ��������ɣ���" << endl;
	getline(cin,password);
	if (IsLegal(password, 20, 2)) {
	back2:
		cout << "����д��ַ��������40���ַ�������ʹ��Ӣ���ַ������֣���" << endl;
		getline(cin, address);
		if (IsLegal(address, 40, 3)) {
		back3:
			cout << "����д�ֻ����루������20���ַ�������ʹ�����֣���" << endl;
			getline(cin, phone);
			if (IsLegal(phone, 20, 4)) {
				string uid = BuildUid('U');
				users[User::GetNum()-1] = User(&uid, &name, &password, &phone, &address, 0, 1);
				return;
			}
			else {
				cout << "�绰����������ߺ��зǷ��ַ������������롣" << endl;
				goto back3;
			}
		}
		else {
			cout << "��ַ�������ߺ��зǷ��ַ������������롣" << endl;
			goto back2;
		}
	}
	else {
		cout << "����������ߺ��зǷ��ַ������������롣" << endl;
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