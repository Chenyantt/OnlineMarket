#define _CRT_SECURE_NO_WARNINGS
#include "box.h"

#include <iostream>
#include <iomanip>
#include <time.h>

#include "color.h"
#include "data.h"

using namespace std;

Message::Message(){
	content = "";
}

Box::Box() {
	num = 0;
	messages_num = 0;
}

void Box::menu() {
	system("cls");
	while (true) {
		cout << "========================================================================" << endl;
		cout << " 1.�鿴���� 2.������ʷ��Ϣ 3.�������� 4.�����û�������" << endl;
		cout << "========================================================================" << endl;
		cout << "�����룺";
		string input;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout << "����������:��" << input << "��" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "����������������롣" << RESET << endl << endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				check();
				break;
			case '2':
				search();
				break;
			case '3':
				send();
				break;
			case '4':
				system("cls");
				cout << FRONT_RED << "--- ���������� ---" << RESET << endl;
				return;
			default:
				cout << FRONT_RED << "����������������롣" << RESET << endl << endl;
				break;
			}
			cout << endl;
		}
	}
	return;
}

void Box::check() {
	if (num == 0) {
		cout << "������ʷ��Ϣ��" << endl;
		return;
	}
	cout << "������ʷ��������У�";
	for (int i = 0; i < num -1; ++i) {
		cout << talkers[i] << ',';
	}
	cout << talkers[num - 1] << endl;
	cout << "������Ҫ�鿴���������ID��";
	string id;
	getline(cin, id);
	while (id == "") getline(cin, id);
	cout << "*******************************" << endl;
	cout << "          "<<FRONT_GREEN<<" ���촰�� " << endl<<RESET;
	for (int i = 0; i < num; ++i) {
		if (talkers[i] == id) {
			for (int j = 0; j < messages_num; ++j) {
				if (messages[j].sender == id) {
					cout << FRONT_DARKGREEN << setw(20) << messages[j].time << RESET << endl;
					cout << id << endl;
					cout << REVERSE << messages[j].content << RESET << endl;
				}
				else if (messages[j].receiver == id) {
					cout << FRONT_DARKGREEN << setw(20) << messages[j].time << RESET << endl;
					cout << setw(30) << "��" << endl;
					for (int i = 0; i < 30 - messages[j].content.length(); ++i) cout << ' ';
					cout << REVERSE << messages[j].content << RESET << endl;
				}
			}
			cout << "*******************************" << endl;
			return;
		}
	}
	cout << "������ʷ��Ϣ��" << endl;
	return;
}

void Box::search() {
	cout << "��������ҵĹؼ��֣�";
	string input;
	int flag = 0;
	getline(cin, input);
	while (input == "") getline(cin, input);
	for (int j = 0; j < messages_num; ++j) {
		if (messages[j].content.find(input) != -1) {
			if (flag == 0) cout << "*******************************************" << endl;
			flag = 1;
			if (messages[j].sender == owner->getid()) {
				cout <<REVERSE << FRONT_GREEN<< "����" << messages[j].receiver << ":" <<RESET <<REVERSE<< messages[j].content<<RESET 
					<<'('<< messages[j].time << ')' << endl;
			}
			else {
				cout << REVERSE << FRONT_RED << "����" << messages[j].receiver << ":" << RESET << REVERSE << messages[j].content << RESET
					<< '(' << messages[j].time << ')' << endl;
			}
		}
	}
	if(flag == 0) cout << "������ʷ��Ϣ��" << endl;
	else cout << "*******************************************" << endl;
	return;
}

void Box::send() {
	cout << "������Ҫ���͵Ķ���ID��";
	string id;
	getline(cin, id);
	while (id == "") getline(cin, id);
	if (id == owner->getid()) {
		cout << "���ܸ��Լ�������Ϣ" << endl;
		return;
	}
	cout << "������Ҫ���͵����ݣ�";
	string input;
	getline(cin, input);
	while (input == "") getline(cin, input);
	time_t rawtime;
	struct tm* info;
	char buffer[80];
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%m-%d %H:%M:%S", info);
	string buffer_s = buffer;
	map<string, Box>::iterator iter = boxes.find(id);
	if (iter != boxes.end()) {
		iter->second.messages[iter->second.messages_num].content = input;
		iter->second.messages[iter->second.messages_num].time = buffer_s;
		iter->second.messages[iter->second.messages_num].sender = owner->getid();
		iter->second.messages[iter->second.messages_num].receiver = id;
		iter->second.messages_num++;
		int flag = 0;
		for (int i = 0; i < iter->second.num; ++i) {
			if (iter->second.talkers[i] == owner->getid()) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			iter->second.talkers[num] = owner->getid();
			iter->second.num++;
		}
		messages[messages_num].content = input;
		messages[messages_num].receiver = id;
		messages[messages_num].sender = owner->getid();
		messages[messages_num].time = buffer_s;
		++messages_num;
		for (int i = 0; i < num; ++i) {
			if (talkers[i] == id) { 
				cout << FRONT_GREEN << "���ͳɹ�" << RESET << endl;
				return; 
			}
		}
		talkers[num] = id;
		num++;
		cout << FRONT_GREEN << "���ͳɹ�" << RESET << endl;
		return;
	}
	cout << FRONT_RED << "�û������ڣ�����ʧ�ܡ�" << RESET << endl;
	return;
}