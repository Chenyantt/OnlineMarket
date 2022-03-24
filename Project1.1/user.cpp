#define _CRT_SECURE_NO_WARNINGS
#include "user.h"

#include <iostream>
#include <iomanip>
#include <fstream>

#include "check.h"
#include "register.h"
#include "update.h"
#include "insert.h"
#include "data.h"
#include "calculator.h"
#include "balance.h"
#include "color.h"

using namespace std;

int User::UserNum = 0;

User::User(string* id, string* name, string* password, string* phone, string* address, double m,int s) {
	UserNum++;
	user_id = *id;
	user_name = *name;
	user_password = *password;
	user_address = *address;
	user_phone = *phone;
	money = m;
	state = s;
}

User::User() {
	state = -1;
}

int User::GetNum() {
	return UserNum;
}

void User::ModNum(int n) {
	UserNum = n;
	return;
}

void User::menu() {
	while (true) {
		cout << "===============================================================" <<endl;
		cout << " 1.������� 2.�������� 3.������Ϣ���� 4.������ 5.ע����¼" << endl;
		cout << "===============================================================" << endl;
		cout << "�����룺";
		string input;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout <<"����������:��" << input << "��" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "����������������롣" <<RESET<< endl << endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				buyer_menu();
				break;
			case '2':
				seller_menu();
				break;
			case '3':
				self_menu();
				break;
			case '4':
				boxes[user_id].menu();
				break;
			case '5':
				system("cls");
				cout << FRONT_RED << "--- �˳���¼ ---" << RESET << endl;
				return;
			default:
				cout << FRONT_RED << "����������������롣" <<RESET<< endl << endl;
				break;
			}
		}
	}
	return;
}

string User::getid() const {
	return user_id;
}

string User::getname() const {
	return user_name;
}

string User::getpassword() const {
	return user_password;
}

string User::getphone() const {
	return user_phone;
}

string User::getaddress() const {
	return user_address;
}

double User::getmoney() const {
	return money;
}

int User::getstate() const {
	return state;
}

void User::check_info() const {
	cout << "***************************" << endl;
	cout << "�û�����" << user_name << endl;
	cout << "��ϵ��ʽ��" << user_phone << endl;
	cout << "��ַ��" << user_address << endl;
	cout << "**************************" << endl ;
	return;
}

void User::seller_menu() {
	system("cls");
	while (true) {
		cout << "======================================================================================" << endl;
		cout << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.���ص�¼������" << endl;
		cout << "======================================================================================" << endl;
		cout << "�����룺";
		string input,attribute,value,id,name,des,number;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout <<"����������:��" << input << "��" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "����������������롣" <<RESET<< endl << endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				cout << "��������Ʒ���ƣ�";
				getline(cin, name);
				while (name == "") getline(cin, name);
				cout <<"��������Ʒ�۸�";
				getline(cin, value);
				while (value == "") getline(cin, value);
				cout <<"��������Ʒ������";
				getline(cin, number);
				while (number == "") getline(cin, number);
				cout <<"��������Ʒ������";
				getline(cin,des);
				while (des == "") getline(cin, des);
				Insert("INSERT INTO commodity VALUES(" + name + "," + value + "," + number + "," + des + ")", 1, user_id);
				break;
			case '2':
				Check("SELECT * FROM commodity", 2, user_id);
				break;
			case '3':
				cout << "�����뱻�޸ĵ���ƷID��";
				getline(cin, id);
				while (id == "") getline(cin, id);
				back:
				cout <<"�����뱻�޸ĵ���Ʒ���ԣ�1.�۸�  2.��������";
				getline(cin, attribute);
				while (attribute == "") getline(cin, attribute);
				if (attribute.length() != 1) {
					cout << FRONT_RED <<"����������������롣" <<RESET<< endl;
					goto back;
				}
				else if (attribute == "1") {
					back2:
					cout <<"�����뱻�޸ĵ���Ʒ�۸�";
					getline(cin, value);
					while (value == "") getline(cin, value);
					attribute = "price";
						if (!IsNumberLegal(value)) {
							cout << FRONT_RED <<"�������, ���������롣" <<RESET<< endl;
							goto back2;
						}
				}
				else if (attribute == "2"){
					back1:
					cout <<"�����뱻�޸ĵ���Ʒ������";
					getline(cin, value);
					while (value == "") getline(cin, value);
					attribute = "description";
					if (IsLegal(value, 200, 3));
					else {
						cout << FRONT_RED <<"�������, ���������롣" <<RESET<< endl;
						goto back1;
					}
				}
				else {
					cout << FRONT_RED << "�������, ���������롣" << RESET << endl;
					goto back;
				}
				Update("UPDATE commodity SET "+attribute+" = "+value+" WHERE goods_id = " + id, 2, user_id);
				break;
			case '4':
				cout << "������Ҫ�¼ܵ���ƷID��";
				getline(cin,id);
				while (id == "") getline(cin, id);
				Update("UPDATE commodity SET state = remove WHERE goods_id = " + id, 2, user_id);
				break;
			case '5':
				Check("SELECT * FROM order", 2, user_id);
				break;
			case '6':
				system("cls");
				cout << FRONT_RED<<"--- ���������� ---"<<RESET << endl;
				return;
			default:
				cout << FRONT_RED << "�������, ���������롣" << RESET << endl<< endl;
				break;
			}
			cout << endl;
		}
	}
	return;
}

