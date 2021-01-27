//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  postfix.cpp          ASSIGNMENT #:  4            Grade: _________           *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  March 27, 2020                  *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include "postfix.h"

using namespace std;

//******************** INSERT - LIST ********************
void list::insert(node n)
{
	//Recieves - character node
	//Task - inserts node at end of list
	// Returns - nothing

	//node pointers
	node* new_node, * previous_node, * current_node;

	//allocate memory for new node
	new_node = new (node);

	//if no memory is avaliable
	if (new_node == NULL)
	{
		cout << "Node not inserted. No avaliable memory." << endl;
	}
	else
	{
		//copy recieved node into new node
		new_node->value = n.value;

		previous_node = NULL;
		current_node = start;

		//if list is empty, insert as first
		if (current_node == NULL)
		{
			new_node->next = NULL;
			start = new_node;
		}
		else
		{
			//while not at end of list
			while (current_node != NULL)
			{
				//move to next node
				previous_node = current_node;
				current_node = current_node->next;
			}

			//insert node at end
			previous_node->next = new_node;
			new_node->next = current_node;	//new_node->next = NULL;
		}
	}

	return;
}

//******************** REMOVE FIRST NODE - LIST ********************
node list::removeFirst()
{
	//Recieves - nothing
	//Task - return character node at beginning of list
	// Returns - character node

	node temp_node;

	temp_node.value = '\0';

	//if list is not empty
	if (!isEmpty())
	{
		//copy first node into temp_node
		temp_node.value = start->value;

		//next node becomes new start
		start = start->next;
	}
	else
	{
		cout << "List is empty. Failed to remove first node." << endl;
	}

	return temp_node;
}

//******************** IS EMPTY - LIST ********************
bool list::isEmpty()
{
	//Recieves - nothing
	//Task - determine if list is empty
	// Returns - returns true if list is empty, false if not

	return (start == NULL);
}

//******************** PRINT - LIST ********************
void list::print(ostream& stream)
{
	//Recieves - output stream
	//Task - print list, left to right, to stream
	// Returns - nothing

	node* temp_node = start;

	if (isEmpty())
		stream << "EMPTY";
	else
	{
		while (temp_node != NULL)
		{
			stream << temp_node->value;
			temp_node = temp_node->next;
		}
	}

	return;
}

//******************** GET LENGTH - LIST ********************
int list::length()
{
	//Recieves - nothing
	//Task - calculates the length of characters in list
	// Returns - length of characters in list

	int len = 5;	//5 = EMPTY

	node* temp_node = start;

	if (!isEmpty())
	{
		len = 0;
		while (temp_node != NULL)
		{
			len += 1;
			temp_node = temp_node->next;
		}
	}

	return len;
}

//******************** PUSH - CHAR STACK ********************
void stack::push(node n)
{
	//Recieves - character node
	//Task - push node on top of stack
	// Returns - nothing

	node* new_node;

	//allocate memory for new node
	new_node = new (node);

	//if no memory is avaliable
	if (new_node == NULL)
	{
		cout << "Node not pushed. No avaliable memory." << endl;
	}
	else
	{
		//copy recieved node into new node
		new_node->value = n.value;

		if (isEmpty())
			new_node->next = NULL;
		else
			new_node->next = top;

		top = new_node;
	}

	return;
}

//******************** PUSH - INT STACK ********************
void istack::push(inode n)
{
	//Recieves - integer node
	//Task - push node on top of stack
	// Returns - nothing

	inode* new_node;

	//allocate memory for new node
	new_node = new (inode);

	//if no memory is avaliable
	if (new_node == NULL)
	{
		cout << "Node not pushed. No avaliable memory." << endl;
	}
	else
	{
		//copy recieved node into new node
		new_node->value = n.value;

		if (isEmpty())
			new_node->next = NULL;
		else
			new_node->next = top;

		top = new_node;
	}

	return;
}

//******************** POP - CHAR STACK ********************
node stack::pop()
{
	//Recieves - nothing
	//Task - return character node on top of stack
	// Returns - character node

	node temp_node;

	temp_node.value = '\0';

	//if stack is not empty
	if (!isEmpty())
	{
		//copy top node into temp node
		temp_node.value = top->value;

		top = top->next;
	}
	else
	{
		cout << "Stack is empty. Failed to pop node." << endl;
	}

	return temp_node;
}

//******************** POP - INT STACK ********************
inode istack::pop()
{
	//Recieves - nothing
	//Task - return integer node on top of stack
	// Returns - integer node

	inode temp_node;

	temp_node.value = 0;

	//if stack is not empty
	if (!isEmpty())
	{
		//copy top node into temp node
		temp_node.value = top->value;

		top = top->next;
	}
	else
	{
		cout << "Stack is empty. Failed to pop node." << endl;
	}

	return temp_node;
}

//******************** GET TOP NODE CHAR - CHAR STACK ********************
char stack::topNode()
{
	//Recieves - nothing
	//Task - return character value of top node on stack
	// Returns - character of top node or NULL if empty stack

	if (!isEmpty())
		return top->value;
	else
		return '\0';
}

