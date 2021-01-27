//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Mail.cpp          ASSIGNMENT #:  2            Grade: _________              *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  February 21, 2020               *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Mail.h"

using namespace std;

//******************** MAIL LIST CONSTRUCTOR ********************
mail_list::mail_list()
{
	//Recieves - nothing
	//Task - construct a mail_list linked list
	//Returns - nothing

	start_ptr = NULL;
}

//******************** INSERT NODE ********************
void mail_list::insertnode(mail_node node, ofstream& outfile)
{
	//Recieves - node and file
	//Task - inserts node into linked list, alphabetically, unless
	//		 node already exists, then returns error
	//Returns - potentially error message, unless successful

	bool is_first_name = true;
	bool is_last_name = true;

	bool stop = false;
	bool duplicate_name = false;

	//node pointers
	mail_node* new_ptr, * previous_ptr, * current_ptr;

	//allocate memory for new node
	new_ptr = new (mail_node);

	if (new_ptr == NULL)	//if no memory is available
	{
		cout << "Node not inserted. No available memory." << endl;
	}
	else
	{
		//fill new node with passed node
		for (int i = 0; i < FIRST_NAME_LEN; i++)
			new_ptr->first_name[i] = node.first_name[i];
		for (int i = 0; i < LAST_NAME_LEN; i++)
			new_ptr->last_name[i] = node.last_name[i];
		for (int i = 0; i < STREET_ADDRESS_LEN; i++)
			new_ptr->street_adress[i] = node.street_adress[i];
		for (int i = 0; i < CITY_LEN; i++)
			new_ptr->city[i] = node.city[i];
		for (int i = 0; i < STATE_LEN; i++)
			new_ptr->state[i] = node.state[i];
		for (int i = 0; i < ZIP_CODE_LEN; i++)
			new_ptr->zip_code[i] = node.zip_code[i];
		
		previous_ptr = NULL;
		current_ptr = start_ptr;

		//if linked list is empty, insert node as start
		if (current_ptr == NULL)
		{
			new_ptr->next = NULL;
			start_ptr = new_ptr;
		}
		else
		{
			while (current_ptr != NULL && !stop && !duplicate_name)
			{
				is_first_name = true;
				is_last_name = true;

				//check if the name is already in the list
				for (int i = 0; i < FIRST_NAME_LEN; i++)
				{
					if (new_ptr->first_name[i] != current_ptr->first_name[i])
					{
						is_first_name = false;
					}
				}
				for (int i = 0; i < LAST_NAME_LEN; i++)
				{
					if (new_ptr->last_name[i] != current_ptr->last_name[i])
					{
						is_last_name = false;
					}
				}

				//if name is alread in list, duplicate = true
				if (is_first_name && is_last_name)
				{
					duplicate_name = true;
				}
				//order list alphabetically by last and first name
				else if (strcmp(current_ptr->last_name, new_ptr->last_name) > 0 )
				{
					stop = true;
				}
				else if ((strcmp(current_ptr->last_name, new_ptr->last_name) == 0) 
					&& (strcmp(current_ptr->first_name, new_ptr->first_name) > 0))
				{
					stop = true;
				}
				else
				{
					//check next node
					previous_ptr = current_ptr;
					current_ptr = current_ptr->next;
				}
			}

			//if the node is not a duplicate
			if (!duplicate_name)
			{
				//if the node is the first item alphabetically
				if (previous_ptr == NULL)
				{
					//insert as first item
					new_ptr->next = start_ptr;
					start_ptr = new_ptr;
				}
				else
				{
					//insert between previous and current
					previous_ptr->next = new_ptr;
					new_ptr->next = current_ptr;
				}
			}
			//the node is a duplicate, print error
			else
			{
				for (int i = 0; i < FIRST_NAME_LEN; i++)
				{
					if (new_ptr->first_name[i] != ' ')
					{
						cout << new_ptr->first_name[i];
						outfile << new_ptr->first_name[i];
					}
				}
				cout << " ";
				outfile << " ";
				for (int i = 0; i < LAST_NAME_LEN; i++)
				{
					if (new_ptr->last_name[i] != ' ')
					{
						cout << new_ptr->last_name[i];
						outfile << new_ptr->last_name[i];
					}
				}
				cout << " is already in the list. ";
				cout << "Attempt to add duplicate record failed!" << endl;
				outfile << " is already in the list. ";
				outfile << "Attempt to add duplicate record failed!" << endl;
			}	
		}
	}

	return;
}

