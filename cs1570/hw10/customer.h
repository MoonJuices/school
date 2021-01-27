//Programmer: LUCAS KEHOE & JON CLARK	Date: 12/4/2018
//Class: CS1570			Section: A & E
//File: customer.h
/*Purpose: contains class customer and associated constants*/

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "burger.h"
#include "burgermeister.h"
#include <iostream>
using namespace std;
//PARTICIPANTS
const int PARTICIPANTS = 15;
//PI
const float PI = 3.14159265359;
//CUSTOMER
const int CUSTOMER_NAME_LEN = 100;
const int MAX_MONEY = 75;
const int MIN_MONEY = 25;
const int MAX_WEIGHT = 250;
const int MIN_WEIGHT = 90;
const int MAX_CHOLESTEROL = 300;
const int MIN_CHOLESTEROL = 30;
const int MAX_HEALTH = 100;
const int MIN_HEALTH = 1;
const float CHEESE_WEIGHT = 1.2;
const float SAUCE_WEIGHT = 2.1;

const int LOSE_HEALTH = 2;//eating burger
const int GAIN_HEALTH = 2;//throwing burger
const float PUKE_HEALTH = 0.5;//percent health for puke
const int MAX_CHOLESTEROL_KILL = 300;
const int MAX_WEIGHT_GAIN_KILL = 80;
const int PERCENT_PUKE = 50;
const int PERCENT_TOSS1 = 70;
const int PERCENT_TOSS2 = 80;
//PUKE OATH
const int NUM_PUKE_OATH = 4;
const string puke_oath[NUM_PUKE_OATH]={"AAAHHHHHH........BLAHHH!","BLURP!","GLRFMP!","GAGGG!"};

class customer
{
private:
	char m_c_name[CUSTOMER_NAME_LEN];
	float m_money;
	int m_weight;
	int m_initial_weight;
	short m_cholesterol;
	bool m_isAlive;
	int m_health;
	bool m_qualified;
	bool m_puke;
	bool m_isDone;
	int m_burgersEaten;
public:
	//Desc: generates customer with randomly generated values for
	//      money, weight, cholesterol in the respective ranges
	//      name is taken from list, and customer is always initially alive
	customer();//default constructor

	//Desc: changes customers money, weight, and cholesterol based on
	//      burger passed to function
	//Pre:  customer (CALLING OBJECT)  must be alive
	//Post: changes customers private members based on burger
	void eat(const burger & b, burgermeister & bm);

	//Desc: if the customer is alive, they puke and decrement the passed
	//		burgermeisters money by constant value. if customer is dead
	//		they do not puke.
	//Pre:	customer m_isAlive value must be set
	//Post:	customer puked and burgermeisters money is decremented or
	//		customer did not puke
	void puke(burgermeister & bm);
	
	//Desc: customer throws a burger at another customer in the array
	//		or burgermeister. if the customer has enough money and is alive they throw.
	//		their money is decremented by the price of the burger and
	//		their health is incremented. if the customer hits burgermeister they
	//		are disqualified and the burgermeister takes all their money. if a customer
	//		is hit, the hit customer has a percent chance to throw. if customer is dead,
	//		they do not throw.
	//Pre:	array of customers must be defined,
	//		and burgermesiter must be defined.
	//Post: customer threw burger at random target if they were alive
	//		or didn't throw if they were not alive. the hit customer then
	//		had a chance to also throw
	void toss(customer c[], burgermeister & bm);

	//Desc: returns value requested
	//Pre:  none
	//Post: returned the value
	bool getPuke() { return m_puke; }
	bool getIsAlive() { return m_isAlive; }
	bool getIsDone() { return m_isDone; }
	bool getQualified() { return m_qualified; }
	int getBurgersEaten() {return m_burgersEaten;}

	//Desc: prints the customers name to screen
	//Pre:	none
	//Post:	printed the customers name
	void sayName();

	//Desc: sets customers m_puke value to false
	//Pre:	none
	//Post: customers m_puke value is false
	void resetPuke() { m_puke = false; return; }

	//Desc: returns difference in current and initial weight values
	//Pre:  none
	//Post: returned gained weight
	int getWeightGain() {return m_weight - m_initial_weight;}
	
	//Desc: simulates a round in burger eating contest. walks down array of 
	//		customers, feeding alive customers burgers with eat() function. if burger
	//		contains virulent pathogen, there is a chance that customer dies or 
	//		pukes with puke() function. if customer pukes then, walking down the
	//		array, there is a chance that the next customer can puke. if customer
	//		does not puke, there is a chance that the next customer starts a food
	//		fight with toss() function. Then, the function walks up the array doing
	// 		the same. Then the functions tests if all customers are done, m_isDone,
	//		if all customers are done, the function returns false, else returns true.
	//Pre:	array of customers must be defined,
	//		and burgermeister must be defined.
	//Post: round is simulated. every alive customer has eaten and all
	//		puking and food fighting has taken place. function returned true
	//		if all customers were done, or returned false if customers were
	//		not done
	friend bool c_round(customer c[], burgermeister & bm);
    
	//Desc: tests for winner of contest.
	//		first, tests if there is anyone alive.
	//		if 1 alive, that customer is winner.
	//		if 0 alive, no customer is winner.
	//		if more than 1 alive, continue to second win condition.
	//		second, tests if there is a customer that has eaten the most burgers
	//		if there is a customer that has eaten more than anyone else,
	//		that customer is winner
	//		if there is a tie, continue to third win condition
	//		third, tests if there is a customer that has gained the most weight
	//		if there is a customer that has gained the most weight, they are winner
	//		if there is another tie, arbitrarily picks last customer
	//		in array with highest weight gain as winner
	//		prints winner (or no winner) to screen and reason why (if needed)
	//Pre:	array of customers must be defined
	//Post:	tested win conditions and printed winner to screen
	friend void c_win(customer c[]);

	//Desc: overloads the insertion operator for class customer
	//Pre:  stream must be open
	//Post: overloaded instertion operator
	friend ostream & operator<<(ostream & o, const customer & c);
};

#endif
