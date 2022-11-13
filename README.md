# os


FCFS

// C++ program for implementation of FCFS
// scheduling
#include<iostream>
using namespace std;
 
// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n,
                          int bt[], int wt[])
{
    // waiting time for first process is 0
    wt[0] = 0;
 
    // calculating waiting time
    for (int  i = 1; i < n ; i++ )
        wt[i] =  bt[i-1] + wt[i-1] ;
}
 
// Function to calculate turn around time
void findTurnAroundTime( int processes[], int n,
                  int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int  i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
 
//Function to calculate average time
void findavgTime( int processes[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
 
    //Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt);
 
    //Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);
 
    //Display processes along with all details
    cout << "Processes  "<< " Burst time  "
         << " Waiting time  " << " Turn around time\n";
 
    // Calculate total waiting time and total turn
    // around time
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << "   " << i+1 << "\t\t" << bt[i] <<"\t    "
            << wt[i] <<"\t\t  " << tat[i] <<endl;
    }
 
    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}
 
// Driver code
int main()
{
    //process id's
    int processes[] = { 1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
 
    //Burst time of all processes
    int  burst_time[] = {10, 5, 8};
 
    findavgTime(processes, n,  burst_time);
    return 0;
}








SJF(Non-premptitive)


#include <stdio.h>
int main()
{
    int A[100][4]; // Matrix for storing Process Id, Burst
                   // Time, Average Waiting Time & Average
                   // Turn Around Time.
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");
    // User Input Burst Time and alloting Process Id.
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);
        A[i][0] = i + 1;
    }
    // Sorting process according to their Burst Time.
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++)
            if (A[j][1] < A[index][1])
                index = j;
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;
 
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }
    A[0][2] = 0;
    // Calculation of Waiting Times
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++)
            A[i][2] += A[j][1];
        total += A[i][2];
    }
    avg_wt = (float)total / n;
    total = 0;
    printf("P     BT     WT     TAT\n");
    // Calculation of Turn Around Time and printing the
    // data.
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];
        total += A[i][3];
        printf("P%d     %d     %d      %d\n", A[i][0],
               A[i][1], A[i][2], A[i][3]);
    }
    avg_tat = (float)total / n;
    printf("Average Waiting Time= %f", avg_wt);
    printf("\nAverage Turnaround Time= %f", avg_tat);
}





SJF(premptive)


#include <bits/stdc++.h>
using namespace std;
  
struct Process {
    int pid; // Process ID
    int bt; // Burst Time
    int art; // Arrival Time
};
  
// Function to find the waiting time for all
// processes
void findWaitingTime(Process proc[], int n,
                                int wt[])
{
    int rt[n];
  
    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;
  
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
  
    // Process until all processes gets
    // completed
    while (complete != n) {
  
        // Find process with minimum
        // remaining time among the
        // processes that arrives till the
        // current time`
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) &&
            (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
  
        if (check == false) {
            t++;
            continue;
        }
  
        // Reduce remaining time by one
        rt[shortest]--;
  
        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
  
        // If a process gets completely
        // executed
        if (rt[shortest] == 0) {
  
            // Increment complete
            complete++;
            check = false;
  
            // Find finish time of current
            // process
            finish_time = t + 1;
  
            // Calculate waiting time
            wt[shortest] = finish_time -
                        proc[shortest].bt -
                        proc[shortest].art;
  
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        // Increment time
        t++;
    }
}
  
// Function to calculate turn around time
void findTurnAroundTime(Process proc[], int n,
                        int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}
  
// Function to calculate average time
void findavgTime(Process proc[], int n)
{
    int wt[n], tat[n], total_wt = 0,
                    total_tat = 0;
  
    // Function to find waiting time of all
    // processes
    findWaitingTime(proc, n, wt);
  
    // Function to find turn around time for
    // all processes
    findTurnAroundTime(proc, n, wt, tat);
  
    // Display processes along with all
    // details
    cout << " P\t\t"
        << "BT\t\t"
        << "WT\t\t"
        << "TAT\t\t\n";
  
    // Calculate total waiting time and
    // total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << proc[i].pid << "\t\t"
            << proc[i].bt << "\t\t " << wt[i]
            << "\t\t " << tat[i] << endl;
    }
  
    cout << "\nAverage waiting time = "
        << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
        << (float)total_tat / (float)n;
}
  
