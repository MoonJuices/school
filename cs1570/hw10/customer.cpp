//Programmer: LUCAS KEHOE & JON CLARK	Date: 12/4/2018
//Class: CS1570			Section: A & E
//File: customer.cpp
/*Purpose: contains member functions for class customer*/

#include "customer.h"
#include "burger.h"
#include "burgermeister.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

customer::customer()
{
	//name
	static int counter = 0;
	ifstream in;
	int i_money;//dollars
	in.open("simpson_names.dat");
	for (int i = 0; i <= counter; i++)
		in.getline(m_c_name, CUSTOMER_NAME_LEN - 1, '\n');
	counter++;
	in.close();
	//money
	i_money = rand() % (MAX_MONEY - MIN_MONEY + 1) + MIN_MONEY;//dollars
	if (i_money != MAX_MONEY)
		m_money = i_money + (0.01 * static_cast<float>(rand() % 101));//change
	else
		m_money = i_money;
	//weight
	m_weight = rand() % (MAX_WEIGHT - MIN_WEIGHT + 1) + MIN_WEIGHT;
	m_initial_weight = m_weight;
	//isAlive
	m_isAlive = true;
	//cholesterol
	m_cholesterol = rand() % (MAX_CHOLESTEROL - MIN_CHOLESTEROL + 1)
		+ MIN_CHOLESTEROL;
	//health
	m_health = rand() % (MAX_HEALTH - MIN_HEALTH + 1) + MIN_HEALTH;
	
	m_qualified = true;
	m_puke = false;
	m_isDone = false;
	m_burgersEaten = 0;
}

void customer::eat(const burger & b, burgermeister & bm)
{
	//if alive and has money and is qualified
	if (m_isAlive == true && m_money >= b.get_price() && m_qualified == true)
	{
		cout << m_c_name << " ate the ";
		b.print_burger_name();
		cout << "." << endl;
		m_money -= b.get_price();
		bm += b.get_price();
		m_burgersEaten++;
		m_health -= LOSE_HEALTH;
		m_cholesterol += 2.5 * b.get_bacon() + (PI / 2.0) * b.get_patties()
			+ m_weight / ((b.get_pickles() + 1) * 10.0);//cholesterol equation
		//cholesterol kill
		if (m_cholesterol > MAX_CHOLESTEROL_KILL)
		{
			m_isAlive = false;
			m_qualified = false;
			m_isDone = true;
			bm -= BM_DEAD_C;
			cout << m_c_name << " experienced a heart attack and is        DEAD." << endl;
		}
		m_weight += 14 + 0.5*pow(b.get_patties(), 2) + (1.0 / 8.0)*pow(b.get_bacon(), 2)
			- b.get_pickles() / 4.0 + b.get_cheese()*CHEESE_WEIGHT
			+ b.get_sauce()*SAUCE_WEIGHT;//weight equation
		//weight gain kill
		if (m_weight - m_initial_weight > MAX_WEIGHT_GAIN_KILL && m_isAlive == true)
		{
			m_isAlive = false;
			m_qualified = false;
			m_isDone = true;
			bm -= BM_DEAD_C;
			cout << m_c_name << " burst and is DEAD...........POPP!!!!" << endl;
		}
		//health <0 kill
		if (m_health <= 0 && m_isAlive == true)
		{
			m_isAlive = false;
			m_qualified = false;
			m_isDone = true;
			bm -= BM_DEAD_C;
			cout << m_c_name << " health was reduced to 0 and is          DEAD." << endl;
		}
		//burger has pathogen
		if (b.get_pathogen() == true && m_isAlive == true)
		{
			if ((rand() % 101 + 1) > m_health)//burger kill		
			{
				m_isAlive = false;
				m_qualified = false;
				m_isDone = true;
				bm -= BM_DEAD_C;
				cout << m_c_name << " consumed an unusually tainted burger and is          DEAD." << endl;
			}
			else//puke
			{
				m_health = m_health * PUKE_HEALTH;
				//health <0 kill - int division
				if(m_health <= 0)
				{
					m_isAlive = false;
					m_qualified = false;
					m_isDone = true;
					bm -= BM_DEAD_C;
					cout << "\t" << m_c_name << " health was reduced to 0 and is        DEAD." << endl;
				}
				m_puke = true;
			}
		}
	}
	else if (m_isAlive == false)//dead
//		cout << m_c_name << " is DEAD. They can not eat." << endl;
;	else if (m_qualified == false)//disqualified
//		cout << m_c_name << " is disqualified." << endl;
;	else//not enough money
	{
		m_isDone = true;
		cout << m_c_name << " can not afford this burger." << endl;
	}
	return;
}