//******************** IS EMPTY - CHAR STACK ********************
bool stack::isEmpty()
{
	//Recieves - nothing
	//Task - determine if stack is empty
	// Returns - returns true if stack is empty, false if not

	return (top == NULL);
}

//******************** IS EMPTY - INT STACK ********************
bool istack::isEmpty()
{
	//Recieves - nothing
	//Task - determine if stack is empty
	// Returns - returns true if stack is empty, false if not

	return (top == NULL);
}

//******************** PRINT - CHAR STACK ********************
void stack::print(ostream& stream)
{
	//Recieves - output stream
	//Task - print stack, top to bottom, to stream
	// Returns - nothing

	node* temp_node = top;

	if (isEmpty())
		stream << "EMPTY";
	else
	{
		while (temp_node != NULL)
		{
			stream << temp_node->value;
			temp_node = temp_node->next;
		}
	}

	return;
}

//******************** PRINT - INT STACK ********************
void istack::print(ostream& stream)
{
	//Recieves - output stream
	//Task - print stack, top to bottom, to stream
	// Returns - nothing

	inode* temp_node = top;

	if (isEmpty())
		stream << "EMPTY";
	else
	{
		while (temp_node != NULL)
		{
			stream << temp_node->value << " ";
			temp_node = temp_node->next;
		}
	}

	return;
}

//******************** PRINT CONVERSION ********************
void printConversion(list infix, list postfix, stack s, ostream& stream, const int explen)
{
	//Recieves - infix notation list, postfix notation list, 
	//           stack, output stream, and expression length int
	//Task - prints infix, postfix, and stack to output stream
	// Returns - nothing

	infix.print(stream);
	for (int i = infix.length(); i < explen; i++)
		stream << " ";
	postfix.print(stream);
	for (int i = postfix.length(); i < explen; i++)
		stream << " ";
	s.print(stream);
	stream << endl;

	return;
}

//******************** PRINT CONVERSION HEADER ********************
void printConversionHeader(ostream& stream, const int explen)
{
	//Recieves - output stream and expression length int
	//Task - prints header for CONVERSION DISPLAY
	// Returns - nothing

	for (int i = 0; i < explen; i++)
		stream << "=";
	stream << "CONVERSION DISPLAY";
	for (int i = 0; i < explen + 12; i++)
		stream << "=";
	stream << endl;
	stream << "Infix Expression";
	for (int i = 0; i < explen - 16; i++)
		stream << " ";
	stream << "Postfix Expression";
	for (int i = 0; i < explen - 19; i++)
		stream << " ";
	stream << " Stack Contents (Top to Bottom)";
	stream << endl;
	for (int i = 0; i < explen * 2 + 30; i++)
		stream << "=";
	stream << endl;

	return;
}

//******************** PRINT EVALUATION ********************
void printEvalutaion(list postfix, istack s, ostream& stream, const int explen)
{
	//Recieves - postfix notation list, stack, output stream, and expression length int
	//Task - prints postfix and stack to output stream
	// Returns - nothing

	postfix.print(stream);
	for (int i = postfix.length(); i < explen; i++)
		stream << " ";
	s.print(stream);
	stream << endl;

	return;
}

//******************** PRINT EVALUATION HEADER ********************
void printEvaluationHeader(ostream& stream, const int explen)
{
	//Recieves - output stream and expression length int
	//Task - prints header for EVALUATION DISPLAY
	// Returns - nothing

	for (int i = 0; i < explen; i++)
		stream << "=";
	stream << "EVALUATION DISPLAY";
	for (int i = 0; i < explen + 12; i++)
		stream << "=";
	stream << endl;
	stream << "Postfix Expression";
	for (int i = 0; i < explen - 18; i++)
		stream << " ";
	stream << "Stack Contents (Top to Bottom)";
	for (int i = 0; i < explen; i++)
		stream << " ";
	stream << endl;
	for (int i = 0; i < explen * 2 + 30; i++)
		stream << "=";
	stream << endl;

	return;
}

//******************** PRINT ANSWER ********************
void printAnswer(char expression[], int answer, ostream& stream)
{
	//Recieves - expression, answer int, and output stream
	//Task - prints original expression and the answer to output stream
	// Returns - nothing

	stream << "ORIGINAL EXPRESSION AND THE ANSWER:" << endl;
	for (int i = 0; i < strlen(expression); i++)
		stream << expression[i] << " ";
	stream << "= " << answer << endl << endl;

	return;
}

//******************** PRECEDENCE LESS THAN OR EQUAL TO ********************
bool precedenceLTOET(char c1, char c2)
{
	//Recieves - two characters (*,/,+,-)
	//Task - determines precedence of characters
	// Returns - if c1 precendence <= c2 precedence returns true, else returns false

	char c[2] = {c1, c2};
	int precedence[2] = { 0 };
	bool c1LTOETc2 = false;

	//set precedence for characters
	for (int i = 0; i < 2; i++)
	{
		if (c[i] == '*' || c[i] == '/')
			precedence[i] = 2;
		else if (c[i] == '+' || c[i] == '-')
			precedence[i] = 1;
	}

	//test c1 <= c2
	if (precedence[0] <= precedence[1])
		c1LTOETc2 = true;

	return c1LTOETc2;
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
	Outfile << setw(20) << "Assignment #4" << endl;
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