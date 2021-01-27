//Programmer: LUCAS KEHOE & JON CLARK	Date: 12/4/2018
//Class: CS1570			Section: A & E
//File: burgermeister.h
/*Purpose: This file contains the class burgermeister and associated constants*/

#ifndef BURGERMEISTER_H
#define BURGERMEISTER_H
#include <iostream>
using namespace std;

const int BM_NAME_LEN = 100;
const int BM_DEAD_C = 35;//fee for dead customer
const int BM_PUKE_C = 5;//fee for puke customer

class burgermeister
{
private:
	char m_bm_name[BM_NAME_LEN];
	float m_money;
	float m_initial_money;
public:
	//Desc: generates a burgermeister with defined name and money
	//		initial money is set to money
	burgermeister(const char name[], const float money);

	//Desc: overloads += operator for class burgermeister
	//Pre:	none
	//Post:	add rhs to money
	burgermeister & operator+=(const float & rhs);

	//Desc:	overloads -= operator for class burgermeister
	//Pre:	none
	//Post: subtracts rhs from money, money can not be <0
	burgermeister & operator-=(const float & rhs);
	
	//Desc: prints the burgermeisters name to screen
	//Pre:	none
	//Post:	printed the burgermeisters name
	void sayName();

	//Desc: returns value requested
	//Pre:  none
	//Post: returned the value
	float getMoney() { return m_money; }

	//Desc: returns difference in money and initial money
	//Pre:	none
	//Post:	returns difference
	float getMoneyDiff() {return m_money - m_initial_money;}

	friend void bmEarnings(burgermeister & bm);
};

#endif