void customer::puke(burgermeister & bm)
{
	if (m_isAlive)//alive
	{
		bm -= BM_PUKE_C;
		cout << "\t" << m_c_name << " puked! " << puke_oath[rand()%NUM_PUKE_OATH]<<endl;
	}
	else//dead
		cout << "\t" << m_c_name << " is DEAD. They can not puke."<<endl;
	return;
}

void customer::toss(customer c[], burgermeister & bm)
{
	burger b;
	int target = 0;
	//if is alive and has enough money
	if (m_money >= b.get_price() && m_isAlive == true)
	{
		m_money -= b.get_price();
		bm += b.get_price();
		m_health += GAIN_HEALTH;
		target = rand() % (PARTICIPANTS + 1);
		if (target == PARTICIPANTS)//hit burgermeister
		{
			cout << "\t\t" << m_c_name << " tosses ";
			b.print_burger_name();
			cout << " at ";
			bm.sayName();
			cout << endl;
			bm += m_money;
			cout << "\t\t"; 
			bm.sayName();
			cout << " stole $" << m_money << " from " << m_c_name << endl;
			m_qualified = false;
			m_isDone = true;
			m_money = 0;
		}
		else//hit other customer
		{
			cout << "\t\t" << m_c_name << " tosses ";
			b.print_burger_name();
			cout << " at ";
			c[target].sayName();
			cout << endl;
			//if chance and is alive they throw
			if ((rand() % 100 + 1) <= PERCENT_TOSS2 && c[target].getIsAlive())
				c[target].toss(c, bm);
			else//does not throw
			{
				cout << "\t\t";
				c[target].sayName();
				cout << " did not throw."<<endl;
			}
		}
	}
	//does not throw
	else
		cout << "\t\t" << m_c_name << " did not throw."<<endl;
	return;
}

void customer::sayName()
{
	cout << m_c_name;
	return;
}

bool c_round(customer c[], burgermeister & bm)
{
	static int round = 1;//counter
	int up_ctr = 0, dwn_ctr = 0;//counter
	burger b[PARTICIPANTS];
	bool contestOver = false;
	bool breakLoop = false;
	cout << "\n---------- ROUND #" << round << " ----------\n\n" << endl;

		for (int i = 0; i < PARTICIPANTS; i++)
		{
			c[i].eat(b[i], bm);//eat
			if (c[i].getPuke())
			{
				c[i].puke(bm);
				up_ctr++;//increment
				//if chance and not walk off array
				while ((rand() % 100 + 1) <= PERCENT_PUKE && i + up_ctr < PARTICIPANTS && !breakLoop)
				{
					if (c[i + up_ctr].getIsAlive() == false)
						breakLoop = true;
					else
					{
						c[i + up_ctr].puke(bm);
						up_ctr++;//increment
					}
				}
				if (i+up_ctr < PARTICIPANTS)
				{
					cout << "\t";
					c[i+up_ctr].sayName();
					cout << " did not puke."<<endl;
				}
				//if chance and not walk off array
				if ((rand() % 100 + 1) <= PERCENT_TOSS1 && i + up_ctr < PARTICIPANTS)
				{
					c[i + up_ctr].toss(c, bm);
				}
				else if (i+up_ctr < PARTICIPANTS)
				{
					cout << "\t\t";
					c[i+up_ctr].sayName();
					cout << " did not throw."<<endl;
				}
				up_ctr = 0;//reset
				breakLoop = false;
				dwn_ctr--;//decrement
				//if chance and not walk off array
				while ((rand() % 100 + 1) <= PERCENT_PUKE && i + dwn_ctr >= 0 && !breakLoop)
				{
					if (c[i + dwn_ctr].getIsAlive() == false)
						breakLoop = true;
					else
					{
						c[i + dwn_ctr].puke(bm);
						dwn_ctr--;//decrement
					}
				}
				if (i+dwn_ctr >= 0)
				{
					cout << "\t";
					c[i+dwn_ctr].sayName();
					cout << " did not puke."<<endl;
				}
				//if chance and not walk off array
				if ((rand() % 100 + 1) <= PERCENT_TOSS1 && i + dwn_ctr >= 0)
				{
					c[i + dwn_ctr].toss(c, bm);
				}
				else if (i+dwn_ctr >= 0)
				{
					cout << "\t\t";
					c[i+dwn_ctr].sayName();
					cout << " did not throw."<<endl;
				}
				dwn_ctr = 0;//reset
				breakLoop = false;
				for (int i = 0; i < PARTICIPANTS; i++)
					c[i].resetPuke();//reset all puke
			}
		}
		//output burgermeisters moneys
		cout << "\nKrusty Kurrency: $" << bm.getMoney()<<"."<<endl;
		contestOver = true;//assume true
		for (int i = 0; i < PARTICIPANTS; i++)
		{
			if (c[i].getIsDone() == false)//unless customer is not done
				contestOver = false;
		}
		round++;//increment round ctr
	//return true if contest is not over
	//return false if contest is over
	return !contestOver;
}

