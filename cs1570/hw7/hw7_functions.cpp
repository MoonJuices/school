//Programmer: LUCAS KEHOE	Date: 10/22/2018
//Class: CS1570			Section: A
//File: hw7_functions.cpp
/*Purpose: This file contains the function definitions for hw7.cpp.*/

#include "hw7.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void new_burger(burger & b)
{
  //variables
  int t_patties = 1 + rand() % MAXPATTY; //value [1,MAX]
  int t_bacons = rand() % (MAXBACON + 1); //value [0,MAX]
  int t_pickles = rand() % (MAXPICKLE + 1); //value [0,MAX]
  int t_code = t_patties * 100 + t_bacons * 10 + t_pickles;
  string t_name = "Krusty ";

  if (t_pickles >= t_patties + t_bacons)//SPECIAL CASE
    t_name += MOREPICKLES;
  else if (t_patties + t_bacons == INTMAXPATTYBACON)//SPECIAL CASE
    t_name += MAXPATTYBACON;
  else
  {
    if (t_patties == 1)
      t_name += ONEPATTIES;
    if (t_patties == 2)
      t_name += TWOPATTIES;
    if (t_patties == 3)
      t_name += THREEPATTIES;

    if (t_bacons == 0)
      t_name += ZEROBACONS;
    if (t_bacons == 1)
      t_name += ONEBACONS;
    if (t_bacons == 2)
      t_name += TWOBACONS;
    if (t_bacons == 3)
      t_name += THREEBACONS;

    if (t_pickles == 0)
      t_name += ZEROPICKLES;
    if (t_pickles == 1)
      t_name += ONEPICKLES;
    if (t_pickles == 2)
      t_name += TWOPICKLES;
    if (t_pickles == 3)
      t_name += THREEPICKLES;
  }
  t_name += "Burger";
  cout << "Burger name: " << t_name << endl;
  for (int i = 0; i < SIZE; i++)
  {
    if (b.m_name[i] == "")
    {
      b.m_name[i] = t_name;
      b.m_patties[i] = t_patties;
      b.m_bacons[i] = t_bacons;
      b.m_pickles[i] = t_pickles;
      b.m_code[i] = t_code;
      t_name = "";
      t_patties = 0;
      t_bacons = 0;
      t_pickles = 0;
      t_code = 0;
    }
  }
  remove_duplicates(b);
  sort_burger(b);
  return;
}

void print_burger(const burger b)
{
  for (int i = 0; i < SIZE; i++)
  {
    if (b.m_name[i] != "")
    {
      cout << b.m_name[i] << endl;
      cout << "\t";
      cout << b.m_patties[i] << " patties, ";
      cout << b.m_bacons[i] << " bacons, ";
      cout << b.m_pickles[i] << " pickles" << endl;
      cout << "\tPrice: $";
      cout << BUNP + PATTYP*b.m_patties[i] + BACONP*b.m_bacons[i] 
      + PICKLEP*b.m_pickles[i] << endl;
    }
  }
  return;
}

void remove_burger(burger & b)
{
  //variables
  int code;
  bool b_exists = false;

  cout << "Code: Patties-Bacons-Pickles (ex: 123)" << endl;
  cout << "Enter burger code you would like to delete: ";
  cin >> code;
  for (int i = 0; i < SIZE; i++)
  {
    if (b.m_code[i] == code)
    {
      b_exists = true;
      cout<<"Removed burger: "<<b.m_name[i]<<endl;
      b.m_name[i] = "";
      b.m_patties[i] = 0;
      b.m_bacons[i] = 0;
      b.m_pickles[i] = 0;
      b.m_code[i] = 0;
    }
  }
  if (b_exists == false)
    cout << "ERROR: Could not find burger with code " << code << "." << endl;
  sort_burger(b);
  return;
}

void sort_burger(burger & b)
{
  //variables
  string t_name = "";
  int t_patties = 0;
  int t_bacons = 0;
  int t_pickles = 0;
  int t_code = 0;

  for (int i = 0; i < SIZE - 1; i++)
  {
    for (int j = i + 1; j < SIZE; j++)
    {
      if (b.m_name[i] > b.m_name[j])
      {
	t_name = b.m_name[i];
	t_patties = b.m_patties[i];
	t_bacons = b.m_bacons[i];
	t_pickles = b.m_pickles[i];
	t_code = b.m_code[i];

	b.m_name[i] = b.m_name[j];
	b.m_patties[i] = b.m_patties[j];
	b.m_bacons[i] = b.m_bacons[j];
	b.m_pickles[i] = b.m_pickles[j];
	b.m_code[i] = b.m_code[j];

	b.m_name[j] = t_name;
	b.m_patties[j] = t_patties;
	b.m_bacons[j] = t_bacons;
	b.m_pickles[j] = t_pickles;
	b.m_code[j] = t_code;
      }
    }
  }
  return;
}

void remove_duplicates(burger & b)
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = i + 1; j < SIZE; j++)
    {
      if (b.m_name[i] == b.m_name[j])
      {
	b.m_name[j] = "";
	b.m_patties[j] = 0;
	b.m_bacons[j] = 0;
	b.m_pickles[j] = 0;
	b.m_code[j] = 0;
      }
    }
  }
  return;
}