void User::buyer_menu() {
	system("cls");
	while (true) {
		cout << "======================================================================================================================" << endl;
		cout << "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.���빺�ﳵ 7. �鿴���ﳵ 8.���ص�¼������" << endl;
		cout << "======================================================================================================================" << endl;
		cout << "�����룺";
		string input,goods_name,number;
		int n,j;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout <<"����������:��" << input << "��" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "�������, ���������롣" << RESET << endl << endl;
		}
		else {
			char flag = input[0];
			switch (flag)
			{
			case '1':
				Check("SELECT * FROM commodity", 3, user_id);
				break;
			case '2':
				cout << "��������ƷID��";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				cout <<"��������Ʒ������";
				getline(cin, number);
				while (number == "") getline(cin, number);
				n=Insert("INSERT INTO order VALUES(" + goods_name + "," + number + ")",2,user_id);
				if (n != -1) Update("UPDATE commodity SET number = " + to_string(n) + " WHERE goods_id = " + goods_name, 2, user_id);
				break;
			case '3':
				cout << "��������Ʒ���ƣ�";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				Check("SELECT * FROM commodity WHERE name CONTAINS " + goods_name, 3, user_id);
				break;
			case '4':
				Check("SELECT * FROM order", 3, user_id);
				break;
			case '5':
				cout << "��������ƷID��";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				Check("SELECT * FROM commodity WHERE goods_id CONTAINS " + goods_name, 3, user_id);
				break;
			case '6':
				cout << "��������ƷID��";
				getline(cin, goods_name);
				while (goods_name == "") getline(cin, goods_name);
				for (j = 0; goods[j].getstate() != -1; ++j) {
					if (goods[j].getid() == goods_name) break;
				}
				if (goods[j].getstate() == -1 || goods[j].getstate() == 0) {
					cout << FRONT_RED << "δ��ѯ������ƷID!!!" << RESET << endl;
					
				}
				else {
					cout << "��������Ʒ������";
					getline(cin, number);
					while (number == "") getline(cin, number);
					if (!IsLegal(number, 10, 4) || !IsNumberLegal(number)) {
						cout << FRONT_RED << "������Ʒ�������󣡣�" << RESET << endl;
					}
					else {
						trolleys[user_id].add(goods_name,goods[j].getname(),goods[j].gettime(),goods[j].getseller(), goods[j].getprice(), stoi(number));
						cout << FRONT_GREEN << "����ɹ�" << RESET << endl;
					}
				}
				break;
			case '7':
				trolleys[user_id].check();
				break;
			case '8':
				system("cls");
				cout << FRONT_RED<<"--- ���������� ---" <<RESET<< endl;
				return;
			default:
				cout << FRONT_RED << "�������, ���������롣" << RESET << endl << endl;
				break;
			}
			cout << endl;
		}
	}
	return;
}

void User::self_menu() {
	system("cls");
	while (true) {
		cout << "==========================================================================" << endl;
		cout << "1.�鿴��Ϣ 2.�޸���Ϣ 3.��ֵ 4.�鿴��� 5.���������� 6.�����û�������" << endl;
		cout << "==========================================================================" << endl;
		cout << "�����룺";
		string input;
		getline(cin, input);
		while (input == "") getline(cin, input);
		cout <<"����������:��" << input << "��" << endl;
		if (input.length() != 1) {
			cout << FRONT_RED << "�������, ���������롣" << RESET << endl << endl;
		}
		else {
			string str,output;
			char flag = input[0];
			switch (flag)
			{
			case '1':
				check_info();
				break;
			case '2':
				mod_info();
				break;
			case '3':
				recharge();
				break;
			case '4':
				cout<<"��������ǣ�"<<fixed<<setprecision(1)<<money<<endl;
				break;
			case '5':
				system("cls");
				cout << "��������ʽ��";
				getline(cin, str);
				while (str=="") getline(cin, str);
				output = Calculator(str);
				if ((output[0] < '0' || output[0]>'9') && output[0] != '-')
					cout  << FRONT_RED <<output << RESET << endl;
				else cout <<"����Ľ��Ϊ��" << output << endl;
				break;
			case '6':
				system("cls");
				cout << FRONT_RED << "--- ���������� ---" <<RESET<< endl;
				return;
			default:
				cout << FRONT_RED << "�������, ���������롣" << RESET << endl << endl;
				break;
			}
			cout << endl;
		}
	}
	return;
}

