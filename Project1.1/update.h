#ifndef _UPDATE_
#define _UPDATE_

#include <string>

using namespace std;

void Update(string command, int mode, string id);
void BanSeller(string command, int mode, string id);
void RemoveGoods(string command, int mode, string id);
void BuyGoods(string command, int mode, string id);
void UpdateGoods(string command, int mode, string id);
int BanUser(string command, int mode, string id);

#endif

