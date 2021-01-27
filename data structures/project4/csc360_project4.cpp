//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  csc360_project4.cpp          ASSIGNMENT #:  4            Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                                     Lucas Kehoe                                                   *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                              DUE DATE:  March 27, 2020                  *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:  This program will take a mathematical expression in INFIX notation, convert it to     *
//*             POSTFIX notation, and then evaluate the POSTFIX expression. Mathematical expressions  *
//*             may contain operands between 1 and 9, and operators in the expression may be '*',     *
//*             '/', '+', or '-'. This program will print the steps going from INFIX notation to      *
//*             POSTFIX notation, including the stack, this is CONVERSION DISPLAY. The program will   *
//*             then print the evaluation of the POSTFIX expression, including the stack, this is     *
//*             EVALUATION DISPLAY. The program then will finally print the original expression and   *
//*             answer. Input for this program is done in a text file. Each expression must be        *
//*             on it's own line, and the terminating character for the file should be an uppercase   *
//*             'X'. The output can be found in "output.txt".                                         *
//*                                                                                                   *
//*****************************************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include "postfix.h"

using namespace std;

//constants used in main
const int EXP_LEN = 30;	//MAXIMUM EXPRESSION LENGTH MUST BE AT LEAST 20 CHARACTERS
const char QUIT = 'X';	//Terminating Character in data file
const string INFILE = "data4.txt";	//input file
const string OUTFILE = "output.txt";	//output file

int main()
{
	char expression[EXP_LEN];
	int answer;
	
	bool quit = false;

	//nodes used for processing stacks and lists
	node temp_node, temp_node2;
	inode temp_inode, temp_inode2;

	//lists for infix and postfix
	list infixExpression;
	list postfixExpression;

	//stacks for conversion and evaluation
	stack charStack;
	istack intStack;

	ifstream infile(INFILE);
	ofstream outfile(OUTFILE);

	Header(outfile);

	//get expression from file
	infile.getline(expression, EXP_LEN);
	
	//check expression for terminating character
	for (int i = 0; i < strlen(expression); i++)
	{
		if (expression[i] == QUIT)
			quit = true;
	}

	//while terminating character is not found
	while (!quit)
	{
		//copy expression into infix
		for (int i = 0; i < strlen(expression); i++)
		{
			temp_node.value = expression[i];
			infixExpression.insert(temp_node);
		}

		//========== CONVERSION ==========
		printConversionHeader(cout, EXP_LEN);
		printConversionHeader(outfile, EXP_LEN);

		//while the infix is not empty
		while (!infixExpression.isEmpty())
		{
			printConversion(infixExpression, postfixExpression, charStack, cout, EXP_LEN);
			printConversion(infixExpression, postfixExpression, charStack, outfile, EXP_LEN);

			//remove first character from the left
			temp_node = infixExpression.removeFirst();

			//if digit, insert into postfix
			if (isdigit(temp_node.value))
				postfixExpression.insert(temp_node);
			//else if '(', push onto stack
			else if (temp_node.value == '(')
				charStack.push(temp_node);
			//else if ')'
			else if (temp_node.value == ')')
			{
				//while that stack is not empty and top character is not '(',
				//pop characters off stack and push onto postfix
				while (!charStack.isEmpty() && (charStack.topNode() != '('))
				{
					temp_node2 = charStack.pop();
					postfixExpression.insert(temp_node2);
				}
				charStack.pop();
			}
			//else operator
			else
			{
				//while stack is not empty,
				//and top character is not '(',
				//and precedence is less than or equal to operator on top of stack,
				//pop characters off stack and push onto postfix
				while (!charStack.isEmpty()
					&& charStack.topNode() != '('
					&& precedenceLTOET(temp_node.value, charStack.topNode()))
				{
					temp_node2 = charStack.pop();
					postfixExpression.insert(temp_node2);
				}
				charStack.push(temp_node);
			}
		}
		//now infix is empty
		//while the stack is not empty
		while (!charStack.isEmpty())
		{
			printConversion(infixExpression, postfixExpression, charStack, cout, EXP_LEN);
			printConversion(infixExpression, postfixExpression, charStack, outfile, EXP_LEN);

			//pop character off stack and push onto postfix
			temp_node = charStack.pop();
			postfixExpression.insert(temp_node);
		}

		printConversion(infixExpression, postfixExpression, charStack, cout, EXP_LEN);
		printConversion(infixExpression, postfixExpression, charStack, outfile, EXP_LEN);
		cout << endl;
		outfile << endl;
		//========== END CONVERSION ==========

		//========== EVALUATION ==========
		printEvaluationHeader(cout, EXP_LEN);
		printEvaluationHeader(outfile, EXP_LEN);

		//while the postfix is not empty
		while (!postfixExpression.isEmpty())
		{
			printEvalutaion(postfixExpression, intStack, cout, EXP_LEN);
			printEvalutaion(postfixExpression, intStack, outfile, EXP_LEN);

			//remove first character from the left
			temp_node = postfixExpression.removeFirst();

			//if digit, push onto stack
			if (isdigit(temp_node.value))
			{
				temp_inode.value = temp_node.value - 48;

				intStack.push(temp_inode);
			}
			//else, evaluate top 2 ints on stack
			else
			{
				switch (temp_node.value)
				{
				case '+':
					temp_inode = intStack.pop();
					temp_inode2 = intStack.pop();
					temp_inode.value = temp_inode2.value + temp_inode.value;
					intStack.push(temp_inode);
					break;
				case '-':
					temp_inode = intStack.pop();
					temp_inode2 = intStack.pop();
					temp_inode.value = temp_inode2.value - temp_inode.value;
					intStack.push(temp_inode);
					break;
				case '*':
					temp_inode = intStack.pop();
					temp_inode2 = intStack.pop();
					temp_inode.value = temp_inode2.value * temp_inode.value;
					intStack.push(temp_inode);
					break;
				case '/':
					temp_inode = intStack.pop();
					temp_inode2 = intStack.pop();
					temp_inode.value = temp_inode2.value / temp_inode.value;
					intStack.push(temp_inode);
					break;
				default:
					cout << "Invalid operator encountered." << endl;
				}
			}
		}

		printEvalutaion(postfixExpression, intStack, cout, EXP_LEN);
		printEvalutaion(postfixExpression, intStack, outfile, EXP_LEN);
		
		//get top/last integer from stack (answer)
		temp_inode = intStack.pop();
		answer = temp_inode.value;
		
		printEvalutaion(postfixExpression, intStack, cout, EXP_LEN);
		printEvalutaion(postfixExpression, intStack, outfile, EXP_LEN);
		cout << endl;
		outfile << endl;
		//========== END EVALUATION ==========

		//print original expression and answer
		printAnswer(expression, answer, cout);
		printAnswer(expression, answer, outfile);

		//get next expression from file
		infile.getline(expression, EXP_LEN);

		//check expression for terminating character
		for (int i = 0; i < strlen(expression); i++)
		{
			if (expression[i] == QUIT)
				quit = true;
		}
	}

	Footer(outfile);

	infile.close();
	outfile.close();

	cout << "END OF PROGRAM OUTPUT" << endl;

	return 0;
}