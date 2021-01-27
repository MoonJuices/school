//Programmer: LUCAS KEHOE	Date: 10/22/2018
//Class: CS1570			Section: A
//File: hw7.cpp
/*Purpose: The purpose of this program is to generate burgers randomly and 
put them into a list. The program then sorts the list alphabetically and can
print the list of burgers to the screen. The user is capable of manually 
removing burgers from the list as well.*/

#include "hw7.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int main()
{
  //variables
  burger kburger;
  char quit = 'n';
  int option;
  //seed
  srand(time(NULL));
  //set decimal point
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  //greeting
  cout << "--------------------KRUSTY BURGER-------------------" << endl;
  cout<<"Hello! Welcome to the Krusty Burger Generator! Let's begin!"<<endl;
  do
  {
    //menu
    cout << "\n1. Generate New Burger" << endl;
    cout << "2. Print List of Burgers" << endl;
    cout << "3. Remove a Burger From List" << endl;
    cout << "0. Quit" << endl;
    cout<<"Choose: ";
    cin >> option;
    switch (option)
    {
      case 1:
        new_burger(kburger);
	break;
      case 2:
	print_burger(kburger);
	break;
      case 3:
	remove_burger(kburger);
	break;
      case 0:
	cout << "Are you sure you would like to quit? (y/n): ";
	cin >> quit;
	break;
      default:
	cout << "Invalid input! Try again!" << endl;
      }
    } while (quit != 'y' && quit != 'Y');
  //sign-off
  cout << "\nThank you for using the Krusty Burger Generator!";
  cout<<" Goodbye! :)" << endl;
  return 0;
}
