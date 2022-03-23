#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <string>

using namespace std;

void Register();
bool IsLegal(string name, int max_length, int mode);
bool IsDuplicate(string name,int mode);
string BuildUid(char c);
void BuildCount(string name);

#endif