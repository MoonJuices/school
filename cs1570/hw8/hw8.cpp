//Programmers: LUCAS KEHOE & JONATHAN CLARK	Date: 11/1/2018
//Class: CS1570					Section: A/E
//File: hw8.cpp
/*Purpose: This program is designed to simulate a political debate between
two candidates. The user prompts the candidates with questions, and then
the candidates respond with randomly generated answers from two seperate files
(answers.dat and nouns.dat). The program then calculates the scores of the
two candidates and declares a winner.*/

#include "hw8.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

int main()
{
  candidate c1, c2;//candidates 1 and 2
 
  c1.candidate_number = CAND_ONE;
  c2.candidate_number = CAND_TWO;
  srand(time(NULL));//seed

  cout<<"Hello! Welcome to the debate!"<<endl;//greet
  
  for(int i = 0; i < NUM_QUESTIONS; i++)//loop for NUM_QUESTIONS
  {
    question_answer(c1);
    score(c1);
    question_answer(c2);
    score(c2);
  }

  win(c1,c2);

  cout<<"Thanks to everyone for attending this awesome event!"<<endl;//signoff

  return 0;
}
