//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  postfix.h          ASSIGNMENT #:  4            Grade: _________             *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  March 27, 2020                  *
//*                                                                                                   *
//*****************************************************************************************************

#ifndef POSTFIX_H
#define POSTFIX_H

using namespace std;

//character node used for list and stack
struct node
{
	//data
	char value;

	//next node
	node* next;
};

//int node used for istack
struct inode
{
	//data
	int value;

	//next node
	inode* next;
};

class list
{
public:
	list() { start = NULL; }	//default constructor
	void insert(node n);
	node removeFirst();
	bool isEmpty();
	void print(ostream& stream);
	int length();
private:
	node* start;
};

class stack
{
public:
	stack() { top = NULL; }	//default constructor
	void push(node n);
	node pop();
	char topNode();
	bool isEmpty();
	void print(ostream& stream);
private:
	node* top;
};

class istack
{
public:
	istack() { top = NULL; }	//default constructor
	void push(inode n);
	inode pop();
	bool isEmpty();
	void print(ostream& stream);
private:
	inode* top;
};

bool precedenceLTOET(char c1, char c2);

void printConversion(list infix, list postfix, stack s, ostream& stream, const int explen);

void printConversionHeader(ostream& stream, const int explen);

void printEvalutaion(list postfix, istack s, ostream& stream, const int explen);

void printEvaluationHeader(ostream& stream, const int explen);

void printAnswer(char expression[], int answer, ostream& stream);

void Header(ofstream& Outfile);

void Footer(ofstream& Outfile);

#endif POSTFIX_H
