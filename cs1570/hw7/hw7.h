//Programmer: LUCAS KEHOE	Date: 10/21/2018
//Class: CS1570				Section: A
//File: hw7.h
/*Purpose: This file contains all the global constats, struct
definitions, and function prototypes for hw7.cpp.*/

#ifndef HW7_H
#define HW7_H
#include <string>
using namespace std;

//GLOBAL CONSTANTS
const int SIZE = 37;//array size
const int MAXPATTY = 3;
const int MAXBACON = 3;
const int MAXPICKLE = 3;
const string ONEPATTIES = "Single ";
const string TWOPATTIES = "Double ";
const string THREEPATTIES = "Triumph ";
const string ZEROBACONS = "Health-Master ";
const string ONEBACONS = "Bacon ";
const string TWOBACONS = "Wilbur ";
const string THREEBACONS = "Klogger ";
const string ZEROPICKLES = "Tasteless ";
const string ONEPICKLES = "Pickly ";
const string TWOPICKLES = "Garden-Fresh ";
const string THREEPICKLES = "Kermit ";
const string MOREPICKLES = "Veggie ";
const string MAXPATTYBACON = "Koronary ";
const int INTMAXPATTYBACON = 6;
const float BUNP = 0.5;
const float PATTYP = 0.75;
const float BACONP = 0.5;
const float PICKLEP = 0.25;

struct burger
{
	string m_name[SIZE] = { "" };
	int m_patties[SIZE] = { 0 };
	int m_bacons[SIZE] = { 0 };
	int m_pickles[SIZE] = { 0 };
	int m_code[SIZE] = { 0 };
};

//Desc: this function will generate a new burger and will add it to the 
//	arrays if the burger does not already exist
//Pre:	must be passed a struct of type burger
//Post: new burger will be generated and will add to list if it does not 
//	already exist then will sort the list alphabetically
void new_burger(burger & b);

//Desc: prints all the generated burgers in a list form
//Pre:	must be passed a struct of type burger
//Post: Prints names of burgers, items on burgers, and price of burgers
void print_burger(const burger b);

//Desc: asks user for burger code and then searches list and 
//	removes burger from list of burgers
//Pre:	must be passed a struct of type burger
//Post: will remove burger from list or return an error if invalid code 
//	is entered
void remove_burger(burger & b);

//Desc:	sorts list of burgers alphabetically using Bubble Sort method
//Pre:	must be passed a struct of type burger
//Post: sorts the burgers in list alphabetically
void sort_burger(burger & b);

//Desc: removes burgers from list when a duplicate is found
//Pre:  must be passed a struct of type burger
//Post: list of burgers with no duplicates
void remove_duplicates(burger & b);

#endif
