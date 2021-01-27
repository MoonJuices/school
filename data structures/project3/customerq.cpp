//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  customerq.cpp                ASSIGNMENT #:  3            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  March 6, 2020                   *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "customerq.h"

using namespace std;

//******************** CUSTOMER LIST CONSTRUCTOR ********************
customerlist::customerlist()
{
	//Recieves - nothing
	//Task - construct customer linked list
	//Returns - nothing

	start = NULL;
}

//******************** INSERT - CUSTOMER LIST ********************
void customerlist::insert(customer c)
{
	//Recieves - customer
	//Task - insert customer into list by arrival time
	//Returns - nothing

	bool stop = false;

	//customer pointers
	customer* new_customer, * previous_customer, * current_customer;

	//allocate memory for new customer
	new_customer = new (customer);

	//if no memory is available
	if (new_customer == NULL)
	{
		cout << "Customer not inserted. No available memory." << endl;
		return;
	}
	else
	{
		//copy recieved customer into new customer
		for (int i = 0; i < NAME_LEN; i++)
		{
			new_customer->first_name[i] = c.first_name[i];
			new_customer->last_name[i] = c.last_name[i];
		}
		new_customer->arrival_time = c.arrival_time;
		new_customer->processing_time = c.processing_time;

		previous_customer = NULL;
		current_customer = start;

		//if list is empty, insert customer at start
		if (current_customer == NULL)
		{
			new_customer->next = NULL;
			start = new_customer;
		}
		else
		{
			//while not at end of list and not stopped
			while (current_customer != NULL && !stop)
			{
				//stop if current customers arrival time is > new customers arrival time
				if (current_customer->arrival_time > new_customer->arrival_time)
					stop = true;
				//move to next customer node
				else
				{
					previous_customer = current_customer;
					current_customer = current_customer->next;
				}
			}

			if (previous_customer == NULL)
			{
				//insert as first customer
				new_customer->next = start;
				start = new_customer;
			}
			else
			{
				//insert between previous and current customer
				previous_customer->next = new_customer;
				new_customer->next = current_customer;
			}
		}
	}

	return;
}

//******************** ARRIVE (REMOVE) - CUSTOMER LIST ********************
customer customerlist::arrive(int arrival_t)
{
	//Recieves - integer arrival time
	//Task - searches list for customer with arrival_time == arrival_t 
	//Returns - if customer is found, returns customer.
	//			if customer is not found, returns customer with arrival_time = -1 (error).

	//customer pointers
	customer* temp_customer, * previous_customer, * current_customer;
	
	customer error;

	//if list is empty
	if (start == NULL)
	{
		cout << "List is empty." << endl;
	}
	else
	{
		//if customer is first customer
		if (start->arrival_time == arrival_t)
		{
			//remove customer
			temp_customer = start;
			start = start->next;

			//return customer
			return *temp_customer;
		}
		//check every customer after first
		else
		{
			previous_customer = start;
			current_customer = start->next;

			//while not at the end of the list
			while (current_customer != NULL)
			{
				//if customer is correct customer
				if (current_customer->arrival_time == arrival_t)
				{
					//remove customer
					temp_customer = current_customer;
					previous_customer->next = current_customer->next;

					//return customer
					return *temp_customer;
				}
				//move to next customer
				else
				{
					previous_customer = current_customer;
					current_customer = current_customer->next;
				}
			}
		}
	}

	//if list is empty OR customer is not found
	error.arrival_time = -1;

	//return error customer (arrival_time = -1)
	return error;
}

//******************** PRINT - CUSTOMER LIST ********************
void customerlist::printlist(ostream& stream)
{
	//Recieves - output stream
	//Task - print names of customers in list to stream
	//Returns - nothing

	//customer pointer
	customer* current_customer;

	current_customer = start;

	//while not at the end of the list
	while (current_customer != NULL)
	{
		//print name
		stream << current_customer->first_name;
		stream << " ";
		stream << current_customer->last_name;
		stream << endl;

		//move to next customer
		current_customer = current_customer->next;
	}

	return;
}

//******************** CUSTOMER QUEUE CONSTRUCTOR ********************
customerqueue::customerqueue()
{
	//Recieves - nothing
	//Task - construct customer queue
	//Returns - nothing

	rear = NULL;
	front = NULL;
}

//******************** PUSH (ADD) - CUSTOMER QUEUE ********************
void customerqueue::push(customer c)
{
	//Recieves - customer
	//Task - places customer at rear of queue
	//Returns - nothing

	//customer pointer
	customer* new_customer;

	//allocate memory for new customer
	new_customer = new (customer);

	//if no memory is available
	if (new_customer == NULL)
	{
		cout << "Customer not pushed. No available memory." << endl;
		return;
	}
	else
	{
		//copy recieved customer into new customer
		for (int i = 0; i < NAME_LEN; i++)
		{
			new_customer->first_name[i] = c.first_name[i];
			new_customer->last_name[i] = c.last_name[i];
		}
		new_customer->arrival_time = c.arrival_time;
		new_customer->processing_time = c.processing_time;

		//if queue is empty place customer at front
		if (front == NULL)
		{
			front = new_customer;
			rear = new_customer;
			front->next = NULL;
		}
		//else place customer at rear
		else
		{
			new_customer->next = rear;
			rear = new_customer;
		}

		return;
	}
}

