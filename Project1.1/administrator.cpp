#define _CRT_SECURE_NO_WARNINGS
#include "administrator.h"

#include <string>
#include <iostream>
#include <Windows.h>

#include "check.h"
#include "update.h"

Administrator::Administrator() : admin_name("admin"), admin_password("123456") {}

void Administrator::Login() {
	string input;
	cout << "�������û�����";
	cin >> input;
	if (input != "admin") {
		system("cls");
		cout << "�û�����������������" << endl;
	}
	else {
		cout << endl << "���������룺";
		cin >> input;
		if (input != "123456") {
			system("cls");
			cout << "�����������������" << endl;
		}
		else {
			system("cls");
			cout << "-----��¼�ɹ�-----" << endl;
			this->Menu();
		}
	}
	return;
}


void Administrator::Menu() {
	while (true) {
		cout << "=========================================================================================" << endl;
		cout << "  1.�鿴������Ʒ  2.������Ʒ  3.�¼���Ʒ  4.�鿴���ж���  5.�鿴�����û�  6.����û�  7.ע��" << endl;
		cout << "=========================================================================================" << endl;
		cout<<"�����룺";
		string input,name,id;
		cin >> input;
		cout << endl << "����������:�� " << input << " ��" << endl;
		if (input.length() != 1) {
			system("cls");
			cout << "����������������롣" << endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				Check("SELECT * FROM commodity", 1, "administrator");
				break;
			case '2':
				cout << "��������Ʒ���ƣ�";
				cin >> name;
				cout << endl;
				Check("SELECT * FROM commodity WHERE name CONTAINS " + name, 1, "administrator");
				break;
			case '3':
				cout << "������Ҫ�¼ܵ���ƷID��";
				cin >> id;
				cout << endl;
				Update("UPDATE commodity SET state = remove WHERE goods_id = " + id, 1, "administrator");
				break;
			case '4':
				Check("SELECT * FROM order", 1, "administrator");
				break;
			case '5':
				Check("SELECT * FROM user", 1, "administrator");
				break;
			case '6':
				cout << "������Ҫ������û�ID��";
				cin >> id;
				cout << endl;
				if(BanUser("UPDATE user SET state = inactive WHERE id = " + id, 1, "administrator"))
					Update("UPDATE commodity SET state = remove WHERE id = " + id, 3, "administrator");
				break;
			case '7':
				system("cls");
				cout << "--- �˳���¼ ---" << endl;
				return;
			default:
				system("cls");
				cout << "����������������롣" << endl << endl;
				break;
			}
		}
	}
}