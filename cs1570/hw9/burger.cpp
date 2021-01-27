//Programmer: LUCAS KEHOE	Date: 11/9/2018
//Class: CS1570			Section: A
//File: burger.cpp
/*Purpose: This file contains the constructors and member funcions for class
burger.*/

#include "burger.h"
#include <iostream>
#include <cstring>
using namespace std;

burger::burger()
{
  int chance;//temp variable
  //PATTIES BACON PICKLES
  m_patties = rand() % (MAX_PATTIES - MIN_PATTIES + 1) + MIN_PATTIES;
  m_bacon = rand() % (MAX_BACON - MIN_BACON + 1) + MIN_BACON;
  m_pickles = rand() % (MAX_PICKLES - MIN_PICKLES + 1) + MIN_PICKLES;
  //CHEESE
  chance = rand() % 100 + 1;
  if (chance <= PERCENT_CHEESE)
    m_cheese = true;
  else
    m_cheese = false;
  //SAUCE
  chance = rand() % 100 + 1;
  if (chance <= PERCENT_SAUCE)
    m_sauce = true;
  else
    m_sauce = false;
  //PATHOGEN
  chance = rand() % 100 + 1;
  if (chance <= PERCENT_PATHOGEN)
    m_pathogen = true;
  else
    m_pathogen = false;

  m_price = price_burger();
  this->name_burger();
}

burger::burger(int pat, int bac, int pic, const bool has_cheese, 
const bool has_sauce, const bool has_pathogen)
{
  //pat in range
  if (pat > MAX_PATTIES)
    pat = MAX_PATTIES;
  else if (pat < MIN_PATTIES)
    pat = MIN_PATTIES;
  m_patties = pat;
  //bac in range
  if (bac > MAX_BACON)
    bac = MAX_BACON;
  else if (bac < MIN_BACON)
    bac = MIN_BACON;
  m_bacon = bac;
  //pic in range
  if (pic > MAX_PICKLES)
    pic = MAX_PICKLES;
  else if (pic < MIN_PICKLES)
    pic = MIN_PICKLES;
  m_pickles = pic;
  //cheese, sauce, pathogen
  m_cheese = has_cheese;
  m_sauce = has_sauce;
  m_pathogen = has_pathogen;

  m_price = price_burger();
  this->name_burger();
}

float burger::price_burger()const
{
  return BUN_P+m_patties*PATTIES_P+m_bacon*BACON_P+m_pickles*PICKLES_P
  +m_cheese*CHEESE_P+m_sauce*SAUCE_P;//price calculation
}

void burger::name_burger()
{
  strcpy(m_b_name, "Krusty ");
  if (m_pickles >= m_patties + m_bacon)//special case
    strcat(m_b_name, MORE_PICKLES);
  else if (m_patties + m_bacon == INTMAXPATTIESBACON)//special case
    strcat(m_b_name, MAX_PATTIES_BACON);
  else
  {
    //patties
    if (m_patties == 1)
      strcat(m_b_name, ONE_PATTIES);
    else if (m_patties == 2)
      strcat(m_b_name, TWO_PATTIES);
    else if (m_patties == 3)
      strcat(m_b_name, THREE_PATTIES);
    else if (m_patties == 4)
      strcat(m_b_name, FOUR_PATTIES);
    //bacon
    if (m_bacon == 0)
      strcat(m_b_name, ZERO_BACON);
    else if (m_bacon == 1)
      strcat(m_b_name, ONE_BACON);
    else if (m_bacon == 2)
      strcat(m_b_name, TWO_BACON);
    else if (m_bacon == 3)
      strcat(m_b_name, THREE_BACON);
    else if (m_bacon == 4)
      strcat(m_b_name, FOUR_BACON);
    //pickles
    if (m_pickles == 0)
      strcat(m_b_name, ZERO_PICKLES);
    else if (m_pickles == 1)
      strcat(m_b_name, ONE_PICKLES);
    else if (m_pickles == 2)
      strcat(m_b_name, TWO_PICKLES);
    else if (m_pickles == 3)
      strcat(m_b_name, THREE_PICKLES);
    else if (m_pickles == 4)
      strcat(m_b_name, FOUR_PICKLES);
  }
  //cheese
  if (m_cheese == true)
    strcat(m_b_name, WITH_CHEESE);
  //sauce
  if (m_sauce == true)
    strcat(m_b_name, WITH_SAUCE);
  
  strcat(m_b_name, "Burger");
  return;
}

void burger::print_burger_name()const
{
  cout<<m_b_name;//can not return b_name because char array
  return;
}

ostream & operator<<(ostream & o, const burger & b)
{
  cout << b.m_b_name << endl;
  cout << "(" << b.m_patties << ", " << b.m_bacon << ", " << b.m_pickles;
  cout << ", " << b.m_cheese << ", " << b.m_sauce << ", " << b.m_pathogen;
  cout << ", $" << b.m_price << ")" << endl;
  /*cout << "Patties: " << b.m_patties << endl;
  cout << "Bacon: " << b.m_bacon << endl;
  cout << "Pickles: " << b.m_pickles << endl;
  cout << "Has cheese: " << b.m_cheese << endl;
  cout << "Has sauce: " << b.m_sauce << endl;
  cout << "Has pathogen: " << b.m_pathogen << endl;
  cout << "Price: $" << b.m_price << endl;*/
  return o;
}
