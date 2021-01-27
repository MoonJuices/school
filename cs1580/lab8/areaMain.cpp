//Programmer: LUCAS KEHOE	Date:10/9/2018
//Class: CS1580			Section: D
//File: areaMain.cpp
/*Purpose: The purpose of this program is to get the length and width
of a rectangle from the user and then calculate the area of a rectangle.
Then the program gets the radius of a circle from the user and calculates
the area of a circle.*/

#include "area.h"
#include <iostream>
using namespace std;

int main()
{
  //structs
  area my_area;

  greet();

  getRecDim(my_area.m_recDim.m_width, my_area.m_recDim.m_length);
  my_area.m_rect_area = 
  calculateArea(my_area.m_recDim.m_width, my_area.m_recDim.m_length);
  cout<<"Area of entered rectangle is: "<<my_area.m_rect_area<<endl;

  getCircleDim(my_area.m_circleDim.m_radius);
  my_area.m_circle_area = calculateArea(my_area.m_circleDim.m_radius);
  cout<<"Area of entered circle is: "<<my_area.m_circle_area<<endl;
  
  signoff();
  
  return 0;
}
