//Programmer: LUCAS KEHOE	Date: 11/9/2018
//Class: CS1570			Section: A
//File: hw9.cpp
/*Purpose: The purpose of this program is to test the functionality of 
our created classes burger and customer.*/

#include "burger.h"
#include "customer.h"
#include <iostream>
using namespace std;

int main()
{
  srand(time(NULL));//seed rand

  burger b1[PARTICIPANTS], b2(4, 4, 4, true, true, true);//burgers
  customer c1[PARTICIPANTS];//customers

  cout.setf(ios::fixed);//magic code
  cout.setf(ios::showpoint);//magic code
  cout.precision(2);//magic code

  cout<<"Hello! Welcome to Lucas Kehoe's Burger/Customer Driver!"<<endl;//hi
  cout<<"----------PARTICIPANTS----------"<<endl;
  for(int i = 0; i < PARTICIPANTS; i++)
    cout<<c1[i];//print customers

  cout<<"----------BURGERS----------"<<endl;
  for(int i = 0; i < PARTICIPANTS; i++)
    cout<<b1[i];//print burgers
  cout<<"----------DEATH BURGER----------"<<endl;
  cout<<b2;//print defined burger
  
  cout<<"----------ROUND 1----------"<<endl;
  for(int i = 0; i < PARTICIPANTS; i++)  
  {  
    c1[i].eat(b1[i]);//eat
    cout << c1[i];
  }
  cout<<"----------ROUND 2: SUDDEN DEATH----------"<<endl;
  for(int i = 0; i < PARTICIPANTS; i++)
  {
    c1[i].eat(b2);//eat
    cout << c1[i];  
  }

  cout<<"The contest is over, goodbye. :)"<<endl;//sign-off
  return 0;
}
