//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Flight.cpp                   ASSIGNMENT #:  1            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  February 5, 2020                *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Flight.h"

using namespace std;

//******************** FLIGHT CONSTRUCTOR ********************
flight::flight(int num, string to, string from)
{
	//Recieves - flight number, flight to, and flight from
	//Task - construct flight
	//Returns - nothing

	flight_num = num;
	flight_to = to;
	flight_from = from;

	//fill seating chart with empty seats
	for (int i = 0; i < NCOL; i++)
	{
		for (int j = 0; j < NROW; j++)
		{
			seating_chart[i][j] = EMPTY;
		}
	}

	//fill waiting list with empty seats
	for (int i = 0; i < WAIT_LIST_LEN; i++)
	{
		waiting_list[i] = EMPTY;
	}
}

//******************** FLIGHT DEFAULT CONSTRUCTOR ********************
flight::flight()
{
	//Recieves - nothing
	//Task - construct default flight
	//Returns - nothing

	flight_num = 0;
	flight_to = "";
	flight_from = "";

	//fill seating chart with empty seats
	for (int i = 0; i < NCOL; i++)
	{
		for (int j = 0; j < NROW; j++)
		{
			seating_chart[i][j] = EMPTY;
		}
	}

	//fill waiting list with empty seats
	for (int i = 0; i < WAIT_LIST_LEN; i++)
	{
		waiting_list[i] = EMPTY;
	}
}

//******************** GET FLIGHT NUMBER ********************
int flight::get_flight_num()
{ 
	//Recieves - nothing
	//Task - return flight number
	//Returns - flight number

	return flight_num;
}

//******************** GET SEATING LIST NUMBER ********************
int flight::get_seat(const int col, const int row) 
{ 
	//Recieves - some constant col and some constant row
	//Task - return seating chart number in col row
	//Returns - seating chart number in col row

	return seating_chart[col][row];
}

//******************** GET WAITING LIST NUMBER ********************
int flight::get_wait(const int n) 
{
	//Recieves - some constant n
	//Task - return nth value of waiting list
	//Returns - nth value of waiting list

	return waiting_list[n]; 
}

//******************** SET SEATING LIST NUMBER ********************
void flight::set_seat(const int col, const int row, const int boarding_number)
{
	//Recieves - some constant col, some constant row, and boarding number
	//Task - sets col and row of seating chart to boarding number
	//Returns - nothing

	//test if row and col are within bounds of seating chart
	if (col < NCOL && row < NROW)
	{
		seating_chart[col][row] = boarding_number;
	}

	return;
}

//******************** SET WAITING LIST NUMBER ********************
void flight::set_wait(const int n, const int boarding_number) 
{
	//Recieves - some constant n and boarding number
	//Task - sets nth waiting list to boarding number
	//Returns - nothing

	//test if n is within bounds of waiting list
	if (n < WAIT_LIST_LEN)
	{
		waiting_list[n] = boarding_number;
	}

	return;
}

