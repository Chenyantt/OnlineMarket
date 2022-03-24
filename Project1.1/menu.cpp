#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"

#include <iostream>
#include <string>

#include "color.h"

using namespace std;

void Welcome() {
	cout << FRONT_YELLOW << "*******************************************************************************************************" << endl;
	cout << FRONT_RED << "*******************************************************************************************************" << endl;
	cout << FRONT_GREEN << "*******************************************************************************************************" << endl;
	cout << FRONT_WHITE << "*******************************************************************************************************" << endl;
	cout << "*******************************************************************************************************" << endl;
	cout <<"**\x1B[36m*  *\x1B[0m***\x1B[36m*   *\x1B[0m***\x1B[36m*  *\x1B[0m**\x1B[36m*        *\x1B[0m*\x1B[36m*  *\x1B[0m*******\x1B[36m*        *\x1B[0m*\x1B[36m*          *\x1B[0m*****\x1B[36m* *\x1B[0m*****\x1B[36m* *\x1B[0m*****\x1B[36m*        *\x1B[0m****" << endl;
	cout << "***\x1B[36m*  *\x1B[0m*\x1B[36m*  *  *\x1B[0m*\x1B[36m*  *\x1B[0m***\x1B[36m* *******\x1B[0m**\x1B[36m*  *\x1B[0m*******\x1B[36m*  *\x1B[0m*******\x1B[36m*  *****\x1B[36m*  *\x1B[0m****\x1B[36m* * *\x1B[0m***\x1B[36m* * *\x1B[0m****\x1B[36m*  ******\x1B[0m*****" << endl;
	cout << "****\x1B[36m*  *  *\x1B[0m*\x1B[36m*  *  *\x1B[0m****\x1B[36m*        *\x1B[0m*\x1B[36m*  *\x1B[0m*******\x1B[36m*  *\x1B[0m*******\x1B[36m*  *\x1B[0m****\x1B[36m*  *\x1B[0m***\x1B[36m*  *  *\x1B[0m*\x1B[36m*  *  *\x1B[0m***\x1B[36m*        *\x1B[0m****" << endl;
	cout << "*****\x1B[36m* * *\x1B[0m***\x1B[36m* * *\x1B[0m*****\x1B[36m* *******\x1B[0m**\x1B[36m*  *******\x1B[0m*\x1B[36m*  *\x1B[0m*******\x1B[36m*  *****\x1B[36m*  *\x1B[0m**\x1B[36m*  *\x1B[0m*\x1B[36m*  *  *\x1B[0m*\x1B[36m*  *\x1B[0m**\x1B[36m*  ******\x1B[0m*****" << endl;
	cout << "******\x1B[36m* *\x1B[0m*****\x1B[36m* *\x1B[0m******\x1B[36m*        *\x1B[0m*\x1B[36m*        *\x1B[0m*\x1B[36m*        *\x1B[0m*\x1B[36m*          *\x1B[0m*\x1B[36m*  *\x1B[0m***\x1B[36m*   *\x1B[0m***\x1B[36m*  *\x1B[0m*\x1B[36m*        *\x1B[0m****" << endl;
	cout  << "*******************************************************************************************************" << endl;
	cout << FRONT_YELLOW << "*******************************************************************************************************" << endl;
	cout << "*******************************************************************************************************" << endl;
	cout << FRONT_RED << "***********************" << FRONT_WHITE << "***** ============================================ *****"<< FRONT_RED << "************************" << endl;
	cout << FRONT_RED << "************************" << FRONT_WHITE << "***** ||  \x1B[36m  " << REVERSE << "��ӭ�����������¼���Ʒ����ƽ̨ \x1B[0m" << RESET << "   || *****" << FRONT_RED << "*************************" << endl;
	cout << FRONT_GREEN << "*************************" << FRONT_WHITE << "*** ============================================ ***" << FRONT_GREEN << "**************************" << endl;
	cout << FRONT_GREEN << "**************************" << FRONT_WHITE << "*************************************************" << FRONT_GREEN << "****************************" << endl;
	cout << FRONT_DARKGREEN << "*********************************" << FRONT_WHITE << "***********************************" << FRONT_DARKGREEN << "***********************************" << endl;
	cout << FRONT_DARKGREEN << "**********************************" << FRONT_WHITE << "*********************************" << FRONT_DARKGREEN << "************************************" << endl;
	cout << FRONT_BLUE << "***********************************" << FRONT_WHITE << "*****"<< FRONT_GREEN<<"    "<<REVERSE<<"�밴���������"<< RESET <<"    ****" << FRONT_BLUE << "*************************************" << endl;
	cout << FRONT_BLUE << "************************************" << FRONT_WHITE << "****************************" << FRONT_BLUE << "***************************************" << endl;
	cout << FRONT_PURPLR << "*******************************************************************************************************" << endl;
	cout << FRONT_PURPLR << "*******************************************************************************************************" << FRONT_WHITE << endl;
	system("pause");
	system("cls");
	return;
}

