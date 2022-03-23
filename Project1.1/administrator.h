#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

#include <string>

using namespace std;

class Administrator {
public:
	Administrator();
	void Login();
	void Menu();
private:
	string admin_name;
	string admin_password;
};

void CheckMessage();
void SearchMessage();

#endif