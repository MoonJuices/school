#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#include <errno.h>
#include <sys/shm.h>
#include <sys/sem.h>

//attempts to remove the first item on the table = t[t_size]
//and then moves all other items on table forward. returns value removed or -1 if fails
int removetable(int t_size, int t[]);

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
	
	//**SEMAPHORE CODE (SIGNAL/WAIT)**
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
		
		if (semop(sem_id, semSignalCommand, 1) == -1)
		{
			cerr << "Unable to signal semaphore" << endl;
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
		//count number of table contents
		numTableContents = counttable(table_size, table);
		if(numTableContents == -1)
		{
			cout << "Unable to count Table Contents" << endl;
			return 1;
		}
		//cout << "The number of table contents before removing is: " << numTableContents << endl;
		
		//if nothing on table	
		while(numTableContents==0)
		{
			cout << "Table is currently empty, Subject will wait." << endl;
			
			//subject wait
			sem_id = semget(subjectSemKey,1,0);
			if(sem_id <= 0)
			{
				cerr << "Unable to access subject semaphore with key = " << sem_id << endl;
				return 1;
			}
			if (semop(sem_id, semWaitCommand, 1) == -1)
			{
				cerr << "Unable to wait subject semaphore" << endl;
				return 1;
			}
			
			//count table again
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
		//remove item
		newValue = removetable(table_size, table);
		if(newValue == -1)
		{
			cerr << "Error removing gift from table" << endl;
		}
		
		//print item taken
		cout << "Subject took item with value = " << newValue << endl;
			
		//count table
		numTableContents = counttable(table_size, table);
		if(numTableContents == -1)
		{
			cout << "Unable to count Table Contents" << endl;
			return 1;
		}
		//cout << "The number of table contents after removing is: " << numTableContents << endl;
			
		//signal royal if there is now 9(table_size-1) items on table
		if(numTableContents == table_size-1)
		{
			sem_id = semget(royalSemKey,1,0);
			if(sem_id <= 0)
			{
				cerr << "Unable to access royal semaphore with key = " << sem_id << endl;
			}
			if (semop(sem_id, semSignalCommand, 1) == -1)
			{
				cerr << "Unable to signal royal semaphore" << endl;
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
		
		//prompt user to remove another item
		cout << "Would you like to take another item from the table? ('n' to quit, other to continue) " << endl;
		cin >> choice;
		
	}while(choice!='n' && choice!='N');
	
	return 0;
}

int removetable(int t_size, int t[])
{
	int returnVal = 0;
	int numTable = 0;
	int shm_id = 0, shm_id2 = 0;
	int *sharedValuePtr, *sharedValuePtr2;
	int sharedValueRead = 0;
	int detachstatus = 0;
	
	//get number of items on table
	numTable = counttable(t_size, t);
	if(numTable == -1)
	{
		cout << "Unable to count Table Contents" << endl;
		return -1;
	}
	
	//error encountered
	if(numTable==0)
	{
		cerr << "ERROR: A Subject was inproperly signaled!" << endl;
		return -1;
	}
	
	shm_id = shmget(t[0], 1024, 0);
	if (shm_id <= 0)
	{
		cerr << "Unable to access shared memory with key = " << shm_id << endl;
		return -1;
	}
	
	sharedValuePtr = (int *) shmat(shm_id, NULL, 0);
	
	if (sharedValuePtr == (int *) -1)
	{
		cerr << "shmat faield" << endl;
		return -1;
	}
	
	//get first item on table
	returnVal = *sharedValuePtr;
	
	detachstatus = shmdt(sharedValuePtr);
	if(detachstatus!=0)
	{
		cerr << "shmdt failed" << endl;
		return -1;
	}
	
	//shift rest of items forward on table
	for(int i = 0; i < numTable; i++)
	{
		shm_id = shmget(t[i], 1024, 0);
		if (shm_id <= 0)
		{
			cerr << "Unable to access shared memory with key = " << shm_id << endl;
			return -1;
		}
		if(i+1<numTable)
		{
			shm_id2 = shmget(t[i+1], 1024, 0);
			if (shm_id <= 0)
			{
				cerr << "Unable to access shared memory with key = " << shm_id << endl;
				return -1;
			}
		}
		
		sharedValuePtr = (int *) shmat(shm_id, NULL, 0);
		if(i+1<numTable)
			sharedValuePtr2 = (int *) shmat(shm_id2, NULL, 0);
		
		if (sharedValuePtr == (int *) -1)
		{
			cerr << "shmat faield" << endl;
			return -1;
		}
		if(i+1<numTable)
		{
			if (sharedValuePtr2 == (int *) -1)
			{
				cerr << "shmat faield" << endl;
				return -1;
			}
		}
		
		if(i+1<numTable)
			*sharedValuePtr = *sharedValuePtr2;
		else
			*sharedValuePtr = 0;
		
		detachstatus = shmdt(sharedValuePtr);
		if(detachstatus!=0)
		{
			cerr << "shmdt failed" << endl;
			return -1;
		}
		
		if(i+1<numTable)
		{
			detachstatus = shmdt(sharedValuePtr2);
			if(detachstatus!=0)
			{
				cerr << "shmdt failed" << endl;
				return -1;
			}
		}	
	}
	
	return returnVal;
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
