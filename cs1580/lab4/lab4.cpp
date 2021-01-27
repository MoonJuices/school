//Programmer: LUCAS KEHOE	Date:9/11/2018
//Class: CS1580			Section: D
//File: lab4.cpp
/*Purpose: This program allows the user to create a Tabletop Rpg Character
and gives them the option to change the characters stats and name. This
program uses a menu system to allow the user to go back and change
their characters variables as they wish.
*/

#include <iostream>
using namespace std;

int main()
{
  //variables
  //character name
  string characterName = "";
  //character stats
  int strength = 0, dexterity = 0, constitution = 0;
  int intelligence = 0, wisdom = 0, charisma = 0;
  //user menu input
  int input = 0;
  
  //prompt user
  cout<<"----------------TABLETOP RPG CHARACTER CREATOR---------------"<<endl;
  cout<<"Hello! Welcome to the Tabletop RPG Character Creator!"<<endl;

  do
  {
    //menu
    cout<<endl;
    cout<<"Enter 1 to edit character stats."<<endl;
    cout<<"Enter 2 to edit character name."<<endl;
    cout<<"Enter 3 to view character."<<endl;
    cout<<"Enter 4 to Exit Program."<<endl;
    cout<<"Input: ";
    cin>>input;//request user input
    
    if(input==1)//input 1
    {
      //All the loops in this if statement follow the same format.
      //strength loop
      do
      {
        cout<<"Character strength (0-20): ";//ask for stat
        cin>>strength;//input stat
        if(strength>20||strength<0)//if stat is illegal value
          cout<<"Invalid Strength! Try again!"<<endl;//invalid value
      }while(strength>20||strength<0);//repeat loop if value is invalid
   
      //dexterity loop
      do
      {
        cout<<"Character Dexterity (0-20): ";
        cin>>dexterity;
        if(dexterity>20||dexterity<0)
          cout<<"Invalid Dexterity! Try again!"<<endl;
      }while(dexterity>20||dexterity<0);

      //constitution loop
      do
      {
        cout<<"Character Constitution (0-20): ";
        cin>>constitution;
        if(constitution>20||constitution<0)
          cout<<"Invalid Constitution! Try again!"<<endl;
      }while(constitution>20||constitution<0);
    
      //intelligence loop
      do
      {
        cout<<"Character Intelligence (0-20): ";
        cin>>intelligence;
        if(intelligence>20||intelligence<0)
          cout<<"Invalid Intelligence! Try again!"<<endl;
      }while(intelligence>20||intelligence<0);

      //wisdom loop 
      do
      {
        cout<<"Character Wisdom (0-20): ";
        cin>>wisdom;
        if(wisdom>20||wisdom<0)
          cout<<"Invalid Wisdom! Try again!"<<endl;
      }while(wisdom>20||wisdom<0);

      //charisma loop
      do
      {
        cout<<"Character Charisma (0-20): ";
        cin>>charisma;
        if(charisma>20||charisma<0)
          cout<<"Invalid Charisma! Try again!"<<endl;
      }while(charisma>20||charisma<0);
    }
    else if(input==2)//input 2
    {
      cout<<"Character Name (no spaces): ";
      cin>>characterName;//request character name
    }
    else if(input==3)//input 3
    {
      //echo character variables
      cout<<"Character Name: "<<characterName<<endl;
      cout<<"Character Strength: "<<strength<<endl;
      cout<<"Character Dexterity: "<<dexterity<<endl;
      cout<<"Character Constitution: "<<constitution<<endl;
      cout<<"Character Intelligence: "<<intelligence<<endl;
      cout<<"Character Wisdom: "<<wisdom<<endl;
      cout<<"Character Charisma: "<<charisma<<endl;
    }
    else if(input==4)//input 4
    {
      //goodbye message :)
      cout<<endl;
      cout<<"Thank you for using the Tabletop RPG Character Creator!"<<endl;
      cout<<"Have a nice day, "<<characterName<<"!"<<endl;
    }
    else//invalid input
    {
      cout<<"Invalid input! Try again!"<<endl;
    }
  }while(input!=4);
return 0;
}
