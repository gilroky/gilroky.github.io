/*
 * Gas.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Curtis
 */

#include "Gas.h"

using namespace std;

//***************************************************************
//    	GAS FEE CALCULATION
//****************************************************************

//Removed unused code - KG

void Gas::gasFeeCalculation()
{

	double gallons, charge, total; // Removed charge = 0 as we give charge a variable later on - KG
	const int fee = 15;
	double costUpTo6K = 2.35, // Changed int to double as we are working with decimals values. - KG
		costUpTo20K = 3.75,
		costOver20K = 6.00;

	system("cls");

   cout << "\n\n\n\tEnter the total number of gallons used, divided by 1000: ";
	cin >> gallons;

	if (gallons > 20){
		charge = (gallons - 20) * costOver20K;
		charge = charge + (14 * costUpTo20K);
		charge = charge + (6 * costUpTo6K);
	}
	else if (gallons > 6 && gallons <= 20){

		charge = (gallons - 6) * costUpTo20K; // Removed one = sign from double to correct calculation - KG
		charge = charge + (6 * costUpTo6K);
	}
	else{

		charge = gallons * costUpTo6K;
	}

	total = charge + fee; // Simplified code for total - KG
	cout << "\n\n\n\tYou have used " << gallons << " thousand gallons of water." << endl;
	cout << "\n\n\n\tYour total water bill is $" << setprecision(2) << total; // Corrected output to show total, not total and charge - KG
   getch();
}


Gas::Gas() {
	// TODO Auto-generated constructor stub

}

Gas::~Gas() {
	// TODO Auto-generated destructor stub
}

