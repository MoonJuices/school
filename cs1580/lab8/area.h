//Programmer: LUCAS KEHOE	Date:10/9/2018
//Class: CS1580			Section: D
//File: area.h 
/*Purpose: The purpose of this file is to contain the global constants,
structs, and funtion declarations for the program.*/

#ifndef AREA_H
#define AREA_H
using namespace std;

//GLOBAL CONSTANTS
const float PI = 3.14159265359;

//STRUCTS
struct rectangle
{
  float m_width;
  float m_length;
};
struct circle
{
  float m_radius;
};
struct area
{
  rectangle m_recDim;
  circle m_circleDim;
  float m_rect_area;
  float m_circle_area;
};

//FUNCTION DECLARATIONS

//Desc:	print greeting message to screen
//Pre:	none
//Post:	print greeting to screen
void greet();

//Desc: passes dimensions of rectangle by reference
//Pre:	none
//Post:	passes dimension1 > 0 and dimension2 > 0 by reference
void getRecDim(float & dimension1, float & dimension2);

//Desc:	calculates the area of a rectangle
//Pre:	dimension1 and dimension2 need to be positive
//Post:	returns the area of a rectangle
float calculateArea(float dimension1, float dimension2);

//Desc: passes radius of circle by reference
//Pre:	none
//Post:	passes radius(dimension1) > 0 by reference
void getCircleDim(float & dimension1);

//Desc:	calculate the area of a circle
//Pre:	radius(dimension1) need to be positive
//Post:	returns the area of a circle with radius(dimension1)
float calculateArea(float dimension1);

//Desc: prints signoff message to screen
//Pre:	none
//Post:	prints signoff to screen
void signoff();

#endif
