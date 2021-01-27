//Programmer: LUCAS KEHOE	Date: 10/16/18
//Class: CS1580			Section: D
//File: lab9.cpp
/*Purpose: The purpose of this program is to randomly generate 2 arrays
of dragons, print them to the screen, swap their values, and print them
to the screen again.*/

//STRUCTS
struct dragon
{
  int numb_wingPairs;
  int numb_legPairs;
};

//Desc: generates random value of legs and wings for dragons in an array
//Pre:  must be passed an array of dragons
//Post:	give values of 0 to 3 (inclusive) for pairs of leg and wings for
//	dragons in passed array
void randDragons(dragon array[]);

//Desc: will swap the values of legs and wings of two dragon arrays
//Pre:  must be passed 2 dragon arrays of equal size
//Post: swap the values of legs and wings of the arrays
void swapDragons(dragon array1[], dragon array2[]);

//Desc: will print the number of legs and wings of the dragons in the array
//Pre:	must be passed an array of dragons
//Post: prints the number of legs and wings to the screen in readable format
void printDragons(dragon array[]);

using namespace std;
#include <iostream>
#include <cstdlib>

//GLOBAL CONSTANTS
const int SIZE = 4;
const int MAX_WING_PAIR = 3;
const int MAX_LEG_PAIR = 3;

int main()
{
  //variables
  dragon group1[SIZE], group2[SIZE];
  //seed
  srand(time(NULL));

  //greeting
  cout<<"Welcome to the dragon random generation machine"<<endl;
  cout<<"The dragons generated this round are: "<<endl;

  //give dragon values
  randDragons(group1);
  randDragons(group2);

  //print groups
  cout<<"Group 1:"<<endl;
  printDragons(group1);
  cout<<"Group 2:"<<endl;
  printDragons(group2);
  
  //swap
  swapDragons(group1, group2);

  //print groups
  cout<<"After swapping the arrays are: "<<endl;
  cout<<"Group 1:"<<endl;
  printDragons(group1);
  cout<<"Group 2:"<<endl;
  printDragons(group2);

  //signoff
  cout<<"Thank you for using the dragon random generator machine"<<endl;
  cout<<"Have a nice day! :)"<<endl;
 
  return 0;
}

//define the operator for dragons
ostream& operator <<(ostream & os, const dragon & d)
{
  os<<"Number of legs is: "<<d.numb_legPairs * 2<<endl;
  os<<"   Number of wings is: "<<d.numb_wingPairs * 2<<endl;
  return os;
}

void randDragons(dragon array[])
{
  for(int i = 0; i < SIZE; i++)
  {
    array[i].numb_wingPairs = rand() % (MAX_WING_PAIR + 1);//randwings [0,3]
    array[i].numb_legPairs = rand() % (MAX_LEG_PAIR + 1);//randlegs [0,3]
  }
  return;
}

void printDragons(dragon array[])
{
  for(int i = 0; i < SIZE; i++)
  {
    cout<<i+1<<". "<<array[i];
  }
  return;
}

void swapDragons(dragon array1[], dragon array2[])
{
  //temp variables
  int temp_wing = 0, temp_leg = 0;
  
  for(int i = 0; i < SIZE; i++)
  {
    temp_wing = array1[i].numb_wingPairs;
    temp_leg = array1[i].numb_legPairs;

    array1[i].numb_wingPairs = array2[i].numb_wingPairs;
    array1[i].numb_legPairs = array2[i].numb_legPairs;

    array2[i].numb_wingPairs = temp_wing;
    array2[i].numb_legPairs = temp_leg;
  }
  return;
}
