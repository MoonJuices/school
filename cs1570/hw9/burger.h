//Programmer: LUCAS KEHOE	Date: 11/9/2018
//Class: CS1570			Section: A
//File: burger.h
/*Purpose: This file contains the class burger and associated constants*/

#ifndef BURGER_H
#define BURGER_H
#include <iostream>
using namespace std;
//burger requirements
const int BURGER_NAME_LEN = 100;
const int MAX_PATTIES = 4;
const int MIN_PATTIES = 1;
const int MAX_BACON = 4;
const int MIN_BACON = 0;
const int MAX_PICKLES = 4;
const int MIN_PICKLES = 0;
const int PERCENT_CHEESE = 50;
const int PERCENT_SAUCE = 50;
const int PERCENT_PATHOGEN = 10;
const int INTMAXPATTIESBACON = 8;
//naming conventions
const int WORD_SIZE = 20;
const char MORE_PICKLES[WORD_SIZE] = "Veggie ";
const char MAX_PATTIES_BACON[WORD_SIZE] = "Koronary ";
const char ONE_PATTIES[WORD_SIZE] = "Single ";
const char TWO_PATTIES[WORD_SIZE] = "Double ";
const char THREE_PATTIES[WORD_SIZE] = "Triumph ";
const char FOUR_PATTIES[WORD_SIZE] = "Quadruple ";
const char ZERO_BACON[WORD_SIZE] = "Health-Master ";
const char ONE_BACON[WORD_SIZE] = "Bacon ";
const char TWO_BACON[WORD_SIZE] = "Wilbur ";
const char THREE_BACON[WORD_SIZE] = "Klogger ";
const char FOUR_BACON[WORD_SIZE] = "Whole-Hog ";
const char ZERO_PICKLES[WORD_SIZE] = "Tasteless ";
const char ONE_PICKLES[WORD_SIZE] = "Pickly ";
const char TWO_PICKLES[WORD_SIZE] = "Garden-Fresh ";
const char THREE_PICKLES[WORD_SIZE] = "Kermit ";
const char FOUR_PICKLES[WORD_SIZE] = "Big-Dill ";
const char WITH_CHEESE[WORD_SIZE] = "Cheesy ";
const char WITH_SAUCE[WORD_SIZE] = "Saucy ";
//burger prices
const float BUN_P = 0.5;
const float PATTIES_P = 0.75;
const float BACON_P = 0.5;
const float PICKLES_P = 0.25;
const float CHEESE_P = 0.25;
const float SAUCE_P = 0.10;

class burger
{
  private:
    int m_patties;
    int m_bacon;
    int m_pickles;
    bool m_cheese;
    bool m_sauce;
    bool m_pathogen;
    char m_b_name[BURGER_NAME_LEN];
    float m_price;
  public:
    //Desc: generates a burger with random variables
    burger();//default constructor

    //Desc: generates a burger with defined variables
    burger(int pat, int bac, int pic, const bool has_cheese,
    const bool has_sauce, const bool has_pathogen);

    //Desc: calculates and returns the price of burger
    //Pre:  must have values for patties, bacon, and pickles
    //Post: returns float price of burger
    float price_burger()const;

    //Desc: generates name of burger based on private members of burger
    //Pre:  patties, bacon, pickles, cheese, sauce must have values
    //Post: generates name of the burger
    void name_burger();

    //Desc: returns variable
    //Pre:  none
    //Post: returns variable
    float get_price()const { return m_price; }
    int get_patties()const { return m_patties; }
    int get_bacon()const { return m_bacon; }
    int get_pickles()const { return m_pickles; }
    bool get_cheese()const { return m_cheese; }
    bool get_sauce()const { return m_sauce; }
    bool get_pathogen()const { return m_pathogen; }
    
    //Desc: prints burger name
    //Pre:  none
    //Post: prints burgers name to screen
    void print_burger_name()const;

    //Desc: allows user to use insertion operator for burger
    //Pre:  stream must be open
    //Post: allows us to output burger
    friend ostream & operator<<(ostream & o, const burger & b);
};

#endif
