//Programmer: LUCAS KEHOE	Date: 10/10/2018
//Class: CS1570			Section: A
//File: hw6.h
/*Purpose: This file contains the function declarations and global constants
for hw6.cpp and hw6_funct.cpp*/

#ifndef HW6_H
#define HW6_H
using namespace std;

//GLOBAL CONSTANTS
const int MIN_X = 0, MAX_X = 99999, MIN_N = 2, MAX_N = 10;

//Desc:	loops user through menu allowing them to branch to other functions
//Pre:	none
//Post:	user will select an option and will be taken to other function
void menu();

//Desc:	get user input for x
//Pre:	none
//Post:	return x in range of MIN_X and MAX_X
int get_x();

//Desc: get user input for n
//Pre:	none
//Post:	return n in range of MIN_N and MAX_N
int get_n();

//Desc:	deciphers the 5 digit number x
//Pre:	x must be a non-negative 5-digit or less number
//Post: passes digits (x4, x3, x2, x1, x0) by reference
void decipher_x(int x, int & x4, int & x3, int & x2, int & x1, int & x0);

//Desc: checks if x is a valid base-n number
//Pre:	digits of x (x4, x3, x2, x1, x0) must be non-negative int less than 10
//      and n must be less than 10, greater than or equal to 2
//Post:	returns true or false whether or not x is a valid base-n number
bool check_x_base_n(const int x4, const int x3, const int x2,
const int x1, const int x0, const int n);

//Desc: prints to screen x base-n in terms of base-10
//Pre:	x4, x3, x2, x1, x0 must all be positive(or 0) and less than n
//Post:	prints the x base-n equivalent base-10 to screen
void print_x_base_10(const int x4, const int x3, const int x2,
const int x1, const int x0, const int n);

//Desc: calculates the lowest base-n that x can have
//Pre:	x4 or x3 or x2 or x1 or x0 must be greater than n, all non-negative
//Post: prints and returns the new base-n of x
int new_n(int n, const int x4, const int x3, const int x2,
const int x1, const int x0);

//Desc:	randomly generates a new "x" so it can be a valid base-n
//Pre:	x4 or x3 or x2 or x1 or x0 must be greater than n, all non-negative
//Post: prints/return new "x" to screen and passes x4,x3,x2,x1,x0 by reference
int new_x(const int n, int & x4, int & x3, int & x2, int & x1, int & x0);

#endif
