//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  customerq.h                  ASSIGNMENT #:  3            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  March 6, 2020                   *
//*                                                                                                   *
//*****************************************************************************************************

#ifndef CUSTOMERQ_H
#define CUSTOMERQ_H

using namespace std;

//constant used by customer node
const int NAME_LEN = 20;

struct customer
{
	//customer data
	char first_name[NAME_LEN];
	char last_name[NAME_LEN];
	int arrival_time;
	int processing_time;

	//next customer
	customer* next;
};

class customerqueue
{
public:
	customerqueue();	//default constructor
	void push(customer c);
	customer pop();
	customer process();
	int getwait();
	bool isempty();
private:
	customer* front;
	customer* rear;
};

class customerlist
{
public:
	customerlist();		//default constructor
	void insert(customer c);
	customer arrive(int arrival_t);
	void printlist(ostream& stream);
	friend void printarrivaldeparture(customerlist& arrival, customerlist& departure, ostream& stream);
private:
	customer* start;
};

void Header(ofstream& Outfile);

void Footer(ofstream& Outfile);

#endif CUSTOMERQ_H