void c_win(customer c[])
{
	int potentialWinners = 0;
	int tempHighBurgerEaten = 0, tempHighWeightGain = 0;
	int customerHighBurger = 0, customerHighWeightGain = 0;//index

	cout << "Everyone stopped eating! The contest is over!" << endl;
	
	for (int i = 0; i < PARTICIPANTS; i++)
	{
		if (c[i].getIsAlive() == true && c[i].getQualified() == true)
		{
			potentialWinners++;//increment
		}
	}
	
	switch(potentialWinners)
	{
		case 1://one winner
			for (int i = 0; i < PARTICIPANTS; i++)
			{
				if (c[i].getIsAlive() == true && c[i].getQualified() == true)
				{
cout<<"\n**************************";
					c[i].sayName();
					cout << " is your 2018 Krusty Burger Eating Contest Champion!"<<endl;
				}
			}
			break;
		case 0://no winner
			cout << "Unfortunately, there are no winners in this contest!"<<endl;
			break;
		default://more than one winner
			potentialWinners = 1;
			for (int i = 0; i < PARTICIPANTS; i++)
			{
				if (c[i].getIsAlive() == true && c[i].getQualified() == true)
				{
					if(c[i].getBurgersEaten()>=tempHighBurgerEaten)
					{
						customerHighBurger = i;
						if(c[i].getBurgersEaten()==tempHighBurgerEaten)
						{
							potentialWinners++;//increment
						}
						tempHighBurgerEaten = c[i].getBurgersEaten();
					}
				}
			}
			switch(potentialWinners)
			{
				case 1://one winner
				cout<<"\n**************************";
					c[customerHighBurger].sayName();
					cout<< " is your 2018 Krusty Burger Eating Contest Champion! They ate the most burgers!"<<endl;
					break;
				default://more than one winner
					for(int i = 0; i < PARTICIPANTS; i++)
					{
						if (c[i].getIsAlive() == true && c[i].getQualified() == true)
						{
							if(c[i].getWeightGain()>=tempHighWeightGain)
							{
								customerHighWeightGain = i;
							}
						}
					}
cout<<"\n**************************";	c[customerHighWeightGain].sayName();
					cout << " is your 2018 Krusty Burger Eating Contest Champion! They gained the most weight!"<<endl;
			}
	}
	cout << "Thank you to all our wonderful participants! We hope to see you next year!" << endl;
	return;
}

ostream & operator<<(ostream & o, const customer & c)
{
	cout << c.m_c_name << " weighs " << c.m_weight << " lbs, has $" << c.m_money;
	cout << ", " << c.m_cholesterol << " IBU, and is ";
	if (c.m_isAlive == true)
		cout << "ALIVE." << endl;
	else
		cout << "DEAD." << endl;
	return o;
}
