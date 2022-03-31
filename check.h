#ifndef _CHECK_H_
#define _CHECK_H_

#include <string>

using namespace std;

//类SQL函数，查看商品、用户、订单列表
void Check(string command, int mode, string name);
//查看用户，并展示其列表
void CheckUser(string command, int mode, string name);
//查看或搜索部分商品，并展示其列表
void CheckOrder(string command, int mode, string name);
//查看订单，并展示其列表
void CheckGoods(string command, int mode, string name);

#endif 