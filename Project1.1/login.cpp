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
	cout << "�������û�����" ;
	cin >> name;
	cout << endl << "���������룺";
	cin >> password;
	for (int i = 0; users[i].getstate()!= -1; i++) {
		if (users[i].getname() == name && users[i].getpassword() == password && users[i].getstate()==1) {
			system("cls");
			cout << endl << "-----��¼�ɹ�-----" << endl;
			users[i].menu();
			return;
		}
		else if (users[i].getname() == name && users[i].getpassword() == password && users[i].getstate() == 0) {
			cout << endl << "���û��ѱ�����޷���¼" << endl;
			return;
		}
	}
	system("cls");
	cout << endl << "�û�������������������µ�¼" << endl;
	goto back;
}