// Driver code
int main()
{
    Process proc[] = { { 1, 6, 2 }, { 2, 2, 5 },
                    { 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);
  
    findavgTime(proc, n);
    return 0;
}






Round-robin


// C++ program for implementation of RR scheduling
#include<iostream>
using namespace std;

// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n,
			int bt[], int wt[], int quantum)
{
	// Make a copy of burst times bt[] to store remaining
	// burst times.
	int rem_bt[n];
	for (int i = 0 ; i < n ; i++)
		rem_bt[i] = bt[i];

	int t = 0; // Current time

	// Keep traversing processes in round robin manner
	// until all of them are not done.
	while (1)
	{
		bool done = true;

		// Traverse all processes one by one repeatedly
		for (int i = 0 ; i < n; i++)
		{
			// If burst time of a process is greater than 0
			// then only need to process further
			if (rem_bt[i] > 0)
			{
				done = false; // There is a pending process

				if (rem_bt[i] > quantum)
				{
					// Increase the value of t i.e. shows
					// how much time a process has been processed
					t += quantum;

					// Decrease the burst_time of current process
					// by quantum
					rem_bt[i] -= quantum;
				}

				// If burst time is smaller than or equal to
				// quantum. Last cycle for this process
				else
				{
					// Increase the value of t i.e. shows
					// how much time a process has been processed
					t = t + rem_bt[i];

					// Waiting time is current time minus time
					// used by this process
					wt[i] = t - bt[i];

					// As the process gets fully executed
					// make its remaining burst time = 0
					rem_bt[i] = 0;
				}
			}
		}

		// If all processes are done
		if (done == true)
		break;
	}
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
						int bt[], int wt[], int tat[])
{
	// calculating turnaround time by adding
	// bt[i] + wt[i]
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],
									int quantum)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	// Function to find waiting time of all processes
	findWaitingTime(processes, n, bt, wt, quantum);

	// Function to find turn around time for all processes
	findTurnAroundTime(processes, n, bt, wt, tat);

	// Display processes along with all details
	cout << "PN\t "<< " \tBT "
		<< " WT " << " \tTAT\n";

	// Calculate total waiting time and total turn
	// around time
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
			<< wt[i] <<"\t\t " << tat[i] <<endl;
	}

	cout << "Average waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
}

// Driver code
int main()
{
	// process id's
	int processes[] = { 1, 2, 3};
	int n = sizeof processes / sizeof processes[0];

	// Burst time of all processes
	int burst_time[] = {10, 5, 8};

	// Time quantum
	int quantum = 2;
	findavgTime(processes, n, burst_time, quantum);
	return 0;
}




Priority Scheduling

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






Priority Scheduling with different arrival time


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






Fork


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
main()
{
pid_t pid;
int x = 5;
pid =
fork(); x++;
if (pid < 0)
{
printf("Process creation
error"); exit(-1);
}
else if (pid == 0)
{
printf("Child process:");
printf("\nProcess id is %d", getpid());
printf("\nValue of x is %d", x);
printf("\nProcess id of parent is %d\n", getppid());
}
else
{
printf("\nParent process:");
printf("\nProcess id is %d", getpid());
printf("\nValue of x is %d", x);
printf("\nProcess id of shell is %d\n", getppid());
}
}




Wait

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
main()
{
int i, status;
pid_t pid;
pid = fork();
if (pid < 0)
{
printf("\nProcess creation
failure\n"); exit(-1);
}
else if(pid > 0)
{
wait(NULL);
printf ("\nParent starts\nEven Nos:
"); for (i=2;i<=10;i+=2)
printf ("%3d",i); printf
("\nParent ends\n");
}
else if (pid == 0)
{
printf ("Child starts\nOdd Nos:
"); for (i=1;i<10;i+=2)
printf ("%3d",i);
printf ("\nChild ends\n");
}
}





Exec


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
main(int argc, char*argv[])
{
pid_t pid;
int i;
if (argc != 3)
{
printf("\nInsufficient arguments to load program");
printf("\nUsage: ./a.out <path> <cmd>\n"); exit(-
1);
}
switch(pid = fork())
{
case -1:
printf("Fork
failed"); exit(-1);
case 0:
printf("Child process\n");
i = execl(argv[1], argv[2],
0); if (i < 0)
{
printf("%s program not loaded using exec
system call\n", argv[2]);
exit(-1);
}
default:
wait(NULL);
printf("Child
Terminated\n"); exit(0);
}
}

