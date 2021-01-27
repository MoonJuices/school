//Programmer: LUCAS KEHOE	Date:10/30/2018
//Class: CS1580			Section: D
//File: lab11.cpp
/*Purpose: The purpose of this program is to get data for a class object
of type dragon and then echo that data back to the user. This labs purpose
is to familiarize ourselves with classes.*/

#include <iostream>
using namespace std;

//Desc:	greeting(); outputs greeting message to user
//Pre:	none
//Post:	prints greeting message to screen

//Desc:	getStats(); gets stats for an object dragon
//Pre:  none
//Post: float>0 for height, float>0 for weight, bool for wings, int>0 for legs

//Desc: printStats(); prints dragons stats to screen
//Pre:	dragon should have entered values for stats, otherwise it will be crap
//Post:	prints dragons stats to the screen

//Desc: signOff(); outputs signoff message to user
//Pre:	none
//Post:	prints signoff message to screen
class dragon
{
  public:
    void greeting();
    void getStats();
    void printStats();
    void signOff();
  private:
    float m_height;
    float m_weight;
    bool m_wings;
    int m_legs;
};

int main()
{
  dragon d1, d2;//dragon 1 and dragon 2

  d1.greeting();
  cout<<"Dragon 1"<<endl;
  d1.getStats();
  d1.printStats();
  cout<<"Dragon 2"<<endl;
  d2.getStats();
  d2.printStats();
  d1.signOff();
  
  return 0;
}

void dragon::greeting()
{
  cout<<"Hello, User. :)"<<endl;
  return;
}

void dragon::getStats()
{
  char has_wings;
  do
  {
    cout<<"Please enter your dragons height: ";
    cin>>m_height;
  }while(m_height<=0);//height must be greater than 0
  do
  {
    cout<<"Please enter your dragons weight: ";
    cin>>m_weight;
  }while(m_weight<=0);//weight must be greater than 0
  cout<<"Please enter if your dragon has wings (T/F): ";
  cin>>has_wings;
  switch(has_wings)
  {
    case 'T':
    case 't':
      m_wings = true;
      break;
    case 'F':
    case 'f':
      m_wings = false;
      break;
    default:
      m_wings = false;//if user fails to enter a valid input, default to false
  }
  do
  {
    cout<<"Please enter the number of legs for your dragon: ";
    cin>>m_legs;
  }while(m_legs<=0);//legs must be greater than 0
  return;
}

void dragon::printStats()
{
  cout<<"Height: "<<m_height<<" feet"<<endl;
  cout<<"Weight: "<<m_weight<<" pounds"<<endl;
  cout<<"Does it have wings: ";
  if(m_wings == true)
    cout<<"True"<<endl;
  else
    cout<<"False"<<endl;
  cout<<"Number of Legs: "<<m_legs<<endl;
  return;
}

void dragon::signOff()
{
  cout<<"Goodbye. :)"<<endl;
  return;
}
