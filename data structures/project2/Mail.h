//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Mail.h          ASSIGNMENT #:  2            Grade: _________                *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  February 21, 2020               *
//*                                                                                                   *
//*****************************************************************************************************

#ifndef MAIL_H
#define MAIL_H

#include <string>

using namespace std;

//constants used by mail_node struct
const int FIRST_NAME_LEN = 12;
const int LAST_NAME_LEN = 12;
const int STREET_ADDRESS_LEN = 20;
const int CITY_LEN = 12;
const int STATE_LEN = 2;
const int ZIP_CODE_LEN = 5;

struct mail_node
{
	//data
	char first_name[FIRST_NAME_LEN];
	char last_name[LAST_NAME_LEN];
	char street_adress[STREET_ADDRESS_LEN];
	char city[CITY_LEN];
	char state[STATE_LEN];
	char zip_code[ZIP_CODE_LEN];

	//linked list
	mail_node* next;
};

class mail_list
{
public:
	mail_list();	//default constructor
	void insertnode(mail_node node, ofstream& outfile);
	mail_node deletenode(mail_node node);
	void changenode(mail_node node, int field_number, string new_value, ofstream& outfile);
	void printlist(ostream& stream);
private:
	mail_node* start_ptr;
};

void Header(ofstream& Outfile);

void Footer(ofstream& Outfile);

#endif MAIL_H
