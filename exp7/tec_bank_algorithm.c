#include <pthread.h>
#include <stdio.h>

void *start_banker(void *param);

#define MAX_PRO 256   /* max process count */
#define MAX_RES 256	/* max resource type */

int available[MAX_RES];
int max[MAX_PRO][MAX_RES];
int allocation[MAX_PRO][MAX_RES];
int need[MAX_PRO][MAX_RES];
int request[MAX_RES];
int work[MAX_RES];
int finish[MAX_PRO];
int stop_flag = 0;
int m,n;
pthread_mutex_t mutex;
int proc_ids[MAX_PRO];

int main(int argc, char *argv[])
{
	pthread_t tid[MAX_PRO];
	pthread_attr_t attr[MAX_PRO];

	int id;
	int i,j;

	printf ("please input the process count(<=%d).\n",MAX_PRO);
	scanf("%d", &n);

	printf ("please input the resource type count(<=%d).\n",MAX_RES);
	scanf("%d", &m);
	
	if (m>256 || n>256 || m<0 || n<0)
	{
		printf ("input error\n");
		return -1;
	}
	
	printf ("please input allocation matrix\n");
	for (i=0;i<n;i++)
		for (j=0;j<m;j++)
			scanf("%d", &allocation[i][j]);
	
	printf ("please input max matrix\n");
	for (i=0;i<n;i++)
		for (j=0;j<m;j++)
			scanf("%d", &max[i][j]);

	printf ("please input available vector\n");
	for (j=0;j<m;j++)
		scanf("%d", &available[j]);

	for (i=0;i<n;i++)
		for (j=0;j<m;j++)
			/****************** get the need matrix here ************************/	

	printf ("please input the process No. that request new resources\n");
	scanf("%d", &id);

	printf ("please input the request vector\n");
	for (j=0;j<m;j++)
		scanf("%d", &request[j]);

	
	printf ("#########################################\n");
	printf ("Allocation Matrix\n");
	for (i=0;i<n;i++)
	{
		printf ("P%d\t\t",i);
		for (j=0;j<m;j++)
			printf ("%d\t",allocation[i][j]); 
		printf ("\n");
	}

	printf ("Max Matrix\n");
	for (i=0;i<n;i++)
	{
		printf ("P%d\t\t",i);
		for (j=0;j<m;j++)
			printf ("%d\t",max[i][j]); 
		printf ("\n");
	}

	printf ("Available Vector\n");
	for (j=0;j<m;j++)
		printf ("%d\t",available[j]);
	printf ("\n");

	printf ("with additional resouces requests\nP%d\t\t",id);
	for (j=0;j<m;j++)
		printf ("%d\t", request[j]);
	printf ("\n");

	for (j=0;j<m;j++)
	{
		/************** a new request, available matrix should be modified **********************/
		
		
		if (available[j]<0)
		{
			printf ("unsafe!\n");
			return 0;
		}
		/************** a new request, allocation and need matrix should be modified ******************/
		
		
		
	}

	for (i=0;i<n;i++)
		finish[i] = 0;
	for (j=0;j<m;j++)
		work[j] = available[j];
   
  //pay attention to the thread mutual exclusion
	printf ("start...\n");
	for (i=0;i<n;i++)
	{
		proc_ids[i] = i;
		/******************** init and creat threads here, which will implement start_banker with parameter "process id" *********/
		
	}
	sleep(1);
	for (i=0;i<n;i++)
	{
		if (finish[i]==0)
		{
			printf ("unsafe!!\n");
			break;
		}
	}
	if (i==n)
		printf ("safe!!\n");
	stop_flag = 1;
	printf ("Finish...\n");
	sleep(1);
	for (i=0;i<n;i++)
		/******************** use XX function here to wait the threads to finish **********************/
		
		
	return 0;
}

void *start_banker(void *param)
{
	int j;
	int id = *(int *)param; //process id
	
	while (!stop_flag && !finish[id]) 
	{
		for (j=0;j<m;j++)
		{
			if (need[id][j]> ?? /************* fill the condition to break ***********/)
				break;
		}
		if (j==m) // need <= work
		{
			/******************** fill the code here to calculate work matrix and set finish value *******************/
			
			printf ("P%d finished\n",id);
			
		}
	}
	pthread_exit(0);
}
