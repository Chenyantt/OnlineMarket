#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <string>
#include <stack>
#include <vector>

using namespace std;

//计算器
string Calculator(string equation);
//判断表达式是否含有非法字符
int isLegal(string equation);
//判断表达式圆括号是否匹配
int BracketMatch(string equation);
//判断数字内部是否存在非法空格
int isBlankLegal(string &equation);
//将字符串转化为<vector>数组
void Operand(string equation,vector<string> &vec);
//判断是否有相邻的两个不合法的操作符
int isOperatorNext(vector<string> vec);
//判断是否存在不合法的单目+，*，/操作符
int isAddLegal(vector<string> vec);
//判断数字格式是否合法
int isNumberLegal(vector<string> vec);
//将负数转化为0-N的形式
void NegativeDeal(vector<string> &vec);
//生成逆波兰表达式
vector<string> ReverseNotation(vector<string> vec);
//计算逆波兰表达式的值
vector<string> Eval(vector<string> &vec);
//将<vector>数组转化为字符串，并四舍五入保留一位小数
string vec_to_str(vector<string> vec);

#endif 