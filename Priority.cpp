Same arrival time--
  
  // C++ program for implementation of FCFS
// scheduling
#include<bits/stdc++.h>
using namespace std;

struct Process
{
	int pid; // Process ID
	int bt; // CPU Burst time required
	int priority; // Priority of this process
};

// Function to sort the Process acc. to priority
bool comparison(Process a, Process b)
{
	return (a.priority > b.priority);
}

// Function to find the waiting time for all
// processes
void findWaitingTime(Process proc[], int n,
					int wt[])
{
	// waiting time for first process is 0
	wt[0] = 0;

	// calculating waiting time
	for (int i = 1; i < n ; i++ )
		wt[i] = proc[i-1].bt + wt[i-1] ;
}

// Function to calculate turn around time
void findTurnAroundTime( Process proc[], int n,
						int wt[], int tat[])
{
	// calculating turnaround time by adding
	// bt[i] + wt[i]
	for (int i = 0; i < n ; i++)
		tat[i] = proc[i].bt + wt[i];
}

//Function to calculate average time
void findavgTime(Process proc[], int n)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	//Function to find waiting time of all processes
	findWaitingTime(proc, n, wt);

	//Function to find turn around time for all processes
	findTurnAroundTime(proc, n, wt, tat);

	//Display processes along with all details
	cout << "\nProcesses "<< " Burst time "
		<< " Waiting time " << " Turn around time\n";

	// Calculate total waiting time and total turn
	// around time
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << proc[i].pid << "\t\t"
			<< proc[i].bt << "\t " << wt[i]
			<< "\t\t " << tat[i] <<endl;
	}

	cout << "\nAverage waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
}

void priorityScheduling(Process proc[], int n)
{
	// Sort processes by priority
	sort(proc, proc + n, comparison);

	cout<< "Order in which processes gets executed \n";
	for (int i = 0 ; i < n; i++)
		cout << proc[i].pid <<" " ;

	findavgTime(proc, n);
}

// Driver code
int main()
{
	Process proc[] = {{1, 10, 2}, {2, 5, 0}, {3, 8, 1}};
	int n = sizeof proc / sizeof proc[0];
	priorityScheduling(proc, n);
	return 0;
}









Different arrival time--
  // C++ implementation for Priority Scheduling with
//Different Arrival Time priority scheduling
/*1. sort the processes according to arrival time
2. if arrival time is same the acc to priority
3. apply fcfs
*/

#include <bits/stdc++.h>

using namespace std;

#define totalprocess 5

// Making a struct to hold the given input

struct process
{
int at,bt,pr,pno;
};

process proc[50];

/*
Writing comparator function to sort according to priority if
arrival time is same
*/

bool comp(process a,process b)
{
if(a.at == b.at)
{
return a.pr<b.pr;
}
else
{
	return a.at<b.at;
}
}

// Using FCFS Algorithm to find Waiting time
void get_wt_time(int wt[])
{
// declaring service array that stores cumulative burst time
int service[50];

// Initialising initial elements of the arrays
service[0] = proc[0].at;
wt[0]=0;


for(int i=1;i<totalprocess;i++)
{
service[i]=proc[i-1].bt+service[i-1];

wt[i]=service[i]-proc[i].at;

// If waiting time is negative, change it into zero
	
	if(wt[i]<0)
	{
	wt[i]=0;
	}
}

}

void get_tat_time(int tat[],int wt[])
{
// Filling turnaroundtime array

for(int i=0;i<totalprocess;i++)
{
	tat[i]=proc[i].bt+wt[i];
}
	
}

void findgc()
{
//Declare waiting time and turnaround time array
int wt[50],tat[50];

double wavg=0,tavg=0;

// Function call to find waiting time array
get_wt_time(wt);
//Function call to find turnaround time
get_tat_time(tat,wt);
	
int stime[50],ctime[50];

stime[0] = proc[0].at;
ctime[0]=stime[0]+tat[0];

// calculating starting and ending time
for(int i=1;i<totalprocess;i++)
	{
		stime[i]=ctime[i-1];
		ctime[i]=stime[i]+tat[i]-wt[i];
	}
	
cout<<"Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time"<<endl;
	
	// display the process details
	
for(int i=0;i<totalprocess;i++)
	{
		wavg += wt[i];
		tavg += tat[i];
		
		cout<<proc[i].pno<<"\t\t"<<
			stime[i]<<"\t\t"<<ctime[i]<<"\t\t"<<
			tat[i]<<"\t\t\t"<<wt[i]<<endl;
	}
	
		// display the average waiting time
		//and average turn around time
	
	cout<<"Average waiting time is : ";
	cout<<wavg/(float)totalprocess<<endl;
	cout<<"average turnaround time : ";
	cout<<tavg/(float)totalprocess<<endl;

}

int main()
{
int arrivaltime[] = { 1, 2, 3, 4, 5 };
int bursttime[] = { 3, 5, 1, 7, 4 };
int priority[] = { 3, 4, 1, 7, 8 };
	
for(int i=0;i<totalprocess;i++)
{
	proc[i].at=arrivaltime[i];
	proc[i].bt=bursttime[i];
	proc[i].pr=priority[i];
	proc[i].pno=i+1;
	}
	
	//Using inbuilt sort function
	
	sort(proc,proc+totalprocess,comp);
	
	//Calling function findgc for finding Gantt Chart
	
	findgc();

	return 0;
}

// This code is contributed by Anukul Chand.
