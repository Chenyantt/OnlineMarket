#define _CRT_SECURE_NO_WARNINGS
#include "administrator.h"

#include <string>
#include <iostream>
#include <map>

#include "check.h"
#include "update.h"
#include "color.h"
#include "data.h"

Administrator::Administrator() : admin_name("admin"), admin_password("123456") {}

void Administrator::Login() {
	string input;
	cout << "�������û�����";
	getline(cin, input);
	while (input == "") getline(cin, input);
	if (input != "admin") {
		system("cls");
		cout << FRONT_RED << "�û�����������������" <<RESET<< endl;
	}
	else {
		cout << "���������룺";
		getline(cin, input);
		while (input == "") getline(cin, input);
		if (input != "123456") {
			system("cls");
			cout << FRONT_RED << "�����������������" <<RESET<< endl;
		}
		else {
			system("cls");
			cout << FRONT_GREEN << "------��¼�ɹ�------" <<RESET<< endl << endl;
			this->Menu();
		}
	}
	return;
}


void Administrator::Menu() {
	while (true) {
		cout << "========================================================================================================================" << endl;
		cout << "1.�鿴������Ʒ 2.������Ʒ 3.�¼���Ʒ 4.�鿴���� 5.�鿴�û� 6.����û� 7.�鿴�����û����� 8.�鿴ָ���û����� 9.ע��" << endl;
		cout << "========================================================================================================================" << endl;
		cout<<"�����룺";
		string input,name,id;
		getline(cin, input);
		while(input=="") getline(cin, input);
		cout << "����������:��" << input << "��" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "����������������롣" <<RESET<< endl<< endl;
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
				getline(cin, name);
				while (name == "") getline(cin, name);
				Check("SELECT * FROM commodity WHERE name CONTAINS " + name, 1, "administrator");
				break;
			case '3':
				cout << "������Ҫ�¼ܵ���ƷID��";
				getline(cin, id);
				while (id == "") getline(cin, id);
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
				getline(cin, id);
				while (id == "") getline(cin, id);
				if(BanUser("UPDATE user SET state = inactive WHERE id = " + id, 1, "administrator"))
					Update("UPDATE commodity SET state = remove WHERE id = " + id, 3, "administrator");
				break;
			case '7':
				CheckMessage();
				break;
			case '8':
				SearchMessage();
				break;
			case '9':
				system("cls");
				cout << FRONT_RED <<"--- �˳���¼ ---" <<RESET<< endl;
				return;
			default:
				cout << FRONT_RED << "����������������롣" <<RESET<< endl;
				break;
			}
			cout << endl;
		}
	}
}

void CheckMessage() {
	int flag = 0;
	for (map<string, Box>::iterator iter = boxes.begin(); iter != boxes.end(); ++iter) {
		for (int j = 0; j < iter->second.messages_num; ++j) {
			if(flag==0) cout << "*******************************************" << endl;
			flag = 1;
			if(iter->second.messages[j].sender== iter->second.owner->getid())
			cout << REVERSE << FRONT_GREEN << iter->second.messages[j].sender << "���͸�" << iter->second.messages[j].receiver
				<< ':' <<RESET<<REVERSE <<iter->second.messages[j].content  <<RESET<< '('
				<< iter->second.messages[j].time<<')' << endl;
		}
	}
	if (!flag) cout << "������ʷ��Ϣ" << endl;
	else cout << "*******************************************" << endl;
	return;
}

void SearchMessage() {
	cout << "��������ҵ��û���";
	string input;
	int flag = 0;
	getline(cin, input);
	while (input == "") getline(cin, input);
	map<string, Box>::iterator iter = boxes.find(input);
	if (iter == boxes.end())
	{
		cout << FRONT_RED << "���޸��û�" << RESET << endl;
		return;
	}
	if (iter->second.num == 0) {
		cout << "������ʷ��Ϣ" << endl;
		return;
	}
	cout << "*******************************************" << endl;
	cout << "���û�����ʷ��Ϣ��" << endl;
	for (int i = 0; i < iter->second.messages_num; ++i) {
		if (iter->second.messages[i].sender == input) {
			cout << REVERSE << FRONT_GREEN << "���͸�" << iter->second.messages[i].receiver << "��"
				<<RESET <<REVERSE<< iter->second.messages[i].content <<RESET<<'('<< iter->second.messages[i].time
				<<')' << endl;
		}
		else {
			cout << REVERSE << FRONT_RED << "������" << iter->second.messages[i].receiver << "��"
				<< RESET << REVERSE << iter->second.messages[i].content << RESET << '(' << iter->second.messages[i].time
				<< ')' << endl;
		}
	}
	cout << "******************************************" << endl;
	return;
}