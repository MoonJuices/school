//Programmers: LUCAS KEHOE & JONATHAN CLARK	Date: 11/1/2018
//Class: CS1570					Section: A/E
//File: hw8_funct.cpp
/*Purpose: This file contains all the function defintions for hw8.cpp.*/

#include "hw8.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

void question_answer(candidate & c)
{
  ifstream inanswers;
  ifstream innouns;
  char temp_answer[SIZE] = "";
  char noun[WORD] = "";
  int numberofanswers = 0, numberofnouns = 0;
  int ctr1 = 0, ctr2 = 0, ctr3 = 0;//counters
  
  for(int i = 0; i < SIZE; i++)//reset question and answer arrays
  {
    c.question[i] = '\0';
    c.answer[i] = '\0';
  }

  cout<<"Candidate #"<<c.candidate_number<<": ";
  cin.getline(c.question,SIZE-1,'\n');//ask question
  cout<<endl;

  inanswers.open("answers.dat");
  inanswers>>numberofanswers;//first value in answers.dat
  
  for(int i = 0; i < rand()%numberofanswers+1; i++)//get rand answer
    inanswers.getline(temp_answer,SIZE-1,'\n');
  
  while(temp_answer[ctr1]!='\0')
  { 
    if(temp_answer[ctr1]!='*')
    {
      c.answer[ctr2] = temp_answer[ctr1];//copy char by char
      ctr1++;//increment
      ctr2++;//increment
    }
    else//else "*noun*"
    {
      ctr1+=SKIP;//skip "*noun*"

      innouns.open("nouns.dat");
      numberofnouns = 0;
      while(innouns>>noun)//find number of nouns in nouns.dat
        numberofnouns++;
      innouns.close();
      innouns.open("nouns.dat");
      for(int n = 0; n < rand()%numberofnouns+1; n++)//get rand noun
        innouns.getline(noun,WORD-1,'\n');
      while(noun[ctr3]!='\0')
      {
        c.answer[ctr2] = noun[ctr3];//copy char by char
        ctr2++;//increment
        ctr3++;//increment
      }
      ctr3 = 0;//reset
      innouns.close();    
    }
  }
  cout<<"ans: "<<c.answer<<endl<<endl;
  inanswers.close();
  return;
}

void score(candidate & c)
{
  int ans_num_let[LETTERS] = {0};
  int que_num_let[LETTERS] = {0};
  int ctr = 0;

  for(int ascii_index = 0; ascii_index < LETTERS; ascii_index++)
  {
    ctr = 0;//reset
    while(c.question[ctr]!='\0')
    {
      if(c.question[ctr]==97+ascii_index||c.question[ctr]==65+ascii_index)
        que_num_let[ascii_index]+=1;
      ctr++;//increment
    }
  }

  for(int ascii_index = 0; ascii_index < LETTERS; ascii_index++)
  {
    ctr = 0;//reset
    while(c.answer[ctr]!='\0')
    {
      if(c.answer[ctr]==97+ascii_index||c.answer[ctr]==65+ascii_index)
        ans_num_let[ascii_index]+=1;
      ctr++;//increment
    }
  }
  
  for(int i = 0; i < LETTERS; i++)
    c.cscore += que_num_let[i] - ans_num_let[i];//score calculation
  
  cout<<"Score = "<<c.cscore<<endl<<endl<<endl;
  return;
}

void win(candidate & c1, candidate & c2)
{
  if(c1.cscore < c2.cscore)
    cout<<"Candidate "<<c1.candidate_number<<" Wins!"<<endl;
  else if(c2.cscore < c1.cscore)
    cout<<"Candidate "<<c2.candidate_number<<" Wins!"<<endl;
  else//unlikely event that they tie
    cout<<"GADZOOKS! IT'S A TIE!"<<endl;
  return;
}
