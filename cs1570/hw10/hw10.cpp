//Programmer: LUCAS KEHOE & JON CLARK	Date: 12/4/2018
//Class: CS1570			Section: A & E
//File: hw10.cpp
/*Purpose: The purpose of this program is to simulate a burger eating
contest.*/

#include "burger.h"
#include "customer.h"
#include "burgermeister.h"
#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));//seed rand

	burgermeister bm1("Krusty", 100);
	customer c1[PARTICIPANTS];

	//setprecision for $ output
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout << "\n\n\n\t\tBegin the Contest!!!\n" << endl;
	//introduce contestants
	cout << "The contestants are: " << endl;
	for (int i = 0; i < PARTICIPANTS; i++)
		cout <<"\t"<< c1[i];
	
	while(c_round(c1, bm1));

	c_win(c1);//output winner
	bmEarnings(bm1);//output burgermeister earnings

	return 0;
}