//******************** POP (REMOVE) - CUSTOMER QUEUE ********************
customer customerqueue::pop()
{
	//Recieves - nothing
	//Task - removes customer at front of queue
	//Returns - customer at front of queue 
	//			or returns customer with arrival_time = -1 if queue is empty

	//customer pointers
	customer* temp_customer, * previous_customer, * current_customer;
	
	customer error;

	//if queue is empty
	if (front == NULL)
	{
		cout << "Queue is empty." << endl;
	}
	else
	{
		//if queue contains one customer
		if (rear == front)
		{
			//remove customer
			temp_customer = front;
			rear = NULL;
			front = NULL;

			//return customer
			return *temp_customer;
		}
		else
		{
			previous_customer = rear;
			current_customer = rear->next;

			//while not at the end of the list
			while (current_customer != NULL)
			{
				if (current_customer == front)
				{
					//remove customer
					temp_customer = front;
					front = previous_customer;
					front->next = NULL;

					//return customer
					return *temp_customer;
				}
				else
				{
					//move to next customer
					previous_customer = current_customer;
					current_customer = current_customer->next;
				}
			}
		}
	}

	//if queue is empty
	error.arrival_time = -1;

	//return error customer (arrival_time = -1)
	return error;
}

//******************** PROCESS - CUSTOMER QUEUE ********************
customer customerqueue::process()
{
	//Recieves - nothing
	//Task - decrements processing_time of customer at front of queue by 1
	//Returns - customer at front of queue if their processing_time <= 0
	//			otherwise returns customer with arrival_time = -1 (customer not fully processed)

	customer c;

	//if queue is not empty
	if (front != NULL)
	{
		//decrement front customers processing_time by 1
		front->processing_time--;

		//if customers processing_time <= 0 (indicating fully processed)
		if (front->processing_time <= 0)
		{
			//pop and return customer
			c = pop();
			return c;
		}
	}

	//return customer with arrival_time = -1
	c.arrival_time = -1;
	return c;
}

//******************** GET WAIT - CUSTOMER QUEUE ********************
int customerqueue::getwait()
{
	//Recieves - nothing
	//Task - get the sum processing_time of customers in queue 
	//Returns - sum processing_time of customers in queue

	int wait = 0;

	customer* current_customer;

	//if queue is empty
	if (front == NULL)
	{
		wait = 0;
	}
	//if queue contains one customer
	else if (front == rear)
	{
		wait = front->processing_time;
	}
	//if queue contains > 1 customer
	else
	{
		current_customer = rear;

		//while not at the end of the list
		while (current_customer != NULL)
		{
			wait += current_customer->processing_time;

			//move to next customer
			current_customer = current_customer->next;
		}
	}

	return wait;
}

//******************** IS EMPTY - CUSTOMER QUEUE ********************
bool customerqueue::isempty()
{
	//Recieves - nothing
	//Task - determines if queue is empty or not
	//Returns - boolean whether queue is empty or not

	//assume queue is non-empty
	bool empty = false;

	//if front of queue is empty
	if (front == NULL)
		empty = true;

	return empty;
}

//******************** PRINT ARRIVAL/DEPARTURE - CUSTOMER LISTS ********************
void printarrivaldeparture(customerlist& arrival, customerlist& departure, ostream& stream)
{
	//Recieves - 2 customerlists (arrival/departure) and output stream
	//Task - prints list of customers arrival list and departure list to stream
	//Returns - nothing

	string name;

	//customer pointers
	customer* current_arrival, * current_departure;

	current_arrival = arrival.start;
	current_departure = departure.start;

	stream << "----------------------------------------";
	stream << "+-";
	stream << "----------------------------------------" << endl;

	stream << "The order of customer arrival is:       | ";
	stream << "The order of customer departure is:     " << endl;

	stream << "----------------------------------------";
	stream << "+-";
	stream << "----------------------------------------" << endl;

	//while not at the end of both lists
	while (current_arrival != NULL || current_departure != NULL)
	{
		stream << setw(NAME_LEN * 2);

		//if not at end of arrival list
		if (current_arrival != NULL)
		{
			//print arrived customer
			name = current_arrival->first_name;
			name += " ";
			name += current_arrival->last_name;
			stream << left << name;

			//move to next customer in arrival
			current_arrival = current_arrival->next;
		}

		stream << "| ";

		stream << setw(NAME_LEN * 2);

		//if not at end of departure list
		if (current_departure != NULL)
		{
			//print departed customer
			name = current_departure->first_name;
			name += " ";
			name += current_departure->last_name;
			stream << left << name;

			//move to next customer in departure
			current_departure = current_departure->next;
		}
		
		stream << endl;
	}

	stream << "----------------------------------------";
	stream << "+-";
	stream << "----------------------------------------" << endl;

	return;
}

//******************** FUNCTION HEADER ********************
void Header(ofstream& Outfile)
{
	//Recieves - the output file
	//Task - prints the output header
	//Returns - nothing

	Outfile << right << setw(30) << "Lucas Kehoe";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2020";
	Outfile << setw(20) << "Assignment #3" << endl;
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

	Outfile << right << endl;
	Outfile << setw(35) << "-------------------------" << endl;
	Outfile << setw(35) << "| END OF PROGRAM OUTPUT |" << endl;
	Outfile << setw(35) << "-------------------------" << endl;

	return;
}