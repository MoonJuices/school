//Programmer: LUCAS KEHOE	Date: 11/6/2018
//Class: CS1580			Section: D
//File: lab12.cpp
/*Purpose: This program is designed to give us experience using classes.
In this program, we create rectangles, set their length and width,
and overload the << operator to output rectangles to the screen.*/

#include <iostream>
using namespace std;

//Rectangle with Num, Length, and Width. Mutator and Accessor functions.
class rectangle
{
  private:
    int num;
    int length;
    int width;
  public:
    rectangle() : num(1), length(1), width (1) {}//default constructor
    rectangle(int n, int l, int w)//constructor
    {
      num = n;
      length = l;
      width = w;
    }
    int getLength();
    bool setLength(const int len);
    int getWidth();
    bool setWidth(const int wid);
    int getNum();
    bool setNum(const int n);
};

//Desc:	overload the << operator to print rectangles to the screen
//Pre:  rectangle must have valid values for num, length, and width (i.e. >0)
//Post:	prints area and num of rectangle to the screen
ostream &operator<<(ostream &stream, rectangle r);

//Desc: uses mutator functions to set values of rectangle
//Pre:	none (must be passed rectangle)
//Post:	VALID user set values for num, length, and width
void setRectangle(rectangle &r);

int main()
{
  rectangle rec1, rec2(2,4,6), rec3;
  cout<<"Welcome to the Rectangle lesson"<<endl;//greet
  cout<<rec1<<endl;
  cout<<rec2<<endl;
  setRectangle(rec3);
  cout<<rec3<<endl;
  cout<<"Thanks for your participation"<<endl;//sign-off
  return 0;
}

int rectangle::getLength()
{
  return length;
}

bool rectangle::setLength(const int len)
{
  length = len;
  return len>0;
}

int rectangle::getWidth()
{
  return width;
}

bool rectangle::setWidth(const int wid)
{
  width = wid;
  return wid>0;
}

int rectangle::getNum()
{
  return num;
}

bool rectangle::setNum(const int n)
{
  num = n;
  return n>0;
}

ostream &operator<<(ostream &stream, rectangle r)
{
  cout<<"Area of rectangle "<<r.getNum()<<" = "<<r.getLength()*r.getWidth();
  return stream;
}

void setRectangle(rectangle &r)
{
  int temp;
  do
  {
    cout<<"Please enter a number for rectangle: ";
    cin>>temp;
  }while(!r.setNum(temp));
  do
  {
    cout<<"Please enter a length for rectangle: ";
    cin>>temp;
  }while(!r.setLength(temp));
  do
  {
    cout<<"Please enter a width for rectangle: ";
    cin>>temp;
  }while(!r.setWidth(temp));
  return;
}
