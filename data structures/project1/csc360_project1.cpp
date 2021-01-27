//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  csc360_project1.cpp          ASSIGNMENT #:  1            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  February 5, 2020                *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program is designed to read passenger information from a data sheet and assign    *
//*   the passengers a seat on their designated flights. If no seat can be found for the passenger    *
//*   then the passenger is placed on a waiting list. After the program has finished reading in all   *
//*   the passegers, the flight information is then printed out to a file, with seating charts and    *
//*   waiting list.                                                                                   *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include "Flight.h"

using namespace std;

//constants used in main
const int NFLIGHT = 8;
const int DELIM = -999;
const string INFILE = "data1.txt";
const string OUTFILE = "output.txt";

int main()
{
	//construct flights
	flight flight_list[NFLIGHT] = {
		{1010, "Memphis, Tennessee", "Jackson, Mississippi"},
		{1015, "Jackson, Mississippi", "Memphis, Tennessee"},
		{1020, "Little Rock, Arkansas", "Jackson, Mississippi"},
		{1025, "Jackson, Mississippi", "Little Rock, Arkansas"},
		{1030, "Stevenport, Louisiana", "Jackson, Mississippi"},
		{1035, "Jackson, Mississippi", "Stevenport, Louisiana"},
		{1040, "Huntsville, Alabama", "Jackson, Mississippi"},
		{1045, "Jackson, Mississippi", "Huntsville, Alabama"}
	};

	//passenger information
	int boarding_number = 0;
	int flight_number = 0;
	int seat_row = 0;
	int seat_col = 0;
	char section = '\0';
	char seat_col_c = '\0';

	bool quit = false;

	//open files
	ifstream ifile(INFILE);
	ofstream ofile(OUTFILE);

	Header(ofile);

	if (ifile.fail()) //if fail to open data file
	{
		cout << "File not found!" << endl;
		ofile << "File not found!" << endl;
	}
	else
	{
		do
		{
			//read boarding number from data file
			ifile >> boarding_number;

			if (boarding_number == DELIM) //if delimiter, then quit
			{
				quit = true;
			}
			else
			{
				//read flight number, section, seat row, and seat column from data file
				ifile >> flight_number >> section >> seat_row >> seat_col_c;

				//assign array value for seat column
				switch (seat_col_c)
				{
				case 'L':
					seat_col = 0;
					break;
				case 'M':
					seat_col = 1;
					break;
				case 'R':
					seat_col = 2;
					break;
				default:
					seat_col = -1; //default give invalid value for seat column
				}

				//assign array value for seat row
				seat_row = seat_row - 1;

				//attempt to seat passenger on flights
				for (int i = 0; i < NFLIGHT; i++)
				{
					flight_list[i].seat(boarding_number, flight_number, section, seat_row, seat_col);
				}
			}
		} while (quit == false);

		//print flights to stream cout and ofile
		for (int i = 0; i < NFLIGHT; i++)
		{
			flight_list[i].print_flight(cout);
			flight_list[i].print_flight(ofile);
		}
	}

	Footer(ofile);

	//close files
	ifile.close();
	ofile.close();

	cout << endl << "END OF PROGRAM OUTPUT" << endl;

	return 0;
}
