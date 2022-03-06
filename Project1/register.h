#ifndef _REGISTER_
#define _REGISTER_

#include <string>

using namespace std;

void Register();
bool IsLegal(string name, int max_length, int mode);
bool IsDuplicate(string name,int mode);
string BuildUid(char c,int mode);
void BuildCount(string name);
#endif

