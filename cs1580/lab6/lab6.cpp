//Programmer: LUCAS KEHOE	Date:9/25/2018
//Class: CS1580 		Section: D
//File: lab6.cpp
/*Purpose: The purpose of this program is to take in the radius from the
user and calculate the area of the circle based on the given radius.*/

#include <iostream>
using namespace std;

//FUNCTION PROTOTYPE
void greeting();
float RadIn();
float CalcArea(float radius);
void outputRes(float radius, float area);
void signOff();

int main()//main
{
  float radius = 0, area = 0;//variables
  greeting();
  radius = RadIn();
  area = CalcArea(radius);
  outputRes(radius, area);
  signOff();
  return 0;
}

void greeting()//greeting message
{
  cout<<"Welcome to the circle area calculator."<<endl;
  return;
}

float RadIn()//take in radius
{
  float radius = 0;//variables
  do
  {
    cout<<"Please enter a positive radius: ";
    cin>>radius;
  }while(radius<=0);
  return radius;
}

float CalcArea(float radius)//calculate area of circle
{
  const float PI = 3.14159265359;//constants
  float area = 0;//variables
  area = PI*radius*radius;//area calculation
  return area;
}

void outputRes(float radius, float area)//output radius and area
{
  cout<<"You entered the radius: "<<radius<<endl;//echo
  cout<<"The area of your circle is: "<<area<<endl;//output calculation
  return;
}

void signOff()//signoff message
{
  cout<<"Thank you for using the circle calculator."<<endl;
  cout<<"Have a good day."<<endl;
  return;
}