string Menu() {
	cout << "==========================================================================" << endl;
	cout << "                      " << REVERSE << "��ӭ�����������»����Ʒ����ƽ̨" << RESET << "   " << endl;
	cout << "==========================================================================" << endl << endl;
	cout << "---------->   1.����Ա��¼ 2.�û�ע�� 3.�û���¼ 4.�˳�ϵͳ   <----------" << endl;
	cout << endl;
	cout << "�����룺";
	string output;
	getline(cin, output);
	cout << "\x1B[0m";
	while (output == "") getline(cin, output);
	cout << "����������:��" << output << "��" << endl;
	return output;
}

void Goodbye() {
	system("cls");
	cout << "\x1B[36m";
	cout << FRONT_YELLOW <<"  d888b   " <<FRONT_RED <<"  .d88b.     " << FRONT_GREEN << "  .d88b.     " << FRONT_DARKGREEN << " d8888b.    " << FRONT_BLUE << " d8888b.  " << FRONT_PURPLR << "db     db " << FRONT_WHITE << " d88888b " << endl;
	cout << FRONT_YELLOW << " 88'  Y8b " << FRONT_RED << " .8P    Y8. " << FRONT_GREEN << " .8P    Y8.  " << FRONT_DARKGREEN << " 88    `8D  " << FRONT_BLUE << " 88   `8D " << FRONT_PURPLR << " `8b   d8' " << FRONT_WHITE << "88'" << endl;
	cout << FRONT_YELLOW << "88        " << FRONT_RED << " 88     88  " << FRONT_GREEN << " 88     88 " << FRONT_DARKGREEN << "  88      88  " << FRONT_BLUE << "888oooY'   " << FRONT_PURPLR << " `8bd8'  " << FRONT_WHITE << "88ooooo" << endl;
	cout << FRONT_YELLOW << "88   ooo  " << FRONT_RED << " 88     88 " << FRONT_GREEN << " 88     88  " << FRONT_DARKGREEN << " 88      88  " << FRONT_BLUE << "888~~~b.   " << FRONT_PURPLR << "   88    " << FRONT_WHITE << "88~~~~~" << endl;
	cout << FRONT_YELLOW << "88.  ~8~ " << FRONT_RED << " `8b    d8' " << FRONT_GREEN << " `8b   d8' " << FRONT_DARKGREEN << "  88    .8D  " << FRONT_BLUE << "88     8D   " << FRONT_PURPLR << " 88    " << FRONT_WHITE << " 88." << endl;
	cout << FRONT_YELLOW << " Y888P    " << FRONT_RED << " `Y88P'   " << FRONT_GREEN << "  `Y88P'   " << FRONT_DARKGREEN << "  Y8888D'     " << FRONT_BLUE << "Y8888P'    " << FRONT_PURPLR << " YP    " << FRONT_WHITE << " Y88888P" <<"\x1B[0m" << endl;
	cout << FRONT_YELLOW << endl <<"                             " << REVERSE << "ллʹ��,�ټ�" << RESET << endl;
	getchar();
}