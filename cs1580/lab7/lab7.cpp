//Programer: LUCAS KEHOE	Date:10/2/2018
//Class: CS1580			Section: D
//File: lab7.cpp
/*Purpose: This program can generate a random number in a range
of values input by the user.*/

#include <iostream>
#include <cstdlib>
using namespace std;

//Desc: outputs a greeting to the user
//Pre:	none
//Post:	prints a greeting to the screen
void greeting();

//Desc:	takes user input for the bounds of the rng
//Pre:	none
//Post: returns an upper and lower bound by reference
void readNum(int & lower, int & upper);

//Desc: outputs a random number between bounds
//Pre:	lower and upper bounds must be positive integers that are not equal
//Post:	prints a random integer in the range to the screen
void printRand(int lower, int upper);

//Desc: outputs a sign off message to the user
//Pre:	none
//Post:	prints a sign off message to the screen
void signOff();

int main()
{
  //constants
  const int QUIT = 0;
  //variables
  int lower = 0, upper = 0;
  int option = 0;
  //seed
  srand(time(NULL));

  greeting();
  do
  {
    cout<<"1. Input lower and upper bounds"<<endl;
    cout<<"2. Generate 7 random integers in bounds"<<endl;
    cout<<QUIT<<". Quit"<<endl;
    cout<<"What would you like to do? ";
    cin>>option;//user input option
    switch(option)
    {
      case 1:
        readNum(lower, upper);
        break;
      case 2:
        printRand(lower, upper);
        break;
      case 0:
        break;
      default:
        cout<<"Invalid Input!"<<endl;
    }
  }while(option!=QUIT);
  signOff();
  return 0;
}

void greeting()
{
  cout<<"--------------RANDOM NUMBER GENERATOR--------------"<<endl;
  cout<<"This program can produce random integers in a range!"<<endl;
  cout<<"Let's begin! :)"<<endl<<endl;
  return;
}

void readNum(int & lower, int & upper)
{
  //variables
  int val1 = 0, val2 = 0;

  do
  {
    cout<<"Please enter a positive integer: ";
    cin>>val1;
  }while(val1<=0);//val1 must be positive
  do
  {
    cout<<"Please enter a different positive integer: ";
    cin>>val2;
  }while(val2<=0||val1==val2);//val2 must be positive and not equal to val1
  if(val1<val2)//if val1<val2, val1 = lower, val2 = upper
  {
    lower = val1;
    upper = val2;
  }
  else//else val1>val2, val2 = lower, val1 = upper
  {
    lower = val2;
    upper = val1;
  }
  return;
}

void printRand(int lower, int upper)
{
  if(lower!=0&&upper!=0&&lower!=upper)//prevent user from skipping bounds
  {
    for(int i = 1; i <= 7; i++)//7 outputs
    {
      cout<<i<<". Random number between ";
      cout<<lower<<" and "<<upper<<" inclusive is: ";
      cout<<lower+(rand()%(upper-lower+1))<<endl;//random number calculation
    }
  }
  else//user skipped bounds
    cout<<"ERROR: Enter Bounds First"<<endl;
  return;
}

void signOff()
{
  cout<<"Thank you for using the random number generator!"<<endl;
  cout<<"Have a nice day! :)"<<endl; 
  return;
}
