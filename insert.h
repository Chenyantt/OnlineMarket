#ifndef _INSERT_H_
#define _INSERT_H_

#include <string>

using namespace std;

//类SQL函数，实现上架商品或者购买商品
int Insert(string command, int mode, string id);
//上架商品
int Insert_goods(string command, int mode, string id);
//购买商品
int Insert_order(string command, int mode, string id);

#endif