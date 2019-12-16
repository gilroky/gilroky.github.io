/*
 * Login.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Curtis
 */

#include "Login.h"

using namespace std;

void Login::enterPassword(void){

	fputs("Enter 8 character password"); // Buffer overflow avoided by using fputs instead of old puts - KG
	fgets(Password); // Buffer overflow avoided by using fgets instead of old gets - KG
}

void Login::copyUsername(string str1, string str2){
	strcpy(name, str1.c_str());
	strcat(name, " = ");
	strcat(name, str2.c_str());
	cout << name;

}

int Login::copyPassword(){
	strcpy(a, "copyPassword"); // Capitalized P in reference to proper formatting - KG
	strcpy(b, "copyPassword"); // Capitalized P in reference to proper formatting - KG
	strcpy(c, a);
	strcat(c, b);
	printf("a = %s\n", a);
	return 0;

}

int Login::testUsernamePassword(void) {
	arg1 = "Test Username and Password.";

	while (arg1[i] != '\0') {
		buff[i] = arg1[i];
		i++;
	}
	buff[i] = '\0';
	printf("buff=%s\n", buff);

	return 0; // Add missing return - KG

}

void Login::isPasswordOK(void) {

	fputs("Enter Password");

	fgets(passwordCheck);
	PwStatus = (strcmp(passwordCheck, "goodpass") == 0);
	if (PwStatus == false) {
		fputs("Access Denied");
	}
	else {
		fputs("Access Granted");
	}

}

Login::Login() {
	// TODO Auto-generated constructor stub

}

Login::~Login() {
	// TODO Auto-generated destructor stub
}

