//Programmer: LUCAS KEHOE	Date: 11/27/2108
//Class: CS1580			Section: D
//File: lab14.hpp
/*Purpose: This is the .hpp file to go with main.cpp*/

CppShop :: Product :: Product(long ID, float price, bool BOGO)
{
  itemID=ID;
  unitPrice = price;
  ableForBOGO = BOGO;
}

CppShop::ShoppingCart::ShoppingCart(){originalPrice=0; finalPrice=0;}

void CppShop::ShoppingCart::signup(long id, bool student)
{
  userID = id;
  isStudent = student;
  return;
}

void CppShop::ShoppingCart::addToCart(Product & item, int number,
Coupons coupon)
{
  int temp = 0;
  originalPrice += item.getPrice()*number;
  if(coupon == FREETURKEY&&item.getID() == TURKEY)
  {
    temp = number-1;//one free turkey -1
    finalPrice += item.getPrice()*temp;
  }
  if(coupon == BOGOFREE&&item.getBOGO())
  {
    temp = number/2+number%2;
    finalPrice += item.getPrice()*temp;
  }
  if(coupon == SUPER30)
  {
    finalPrice += SAVE30P*item.getPrice()*number;
  }
  
  return;
}

void CppShop::ShoppingCart::checkOut(Coupons coupon)
{
  if(isStudent == true)
  {
    finalPrice = STUDENTRATE*finalPrice;
  }
  if(coupon == SAVE100OFF500&&finalPrice>=500)
  {
    finalPrice -= SAVE100;
  }
  return;
}
