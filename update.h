#ifndef _UPDATE_H_H_
#define _UPDATE_H_H_

#include <string>

using namespace std;

//类SQL函数，更新商品、订单、用户列表
void Update(string command, int mode, string id);
//封禁卖家
void BanSeller(string command, int mode, string id);
//下架商品
void RemoveGoods(string command, int mode, string id);
//购买商品
void BuyGoods(string command, int mode, string id);
//更新商品信息
void UpdateGoods(string command, int mode, string id);
//封禁用户
int BanUser(string command, int mode, string id);

#endif