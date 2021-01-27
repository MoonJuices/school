//Programmer: Lucas Kehoe
//Date: 9/4/2018
//File: lab3
//Class: CS1580
//Section: D
/*Description: Calculates the slope of a line when given a coordinate (x2,y2),
in relation to a fixed coordinate (x1,y1).*/

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
  //variable declaration
  const int x1 = -5,y1 = 6;  //fixed coordinate
  int x2, y2;  //variable coordinate
  float slope;  //slope of line

  //prompt user
  cout<<"Hello and welcome to the slope calculator."<<endl;
  cout<<"Please input the x and y coordinates of the desired point."<<endl;
  cout<<"X (feet): ";
  cin>>x2;  //x input of desired point
  cout<<"Y (feet): ";
  cin>>y2;  //y input of desired point

  //slope calculation
  slope = static_cast<float>(y2-y1)/(x2-x1);

  //output slope of line as float
  cout<<"The slope of the line is: "<<slope<<endl;

  //cast slope as int
  slope = static_cast<int>(slope);

  //output slope of line as int
  cout<<"The slope after casting as an int is: "<<slope<<endl;

  return 0;
}
