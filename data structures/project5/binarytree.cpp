//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  binarytree.cpp          ASSIGNMENT #:  5            Grade: _________        *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  April 29, 2020                  *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include "binarytree.h"

using namespace std;

//******************** GET ITEM (BY ID) ********************
node* btree::getItemById(char itemid[])
{
	// Receives - item ID
	// Task - searches gets the item specified by ID
	// Returns - pointer to item if found, else returns null pointer

	//item pointer
	node* item = NULL;
	
	int status = 0;

	item = search(itemid, status, root);

	//if item is found, return item
	if (status == 1)
	{
		return item;
	}
	//else print error
	else
	{
		cout << "Error - Item not found." << endl;
		return item;
	}
}

//******************** SEARCH TREE ********************
node* btree::search(char itemid[], int& status, node* Root) {

	// Receives - item ID for search, an integer status indicator, and a pointer to the
	//            root of tree/subtree to be searched
	// Task - searches tree (InOrder) for the item
	// Returns - pointer to item if found, and updates status indicator, else returns null pointer

	node* item;
	item = NULL;

	//if root is not NULL
	if (Root != NULL) 
	{
		//search left tree
		if (status == 0)
		{
			//recursion
			item = search(itemid, status, Root->leftChild);
		}

		//check root
		if (status == 0) 
		{
			if (strcmp(Root->id, itemid) == 0)
			{
				status = 1;
				item = Root;
				return item;
			}
		}

		//search right tree
		if (status == 0)
			//recursion
			item = search(itemid, status, Root->rightChild);
	}
	return item;
}

//******************** ITEM EXSISTS ********************
bool btree::itemExists(char itemid[])
{
	// Receives - item ID
	// Task - searches if item by id exists in database
	// Returns - if item exists, returns true, else, returns false

	node* item;
	item = NULL;
	int status = 0;
	
	item = search(itemid, status, root);
	
	if (status == 1)
		return true;
	else
		return false;
}

//******************** INSERT NODE ********************
void btree::insertN(node newData)
{
	// Receives - item node
	// Task - inserts node into binary tree by id
	// Returns - nothing

	bool insert = false;
	
	node* newItem, * currentItem;
	
	//allocate memory for new node
	newItem = new node;

	//if no memory is available, print error
	if (newItem == NULL)
	{
		cout << "Error - Out of memory!" << endl;
	}
	//else procceed to insert node
	else
	{
		//copy data into new node
		strcpy_s(newItem->id, newData.id);
		strcpy_s(newItem->name, newData.name);
		newItem->onHand = newData.onHand;
		newItem->onOrder = newData.onOrder;
		
		newItem->leftChild = NULL;
		newItem->rightChild = NULL;

		//start at root
		currentItem = root;

		//while new node is not inserted
		while (insert == false)
		{
			//if tree is empty, place at first node
			if (currentItem == NULL)
			{
				root = newItem;
				insert = true;
			}
			//else traverse tree
			else
			{
				//traverse left
				if (strcmp(currentItem->id, newItem->id) >= 0)
				{
					//if left child is not empty, move to node
					if (currentItem->leftChild != NULL)
					{
						currentItem = currentItem->leftChild;
					}
					//else left child is empty, place new node
					else
					{
						currentItem->leftChild = newItem;
						insert = true;
					}
				}
				//traverse right
				else
				{
					//if right child is not empty, move to node
					if (currentItem->rightChild != NULL)
					{
						currentItem = currentItem->rightChild;
					}
					//else right child is empty, place new node
					else
					{
						currentItem->rightChild = newItem;
						insert = true;
					}
				}
			}
		}
	}

	return;
};

