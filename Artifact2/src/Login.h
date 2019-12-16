/*
 * Login.h
 *
 *  Created on: Nov 5, 2017
 *      Author: Curtis
 */

#ifndef LOGIN_H_
#define LOGIN_H_

#include <cstring>
#include<iostream>
#include<fstream>
#include <cstdlib>
#include<conio.h>

using namespace std;

class Login {
	Login(int, int);
private:
	char Password[12];
	char name[20];
	char a[13]; // 12 to 13 to correct buffer overflow - KG
	char b[13]; // 12 to 13 to correct buffer overflow - KG
	char c[26];
	char *arg1[28];
	int i = 0;
	char buff[20];
	bool PwStatus[false];
	char passwordCheck[12];

public:
	Login();
	virtual ~Login();

	void enterPassword(void);
	void copyUsername(string str1, string str2);
	int copyPassword();
	int testUsernamePassword(void);
	void isPasswordOK(void);
};

#endif /* LOGIN_H_ */
