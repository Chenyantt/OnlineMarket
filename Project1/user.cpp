#define _CRT_SECURE_NO_WARNINGS
#include "user.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#include "check.h"
#include "register.h"
#include "update.h"
#include "insert.h"

using namespace std;

User::User(string* id, string* name, string* password, string* phone, string* address) :state(0), money(0) {
	user_id = *id;
	user_name = *name;
	user_password = *password;
	user_address = *address;
	user_phone = *phone;
	ofstream ofile;
	ofile.open("user.txt", ios::app);
	ofile <<'\n' << user_id << ',' << *name << ',' << *password << ',' << *phone <<',' << *address<<',' <<setprecision(1)<<fixed<< money<<',' << "active";
	ofile.close();
}

User::User(string* id, string* name, string* password, string* phone, string* address, double m,int s) {
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

void User::menu() {
	while (true) {
		printf("=============================================\n");
		printf(" 1.������� 2.�������� 3.������Ϣ���� 4.ע����¼\n");
		printf("=============================================\n");
		printf("�����룺");
		string input;
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
			case '4':
				system("cls");
				cout << "--- �˳���¼ ---" << endl;
				return;
			case '1':
				buyer_menu();
				break;
			case '2':
				seller_menu();
				break;
			case '3':
				self_menu();
				break;
			default:
				system("cls");
				cout << "����������������롣" << endl << endl;
				break;
			}
		}
	}
	return;
}

string User::getid() {
	return user_id;
}

string User::getname() {
	return user_name;
}

string User::getpassword() {
	return user_password;
}

string User::getphone() {
	return user_phone;
}

string User::getaddress() {
	return user_address;
}

double User::getmoney() {
	return money;
}

int User::getstate() {
	return state;
}

void User::ban() {
	state = 0;
	return;
}

void User::seller_menu() {
	while (true) {
		printf("==============================================================================\n");
		printf("1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.���ص�¼������\n");
		printf("==============================================================================\n");
		printf("�����룺");
		string input,attribute,value,id,name,des,number;
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
			case '6':
				system("cls");
				cout << "--- ���������� ---" << endl;
				return;
			case '1':
				cout << "��������Ʒ���ƣ�";
				cin >> name;
				cout << endl << "��������Ʒ�۸�";
				cin >> value;
				cout << endl << "��������Ʒ������";
				cin >> number;
				cout << endl << "��������Ʒ������";
				getchar();
				getline(cin,des);
				cout << endl;
				Insert("INSERT INTO commodity VALUES(" + name + "," + value + "," + number + "," + des + ")", 1, user_id);
				break;
			case '2':
				Check("SELECT * FROM commodity", 2, user_id);
				break;
			case '3':
				cout << "�����뱻�޸ĵ���ƷID��";
				cin >> id;
				back:
				cout << endl<<"�����뱻�޸ĵ���Ʒ���ԣ�1.�۸�  2.��������";
				cin >> attribute;
				if (attribute.length() != 1) {
					cout <<endl<< "����������������롣" << endl;
					goto back;
				}
				else if (attribute == "1") {
					back2:
					cout << endl << "�����뱻�޸ĵ���Ʒ�۸�";
					cin >> value;
					attribute = "price";
						int index = value.find('.');
						int length = int(value.length());
						if ((index == -1 && !IsLegal(value, 10, 4)) || (index != -1 && length > index + 2) || index == 0) {
							cout << endl << "�������, ���������롣" << endl;
							goto back2;
						}
				}
				else if (attribute == "2"){
					back1:
					cout << endl << "�����뱻�޸ĵ���Ʒ������";
					getchar();
					getline(cin, value);
					attribute = "description";
					if (IsLegal(value, 200, 3));
					else {
						cout << endl << "�������, ���������롣" << endl;
						goto back1;
					}
				}
				else {
					cout << endl << "����������������롣" << endl;
					goto back;
				}
				Update("UPDATE commodity SET "+attribute+" = "+value+" WHERE goods_id = " + id, 2, user_id);
				break;
			case '4':
				cout << "������Ҫ�¼ܵ���ƷID��";
				cin >> id;
				cout << endl;
				Update("UPDATE commodity SET state = remove WHERE goods_id = " + id, 2, user_id);
				break;
			case '5':
				Check("SELECT * FROM order", 2, user_id);
				break;
			default:
				system("cls");
				cout << "����������������롣" << endl << endl;
				break;
			}
		}
	}
	return;
}

