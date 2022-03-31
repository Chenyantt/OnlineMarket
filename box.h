#ifndef _BOX_H_
#define _BOX_H_

#include <string>

#include "user.h"

using namespace std;

class Box;

//消息类
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

//聊天室类
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
	//聊天室菜单
	void menu();
	//查看与好友的历史聊天消息
	void check();
	//用关键词搜索聊天记录
	void search();
	//向好友发送消息
	void send();
private:
	User* owner;
	int num;
	int messages_num;
	Message messages[20];
	string talkers[5];
};

#endif 

