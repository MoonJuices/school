//Programmer: LUCAS KEHOE	Date: 10/10/2018
//Class: CS1570			Section: A
//File: hw6.cpp
/*Purpose: The purpose of this program is to help Krusty (or anyone)
understand numbering systems. This assignment is a spinoff of 
assignment-04, except has 2 more options offered in the menu system.
One option forces a new base-n assignment for x and the other option 
forces a new x for base-n. This program takes in an integer 
x[5-digits or less] and a base-n and then can determine if x is a valid
base-n or not. This program can also print your x base-n in terms of 
base-10 or decimal.*/

#include "hw6.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
  //srand(time(NULL));	
  srand(7);//seed rand

  //greeting message	
  cout << "------------NUMBERING SYSTEMS 2.0-----------" << endl;
  cout << "This program is designed to help you understand" << endl;
  cout << "numbering systems!" << endl;
  cout << "Let's get started!" << endl;

  menu();

  //signoff message
  cout<<"Thank you for using Numbering Systems 2.0! Have a nice day!"<<endl;
  return 0;
}