//******************** DELETE NODE ********************
mail_node mail_list::deletenode(mail_node node)
{
	//Recieves - node
	//Task - deletes node from linked list if it exists
	//Returns - returns node if successfully deleted, returns an
	//			empty node if unsuccessful

	bool is_first_name = true;
	bool is_last_name = true;

	//node pointers
	mail_node* temp_ptr, * previous_ptr, * current_ptr;

	//check to make sure list isn't empty
	if (start_ptr != NULL)
	{
		//check to see if first item is the node
		for (int i = 0; i < FIRST_NAME_LEN; i++)
		{
			if (node.first_name[i] != start_ptr->first_name[i])
			{
				is_first_name = false;
			}
		}
		for (int i = 0; i < LAST_NAME_LEN; i++)
		{
			if (node.last_name[i] != start_ptr->last_name[i])
			{
				is_last_name = false;
			}
		}

		//if the first item is the node, delete and return it
		if (is_first_name && is_last_name)
		{
			temp_ptr = start_ptr;
			start_ptr = start_ptr->next;

			return *temp_ptr;
		}
		//check every node thereafter
		else
		{
			previous_ptr = start_ptr;
			current_ptr = start_ptr->next;
			
			//while not at end of list and node not found yet
			while ((current_ptr != NULL) && !(is_first_name && is_last_name))
			{
				is_first_name = true;
				is_last_name = true;

				//check if node
				for (int i = 0; i < FIRST_NAME_LEN; i++)
				{
					if (node.first_name[i] != current_ptr->first_name[i])
					{
						is_first_name = false;
					}
				}
				for (int i = 0; i < LAST_NAME_LEN; i++)
				{
					if (node.last_name[i] != current_ptr->last_name[i])
					{
						is_last_name = false;
					}
				}
				
				//if it is node, delete and return it
				if (is_first_name && is_last_name)
				{
					temp_ptr = current_ptr;
					previous_ptr->next = current_ptr->next;
					temp_ptr->next = NULL;

					return *temp_ptr;
				}
				else
				{
					//move to next node
					previous_ptr = current_ptr;
					current_ptr = current_ptr->next;
				}
			}
		}
	}

	//fill node with "empty" values for return, signaling an error
	strcpy_s(node.first_name, FIRST_NAME_LEN, "");
	strcpy_s(node.last_name, LAST_NAME_LEN, "");
	strcpy_s(node.street_adress, STREET_ADDRESS_LEN, "");
	strcpy_s(node.city, CITY_LEN, "");
	strcpy_s(node.state, STATE_LEN, "");
	strcpy_s(node.zip_code, ZIP_CODE_LEN, "");

	return node;
}

//******************** CHANGE NODE ********************
void mail_list::changenode(mail_node node, 
	int field_number, string new_value, ofstream& outfile)
{
	//Recieves - node, field number, new value, and file
	//Task - attempts to search linked list for node. if node is found,
	//		 changes the respective field number with new value and
	//		 reinserts node into linked list. if node is not found,
	//		 prints error to file.
	//Returns - potentially error message, otherwise nothing

	bool is_first_name = true;
	bool is_last_name = true;

	mail_node temp;
	
	//attempt to retrieve node
	temp = deletenode(node);

	//check if node was successfully retrieved
	for (int i = 0; i < FIRST_NAME_LEN; i++)
	{
		if (node.first_name[i] != temp.first_name[i])
		{
			is_first_name = false;
		}
	}
	for (int i = 0; i < LAST_NAME_LEN; i++)
	{
		if (node.last_name[i] != temp.last_name[i])
		{
			is_last_name = false;
		}
	}

	//if the node was not successfully retrieved (it doesn't exist)
	//print error message to file
	if (!(is_first_name || is_last_name))
	{
		for (int i = 0; i < FIRST_NAME_LEN; i++)
		{
			if (node.first_name[i] != ' ')
			{
				cout << node.first_name[i];
				outfile << node.first_name[i];
			}
		}
		cout << " ";
		outfile << " ";
		for (int i = 0; i < LAST_NAME_LEN; i++)
		{
			if (node.last_name[i] != ' ')
			{
				cout << node.last_name[i];
				outfile << node.last_name[i];
			}
		}
		cout << " not found. Attempt to change record failed!" << endl;
		outfile << " not found. Attempt to change record failed!" << endl;
	}
	//node temp successfully retrieved
	else
	{
		//change respective field number with new value
		switch (field_number)
		{
		case 1:
			new_value.copy(temp.first_name, FIRST_NAME_LEN);
			break;
		case 2:
			new_value.copy(temp.last_name, LAST_NAME_LEN);
			break;
		case 3:
			new_value.copy(temp.street_adress, STREET_ADDRESS_LEN);
			break;
		case 4:
			new_value.copy(temp.city, CITY_LEN);
			break;
		case 5:
			new_value.copy(temp.state, STATE_LEN);
			break;
		case 6:
			new_value.copy(temp.zip_code, ZIP_CODE_LEN);
			break;
		default:
			cout << "Invalid code!" << endl;
		}

		//reinsert new changed node into list
		insertnode(temp, outfile);
	}

	return;
}

//******************** PRINT LINKED LIST ********************
void mail_list::printlist(ostream& stream)
{
	//Recieves - stream
	//Task - prints linked list to stream
	//Returns - nothing

	//node pointers
	mail_node* current_ptr;

	current_ptr = start_ptr;

	//if list is empty, print message
	if (current_ptr == NULL)
	{
		stream << "MAILING LIST is empty!" << endl;
	}
	else
	{
		//print mailing list header
		stream << endl;
		stream << "===============================MAILING LIST";
		stream << "===============================" << endl;
		stream << "Last Name    ";
		stream << "First Name   ";
		stream << "Address              ";
		stream << "City         ";
		stream << "State ";
		stream << "Zip Code" << endl;
		stream << "===========================================";
		stream << "===============================" << endl;

		//while not at end of list
		while (current_ptr != NULL)
		{
			//print node values
			for (int i = 0; i < LAST_NAME_LEN; i++)
			{
				stream << current_ptr->last_name[i];
			}
			stream << " ";
			for (int i = 0; i < FIRST_NAME_LEN; i++)
			{
				stream << current_ptr->first_name[i];
			}
			stream << " ";
			for (int i = 0; i < STREET_ADDRESS_LEN; i++)
			{
				stream << current_ptr->street_adress[i];
			}
			stream << " ";
			for (int i = 0; i < CITY_LEN; i++)
			{
				stream << current_ptr->city[i];
			}
			stream << " ";
			for (int i = 0; i < STATE_LEN; i++)
			{
				stream << current_ptr->state[i];
			}
			stream << "    ";
			for (int i = 0; i < ZIP_CODE_LEN; i++)
			{
				stream << current_ptr->zip_code[i];
			}
			stream << endl;

			//move to next node
			current_ptr = current_ptr->next;
		}
	}

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
	Outfile << setw(20) << "Assignment #2" << endl;
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