//******************** DELETE NODE ********************
void btree::deleteN(char id[])
{
	// Receives - item ID
	// Task - remove item from tree by ID
	// Returns - nothing

	//node pointers
	node* deletenode, * parent, * node1, * node2, * node3;
	
	bool found = false;

	//initialize to root
	deletenode = root;
	parent = NULL;

	//while node has not been found
	while ((found == false) && (deletenode != NULL))
	{
		//if id matches
		if (strcmp(deletenode->id, id) == 0)
		{
			found = true;
		}
		else
		{
			parent = deletenode;
			//traverse left
			if (strcmp(deletenode->id, id) > 0)
				deletenode = deletenode->leftChild;
			//traverse right
			else
				deletenode = deletenode->rightChild;
		}
	}

	//if node is not in tree, print error
	if (found == false)
	{
		cout << "Error - Node is not in the tree. Delete failed." << endl;
	}
	//else node was found
	else
	{
		//if node has no left child
		if (deletenode->leftChild == NULL)
		{
			//and no right child (node has NO children)
			if (deletenode->rightChild == NULL)
			{
				//remove node from tree
				patchParent(NULL, parent, deletenode);
			}
			//and node has right child (node has ONE right child)
			else
			{
				//remove node from tree, replace with right child
				patchParent(deletenode->rightChild, parent, deletenode);
			}
		}
		//node has left child
		else
		{
			//and no right child (node has ONE left child)
			if (deletenode->rightChild == NULL)
			{
				//remove node from tree, replace with left child
				patchParent(deletenode->leftChild, parent, deletenode);
			}
			//and node has right child (NODE HAS TWO CHILDREN)
			else
			{
				node1 = deletenode;
				node2 = deletenode->leftChild;
				node3 = node2->rightChild;
				
				//find rightmost node of left subtree to replace deleted node
				while (node3 != NULL)
				{
					node1 = node2;
					node2 = node3;
					node3 = node3->rightChild;
				}

				if (node1 != deletenode)
				{
					node1->rightChild = node2->leftChild;
					node2->leftChild = deletenode->leftChild;
				}
				
				//remove node from tree, replace with rightmost node of left subtree
				node2->rightChild = deletenode->rightChild;
				patchParent(node2, parent, deletenode);
			}
		}
	}

	return;
}

//******************** PATCH FUNCTION ********************
void btree::patchParent(node* child, node* parent, node* deletenode)
{

	// Receives - pointer to child node, pointer to parent node, and pointer to deleted node
	// Task - replace deleted node with a new node
	// Returns - The tree is updated accordingly

	//if no parent, child becomes root
	if (parent == NULL)
	{
		root = child;
	}
	//else, patch parent node right or left child
	else
	{
		//patch left child
		if (deletenode == parent->leftChild)
		{
			parent->leftChild = child;
		}
		//patch right child
		else
		{
			parent->rightChild = child;
		}
	}
	return;
}

//******************** PRINT INDIVIDUAL NODE ********************
void btree::printN(ostream& stream, char id[])
{
	// Receives - output stream and an item id
	// Task - print individual item data to stream
	// Returns - nothing

	node* item;
	item = getItemById(id);

	//if item exists, print item data
	if (item != NULL)
	{
		stream << left;
		stream << setw(ID_LEN + 7) << item->id;
		stream << setw(NAME_LEN + 4) << item->name;
		stream << right;
		stream << setw(6) << item->onHand;
		stream << setw(6) << " ";
		stream << setw(6) << item->onOrder;
		stream << endl;
	}
	//item does not exist, print error
	else
	{
		cout << "ERROR - Item not found." << endl;
	}

	return;
}

//******************** PRINT ENTIRE TREE ********************
void btree::printE(ostream& stream, node* Root)
{
	// Receives - output stream and root node
	// Task - prints all item data from specified root node
	// Returns - nothing

	stream << left;
	
	//if root node exists, print left subtree, root, and right subtree
	if (Root != NULL)
	{
		//print left subtree (recursion)
		printE(stream, Root->leftChild);

		//print current root node
		stream << setw(ID_LEN + 7) << Root->id;
		stream << setw(NAME_LEN + 4) << Root->name;
		stream << right;
		stream << setw(6) << Root->onHand;
		stream << setw(6) << " ";
		stream << setw(6) << Root->onOrder;
		stream << endl;

		//print right subtree (recursion)
		printE(stream, Root->rightChild);
	}

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
	Outfile << setw(20) << "Assignment #5" << endl;
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