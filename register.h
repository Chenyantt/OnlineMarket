#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <string>

using namespace std;

//用户注册
void Register();
//判断用户名等相关信息是否合法 username address mode 1/password mode 2/desciption  mode 3/phone mode 4;
bool IsLegal(string name, int max_length, int mode);
//判断用户名是否重复
bool IsDuplicate(string name,int mode);
//建立账户
string BuildUid(char c);
//随机生成不重复的ID
void BuildCount(string name);

#endif