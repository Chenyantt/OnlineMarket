#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

#include <string>

using namespace std;

//管理员类
class Administrator {
public:
	Administrator();
	void Login();
	void Menu();
private:
	string admin_name;
	string admin_password;
};

void CheckMessage();//查看所有用户相互发送的信息
void SearchMessage();//查找特定用户发送或接收到的信息

#endif