#define _CRT_SECURE_NO_WARNINGS

#include "login.h"

#include <iostream>
#include <string>

#include "data.h"
#include "user.h"
#include "color.h"

using namespace std;

void Login() {	
	string name, password;
back:	
	cout << "�������û�����" ;
	getline(cin, name);
	while (name == "") getline(cin, name);
	cout <<"���������룺";
	getline(cin, password);
	while (password == "") getline(cin, password);
	for (int i = 0; users[i].getstate()!= -1; i++) {
		if (users[i].getname() == name && users[i].getpassword() == password && users[i].getstate()==1) {
			system("cls");
			cout <<FRONT_GREEN<<"-----��¼�ɹ�-----" <<RESET<< endl;
			users[i].menu();
			return;
		}
		else if (users[i].getname() == name && users[i].getpassword() == password && users[i].getstate() == 0) {
			system("cls");
			cout <<"���û��ѱ�����޷���¼" << endl;
			return;
		}
	}
	cout << FRONT_RED <<"�û�������������������µ�¼" <<RESET<< endl;
	goto back;
}
