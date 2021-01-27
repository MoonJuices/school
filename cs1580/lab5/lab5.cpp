//Programmer: LUCAS KEHOE	Date:9/18/2018
//Class: CS1580			Section: D
//File: lab5.cpp
/*Purpose: The purpose of this program is to run a poll for the greatest
dragon. Toothless is the best dragon. This poll is not rigged, I swear.
The user is prompted with 3 choices to vote for and then the program
takes in a vote. The program will ask for inputs equal to the number of
voters. After all votes are in, the program will display the final results.*/

#include <iostream>
using namespace std;

int main()
{
  //variable declaration
  //constants
  const int n_voters = 9;//number of voters
  //variables
  int m_vote = 0, s_vote = 0, t_vote = 0, w_vote = 0;//number of votes
  float percent_m = 0, percent_s = 0, percent_t = 0, percent_w = 0;//%vote
  char vote;//user choice
  //user prompt and greeting message
  cout<<"------------HOW TO TRAIN YOUR DRAGON------------"<<endl;
  cout<<"Welcome to How to Train the Greatest Dragon!"<<endl;
  cout<<"Here are your candidates: "<<endl;
  cout<<"M: Meatlug"<<endl;
  cout<<"S: Stormfly"<<endl;
  cout<<"T: Toothless"<<endl<<endl;
  for(int i = 0; i < n_voters; i++)//for loop runs for n_voters
  {
    cout<<"Who do you want to vote for? (M,S,T): ";
    cin>>vote;//user input (char)
    switch(vote)
    {
      //vote for meatlug
      case 'm':
      case 'M':
        cout<<"You voted for Meatlug."<<endl;
        m_vote += 1;
        break;
      //vote for stormfly
      case 's':
      case 'S':
        cout<<"You voted for Stormfly."<<endl;
        s_vote +=1;
        break;
      //vote for toothless, the best dragon
      case 't':
      case 'T':
        cout<<"You voted for Toothless."<<endl;
        t_vote += 1;
        break;
      //wasted vote
      default:
        cout<<"You wasted your vote."<<endl;
        w_vote += 1;
    }
  }
  cout<<endl;
  if(m_vote>0&&s_vote>0&&t_vote>0)//if there are any non-wasted votes
  {
    //percent calculations for votes
    percent_m = static_cast<float>(m_vote)/(m_vote+s_vote+t_vote+w_vote)*100;
    percent_s = static_cast<float>(s_vote)/(m_vote+s_vote+t_vote+w_vote)*100;
    percent_t = static_cast<float>(t_vote)/(m_vote+s_vote+t_vote+w_vote)*100;
    percent_w = static_cast<float>(w_vote)/(m_vote+s_vote+t_vote+w_vote)*100;
    //print final summary of votes
    cout<<"Here is the Voting Summary:"<<endl;
    cout<<"Candidate        Votes        Percentage(%)"<<endl;
    cout<<"Meatlug           "<<m_vote<<"            "<<percent_m<<endl;
    cout<<"Stormfly          "<<s_vote<<"            "<<percent_s<<endl;
    cout<<"Toothless         "<<t_vote<<"            "<<percent_t<<endl;
    cout<<"Wasted            "<<w_vote<<"            "<<percent_w<<endl;
  }
  else//else all votes are wasted
    cout<<"No one successfully voted. Yikes."<<endl;
  //sign-off message
  cout<<endl;
  cout<<"Thank you for using the How to Train the Greatest Dragon!"<<endl;
  cout<<"Have a nice day. dB^)"<<endl;
  return 0;
}
