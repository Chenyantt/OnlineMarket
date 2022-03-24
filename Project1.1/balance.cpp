#include "balance.h"

#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>

#include "calculator.h"
#include "data.h"

using namespace std;

string Balance(string user_id) {
	ifstream ifile;
	ifile.open("recharge.txt", ios::in);
	if (!ifile) {
		cout << "Open File Error." << endl;
		exit(-1);
	}
	char input_c[300];
	string input[300];
	int index = 0;
	ifile.getline(input_c, 300);
	while(ifile.getline(input_c, 300)) {
		string input_s = input_c;
		if (input_s.substr(0, input_s.find(',')) == user_id) {
			input[index] = "+"+input_s.substr(input_s.find(',') + 1);
			index++;
		}
	}
	ifile.close();
	map<int, string> datas;
	for (int i = 0; orders[i].getnumber() != -1;++i) {
		if(orders[i].getseller()==user_id){
			if (datas.find(orders[i].getnumber()) == datas.end()) {
				stringstream ss;
				ss << fixed << setprecision(1) << orders[i].getprice();
				datas.insert(pair<int, string>(orders[i].getnumber(), ss.str()));
			}
			else {
				stringstream ss;
				ss << fixed << setprecision(1) << orders[i].getprice();
				datas[orders[i].getnumber()] += "+" + ss.str();
			}
		}
		else if (orders[i].getbuyer() == user_id) {
			if (datas.find(orders[i].getnumber()) == datas.end()) {
				stringstream ss;
				ss << fixed << setprecision(1) << orders[i].getprice();
				datas.insert(pair<int, string>(orders[i].getnumber(), "-"+ss.str()));
			}
			else {
				stringstream ss;
				ss << fixed << setprecision(1) << orders[i].getprice();
				datas[orders[i].getnumber()] += "-" + ss.str();
			}
		}
	}
	string expression = "";
	for (int i = 0; input[i] != ""; ++i) expression += input[i];
	
	for (map<int,string>::iterator it = datas.begin(); it != datas.end(); it++) { 
		expression += "+" + to_string(it->first) + "*(" + it->second + ")";
	}
	if (expression[0] == '+') expression = expression.substr(1);
	return Calculator(expression);
}