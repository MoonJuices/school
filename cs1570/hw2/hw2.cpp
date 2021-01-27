//Programmer: LUCAS KEHOE	Date:9/5/2018
//File: hw2.cpp
/*Purpose: This program will determine how many miles you must run
in order to reduce your chance of heart attack after ordering
burgers, fries, and milkshakes from Krusty.*/

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
  //variable delcaration
  //constants
  const float AQF = 5.6;  //Air Quality Factor
  const float KBMF = 19.7;  //Krusty Burger Mitigation Factor
  //variables
  int nBurgers, nFries, nMilkshakes, queue, marathons;
  float heartAttack, miles; 
 
  //prompt user and input data
  cout<<"--------------------KRUSTY BURGER--------------------"<<endl;
  cout<<"Hello! How many burgers, fries, and milkshakes would you like?"<<endl;
  cout<<"Burgers: ";
  cin>>nBurgers;  //number of burgers
  cout<<"Fries: ";
  cin>>nFries;  //number of fries
  cout<<"Milkshakes: ";
  cin>>nMilkshakes;  //number of milkshakes
  cout<<endl<<"What is the length of your queue?"<<endl;
  cout<<"Length of queue: ";
  cin>>queue;  //length of queue
  cout<<endl;
  
  //heart attack % calculation
  heartAttack = (nBurgers+nFries)*(static_cast<float>(nMilkshakes)/(queue+1));
  //only add AQF if the customer buys at least one each of burg, fries, milk
  heartAttack += static_cast<bool>(nBurgers&&nFries&&nMilkshakes)*AQF;

  //marathons and miles needed to survive calculation
  miles = heartAttack*KBMF;
  marathons = miles/26;
  miles -= marathons*26;

  //echo inputs and print the data to user
  cout<<"Your order: "<<endl;
  cout<<"  "<<nBurgers<<" Burgers"<<endl;
  cout<<"  "<<nFries<<" Fries"<<endl;
  cout<<"  "<<nMilkshakes<<" Milkshakes"<<endl;
  cout<<"  You were "<<queue<<" in queue"<<endl<<endl;
  cout<<"  Chance of heart attack is "<<heartAttack<<"%"<<endl<<endl;
  cout<<"  You need to run "<<marathons<<" marathons, plus "<<miles;
  cout<<" miles to save your life!"<<endl;  

  return 0;
}
