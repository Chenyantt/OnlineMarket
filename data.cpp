#include "data.h"

using namespace std;

//数据层，包括管理员，用户列表，商品列表，订单列表，购物车列表，聊天室列表
Administrator admin;
User users[50];
Goods goods[50];
Order orders[50];
map<string, Trolley> trolleys;
map<string, Box> boxes;