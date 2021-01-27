//Programmer: LUCAS KEHOE	Date: 11/13/2018
//Class: CS1580			Section: D
//File: lab13.cpp
/*Purpose: The purpose of this lab is to give us practice using template
classes. This program uses template class functions to allow us to perform
different mathematical operations on 2 variables with template functions.*/

#include <iostream>
using namespace std;

//GLOBAL CONSTANTS
const int COMP_COST = 2;
const int MULT_COST = 10;
const int ADD_COST = 4;
const int DIV_COST = 8;

template <class T_Type>
class TempClass
{
  private:
    int cost;
  public:
    TempClass():cost(0){}//default constructor

    //Desc: returns cost
    //Pre:  none
    //Post: returns cost
    int get_cost(){return cost;}

    //Desc: checks 2 passed values and returns the greater of the 2
    //Pre:  T_Type must have greater than and is equal defined for type
    //Post: prints greater value to screen and returns greater value
    T_Type checkVal(T_Type x, T_Type y);

    //Desc: multiplies the 2 passed values and returns value
    //Pre:  T_Type must have multiplication defined for type
    //Post: prints the product of 2 passed values and returns value
    T_Type multiply(T_Type x, T_Type y);

    //Desc: adds the 2 passed values and returns value
    //Pre:  T_Type must have addition defined for type
    //Post: prints the sum of the 2 passed values and returns value
    T_Type add(T_Type x, T_Type y);

    //Desc: divides the 2 passed values and returns value
    //Pre:  T_Type must have division defined for type, and y!=0
    //Post: prints the division of x/y and returns value
    T_Type divide(T_Type x, T_Type y);
};

int main()
{
  TempClass<int> intMath;
  TempClass<double> doubleMath;
  int x1, y1;//arbitrary int x, y
  double x2, y2;//arbitrary double x, y
  cout<<"Hello! Practicing Template Classes!"<<endl;//greeting
  cout<<"Please eneter an integer: ";
  cin>>x1;//integer 1
  do
  {
    cout<<"Please enter a non-zero integer: ";
    cin>>y1;//integer 2
  }while(y1==0);//prevent from being 0 for division
  cout<<"Please enter a double: ";
  cin>>x2;//double 1
  do
  {
    cout<<"Please enter a non-zero double: ";
    cin>>y2;//double 2
  }while(y2==0);//prevent from being 0 for division
  cout<<"----Integer Math----"<<endl;
  intMath.checkVal(x1,y1);
  intMath.multiply(x1,y1);
  intMath.add(x1,y1);
  intMath.divide(x1,y1);
  cout<<"Cost: "<<intMath.get_cost()+doubleMath.get_cost()<<endl;
  cout<<"----Double Math----"<<endl;
  doubleMath.checkVal(x2,y2);
  doubleMath.multiply(x2,y2);
  doubleMath.add(x2,y2);
  doubleMath.divide(x2,y2);
  cout<<"Cost: "<<intMath.get_cost()+doubleMath.get_cost()<<endl;
  cout<<"Thank you, goodbye! :)"<<endl;//sign-off
  return 0;
}

template <class T_Type>
T_Type TempClass<T_Type>::checkVal(T_Type x, T_Type y)
{
  cout<<"The greater value is: ";
  if(x>=y)//if x and y are equal, x is the "greater" value
    cout<<x<<endl;
  else
    cout<<y<<endl;
  cost+=COMP_COST;
  return x>=y?x:y;
}

template <class T_Type>
T_Type TempClass<T_Type>::multiply(T_Type x, T_Type y)
{
  cout<<"Multiplication: "<<x*y<<endl;
  cost+=MULT_COST;
  return x*y;
}

template <class T_Type>
T_Type TempClass<T_Type>::add(T_Type x, T_Type y)
{
  cout<<"Addition: "<<x+y<<endl;
  cost+=ADD_COST;
  return x+y;
}

template <class T_Type>
T_Type TempClass<T_Type>::divide(T_Type x, T_Type y)
{
  if(y==0)
    exit(0);//divide by 0 error, force exit
  else
    cout<<"Division: "<<x/y<<endl;
  cost+=DIV_COST;
  return x/y;
}