void User::ban() {
	state = 0;
	return;
}

void User::mod_money(double n) {
	money -= n;
	return;
}

void User::mod_info() {
	string input, name, phone, address, password1,password2;
back:
	cout << "��ѡ����Ҫ�޸ĵ����ԣ���1.�û���  2.�绰  3.��ַ 4. ���룩��";
	getline(cin, input);
	while (input == "") getline(cin, input);
	if (input.length() != 1) {
		cout << FRONT_RED << "�������, ���������롣" << RESET << endl;
		goto back;
	}
	else {
		char flag = input[0];
		switch (flag)
		{
		case '1':
			back1:
			cout << "��ѡ���޸ĺ���û�����";
			getline(cin, name);
			while (name == "") getline(cin, name);
			if (getname() == name) {
				cout <<FRONT_RED<< "���û�����������û�����ͬ��" <<RESET<< endl;
				goto back1;
			}
			if(IsLegal(name, 10, 1) ){
				if (!IsDuplicate(name, 1)) {
					cout <<FRONT_RED<< "�û����ظ������������롣" <<RESET<< endl;
					goto back1;
				}
				else {
					user_name = name;
					cout << FRONT_GREEN << "----�޸ĳɹ�----" << RESET << endl;
				}
			}
			else {
				cout << FRONT_RED << "�û����������ߺ��зǷ��ַ������������롣" <<RESET<< endl;
				goto back1;
			}
			break;
		case '2':
			back2:
			cout << "��ѡ���޸ĺ�ĵ绰��";
			getline(cin, phone);
			while (phone == "") getline(cin, phone);
			if (IsLegal(phone, 20, 4)) {
				user_phone = phone;
				cout << FRONT_GREEN << "----�޸ĳɹ�----" << RESET << endl;
			}
			else {
				cout <<FRONT_RED << "�绰����������ߺ��зǷ��ַ������������롣" <<RESET<< endl;
				goto back2;
			}
			break;
		case '3':
			back3:
			cout <<"��ѡ���޸ĺ�ĵ�ַ��";
			getline(cin,address);
			while (address == "") getline(cin, address);
			if (IsLegal(address, 40, 1)) {
				user_address = address;
				cout << FRONT_GREEN << "----�޸ĳɹ�----" << RESET << endl;
			}
			else {
			cout << FRONT_RED << "��ַ�������ߺ��зǷ��ַ������������롣" <<RESET<< endl;
			goto back3;
			}
			break;
		case '4':
		back4:
			cout << "����д�޸ĺ�����룺";
			getline(cin, password1);
			while (password1 == "") getline(cin, password1);
			if (IsLegal(password1, 20, 2)) {
				cout << "���ٴ������޸ĺ�����룺";
				getline(cin, password2);
				while (password2 == "") getline(cin, password2);
				if (password1 == password2) {
					user_password = password1;
					cout << FRONT_GREEN << "----�޸ĳɹ�----" << RESET << endl;
				}
				else {
					cout << FRONT_RED << "������������벻һ�£����������롣" << RESET << endl;
					goto back4;
				}
			}
			else {
				cout << FRONT_RED << "����������ߺ��зǷ��ַ������������롣" << RESET << endl;
				goto back4;
			}
			break;
		default:
			cout << FRONT_RED << "����������������롣" <<RESET<< endl;
			goto back;
			break;
		}
	}
	return;
}

void User::recharge() {
	back:
	cout << "�������ֵ��С������������һλС������";
	string m;
	getline(cin, m);
	while (m == "") getline(cin, m);
	if (!IsNumberLegal(m)) {
		cout << FRONT_RED <<"�������, ���������롣" <<RESET<< endl;
		goto back;
	}
	else {
		ofstream ofile;
		ofile.open("recharge.txt", ios::app);
		ofile << '\n' << user_id << ',' << m;
		ofile.close();
		money += stod(m);
		cout << FRONT_GREEN << "---��ֵ�ɹ�---" << RESET << endl;
	}
	return;
}

int IsNumberLegal(string s) {
	if ((s[0]== '0'&& s[1]!= '.') || s[0] == '.' || s[s.length() - 1] == '.') return 0;
	if (s.find('.') != -1 && s.length() > s.find('.') + 2) {
		return 0;
	}
	int cnt = 0;
	for (int i = 0; i<(int)s.length(); ++i) {
		if (s[i] == '.' ) {
			cnt++;
		}
		else if (s[i]<'0' || s[i]>'9') {
			return 0;
		}
	}
	if (cnt >= 2) return 0;
	return 1;
}