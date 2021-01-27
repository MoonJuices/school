//Programmer: LUCAS KEHOE	Date: 11/27/2018
//Class: CS1580			Section: D
//File: lab14.h
/*Purpose: This is the .h file to go with main.cpp*/
#ifndef LAB14HEADER
#define LAB14HEADER

#include <iostream>

using namespace std;

//GLOBAL CONSTATNS
const int SAVE100 = 100;
const float STUDENTRATE = 0.8;
const float SAVE30P = 0.7;

namespace CppShop
{
  enum Items{TURKEY=111, BEER=112, COMPUTER=113, BOOK=114};
  enum Coupons{SAVE100OFF500,FREETURKEY,SUPER30,BOGOFREE};
  
  class Product
  {
    private:
      long itemID;
      float unitPrice;
      bool ableForBOGO;

    public:
      //Desc: construct product
      //Pre:  none
      //Post: constructs product
      Product(long itemID, float unitPrice, bool ableForBOGO = false);
      
      //Desc: returns value
      //Pre:  values must contain data
      //Post: returns the value
      float getPrice(){return unitPrice;}
      long getID(){return itemID;}
      bool getBOGO(){return ableForBOGO;}
  };

  class ShoppingCart
  {
    private:
      static long userID;
      static bool isStudent;
      float originalPrice;
      float finalPrice;

    public:
      //Desc: construct shoppingcart
      //Pre:  none
      //Post: constructs shoppingcart
      ShoppingCart();

      //Desc: returns value
      //Pre:  values must contain data
      //Post:  returns the value
      long getID(){return userID;}
       
      //Desc: sets id and bool if they are student
      //Pre:  must be passed non-negative long and bool (none)
      //Post: sets id and ifstudent
      void signup(long id, bool student);

      //Desc: calculates original/final price based on passed values
      //Pre:  none
      //Post: calculates original/final price based on the passed values
      void addToCart(Product & item, int number, Coupons coupon);
      
      //Desc: calculates the final price based on coupon and if student
      //Pre: none
      //Post: calculates the final price based on the coupon and student val
      void checkOut(Coupons coupon);

      //Desc: returns value
      //Pre:  values must contain data
      //Post: returns the value
      float getOriginalPrice(){return originalPrice;}
      float getFinalPrice(){return finalPrice;}
  };
}

#include "lab14.hpp"
#endif
