//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  csc360_project3.cpp          ASSIGNMENT #:  3            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  March 6, 2020                   *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:  This program recieves a list of customers that have arrival times and processing      *
//*             times. The program then places the customers in queues, by arrival time. The          *
//*             customers pick the shortest line (by processing time). Only the customer at the       *
//*             front of the queue is processed. Once the customer at the front of the queue is       *
//*             fully processed, they leave the store and are recorded in the order in which they     *
//*             leave. The program outputs the list of customer names by which they arrive and        *
//*             when they leave.                                                                      *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include "customerq.h"

using namespace std;

//constants used in main
const int QUIT = -99;
const int NUM_LINES = 3;	//HOW MANY QUEUES ARE THERE?
const int CLOSING_TIME = 50;
const string INFILE = "data3.txt";
const string OUTFILE = "output.txt";

int main()
{
	//variables used for processing queues
	int time = 0;
	int shortest_line = 0;
	int shortest_wait = 0, shortest_wait_temp = 0;
	bool all_lines_empty = true;

	//lists of customers
	customerlist arrival;
	customerlist processing;
	customerlist departure;
	
	//queues of customers
	customerqueue line[NUM_LINES];
	
	//customer used for processing
	customer currentcustomer;
	
	ifstream infile(INFILE);
	ofstream outfile(OUTFILE);

	Header(outfile);

	//if fail to open data file
	if (infile.fail())
	{
		cout << "File not found!" << endl;
		outfile << "File not found!" << endl;
	}
	else
	{
		//retrieve data from file
		do
		{
			infile >> currentcustomer.arrival_time;

			if (currentcustomer.arrival_time != QUIT)
			{
				infile >> currentcustomer.first_name;
				infile >> currentcustomer.last_name;
				infile >> currentcustomer.processing_time;

				//insert customers into arrival/processing lists
				arrival.insert(currentcustomer);
				processing.insert(currentcustomer);
			}
		} while (currentcustomer.arrival_time != QUIT && !infile.eof());

		//while the lines aren't empty and not store closing time
		while (!all_lines_empty || time <= CLOSING_TIME)
		{
			//check if any customers arrive during this time
			do
			{
				//remove customer from list that arrive at this time
				currentcustomer = processing.arrive(time);

				//if a customer has arrived
				if (currentcustomer.arrival_time != -1)
				{
					//assume shortest line is first line
					shortest_line = 0;
					shortest_wait = line[0].getwait();

					//check wait time for rest of lines
					for (int i = 0; i < NUM_LINES; i++)
					{
						shortest_wait_temp = line[i].getwait();

						//if new line is shorter
						if (shortest_wait_temp < shortest_wait)
						{
							//that line becomes shortest line
							shortest_line = i;
							shortest_wait = shortest_wait_temp;
						}
					}

					//put customer at rear of shortest line
					line[shortest_line].push(currentcustomer);
				}
				//reapeat loop if a customer was found
			} while (currentcustomer.arrival_time != -1);

			//process the front of the line
			for (int i = 0; i < NUM_LINES; i++)
			{
				//gets customer if processing time is 0
				currentcustomer = line[i].process();

				//if a customer was returned
				if (currentcustomer.arrival_time != -1)
				{
					//arrival time is set to 0
					//this is because our insert function orders by arrival time
					currentcustomer.arrival_time = 0;

					//insert customer into departure list
					departure.insert(currentcustomer);
				}
			}

			//assume all lines are empty
			all_lines_empty = true;
			
			//check if lines are empty
			for (int i = 0; i < NUM_LINES; i++)
			{
				//if a non-empty line is found
				if (!line[i].isempty())
					all_lines_empty = false;
			}

			//increment time
			time++;
		}

		//print arrival/departure
		printarrivaldeparture(arrival, departure, cout);
		printarrivaldeparture(arrival, departure, outfile);
	}

	Footer(outfile);

	//close files
	infile.close();
	outfile.close();

	cout << endl << "END OF PROGRAM OUTPUT" << endl;

	return 0;
}