void User::buyer_menu() {
	while (true) {
		printf("==================================================================================\n");
		printf("1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.���ص�¼������\n");
		printf("==================================================================================\n");
		printf("�����룺");
		string input,goods_name,number;
		int n;
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
			case '6':
				system("cls");
				cout << "--- ���������� ---" << endl;
				return;
			case '1':
				Check("SELECT * FROM commodity", 3, user_id);
				break;
			case '2':
				cout << "��������ƷID��";
				cin >> goods_name;
				cout << endl << "��������Ʒ������";
				cin >> number;
				cout << endl;
				n=Insert("INSERT INTO order VALUES(" + goods_name + "," + number,2,user_id);
				if (n != -1) Update("UPDATE commodity SET number = " + to_string(n) + " WHERE goods_id = " + goods_name, 2, user_id);
				break;
			case '3':
				cout << "��������Ʒ���ƣ�";
				cin >> goods_name;
				cout << endl;
				Check("SELECT * FROM commodity WHERE name CONTAINS " + goods_name, 3, user_id);
				break;
			case '4':
				Check("SELECT * FROM order", 3, user_id);
				break;
			case '5':
				cout << "��������ƷID��";
				cin >> goods_name;
				cout << endl;
				Check("SELECT * FROM commodity WHERE goods_id CONTAINS " + goods_name, 3, user_id);
				break;
			default:
				system("cls");
				cout << "����������������롣" << endl << endl;
				break;
			}
		}
	}
	return;
}

void User::self_menu() {
	while (true) {
		printf("=============================================\n");
		printf("1.�鿴��Ϣ 2.�޸���Ϣ 3.��ֵ 4.�����û�������\n");
		printf("=============================================\n");
		printf("�����룺");
		string input;
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
			case '4':
				system("cls");
				cout << "--- ���������� ---" << endl;
				return;
			case '1':
				check_info();
				break;
			case '2':
				mod_info();
				break;
			case '3':
				recharge();
				break;
			default:
				system("cls");
				cout << "����������������롣" << endl << endl;
				break;
			}
		}
	}
	return;
}

void User::check_info() {
	cout << "***************************"<< endl;
	cout << "�û�����" << user_name << endl;
	cout << "��ϵ��ʽ��" << user_phone << endl;
	cout << "��ַ��" << user_address << endl;
	cout << "Ǯ����" << money << endl;
	cout << "**************************" << endl<<endl<<endl;
	return;
}

void User::mod_money(double n) {
	money -= n;
	return;
}

void User::mod_info() {
	string input,name,phone,address;
back:
	cout << "��ѡ����Ҫ�޸ĵ����ԣ���1.�û���  2.�绰  3.��ַ����";
	cin >> input;
	if (input.length() != 1) {
		system("cls");
		cout << "����������������롣" << endl;
		goto back;
	}
	else {
		char flag = input[0];
		switch (flag)
		{
		case '1':
			back1:
			cout <<endl<< "��ѡ���޸ĺ���û�����";
			cin >> name;
			if(IsLegal(name, 10, 1) ){
				if (!IsDuplicate(name, 1)) {
					cout <<endl<< "�û����ظ������������롣" << endl;
					goto back1;
				}
				else {
					user_name = name;
					cout << "----�޸ĳɹ�----" << endl;
				}
			}
			else {
				cout << "�û����������ߺ��зǷ��ַ������������롣" << endl;
				goto back1;
			}
			break;
		case '2':
			back2:
			cout <<endl<< "��ѡ���޸ĺ�ĵ绰��";
			cin >> phone;
			if (IsLegal(phone, 20, 4)) {
				user_phone = phone;
				cout << "----�޸ĳɹ�----" << endl;
			}
			else {
				cout <<endl<< "�绰����������ߺ��зǷ��ַ������������롣" << endl;
				goto back2;
			}
			break;
		case '3':
			back3:
			cout <<endl<< "��ѡ���޸ĺ�ĵ�ַ��";
			getchar();
			getline(cin,address);
			if (IsLegal(address, 40, 3)) {
				user_address = address;
				cout << "----�޸ĳɹ�----" << endl;
			}
			else {
			cout <<endl<< "��ַ�������ߺ��зǷ��ַ������������롣" << endl;
			goto back3;
			}
			break;
		default:
			system("cls");
			cout << "����������������롣" << endl;
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
	cin >> m;
	int index = m.find('.');
	int length = int(m.length());
	if ((index == -1 && !IsLegal(m, 10, 4)) || (index != -1 && length > index + 2) || index == 0) {
		cout <<endl<<"�������, ���������롣" << endl;
		goto back;
	}
	else {
		money += stod(m);
		cout << endl << "---��ֵ�ɹ�---" << endl;
	}
	return;
}