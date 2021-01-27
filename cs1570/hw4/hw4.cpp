//Programmer: LUCAS KEHOE	Date:9/19/2018
//Class: CS1570			Section: A
//File: hw4.cpp
/*Purpose: The purpose of this program is to help the user understand
numbering systems in different bases. This program uses a menu system
to ask the user to input a non-negative integer "x" and a base "n."
This program can then determine if the integer x is a valid base-n
number and can also output the number x base-n in base-10.*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  //variable declaration
  //constants
  const int quit = 5, num_try = 3;//num_try = attempts for case 1, case 2
  //range for x and n
  const int  min_x = 0, max_x = 99999, min_n = 2, max_n = 10;
  //variables
  int option = 0, x = 0, temp_x = 0, n = 0;//x=non-neg int, n=base
  int base10_4=0, base10_3=0, base10_2=0, base10_1=0, base10_0=0;
  int i = 0;//counter
  bool x_base_n = false;//is x base-n?
  //prompt user
  cout<<"--------------------NUMBERING SYSTEMS-------------------"<<endl;
  cout<<"This program is designed to help you understand numbering";
  cout<<" systems!"<<endl;
  cout<<"Let's get started! :)"<<endl;
  do
  {
    //menu
    cout<<endl;
    cout<<"1.  Enter a non-negative integer, x [5-digit or less]"<<endl;
    cout<<"2.  Enter an integer base, n  [ 2 <= n < 10 ]"<<endl;
    cout<<"3.  Verify x is a valid base-n number"<<endl;
    cout<<"4.  Convert x base-n to base-10"<<endl;
    cout<<"5.  Quit"<<endl;
    cout<<"Choose [1-5]: ";
    cin>>option;//input menu option
    switch(option)
    {
      case 1:
        i = 0;//initialize counter
        do
        {
          cout<<"Enter a non-negative integer, x [5-digits or less]"<<endl;
          cout<<"x = ";
          cin>>x;//input x
          if(x<min_x||x>max_x)//if x is out of bounds
            cout<<"Invalid input. Attempts remaining: "<<num_try-(i+1)<<endl;
          i += 1;//increment counter
          //exit do-while if x is in bounds or num_try is reached
        }while((x<min_x&&i<num_try)||(x>max_x&&i<num_try));
        break;
      case 2:
        i = 0;//initialize counter
        do
        {
          cout<<"Enter an integer base, n [2 <= n < 10]"<<endl;
          cout<<"n = ";
          cin>>n;//input n
          if(n<min_n||n>=max_n)//if n is out of bounds
            cout<<"Invalid input. Attempts remaining: "<<num_try-(i+1)<<endl;
          i += 1;//increment counter
          //exit do-while if n is in bounds or num_try is reached
        }while((n<min_n&&i<num_try)||(n>=max_n&&i<num_try));
        break;
      case 3:
        //check to make sure x and n are in bounds
        if(x>=min_x&&x<=max_x&&n>=min_n&&n<max_n)
        {
          //DECIPHER DIGITS OF x
          temp_x = x;

          base10_4 = temp_x/pow(10,4);
          temp_x=temp_x-base10_4*pow(10,4);

          base10_3 = temp_x/pow(10,3);
          temp_x=temp_x-base10_3*pow(10,3);

          base10_2 = temp_x/pow(10,2);
          temp_x=temp_x-base10_2*pow(10,2);

          base10_1 = temp_x/pow(10,1);
          temp_x=temp_x-base10_1*pow(10,1);

          base10_0 = temp_x/pow(10,0);
          temp_x=temp_x-base10_0*pow(10,0);
          //END DECIPHER DIGITS
          //if each digit of x is less than n
          if(base10_4<n&&base10_3<n&&base10_2<n&&base10_1<n&&base10_0<n)
          {
            //x is base n
            x_base_n = true;
            cout<<x<<" is a valid base-"<<n<<" number."<<endl;
          }
          else
          {
            //x is not base n
            x_base_n = false;
            cout<<x<<" is not a valid base-"<<n<<" number."<<endl;
          }
        }
        //x or n are not in bounds  
        else
          cout<<"ERROR: Invalid \'x\' or Invalid \'n\'."<<endl;
        break;
      case 4:
        //check to make sure x and n are in bounds
        if(x>=min_x&&x<=max_x&&n>=min_n&&n<max_n)
        {
          //DECIPHER DIGITS OF x
          temp_x = x;

          base10_4 = temp_x/pow(10,4);
          temp_x=temp_x-base10_4*pow(10,4);

          base10_3 = temp_x/pow(10,3);
          temp_x=temp_x-base10_3*pow(10,3);

          base10_2 = temp_x/pow(10,2);
          temp_x=temp_x-base10_2*pow(10,2);

          base10_1 = temp_x/pow(10,1);
          temp_x=temp_x-base10_1*pow(10,1);

          base10_0 = temp_x/pow(10,0);
          temp_x=temp_x-base10_0*pow(10,0);
          //END DECIPHER DIGITS
          //if each digit of x is less than n
          if(base10_4<n&&base10_3<n&&base10_2<n&&base10_1<n&&base10_0<n)
            //x is base n
            x_base_n = true;
          else
            //x is not base n
            x_base_n = false;
          //if x is base n
          if(x_base_n==true)
          {
            cout<<x<<" base-"<<n<<" = ";
            //n^4
            if(base10_4==0)
              cout<<"";
            else
              cout<<base10_4<<"*"<<n<<"^4";
            if(base10_4!=0&&
            (base10_3!=0||base10_2!=0||base10_1!=0||base10_0!=0))
              cout<<" + ";
            //n^3
            if(base10_3==0)
              cout<<"";
            else
              cout<<base10_3<<"*"<<n<<"^3";
            if(base10_3!=0&&(base10_2!=0||base10_1!=0||base10_0!=0))
              cout<<" + ";
            //n^2
            if(base10_2==0)
              cout<<"";
            else
              cout<<base10_2<<"*"<<n<<"^2";
            if(base10_2!=0&&(base10_1!=0||base10_0!=0))
              cout<<" + ";
            //n^1
            if(base10_1==0)
              cout<<"";
            else
              cout<<base10_1<<"*"<<n<<"^1";
            if(base10_1!=0&&(base10_0!=0))
              cout<<" + ";
            //n^0
            if(base10_0==0)
              cout<<"";
            else
              cout<<base10_0<<"*"<<n<<"^0";
            //output the x base-n equivalent of base-10
            cout<<" = "<<base10_4*pow(n,4)+base10_3*pow(n,3)
            +base10_2*pow(n,2)+base10_1*pow(n,1)+base10_0*pow(n,0)
            <<" base-10."<<endl;
          }
          //x is not base n
          else
            cout<<x<<" is not a valid base-"<<n<<" number."<<endl;
        }
        //x or n are not in bounds  
        else
          cout<<"ERROR: Invalid \'x\' or Invalid \'n\'."<<endl;
        break;
      case 5:
        //case 5 is quit
        break;
      default:
        //failed to enter [1-5]
        cout<<"Invalid input. Try again!"<<endl;
    }
  }while(option!=quit);//if user enter quit, exit loop
  //sign-off message
  cout<<"Terminating Program!"<<endl;
  cout<<"Thank you, have a nice day! :)"<<endl;
  return 0;
}
