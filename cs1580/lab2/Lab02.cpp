//Programmer: Lucas K. Kehoe  Date: 8/28/2018
//File:Lab02  Class: cs1580 Section: d
//Description: fix the broken program

#include <iostream>
using namespace std;

int main()
{
//Variable declaration
int input_1;  //A number
int input_2;  //Another  number
int add_res;  //This stores the first operation
int subtraction_results;  //This stores the second operation
int multiplication_results;  //This stores the third operation
int division_result;  //This stores th fourth operation
  
cout<<"Welcome to the math basic tutorial"<<endl;
cout<<"Please input two numbers"<<endl;

cin>>input_1; //This takes in a thing
cin>>input_2;  //This also takes in a thing

//This performs the operation on the numbers
add_res = input_1 + input_2;

//This outputs to the screen
cout<<"Adding the two numbers gives us: "<<add_res<<endl;

//This performs the operation on the numbers
subtraction_results = input_1 - input_2;

//This outputs to the screen
cout<<"Subtracting input 2 from input 1 gives you: "<<subtraction_results<<endl;

//This performs the operation on the numbers
multiplication_results = input_1 * input_2;

//This outputs to the screen
cout<<"Multiplying the two numbers together gives us: ";
cout<<multiplication_results<<endl;

//This performs the operation on the numbers
//NOTE: division_result may be inaccurate as it is an int variable
division_result = input_1/input_2; 

//This outputs to the screen
cout<<"Dividing number 1 by number 2 gives us: "<<division_result<<endl; 

return 0;
}
