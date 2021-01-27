//Programmers: LUCAS KEHOE & JONATHAN CLARK	Date: 11/1/2018
//Class: CS1570					Section: A/E
//File: hw8.h
/*Purpose: This file contains the global variables, structs, and function
prototypes for hw8.cpp and hw8_funct.cpp.*/

#ifndef HW8_H
#define HW8_H

using namespace std;

//GLOBAL VARIABLES
const int SIZE = 700;
const int WORD = 20;
const int NUM_QUESTIONS = 4;
const int LETTERS = 26;
const int CAND_ONE = 1;
const int CAND_TWO = 2;
const int SKIP = 6;

//STRUCTS
struct candidate
{
  int candidate_number = 0;
  
  char question[SIZE] = "";

  char answer[SIZE] = "";

  int cscore = 0;
};

//Desc: user asks candidates a question and then the program randomly
//	generates an answer.
//Pre:	c must be of type candidate
//Post: ntcas question and answer in the passed struct c are set
void question_answer(candidate & c);

//Desc:	calculates candidates scores based on question and answer ntcas
//Pre:	c must be of type candidate
//Post:	score added to cscore of the passed struct c 
void score(candidate & c);

//Desc:	calculates the winner between two candidates
//Pre:  c1 and c2 must be of type candidate
//Post: declared a winner and printed winner to screen
void win(candidate & c1, candidate & c2);

#endif
