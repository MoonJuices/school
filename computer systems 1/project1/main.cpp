#include <csignal>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include <unistd.h>

#include "Command.h"
#include "Token.h"
#include "TokenStream.h"

int main()
{
	Command com1, com2;	// com1 for all commands, com2 for pipe
	char* argument_list[MAX_ARGS] = {NULL};	// arguments for com1
	char* argument_list2[MAX_ARGS] = {NULL};	// arguments for com2
	FILE *fpr, *fpw;	//file input/output redirection
	
	int pid = 0;	// process id
	int pipefd[2];	// used in pipe
	
	// prompt user command input
	cout << ">>>> ";
	com1.read();
	
	while(com1.name() != "exit")	// exit loop if com1 is exit
	{	
		// copy arguments from com1 into argument_list
		for (int i = 0; i < com1.numArgs(); i++)
		{
			argument_list[i] = strdup(com1.args(i).c_str());
		}
		argument_list[com1.numArgs()] = NULL;	// null terminated array
		
		// if command involves a pipe
		if (com1.pipeOut())
		{
			// finish gathering command input
			com2.read();
			
			// copy arguments from com2 into argument_list2
			for (int i = 0; i < com2.numArgs(); i++)
			{
				argument_list2[i] = strdup(com2.args(i).c_str());
			}
			argument_list2[com2.numArgs()] = NULL;	// null terminated array
		}
		
		if (com1.name() == "cd")	// CHANGE DIRECTORY
		{
			// Changes directory, only changes within shell
			if(chdir(argument_list[1]) < 0)	// returns negative if fails
			{
				cout << "Error changing directories" << endl;
			}
		}
		else if (!com1.pipeOut())	// NO PIPE
		{
			if (!com1.backgrounded())	// NO BACKGROUND
			{
				pid = fork();
			
				if(pid < 0)	// fork failure
				{
					cout << "Fork Failed" << endl;
					exit(1);
				}
				else if (pid == 0)	// child process
				{
					if (com1.redirIn())	// file redirect IN
					{
						fpr = fopen(com1.inputRedirectFile().c_str(), "r");
						
						dup2(fileno(fpr), fileno(stdin));
					}
					
					if (com1.redirOut())	//file redirect OUT
					{
						fpw = fopen(com1.outputRedirectFile().c_str(), "w");
						
						dup2(fileno(fpw), fileno(stdout));
					}
					
					if(execvp(argument_list[0], argument_list) < 0)
					{
						cout << "Incorrect command" << endl;
					 	exit(1);
					}
				}
				else	// parent process
				{
					waitpid(pid, NULL, 0);
				}
			}
			else	// BACKGROUND
			{
				pid = fork();
			
				if(pid < 0)	// fork failure
				{
					cout << "Fork Failed" << endl;
					exit(1);
				}
				else if (pid == 0)	// child process
				{	
					pid = fork();
					
					if(pid < 0)	// fork failure
					{
						cout << "Fork Failed" << endl;
						exit(1);
					}
					else if (pid == 0)	// grandchild process
					{
						if (com1.redirIn())	// file redirect IN
						{
							fpr = fopen(com1.inputRedirectFile().c_str(), "r");
							
							dup2(fileno(fpr), fileno(stdin));
						}	
					
						if (com1.redirOut())	// file redirect OUT
						{
							fpw = fopen(com1.outputRedirectFile().c_str(), "w");
						
							dup2(fileno(fpw), fileno(stdout));
						}
					
						if(execvp(argument_list[0], argument_list) < 0)
						{
							cout << "Incorrect command" << endl;
					 		exit(1);
						}	
					}
					else	// child waits for grandchild, then prints PID and command
					{
						waitpid(pid, NULL, 0);
						cout << "COMPLETED: PID = " << pid << " : " << com1 << endl;
						exit(1);
					}
				}
				// parent process
				// would go here in the form of an else statement,
				// however, we wish to continue allowing the previous command to
				// run in the background
			}
		}
		else	// PIPE
		{	
			pid = fork();
			
			if (pid < 0)
			{
				cout << "Fork Failed" << endl;
				exit(1);
			}
			else if (pid == 0)	// child process
			{
				pipe(pipefd);	// open pipe
						//     v
				pid = fork();	// then fork
			
				if(pid < 0)
				{
					cout << "Fork Failed" << endl;
					exit(1);
				}
				else if (pid == 0) // inner child process
				{
					close(pipefd[0]);	// close read end of pipe
					
					dup2(pipefd[1], fileno(stdout));	// duplicate file descriptor
					
					if(execvp(argument_list[0], argument_list) < 0)
					{
						cout << "Incorrect command" << endl;
					 	exit(1);
					}
				}
				else	// inner parent process
				{
					close(pipefd[1]);	// close write end of pipe
					
					dup2(pipefd[0], fileno(stdin));	// duplicate file descriptor
					
					if(execvp(argument_list2[0], argument_list2) < 0)
					{
						cout << "Incorrect command" << endl;
						exit(1);
					}
				}
			}
			else	// parent process
			{
				// wait until pipe is finished, then print PID and command
				waitpid(pid, NULL, 0);
				cout << "COMPLETED: PID = " << pid << " : " << com1 << com2 << endl;
			}
		}
		
		// prompt user command input
		cout << ">>>> ";
		com1.read();
	}
	
	cout << "Thank you for using shoddy-shell! Goodbye!" << endl;
	
	return 0;
}
