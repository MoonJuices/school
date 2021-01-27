#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#include <errno.h>
#include <sys/shm.h>
#include <sys/sem.h>

//attempts to add the item to table = t[t_size] with value = newValue, returns value added, or -1 if fails
int addtable(int t_size, int t[], int newValue);

//counts number of contents on table and returns number of items, or -1 if fails
int counttable(int t_size, int t[]);

int main()
{
	//variables
	int newValue = 0;
	int numTableContents = 0;
	char choice = 'y';
	
	//semaphore and shared memory ids
	int sem_id = 0, shm_id = 0;
	
	//semaphore keys
	const int royalSemKey = 1;
	const int subjectSemKey = 2;
	const int superSemKey = 3;
	
	//table size
	const int table_size = 10;
	//shared memory keys
	int table[table_size] = {11,12,13,14,15,16,17,18,19,20};
	
	//**SEMAPHORE CODES (SIGNAL/WAIT)**
	struct sembuf semSignalCommand[1];
	struct sembuf semWaitCommand[1];
	
	semSignalCommand[0].sem_num=0;
	semSignalCommand[0].sem_op=1;
	semSignalCommand[0].sem_flg=0;
	
	semWaitCommand[0].sem_num=0;
	semWaitCommand[0].sem_op=-1;
	semWaitCommand[0].sem_flg=0;
	
	//attempt create SUPER semaphore (Allows for critical section)
	if(semget(superSemKey,1,IPC_CREAT|IPC_EXCL|0666) != -1)
	{
		sem_id = semget(superSemKey,1,0);
		if(sem_id <= 0)
		{
			cerr << "Unable to access super semaphore with key = " << sem_id << endl;
			return 1;
		}
		
		//attempt to signal
		if (semop(sem_id, semSignalCommand, 1) == -1)
		{
			cerr << "Unable to signal super semaphore" << endl;
			return 1;
		}
	}
	
	//attempt create royal and subject semaphore
	semget(royalSemKey,1,IPC_CREAT|IPC_EXCL|0666);
	semget(subjectSemKey,1,IPC_CREAT|IPC_EXCL|0666);
	
	//attempt create table
	for(int i = 0; i < table_size; i++)
	{
		shmget(table[i], 1024, IPC_CREAT|IPC_EXCL|0666);
	}
	
	do
	{
		//prompt user for input
		cout << "Royal, please enter a positive integer value representing the value of the item you wish to add to the table: ";
		cin >>	newValue;
		
		//prompt user again if value<=0
		while(newValue<=0)
		{
			cout << "Royal, please enter a POSITIVE integer value representing the value of the item you wish to add to the table: ";
			cin >>	newValue;
		}
		
		//get number of table contents
		numTableContents = counttable(table_size, table);
		if(numTableContents == -1)
		{
			cout << "Unable to count Table Contents" << endl;
			return 1;
		}
		//cout << "The number of table contents before adding is: " << numTableContents << endl;
		
		//if the table has too many items
		while(numTableContents >= table_size)
		{
			cout << "Table is currently full, Royal will wait." << endl;
			
			//wait royal
			sem_id = semget(royalSemKey,1,0);
			if(sem_id <= 0)
			{
				cerr << "Unable to access royal semaphore with key = " << sem_id << endl;
				return 1;
			}
			if (semop(sem_id, semWaitCommand, 1) == -1)
			{
				cerr << "Unable to wait royal semaphore" << endl;
				return 1;
			}
			
			//count the table again
			numTableContents = counttable(table_size, table);
			if(numTableContents == -1)
			{
				cout << "Unable to count Table Contents" << endl;
				return 1;
			}
		}
		
		//super semaphore wait to allow no other users to access table
		sem_id = semget(superSemKey,1,0);
		if(sem_id <= 0)
		{
			cerr << "Unable to access super semaphore with key = " << sem_id << endl;
			return 1;
		}
		if (semop(sem_id, semWaitCommand, 1) == -1)
		{
			cerr << "Unable to wait SUPER semaphore" << endl;
		}
		
		//**CRITICAL SECTION START**
		//add item
		newValue = addtable(table_size, table, newValue);
		if(newValue == -1)
		{
			cerr << "Error adding gift to table" << endl;
		}
		
		//count table
		numTableContents = counttable(table_size, table);
		if(numTableContents == -1)
		{
			cout << "Unable to count Table Contents" << endl;
			return 1;
		}
		//cout << "The number of table contents after adding is: " << numTableContents << endl;
		
		//signal subject if there is now 1 item on table
		if(numTableContents == 1)
		{
			sem_id = semget(subjectSemKey,1,0);
			if(sem_id <= 0)
			{
				cerr << "Unable to access subject semaphore with key = " << sem_id << endl;
			}
			if (semop(sem_id, semSignalCommand, 1) == -1)
			{
				cerr << "Unable to signal subject semaphore" << endl;
			}
		}
		//**CRITICAL SECTION END**
		
		//super semaphore signal to allow new user to access table
		sem_id = semget(superSemKey,1,0);
		if(sem_id <= 0)
		{
			cerr << "Unable to access SUPER semaphore with key = " << sem_id << endl;
			return 1;
		}
		if (semop(sem_id, semSignalCommand, 1) == -1)
		{
			cerr << "Unable to signal SUPER semaphore" << endl;
			return 1;	
		}
		
		//prompt user to add another item
		cout << "Would you like to add another item to the table? ('n' to quit, other to continue) " << endl;
		cin >> choice;
		
	}while(choice!='n' && choice!='N');
		
	return 0;
}

