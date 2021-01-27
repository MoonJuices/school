//Programmer: LUCAS KEHOE	Date: 11/27/2018
//Class: CS1580			Section: D
//File: main.cpp
/*Purpose: The purpose if this program is to implement a very simple
shoppincart program.*/

#include "lab14.h"
using namespace CppShop;
long ShoppingCart :: userID= -1;
bool ShoppingCart :: isStudent = false;

int main()
{
  Product turkey(TURKEY, 100);
  Product beer(BEER, 20, true);
  Product computer(COMPUTER, 500);
  Product book(BOOK, 50, true);
  
  ShoppingCart myCart1;
  
  myCart1.signup(9527, true);
  myCart1.addToCart(turkey, 2, FREETURKEY);
  myCart1.addToCart(beer, 11, BOGOFREE);
  myCart1.addToCart(book, 2, BOGOFREE);
  myCart1.addToCart(computer, 2, SUPER30);
  myCart1.checkOut(SAVE100OFF500);

  cout<<"Hello, welcome to Shopmart! :)"<<endl;//greet
  cout<<"Successfully checked out:"<<endl;
  cout<<"Original price is: "<<myCart1.getOriginalPrice()<<endl;
  cout<<"You paid: "<<myCart1.getFinalPrice()<<endl;
  cout<<"You saved: "<<myCart1.getOriginalPrice()-myCart1.getFinalPrice();
  cout<<endl<<"Thank you for shopping with us!"<<endl;//sign-off
  
  ShoppingCart myCart2;
  cout<<"userID of myCart2 is: "<<myCart2.getID()<<endl;//check static
  return 0;
}


