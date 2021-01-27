//Programmer: LUCAS KEHOE & JON CLARK	Date: 12/4/2018
//Class: CS1570			Section: A & E
//File: burgermeister.cpp
/*Purpose: This file contains the constructors and member functions for class
burgermeister.*/

#include "burgermeister.h"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

burgermeister::burgermeister(const char name[], const float money)
{
	strcpy(m_bm_name, name);
	if (money < 0)//money can not be less than 0
		m_money = 0;
	else
		m_money = money;
	m_initial_money = m_money;
}

void burgermeister::sayName()
{
	cout << m_bm_name;
	return;
}

burgermeister & burgermeister::operator+=(const float & rhs)
{
	m_money += rhs;
	return *this;
}

burgermeister & burgermeister::operator-=(const float & rhs)
{
	m_money -= rhs;
	if (m_money < 0)//money can not be less than 0
		m_money = 0;
	return *this;
}

void bmEarnings(burgermeister & bm)
{
	if (bm.getMoneyDiff() > 0)
	{
		bm.sayName();
		cout << " made $" << bm.getMoneyDiff() << "."<<endl;
	}
	else if (bm.getMoney() == 0)
	{
		bm.sayName();
		cout << " went broke!"<<endl;
	}
	else
	{
		bm.sayName();
		cout << " lost $" << abs(bm.getMoneyDiff()) << "."<<endl;
	}
}