int addtable(int t_size, int t[], int newValue)
{
	int numTableContents = 0;
	int shm_id = 0;
	int *sharedValuePtr;
	int sharedValueWrite = newValue;
	int detachstatus = 0;
	
	//get number of items on table
	numTableContents = counttable(t_size, t);
	if(numTableContents == -1)
	{
		cout << "Unable to count Table Contents" << endl;
		return -1;
	}
	
	//error encountered
	if(numTableContents>=t_size)
	{
		cerr << "ERROR: A Royal was inproperly signaled!" << endl;
		return -1;
	}
	
	shm_id = shmget(t[numTableContents], 1024, 0);
	if (shm_id <= 0)
	{
		cerr << "Unable to access shared memory with key = " << shm_id << endl;
	}
	
	sharedValuePtr = (int *) shmat(shm_id, NULL, 0);
	
	if (sharedValuePtr == (int *) -1)
	{
		cerr << "shmat failed" << endl;
		return -1;
	}
	
	//write
	*sharedValuePtr = sharedValueWrite;
	
	detachstatus = shmdt(sharedValuePtr);
	if(detachstatus!=0)
	{
		cerr << "shmdt failed" << endl;
		return -1;
	}
	
	return sharedValueWrite;
}

int counttable(int t_size, int t[])
{
	int count = 0;
	int shm_id = 0;
	int *sharedValuePtr;
	int sharedValueRead = 0;
	int detachstatus = 0;

	do
	{
		shm_id = shmget(t[count], 1024, 0);
		if (shm_id <=0)
		{
			cerr << "Unable to access shared memory with key = " << shm_id << endl;
			return -1;
		}
	
		sharedValuePtr = (int *) shmat(shm_id, NULL, 0);
	
		if (sharedValuePtr == (int *) -1)
		{
			cerr << "shmat failed" << endl;
			return -1;
		}
	
		//read
		sharedValueRead = *sharedValuePtr;
		
		detachstatus = shmdt(sharedValuePtr);
		if(detachstatus!=0)
		{
			cerr << "shmdt failed" << endl;
			return -1;
		}
		
		//if value read is not empty(=0) increment counter
		if(sharedValueRead!=0)
			count++;
			
	}while(sharedValueRead!=0 && count<t_size);

	return count;
}
