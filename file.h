#ifndef _FILE_H_
#define _FILE_H_

//从文件中读取数据，并存在对应的数组中
void Init();
//初始化用户列表
void InitUsers();
//初始化商品列表
void InitGoods();
//初始化订单列表
void InitOrders();
//初始化购物车列表
void InitTrolley();
//初始化聊天室列表
void InitBox();

//程序结束前，存储数据保存进文件中
void Save();
//存储用户数据
void SaveUsers();
//存储商品数据
void SaveOrders();
//存储订单数据
void SaveGoods();
//存储购物车数据
void SaveTrolley();
//存储聊天室数据
void SaveBox();

#endif