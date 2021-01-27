//Programmer: LUCAS KEHOE	Date:9/11/2018
//Class: CS1570			Section: A
//File: hw3.cpp
/*Purpose: This program is designed to generate burger names and burger 
prices for Krusty when the user inputs a 3-digit code.*/

#include <iostream>
using namespace std;

int main()
{
  //variable declaration
  //constants
  const int TERMINATION_CODE = 000; //Terminate Program
  const int PATTY_BACON = 6, MAX_PICKLES = 1;  //Krusty Koronary Burger
  const float PATTY_COST = 0.75, BACON_COST = 0.50;
  const float PICKLE_COST = 0.25, BUN_COST = 0.50;
  //variables
  int code = 0, tempCode = 0, patties = 0, bacon = 0, pickles = 0;
  float price = 0;
  string burgerName = "";

  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  //prompt user and input data
  cout<<"--------------------KRUSTY BURGER--------------------"<<endl;
  cout<<"Hello! This program is designed to generate burger names"<<endl;
  cout<<"and their respective prices."<<endl;
  cout<<"The program will ask you for a 3-digit code."<<endl;
  cout<<"The first digit is the number of patties. Must be value 1-3."<<endl;
  cout<<"The second digit is the oz of bacon. Must be value 0-3."<<endl;
  cout<<"The third digit is number of pickles. Must be value 0-3."<<endl<<endl;
  cout<<"Please enter a 3-digit code: ";
  cin>>code;  //3-digit code

  do
  {
    //deciphering 3-digit code
    tempCode = code;
    patties = tempCode / 100;  //patties = 1st digit
    tempCode = tempCode % 100;
    bacon = tempCode / 10;  //bacon = 2nd digit
    tempCode = tempCode % 10;
    pickles = tempCode;  //pickles = 3rd digit
    
    //naming of burger - patties
    if(patties == 1)
      burgerName = "Single ";
    else if(patties == 2)
      burgerName = "Double ";
    else if(patties == 3)
      burgerName = "Triumph ";
    else
      burgerName = "ERROR";
  
    //naming of burger - bacon
    if(burgerName == "ERROR")
      burgerName = "ERROR";
    else if(bacon == 0)
      burgerName += "Health-Master ";
    else if(bacon == 1)
      burgerName += "Bacon ";
    else if(bacon == 2)
      burgerName += "Wilbur ";
    else if(bacon == 3)
      burgerName += "Klogger ";
    else
      burgerName = "ERROR";

    //naming of burger - pickles
    if(burgerName == "ERROR")
      burgerName = "ERROR";
    else if(pickles == 0)
      burgerName += "Tasteless ";
    else if(pickles == 1)
      burgerName += "Pickly ";
    else if(pickles == 2)
      burgerName += "Garden-Fresh ";
    else if(pickles == 3)
      burgerName += "Kermit ";
    else
      burgerName = "ERROR";

    //naming of burger - special case - Veggie
    if(burgerName == "ERROR")
      burgerName = "ERROR";
    else if(pickles >= patties + bacon)
      burgerName = "Veggie ";
    else
      burgerName = burgerName;

    //naming of burger - special case - Koronary
    if(burgerName == "ERROR")
      burgerName = "ERROR";
    else if(patties + bacon == PATTY_BACON && pickles <= MAX_PICKLES)
      burgerName = "Koronary ";
    else
      burgerName = burgerName;
 
    //naming of burger - Krusty + Burger
    if(burgerName == "ERROR")
      burgerName = "ERROR";
    else
      burgerName = "Krusty " + burgerName + "Burger";

    //output ERROR or burger name and price
    if(burgerName == "ERROR")
      cout<<"There was an ERROR with the input: "<<code<<endl<<endl;
    else
    {
      //price calculation
      price = patties * PATTY_COST + bacon * BACON_COST;
      price += pickles * PICKLE_COST + BUN_COST;
      //output burger name and price
      cout<<"Burger name: "<<burgerName<<endl;
      cout<<"Burger price: $"<<price<<endl<<endl;
    }

    //reprompt user and input data
    cout<<"You may enter another 3-digit code or may type \"";
    cout<<TERMINATION_CODE<<"\" to terminate the program."<<endl<<endl;
    cout<<"Please enter a 3-digit code: ";
    cin>>code;  //3-digit code

  }while(code!=TERMINATION_CODE);  //exit do while loop if code = terminate

  //sign off message
  cout<<endl<<"Thank you for using the Krusty Burger Name Generator!"<<endl;
  cout<<"Have a great day!"<<endl;

  return 0;
}
