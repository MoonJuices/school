//Programmer: LUCAS KEHOE	Date:10/23/2018
//Class: CS1580			Section: D
//File: lab10.cpp
/*Purpose: This program prompts the user to input an integer.
The program then takes the integer and reads in the line from a .txt file.
The program then prints the sentence to the screen, capitalizes the sentence,
and outputs the sentence to the screen again.*/

#include <iostream>
#include <fstream>
using namespace std;

//GLOBAL CONSTANTS
const int SIZE = 120;
const int NUMBEROFSENTENCES = 5;

//Desc: capitalizes the lower case letters in an NTCA
//Pre:	must be passed an array of characters
//Post: capitalizes the lower case letters in an NTCA
void capitalize(char s[]);

int main()
{
  //variables
  int maxslen = SIZE - 1;
  int option = 0;
  char sentence[SIZE];
  
  ifstream in;
  in.open("lab10.txt");

  //greeting message
  cout<<"Hello and Welcome to the convert-o-matic"<<endl;
  cout<<"Please input the number for the sentence you want to take in: ";
  do
  {
    cin>>option;
    if(option>=1&&option<=NUMBEROFSENTENCES)
    {
      cout<<"Thank you for your input"<<endl;
      for(int i = 0; i < option; i++)
        in.getline(sentence, maxslen, '\n');
    }
    else
      cout<<"Invalid input! Please enter an integer between 1 and 5!"<<endl;
  }while(option<1||option>NUMBEROFSENTENCES);
  cout<<"The sentence you chose is:"<<endl;
  cout<<sentence<<endl;
  cout<<"The sentence is being converted"<<endl;
  capitalize(sentence);
  cout<<"The sentence after conversion is:"<<endl;
  cout<<sentence<<endl;
  in.close();

  //sign-off message
  cout<<"Thank you for using the convert-o-matic"<<endl;
  return 0;
}

void capitalize(char s[])
{
  //variables
  char letter ='a';
 
  for(int i = 0; i < SIZE; i++)
  {
    letter = s[i];
    letter = toupper(letter);
    s[i] = letter;
  }
  return;
}
