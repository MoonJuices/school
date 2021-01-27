//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  csc360_project2.cpp          ASSIGNMENT #:  2            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  February 21, 2020               *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program is designed to read mailing list information in from a file and insert    *
//*            the persons in alphabetical order by last and first names. This program is capable of  *
//*            inserting persons into the list, deleting them from the list, changing their values    *
//*            in the list, and printing the list to a file. This program makes use of the data       *
//*            structure linked list.                                                                 *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include "Mail.h"

using namespace std;

//constants used in main
const char QUIT = 'Q';
const string INFILE = "data2.txt";
const string OUTFILE = "output.txt";

int main()
{
	//linked list
	mail_list mailing_list;
	
	//nodes to read into
	mail_node node, temp_node;

	char operationcode = '\0';
	string temp = "";
	
	//used for changing nodes
	int field_number = 0;
	string new_value = "";
	
	bool is_first_name = true;
	bool is_last_name = true;

	ifstream infile(INFILE);
	ofstream outfile(OUTFILE);

	Header(outfile);

	if (infile.fail())	//if fail to open data file
	{
		cout << "File not found!" << endl;
		outfile << "File not found!" << endl;
	}
	else
	{
		do
		{
			//retrieve operation code from file
			getline(infile, temp);
			operationcode = temp[0];

			//fill node with "empty" values
			strcpy_s(node.first_name, FIRST_NAME_LEN, "");
			strcpy_s(node.last_name, LAST_NAME_LEN, "");
			strcpy_s(node.street_adress, STREET_ADDRESS_LEN, "");
			strcpy_s(node.city, CITY_LEN, "");
			strcpy_s(node.state, STATE_LEN, "");
			strcpy_s(node.zip_code, ZIP_CODE_LEN, "");

			if (operationcode != QUIT)	//if not quit
			{
				switch (operationcode)
				{
				case 'A':	//ADD NODE
					//fill node with values from file
					getline(infile, temp);
					temp.copy(node.first_name, FIRST_NAME_LEN);
					getline(infile, temp);
					temp.copy(node.last_name, LAST_NAME_LEN);
					getline(infile, temp);
					temp.copy(node.street_adress, STREET_ADDRESS_LEN);
					getline(infile, temp);
					temp.copy(node.city, CITY_LEN);
					getline(infile, temp);
					temp.copy(node.state, STATE_LEN);
					getline(infile, temp);
					temp.copy(node.zip_code, ZIP_CODE_LEN);
					
					//insert node
					mailing_list.insertnode(node, outfile);
					break;
				case 'D':	//DELETE NODE
					//fill node with first and last name from file
					getline(infile, temp);
					temp.copy(node.first_name, FIRST_NAME_LEN);
					getline(infile, temp);
					temp.copy(node.last_name, LAST_NAME_LEN);
					
					//delete node
					temp_node = mailing_list.deletenode(node);
					
					//test if node was found
					//if temp_node is "empty," delete was failed
					//if temp_node name = node name, delete was success
					is_first_name = true;
					is_last_name = true;

					//test if names are the same
					for (int i = 0; i < FIRST_NAME_LEN; i++)
					{
						if (node.first_name[i] != temp_node.first_name[i])
						{
							is_first_name = false;
						}
					}
					for (int i = 0; i < LAST_NAME_LEN; i++)
					{
						if (node.last_name[i] != temp_node.last_name[i])
						{
							is_last_name = false;
						}
					}

					//if names are not the same, print failure to delete name
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
						cout << " not found."; 
						cout << " Attempt to delete record failed!" << endl;
						outfile << " not found.";
						outfile << " Attempt to delete record failed!" << endl;
					}
					break;
				case 'C':	//CHANGE NODE
					//fill node with first and last name from file
					getline(infile, temp);
					temp.copy(node.first_name, FIRST_NAME_LEN);
					getline(infile, temp);
					temp.copy(node.last_name, LAST_NAME_LEN);
					//get field number and new value from file
					infile >> field_number;
					getline(infile, temp);	//trash field number line
					getline(infile, new_value);

					//change node
					mailing_list.changenode(node, field_number, new_value, outfile);
					break;
				case 'P':	//PRINT LIST
					mailing_list.printlist(cout);
					mailing_list.printlist(outfile);
					break;
				default:
					cout << "Invalid code!" << endl;
				}
			}
		} while (operationcode != QUIT && !infile.eof());
	}

	Footer(outfile);

	//close files
	infile.close();
	outfile.close();

	cout << endl << "END OF PROGRAM OUTPUT" << endl;

	return 0;
}
