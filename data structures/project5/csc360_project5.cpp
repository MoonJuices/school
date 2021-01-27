//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  csc360_project5.cpp          ASSIGNMENT #:  5            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  April 29, 2020                  *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:  This program will take commands from a file and update a database accordingly.        *
//*             This program can insert nodes into a database, delete nodes from a database,          *
//*             print the contents of the entire database or individual items, and adjust the         *
//*             quantities of items on hand and on order.                                             *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include "binarytree.h"

using namespace std;

//constants used in main

const string INFILE = "data5.txt";
const string OUTFILE = "output.txt";

int main()
{
	//database binary tree
	btree dbTree;
	
	//new node
	node newItem;
	newItem.leftChild = NULL;
	newItem.rightChild = NULL;

	//node pointer
	node* currentItem;
	
	char command;

	//item data
	char id[ID_LEN + 1];
	char name[NAME_LEN + 6];
	int onHand;
	int onOrder;
	int quantity;

	ifstream infile(INFILE);
	ofstream outfile(OUTFILE);

	Header(outfile);

	do
	{
		//read command
		infile >> command;
		infile >> ws;

		switch (command)
		{
			//insert node
		case 'I':
			//read item data from file
			infile.get(id, ID_LEN + 1);
			infile >> ws;
			infile.get(name, NAME_LEN + 6);
			infile >> ws;
			infile >> onHand;
			infile >> onOrder;
			infile >> ws;
			
			// copy data to new item node
			strcpy_s(newItem.id, id);
			strcpy_s(newItem.name, name);
			newItem.onHand = onHand;
			newItem.onOrder = onOrder;

			//if the item does not exist yet, insert into tree
			if (!dbTree.itemExists(id))
			{
				dbTree.insertN(newItem);
				outfile << "Item ID Number " << id;
				outfile << " successfully entered into database." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "Item ID Number " << id;
				cout << " successfully entered into database." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			//else the item already exists, print error
			else
			{
				outfile << "ERROR - Attempt to insert a duplicate item (" << id << ") ";
				outfile << "into the database." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "ERROR - Attempt to insert a duplicate item (" << id << ") ";
				cout << "into the database." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			break;

			//delete node
		case 'D':
			//read item data from file
			infile.get(id, ID_LEN + 1);
			infile >> ws;
			infile.get(name, NAME_LEN + 6);
			infile >> ws;

			//if the item exists, delete from tree
			if (dbTree.itemExists(id))
			{
				dbTree.deleteN(id);
				outfile << "Item ID Number " << id;
				outfile << " successfully deleted from database." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "Item ID Number " << id;
				cout << " successfully deleted from database." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			//else the item does not exist, print error
			else
			{
				outfile << "ERROR - ";
				outfile << "Attempt to delete an item (" << id << ") ";
				outfile << "not in the database list." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "ERROR - ";
				cout << "Attempt to delete an item (" << id << ") ";
				cout << "not in the database list." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			break;

			//print
		case 'P':
			//read additional command
			infile >> command;
			infile >> ws;

			switch (command)
			{
				//print entire tree
			case 'E':
				outfile << endl;
				outfile << "      -=- JAKE'S HARDWARE INVENTORY REPORT -=-" << endl;
				outfile << "Item        Item                  Quantity    Quantity" << endl;
				outfile << "ID Number   Description            On Hand    On Order" << endl;
				outfile << "------------------------------------------------------------" << endl;
				dbTree.printE(outfile, dbTree.getRoot());
				outfile << "------------------------------------------------------------" << endl;
				outfile << endl;

				cout << endl;
				cout << "      -=- JAKE'S HARDWARE INVENTORY REPORT -=-" << endl;
				cout << "Item        Item                  Quantity    Quantity" << endl;
				cout << "ID Number   Description            On Hand    On Order" << endl;
				cout << "------------------------------------------------------------" << endl;
				dbTree.printE(cout, dbTree.getRoot());
				cout << "------------------------------------------------------------" << endl;
				cout << endl;
				break;

				//print individual item
			case 'N':
				//read item data from file
				infile.get(id, 6);
				infile >> ws;

				//if the item exists, print item
				if (dbTree.itemExists(id))
				{
					outfile << endl;
					outfile << "              -=- INDIVIDUAL ITEM REPORT -=-" << endl;
					outfile << "Item        Item                  Quantity    Quantity" << endl;
					outfile << "ID Number   Description            On Hand    On Order" << endl;
					outfile << "------------------------------------------------------------" << endl;
					dbTree.printN(outfile, id);
					outfile << "------------------------------------------------------------" << endl;
					outfile << endl;

					cout << endl;
					cout << "              -=- INDIVIDUAL ITEM REPORT -=-" << endl;
					cout << "Item        Item                  Quantity    Quantity" << endl;
					cout << "ID Number   Description            On Hand    On Order" << endl;
					cout << "------------------------------------------------------------" << endl;
					dbTree.printN(cout, id);
					cout << "------------------------------------------------------------" << endl;
					cout << endl;
				}
				//else the item does not exist, print error
				else
				{
					outfile << "ERROR - ";
					outfile << "Attempt to print an item (" << id << ") ";
					outfile << "not in the database list." << endl;
					cout << "ERROR - ";
					cout << "Attempt to print an item (" << id << ") ";
					cout << "not in the database list." << endl;
				}
				break;

				//invalid print type, print error
			default:
				cout << "ERROR - Invalid print type." << endl;
				break;
			}
			break;

			//adjust - sold
		case 'S':
			//read item data from file
			infile.get(id, ID_LEN + 1);
			infile >> ws;
			infile >> quantity;

			//if the item exists
			if (dbTree.itemExists(id))
			{
				//get item
				currentItem = dbTree.getItemById(id);

				//if enough quantity exists, update on hand
				if (currentItem->onHand >= quantity)
				{
					currentItem->onHand -= quantity;
					outfile << "Quantity on Hand for item (" << id << ") ";
					outfile << "successfully updated." << endl;
					outfile << "------------------------------------------------------------" << endl;
					cout << "Quantity on Hand for item (" << id << ") ";
					cout << "successfully updated." << endl;
					cout << "------------------------------------------------------------" << endl;
				}
				//else not enough quantity exists, print error
				else
				{
					outfile << "ERROR - ";
					outfile << "Attempt to update an item (" << id << ") ";
					outfile << "with insuffient quanitity on Hand." << endl;
					outfile << "------------------------------------------------------------" << endl;
					cout << "ERROR - ";
					cout << "Attempt to update an item (" << id << ") ";
					cout << "with insuffient quanitity on Hand." << endl;
					cout << "------------------------------------------------------------" << endl;
				}
			}
			//else the item does not exist, print error
			else
			{
				outfile << "ERROR - ";
				outfile << "Item  (" << id << ") not in database. ";
				outfile << "Data not updated." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "ERROR - ";
				cout << "Item  (" << id << ") not in database. ";
				cout << "Data not updated." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			
			break;

			//adjust - order
		case 'O':
			//read item data from file
			infile.get(id, ID_LEN + 1);
			infile >> ws;
			infile >> quantity;

			//if the item exists, update on hand
			if (dbTree.itemExists(id))
			{
				//get item
				currentItem = dbTree.getItemById(id);

				currentItem->onHand += quantity;
				outfile << "Quantity on Hand for item (" << id << ") ";
				outfile << "successfully updated." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "Quantity on Hand for item (" << id << ") ";
				cout << "successfully updated." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			//else the item does not exist, print error
			else
			{
				outfile << "ERROR - ";
				outfile << "Item (" << id << ") not on database. ";
				outfile << "Data not updated." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "ERROR - ";
				cout << "Item (" << id << ") not on database. ";
				cout << "Data not updated." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			break;

			//adjust - recieved
		case 'R':
			//read item data from file
			infile.get(id, ID_LEN + 1);
			infile >> ws;
			infile >> quantity;

			//if the item exists, update on order and on hand
			if (dbTree.itemExists(id))
			{
				//get item
				currentItem = dbTree.getItemById(id);

				currentItem->onOrder -= quantity;
				currentItem->onHand += quantity;
				outfile << "Quantity on Order for item (" << id << ") ";
				outfile << "successfully updated." << endl;
				outfile << "------------------------------------------------------------" << endl;
				outfile << "Quantity on Hand for item (" << id << ") ";
				outfile << "successfully updated." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "Quantity on Order for item (" << id << ") ";
				cout << "successfully updated." << endl;
				cout << "------------------------------------------------------------" << endl;
				cout << "Quantity on Hand for item (" << id << ") ";
				cout << "successfully updated." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			//else the item does not exist, print error
			else
			{
				outfile << "ERROR - ";
				outfile << "Item (" << id << ") not on database. ";
				outfile << "Data not updated." << endl;
				outfile << "------------------------------------------------------------" << endl;
				cout << "ERROR - ";
				cout << "Item (" << id << ") not on database. ";
				cout << "Data not updated." << endl;
				cout << "------------------------------------------------------------" << endl;
			}
			break;
		
			//quit
		case 'Q':
			break;

			//invalid command, print error
		default:
			cout << "ERROR - Invalid command." << endl;
			break;
		}
	} while (command != 'Q');

	Footer(outfile);

	cout << "END OF PROGRAM OUTPUT" << endl;

	return 0;
}