//******************** SEATING/WAITING LIST FUNCTION ********************
void flight::seat(int boarding_number, int flight_number, char section, int seat_row, int seat_col)
{
	//Recieves - boarding number, flight number, section, seat row, and seat column for passenger
	//Task - attempts to seat passenger according to function, otherwise places passenger on waiting list
	//Returns - nothing

	bool seated = false;
	int i = 0, j = 0; //counters

	//test if seat col and seat row are within bounds, and test if flight number matches
	if (seat_col >= 0 && seat_col < NCOL && seat_row >= 0 && seat_row < NROW && flight_number == flight_num)
	{
		//if seat is empty, seat them
		if (seating_chart[seat_col][seat_row] == EMPTY && !seated)
		{
			seating_chart[seat_col][seat_row] = boarding_number;
			seated = true;
		}

		//attempt to seat them in the same row
		while (i < NCOL && !seated)
		{
			if (seating_chart[i][seat_row] == EMPTY && !seated)
			{
				seating_chart[i][seat_row] = boarding_number;
				seated = true;
			}
			i++;
		}
		i = 0;

		//attempt to seat them in the same column, respecting section
		if (section == FIRST_CLASS && !seated)
		{
			while (i < FIRST_CLASS_LEN && !seated)
			{
				if (seating_chart[seat_col][i] == EMPTY && !seated)
				{
					seating_chart[seat_col][i] = boarding_number;
					seated = true;
				}
				i++;
			}
			i = 0;
		}
		else if (section == COACH && !seated)
		{
			i = FIRST_CLASS_LEN;
			while (i < NROW && !seated)
			{
				if (seating_chart[seat_col][i] == EMPTY && !seated)
				{
					seating_chart[seat_col][i] = boarding_number;
					seated = true;
				}
				i++;
			}
			i = 0;
		}

		//attempt to seat them front to back, left to right, respecting section
		if (section == FIRST_CLASS && !seated)
		{
			while (i < FIRST_CLASS_LEN && !seated)
			{
				while (j < NCOL && !seated)
				{
					if (seating_chart[j][i] == EMPTY && !seated)
					{
						seating_chart[j][i] = boarding_number;
						seated = true;
					}
					j++;
				}
				j = 0;
				i++;
			}
			i = 0;
		}
		else if (section = COACH && !seated)
		{
			i = FIRST_CLASS_LEN;
			while (i < NROW && !seated)
			{
				while (j < NCOL && !seated)
				{
					if (seating_chart[j][i] == EMPTY && !seated)
					{
						seating_chart[j][i] = boarding_number;
						seated = true;
					}
					j++;
				}
				j = 0;
				i++;
			}
			i = 0;
		}

		//place passenger on waiting list :(
		while (i < WAIT_LIST_LEN && !seated)
		{
			if (waiting_list[i] == EMPTY && !seated)
			{
				waiting_list[i] = boarding_number;
				seated = true;
			}
			i++;
		}
		i = 0;
	}

	return;
}

//******************** PRINT FLIGHT ********************
void flight::print_flight(ostream& stream)
{
	//Recieves - the output stream
	//Task - prints the flight information, seating chart, and waiting list
	//Returns - nothing

	int ctr = 0; //counter

	stream << "----------------------------------------" << endl << endl;

	//print flight information
	stream << setw(40) << "Southern Comfort Airlines" << endl << endl;
	stream << "Flight " << flight_num;
	stream << setw(31) << "FROM: " << flight_from << endl;
	stream << setw(40) << "TO: " << flight_to << endl << endl;

	//print seating chart
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			stream << "     " << seating_chart[j][i];
		}
		stream << endl;
	}

	//print waiting list
	stream << endl << "WAITING LIST" << endl << endl << "     ";
	while (ctr < WAIT_LIST_LEN && waiting_list[ctr] != EMPTY)
	{
		stream << waiting_list[ctr] << "  ";
		if ((ctr + 1) % 10 == 0)
		{
			stream << endl << "     ";
		}
		ctr++;
	}
	ctr = 0;

	//print if waiting list is empty
	if (waiting_list[0] == EMPTY)
	{
		stream << "There is no waiting list for this flight.";
	}

	stream << endl << endl << "END OF SEATING CHART" << endl << endl;

	stream << "----------------------------------------" << endl;

	return;
}

//******************** FUNCTION HEADER ********************
void Header(ofstream& Outfile)
{
	//Recieves - the output file
	//Task - prints the output header
	//Returns - nothing

	Outfile << setw(30) << "Lucas Kehoe";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2020";
	Outfile << setw(20) << "Assignment #1" << endl;
	Outfile << setw(60) << "----------------------------------------" << endl;
	Outfile << setw(60) << "----------------------------------------" << endl << endl;
	
	return;
}

//******************** FUNCTION FOOTER ********************
void Footer(ofstream& Outfile)
{
	//Recieves - the output file
	//Task - prints the output footer
	//Returns - nothing

	Outfile << endl;   
	Outfile << setw(35) << "-------------------------" << endl; 
	Outfile << setw(35) << "| END OF PROGRAM OUTPUT |" << endl;   
	Outfile << setw(35) << "-------------------------" << endl;
	
	return;
}