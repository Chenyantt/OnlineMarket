#ifndef _ADMINISTRATOR_
#define _ADMINISTRATOR_

#include <string>

using namespace std;

class Administrator {
public:
	Administrator();
	void Menu();
	void Login();
private:
	string admin_name;
	string admin_password;
};

#endif

