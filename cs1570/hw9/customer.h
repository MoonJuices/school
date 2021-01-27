//Programmer: LUCAS KEHOE	Date: 11/9/2018
//Class: CS1570			Section: A
//File: customer.h
/*Purpose: contains class customer and associated constants*/

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "burger.h"
#include <iostream>
using namespace std;
//PARTICIPANTS
const int PARTICIPANTS = 15;
//PI
const float PI = 3.14159265359;
//CUSTOMER
const int CUSTOMER_NAME_LEN = 100;
const int MAX_MONEY = 75;
const int MIN_MONEY = 25;
const int MAX_WEIGHT = 250;
const int MIN_WEIGHT = 90;
const int MAX_CHOLESTEROL = 300;
const int MIN_CHOLESTEROL = 30;
const float CHEESE_WEIGHT = 1.2;
const float SAUCE_WEIGHT = 2.1;

class customer
{
  private:
    char m_c_name[CUSTOMER_NAME_LEN];
    float m_money;
    int m_weight;
    short m_cholesterol;
    bool m_isAlive;
  public:
    //Desc: generates customer with randomly generated values for
    //      money, weight, cholesterol in the respective ranges
    //      name is taken from list, and customer is always initially alive
    customer();//default constructor

    //Desc: changes customers money, weight, and cholesterol based on
    //      burger passed to function
    //Pre:  customer must be alive
    //Post: changes customers private members based on burger
    void eat(const burger & b);

    //Desc: returns isAlive
    //Pre:  none
    //Post: returns isAlive
    //bool get_isAlive()const { return m_isAlive; }

    //Desc: overloads the insertion operator for class customer
    //Pre:  stream must be open
    //Post: overloaded instertion operator
    friend ostream & operator<<(ostream & o, const customer & c);
};

#endif
