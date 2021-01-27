//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  binarytree.h          ASSIGNMENT #:  5            Grade: _________          *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  April 29, 2020                  *
//*                                                                                                   *
//*****************************************************************************************************

#ifndef BINARYTREE_H
#define BINARYTREE_H

using namespace std;

//node constants
const int ID_LEN = 5;
const int NAME_LEN = 20;

struct node
{
	//node data
	char id[ID_LEN + 1];
	char name[NAME_LEN + 1];
	int onHand;
	int onOrder;

	//children
	node* leftChild;
	node* rightChild;
};

class btree
{
public:
	btree() { root = NULL; }	//default constructor
	node* getRoot() { return root; }	//accessor function gets root
	node* getItemById(char[]);
	node* search(char[], int&, node*);
	bool itemExists(char[]);
	void insertN(node);
	void deleteN(char[]);
	void patchParent(node*, node*, node*);
	void printN(ostream&, char[]);
	void printE(ostream&, node*);

private:
	node* root;	//root node
};

void Header(ofstream& Outfile);

void Footer(ofstream& Outfile);

#endif BINARYTREE_H
