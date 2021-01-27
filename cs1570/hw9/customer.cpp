//Programmer: LUCAS KEHOE	Date: 11/9/2018
//Class: CS1570			Section: A
//File: customer.cpp
/*Purpose: contains member functions for class customer*/

#include "customer.h"
#include "burger.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

customer::customer()
{
  //name
  static int counter = 0;
  ifstream in;
  int i_money;//dollars
  in.open("simpson_names.dat");
  for (int i = 0; i <= counter; i++)
    in.getline(m_c_name, CUSTOMER_NAME_LEN - 1, '\n');
  counter++;
  in.close();
  //money
  i_money = rand() % (MAX_MONEY - MIN_MONEY + 1) + MIN_MONEY;//dollars
  if (i_money != MAX_MONEY)
    m_money = i_money + (0.01 * static_cast<float>(rand() % 101));//change
  else
    m_money = i_money;
  //weight
  m_weight = rand() % (MAX_WEIGHT - MIN_WEIGHT + 1) + MIN_WEIGHT;
  //isAlive
  m_isAlive = true;
  //cholesterol
  m_cholesterol = rand() % (MAX_CHOLESTEROL - MIN_CHOLESTEROL + 1)
  + MIN_CHOLESTEROL;
}

void customer::eat(const burger & b)
{
  if(m_isAlive==true)
  {
    m_money -= b.get_price();
    if (m_money < 0)
      m_money = 0;
    m_cholesterol += 2.5 * b.get_bacon() + (PI / 2.0) * b.get_patties()
    + m_weight / ((b.get_pickles() + 1) * 10.0);//cholesterol equation
    m_weight += 0.5*pow(b.get_patties(),2)+(1.0 / 8.0)*pow(b.get_bacon(),2)
    - b.get_pickles() / 4.0 + b.get_cheese()*CHEESE_WEIGHT
    + b.get_sauce()*SAUCE_WEIGHT;//weight equation
    if (b.get_pathogen() == true)
      m_isAlive = false;
    cout<<m_c_name<<" ate the ";
    b.print_burger_name();
    cout<<"."<<endl;
  }
  else
    cout<<m_c_name<<" is DEAD. They can not eat."<<endl;
  return;
}

ostream & operator<<(ostream & o, const customer & c)
{
  cout<<c.m_c_name<<" weighs "<<c.m_weight<<" lbs, has $"<<c.m_money;
  cout<<", "<<c.m_cholesterol<<" IBU and is ";
  if (c.m_isAlive == true)
    cout << "ALIVE." << endl;
  else
    cout << "DEAD." << endl;
  return o;
}
