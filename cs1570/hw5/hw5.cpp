//Programer: LUCAS KEHOE	Date:10/1/2018
//Class: CS1570			Section: A
//File: hw5.cpp
/*Purpose: The purpose of this program is to calculate Krusty's Profit
values based on the number of animal parts and animal types he uses
in his burger. This program takes in user input for lower and upper bounds
for the two categories and can then generate a table based on those values,
outputing the table to the screen.*/

#include <iostream>
#include <cmath>
using namespace std;

//Desc: outputs to user a greeting message
//Pre: 	none
//Post: greeting message output to screen
void greet();

//Desc:	takes input from user for lower bound of animal part
//Pre:	none
//Post:	returns lower bound of animal part>0
int in_anim_part_lower();

//Desc: takes input from user for upper bound of animal part
//Pre: 	lower bound of animal part must be positive
//Post: returns upper bound of animal part>lower bound of animal part
int in_anim_part_upper(const int a_p_lower);

//Desc: takes input from user for lower bound of animal type
//Pre: 	none
//Post: returns lower bound of animal type>0
int in_anim_type_lower();

//Desc: takes input from user for upper bound of animal type
//Pre: 	lower bound of animal type must be positive
//Post: returns upper bound of animal type>lower bound of animal type
int in_anim_type_upper(const int a_t_lower);

//Desc: outputs a table of values
//Pre: 	lower bound of animal parts must be positive and upper bound of 
//	animal parts must be greater than lower bound of animal parts. 
//      lower bound of animal types must be positive and upper bound of
//	animal types must be greater than lower bound of animal types.
//Post: table is output to screen
void table(const int a_p_lower, const int a_p_upper, const int a_t_lower, 
const int a_t_upper);

//Desc: calculates a value using Prof Frink's equation
//Pre: 	animal parts must not equal 0
//Post: returns calculated value
double krusty_kalculator(const int anim_part, const int anim_type);

//Desc: outputs to user a sign off message
//Pre: 	none
//Post: sign off message output to screen
void sign_off();

int main()
{
  //variables
  int option = 0;
  int anim_part_lower = 0, anim_part_upper = 0;
  int anim_type_lower = 0, anim_type_upper = 0;
  char quit = 'n';

  greet();
  do
  {
    cout << "1. Input Animal Part Bounds" << endl;
    cout << "2. Input Animal Type Bounds" << endl;
    cout << "3. Output Table" << endl;
    cout << "0. Quit" << endl;
    cout << "What would you like to do? ";
    cin >> option;//user input option?
    cout << endl;
    switch (option)
    {
      case 1:
        anim_part_lower = in_anim_part_lower();
        anim_part_upper = in_anim_part_upper(anim_part_lower);
        break;
      case 2:
	anim_type_lower = in_anim_type_lower();
	anim_type_upper = in_anim_type_upper(anim_type_lower);
	break;
      case 3:
	table(anim_part_lower, anim_part_upper, anim_type_lower, 
        anim_type_upper);
	break;
      case 0:
	cout << "Are you sure you want to quit? (y/n) ";
	cin >> quit;//user input quit?
	break;
      default:
	cout << "Invalid Input" << endl;
    }
    cout << endl;
  } while (quit != 'y' && quit != 'Y');//if user input quit then exit loop
  sign_off();
  return 0;
}

void greet()
{
  cout << "--------------------PROFIT CALCULATOR--------------------" << endl;
  cout << "Hello! This program is designed to calculate Krusty's profits!";
  cout << endl;
  cout << "The calculation is made based on the number of animal parts used";
  cout << endl << "and the number of animal types used in the burgers."<<endl;
  return;
}

int in_anim_part_lower()
{
  //variables
  int a_p_lower = 0;

  do
  {
    cout << "Enter a lower bound for animal parts: ";
    cin >> a_p_lower;//user input
  } while (a_p_lower <= 0);//if a_p_lower is greater than 0, exit loop
  return a_p_lower;
}

int in_anim_part_upper(const int a_p_lower)
{
  //variables
  int a_p_upper;

  do
  {
    cout << "Enter an upper bound for animal parts: ";
    cin >> a_p_upper;//user input
  } while (a_p_upper < a_p_lower);//if a_p_lower greater than a_p_upper, exit
  return a_p_upper;
}

int in_anim_type_lower()
{
  //variables
  int a_t_lower = 0;

  do
  {
    cout << "Enter a lower bound for animal types: ";
    cin >> a_t_lower;//user input
  } while (a_t_lower <= 0);//if a_t_lower is greater than 0, exit loop
  return a_t_lower;
}

int in_anim_type_upper(const int a_t_lower)
{
  //variables
  int a_t_upper;

  do
  {
    cout << "Enter an upper bound for animal types: ";
    cin >> a_t_upper;//user input
  } while (a_t_upper < a_t_lower);//if a_t_lower greater than a_t_upper, exit
  return a_t_upper;
}

void table(const int a_p_lower, const int a_p_upper, const int a_t_lower, 
const int a_t_upper)
{
  //variables
  double temp = 0;
  int temp_a_p = 0, temp_a_t = 0;

  //2 deciaml point
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  if (a_p_lower > 0 && a_t_lower > 0)//a_p_lower and a_t_lower greater than 0
  {
    //TABLE
    cout << "Table f(animal parts, animal types): " << endl;
    temp_a_p = a_p_lower;
    do
    {
      temp_a_t = a_t_lower;
      do
      {
	cout << "f(" << temp_a_p << "," << temp_a_t << ") ";
	temp_a_t += 1;//index animal type
      }while (temp_a_t <= a_t_upper);
      cout << endl;
      temp_a_p += 1;//index animal part
    }while (temp_a_p <= a_p_upper);
    //ACTUAL VALUES
    cout << "Profit Values: " << endl;
    temp_a_p = a_p_lower;
    do
    {
      temp_a_t = a_t_lower;
      do
      {
        temp = krusty_kalculator(temp_a_p, temp_a_t);
	cout << temp << " ";
	temp_a_t += 1;//index animal type
      }while (temp_a_t <= a_t_upper);
      cout << endl;
      temp_a_p += 1;//index animal part
    }while (temp_a_p <= a_p_upper);
  }
  else
    cout << "Please enter bounds first." << endl;
  return;
}

double krusty_kalculator(const int anim_part, const int anim_type)
{
  double kalculation = 0;
  if (anim_part != 0)//no divide by 0
    kalculation = anim_part * exp(-1 * pow(anim_type, 2) / anim_part);
  else
    cout << "DIVIDE BY 0 ERROR" << endl;
  return kalculation;
}

void sign_off()
{
  cout << "Thank you for using the PROFIT CALCULATOR. Have a nice day!"<<endl;
  return;
}
