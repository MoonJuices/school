//Programmer: LUCAS KEHOE	Date:10/10/2018
//Class: CS1570			Section: A
//File: hw6_funct.cpp
/*Purpose: The purpose of this file is to define the functions used in
hw6.cpp*/

#include "hw6.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

void menu()
{
  //variables
  int option = 0;//menu selector
  char quit = 'n';
  int x = 0, n = 0;//x and base-n
  int x4 = 0, x3 = 0, x2 = 0, x1 = 0, x0 = 0;//individual digits of x
  bool x_is_base_n = false;
  bool step1 = false, step2 = false;

  do
  {
    cout << endl;
    cout << "1. Enter a non-negative integer, x [5-digit or less]" << endl;
    cout << "2. Enter an integer base, n" << endl;
    cout << "3. Verify x is a valid base n number" << endl;
    cout << "4. Force validation with new (smallest) base assignment" << endl;
    cout << "5. Force validation with new (random digits in) x" << endl;
    cout << "6. Convert x to base 10" << endl;
    cout << "7. Quit" << endl;
    cout << "Choose [1-7]: ";
    cin >> option;
    switch (option)
    {
      case 1:
        step1 = true;
	x = get_x();
	break;
      case 2:
	step2 = true;
	n = get_n();
	break;
      case 3:
	if (step1 == true && step2 == true)//ensures user went through step1,2
	{
	  decipher_x(x, x4, x3, x2, x1, x0);
	  x_is_base_n = check_x_base_n(x4, x3, x2, x1, x0, n);
	  if (x_is_base_n == true)
	    cout << x << " is a valid base-" << n << " number." << endl;
	  else
	    cout << x << " is not a valid base-" << n << " number." << endl;
	}
	else
	  cout << "You must complete Step 1 and Step 2!" << endl;
	break;
      case 4:
	if (step1 == true && step2 == true)//ensures user went through step1,2
	{
	  decipher_x(x, x4, x3, x2, x1, x0);
	  x_is_base_n = check_x_base_n(x4, x3, x2, x1, x0, n);
	  if (x_is_base_n == true)
	    cout << x << " is a valid base-" << n << " number." << endl;
	  else
	    n = new_n(n, x4, x3, x2, x1, x0);
	}
	else
	  cout << "You must complete Step and Step 2!" << endl;
	break;
      case 5:
	if (step1 == true && step2 == true)//ensures user went through step1,2
	{
	  decipher_x(x, x4, x3, x2, x1, x0);
	  x_is_base_n = check_x_base_n(x4, x3, x2, x1, x0, n);
	  if (x_is_base_n == true)
	    cout << x << " is a valid base-" << n << " number." << endl;
	  else
	    x = new_x(n, x4, x3, x2, x1, x0);
	}
	else
	  cout << "You must complete Step 1 and Step 2!" << endl;
	break;
      case 6:
	if (step1 == true && step2 == true)//ensures user went through step1,2
	{
	  decipher_x(x, x4, x3, x2, x1, x0);
	  x_is_base_n = check_x_base_n(x4, x3, x2, x1, x0, n);
	  if (x_is_base_n == true)
	    print_x_base_10(x4, x3, x2, x1, x0, n);
	  else
	    cout << x << " is not a valid base-" << n << " number." << endl;
	}
	else
	  cout << "You must complete Step 1 and Step 2!" << endl;
	break;
      case 7:
	cout << "Are you sure you would like to quit? (y/n): ";
	cin >> quit;
	break;
      default:
	cout << "Invalid Input! Try again!" << endl;
    }
  } while (quit != 'Y' && quit != 'y');
  return;
}

int get_x()
{
  //variables
  int x = 0;

  do
  {
    cout << "Enter a non-negative integer, x [5-digit or less]: ";
    cin >> x;
  } while (x<MIN_X || x>MAX_X);
  return x;
}

int get_n()
{
  //variables
  int n = 0;

  do
  {
    cout << "Enter an integer base, n [2<=n<10]: ";
    cin >> n;
  } while (n < MIN_N || n >= MAX_N);
  return n;
}

void decipher_x(int x, int & x4, int & x3, int & x2, int & x1, int & x0)
{
  //decipher digits
  x4 = x / pow(10, 4);
  x -= x4 * pow(10, 4);
  x3 = x / pow(10, 3);
  x -= x3 * pow(10, 3);	
  x2 = x / pow(10, 2);
  x -= x2 * pow(10, 2);
  x1 = x / pow(10, 1);
  x -= x1 * pow(10, 1);
  x0 = x / pow(10, 0);
  return;
}

bool check_x_base_n(const int x4, const int x3, const int x2,
const int x1, const int x0, const int n)
{
  //variables
  bool x_is_base_n = false;
  
  if (x4 < n&&x3 < n&&x2 < n&&x1 < n&&x0 < n)
    x_is_base_n = true;
  return x_is_base_n;
}

void print_x_base_10(const int x4, const int x3, const int x2,
const int x1, const int x0, const int n)
{
  //cout<<x<<" base-"<<n<<" = ";
  //calculation
  cout << x4 * pow(10, 4) + x3 * pow(10, 3) + x2 
  * pow(10, 2) + x1 * pow(10, 1) + x0 * pow(10, 0) << " base-" << n << " = ";
  if (x4 == 0)
    cout << "";
  else
    cout << x4 << "*" << n << "^4";
  if (x4 != 0 && (x3 != 0 || x2 != 0 || x1 != 0 || x0 != 0))
    cout << " + ";
  if (x3 == 0)
    cout << "";
  else
    cout << x3 << "*" << n << "^3";
  if (x3 != 0 && (x2 != 0 || x1 != 0 || x0 != 0))
    cout << " + ";
  if (x2 == 0)
    cout << "";
  else
    cout << x2 << "*" << n << "^2";
  if (x2 != 0 && (x1 != 0 || x0 != 0))
    cout << " + ";
  if (x1 == 0)
    cout << "";
  else
    cout << x1 << "*" << n << "^1";
  if (x1 != 0 && (x0 != 0))
    cout << " + ";
  if (x0 == 0)
    cout << "";
  else
    cout << x0 << "*" << n << "^0";
  //calculation for x base-n to decimal
  cout<<" = "<<x4*pow(n,4)+x3*pow(n,3)+x2*pow(n,2)+x1*pow(n,1)
  +x0*pow(n,0)<<" base-10"<<endl;
  return;
}

int new_n(int n, const int x4, const int x3, const int x2,
const int x1, const int x0)
{
  if (x4 >= n)//if digit is >= n
    n = x4 + 1;//make n = digit + 1
  if (x3 >= n)
    n = x3 + 1;
  if (x2 >= n)
    n = x2 + 1;
  if (x1 >= n)
    n = x1 + 1;
  if (x0 >= n)
    n = x0 + 1;
  cout << "New base-n: " << n << endl;
  return n;
}

int new_x(const int n, int & x4, int & x3, int & x2, int & x1, int & x0)
{
  int x = 0;
  if (x0 >= n)//if digit is >= n
    x0 = rand() % n;//make digit some random value [0,n)
  if (x1 >= n)
    x1 = rand() % n;
  if (x2 >= n)
    x2 = rand() % n;
  if (x3 >= n)
    x3 = rand() % n;
  if (x4 >= n)
    x4 = rand() % n;
  //calculate new x base-n with new digits
  x = x4 * pow(10, 4) + x3 * pow(10, 3) + x2 * pow(10, 2) 
  + x1 * pow(10, 1) + x0 * pow(10, 0);
  cout << "New x: " << x << endl;
  return x;
}
