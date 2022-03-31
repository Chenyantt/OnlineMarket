#ifndef _USER_H_
#define _USER_H_

#include <string>

using namespace std;

//用户类
class User {
public:
	User();
	User(string* id, string* name, string* password, string* phone, string* address, double m,int state);
	static int GetNum(); //获取当前用户总数
	static void ModNum(int n);//更改当前用户总数
	void menu();//用户菜单
	void seller_menu();//卖家菜单
	void buyer_menu(); //买家菜单
	void self_menu();//个人信息中心菜单
	string getid() const;//获取用户ID
	string getname() const; //获取用户名
	string getpassword() const; //获取用户密码
	string getphone() const;//获取用户电话
	string getaddress() const; //获取用户地址
	double getmoney() const;//获取账户余额
	int getstate() const; //获取用户状态
	void check_info() const; //查看用户个人信息
	void mod_info(); //改变余额
	void recharge();//充值
	void ban(); //封禁用户
	void mod_money(double n);//更改个人信息
	void Account();//发布打折优惠
private:
	static int UserNum;
	string user_id;
	string user_name;
	string user_password;
	string user_phone;
	string user_address;
	double money;
	int state;
};

int IsNumberLegal(string s);//判断数字是否合法

#endif