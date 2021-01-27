//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Flight.h                     ASSIGNMENT #:  1            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  February 5, 2020                *
//*                                                                                                   *
//*****************************************************************************************************

#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

using namespace std;

//constants used by class flight
const int NCOL = 3;
const int NROW = 10;
const int WAIT_LIST_LEN = 50;
const int EMPTY = -999;
const int FIRST_CLASS_LEN = 3;
const char FIRST_CLASS = 'F';
const char COACH = 'C';

class flight
{
private:
	int flight_num;
	string flight_to;
	string flight_from;
	int seating_chart[NCOL][NROW];
	int waiting_list[WAIT_LIST_LEN];
public:
	flight(); //default constructor
	flight(int num, string to, string from); //constructor

	//accessors
	int get_flight_num();
	int get_seat(const int col, const int row);
	int get_wait(const int n);
	
	//manipulators
	void set_seat(const int col, const int row, const int boarding_number);
	void set_wait(const int n, const int boarding_number);
	void seat(int boarding_number, int flight_number, char section, int seat_row, int seat_col);
	void print_flight(ostream& stream);
};

void Header(ofstream& Outfile);

void Footer(ofstream& Outfile);

#endif FLIGHT_H