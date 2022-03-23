#ifndef _BOX_H_
#define _BOX_H_

#include <string>

#include "user.h"

using namespace std;

class Box;

class Message
{
public:
	friend void BuildCount(string name);
	friend void InitUsers();
	friend void InitBox();
	friend void SaveBox();
	friend void CheckMessage();
	friend void SearchMessage();
	friend Box;
	Message();
private:
	string time;
	string sender;
	string receiver;
	string content;
};

class Box
{
public:
	friend void BuildCount(string name);
	friend void InitUsers();
	friend void InitBox();
	friend void SaveBox();
	friend void CheckMessage();
	friend void SearchMessage();
	Box();
	void menu();
	void check();
	void search();
	void send();
private:
	User* owner;
	int num;
	int messages_num;
	Message messages[20];
	string talkers[5];
};

#endif 

