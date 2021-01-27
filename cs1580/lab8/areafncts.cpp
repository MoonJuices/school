//Programmer: LUCAS KEHOE	Date:10/9/2018
//Class: CS1580			Section: D
//File: areafncts.cpp 
/*Purpose: This file contains the function definitions used by the program.*/

#include "area.h"
#include <iostream>
using namespace std;

void greet()
{
  cout<<"Welcome to Area Calculator"<<endl;
  return;
}

void getRecDim(float & dimension1, float & dimension2)
{
  do
  {
    cout<<"Enter the length of the rectangle: ";
    cin>>dimension1;
  }while(dimension1<=0);//length must be > 0
  do
  {
    cout<<"Enter the width of the rectangle: ";
    cin>>dimension2;
  }while(dimension2<=0);//width must be > 0
  return;
}

float calculateArea(float dimension1, float dimension2)
{
  float area = 0;
  area = dimension1 * dimension2;//area = length * width
  return area;
}

void getCircleDim(float & dimension1)
{
  do
  {
    cout<<"Enter the radius of a circle: ";
    cin>>dimension1;
  }while(dimension1<=0);//radius must be > 0
  return;
}

float calculateArea(float dimension1)
{
  float area = 0;
  area = PI * dimension1 * dimension1;//area = pi * r^2
  return area;
}

void signoff()
{
  cout<<"Have a Good Day!"<<endl;
  return;
}
