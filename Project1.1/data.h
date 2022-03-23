#ifndef _DATA_H_
#define _DATA_H_

#include <map>

#include "user.h"
#include "administrator.h"
#include "goods.h"
#include "order.h"
#include "trolley.h"
#include "box.h"

using namespace std;

extern Administrator admin;
extern User users[50];
extern Goods goods[50];
extern Order orders[50];
extern map<string, Trolley> trolleys;
extern map<string, Box> boxes;
#endif