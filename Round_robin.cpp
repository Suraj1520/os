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

























With different arrival time
//C++ Program for implementing
//Round Robin Algorithm
//code by sparsh_cbs
#include <iostream>

using namespace std;

void queueUpdation(int queue[],int timer,int arrival[],int n, int maxProccessIndex){
	int zeroIndex;
	for(int i = 0; i < n; i++){
		if(queue[i] == 0){
			zeroIndex = i;
			break;
		}
	}
	queue[zeroIndex] = maxProccessIndex + 1;
}

void queueMaintainence(int queue[], int n){
	for(int i = 0; (i < n-1) && (queue[i+1] != 0) ; i++){
		int temp = queue[i];
		queue[i] = queue[i+1];
		queue[i+1] = temp;
	}
}

void checkNewArrival(int timer, int arrival[], int n, int maxProccessIndex,int queue[]){
	if(timer <= arrival[n-1]){
	bool newArrival = false;
	for(int j = (maxProccessIndex+1); j < n; j++){
			if(arrival[j] <= timer){
			if(maxProccessIndex < j){
				maxProccessIndex = j;
				newArrival = true;
			}
		}
	}
	//adds the incoming process to the ready queue
	//(if any arrives)
	if(newArrival)
		queueUpdation(queue,timer,arrival,n, maxProccessIndex);
	}
}

//Driver Code
int main(){
	int n,tq, timer = 0, maxProccessIndex = 0;
	float avgWait = 0, avgTT = 0;
	cout << "\nEnter the time quanta : ";
	cin>>tq;
	cout << "\nEnter the number of processes : ";
	cin>>n;
	int arrival[n], burst[n], wait[n], turn[n], queue[n], temp_burst[n];
	bool complete[n];

	cout << "\nEnter the arrival time of the processes : ";
	for(int i = 0; i < n; i++)
		cin>>arrival[i];

	cout << "\nEnter the burst time of the processes : ";
	for(int i = 0; i < n; i++){
		cin>>burst[i];
		temp_burst[i] = burst[i];
	}

	for(int i = 0; i < n; i++){ //Initializing the queue and complete array
		complete[i] = false;
		queue[i] = 0;
	}
	while(timer < arrival[0]) //Incrementing Timer until the first process arrives
		timer++;
	queue[0] = 1;
	
	while(true){
		bool flag = true;
		for(int i = 0; i < n; i++){
			if(temp_burst[i] != 0){
				flag = false;
				break;
			}
		}
		if(flag)
			break;

		for(int i = 0; (i < n) && (queue[i] != 0); i++){
			int ctr = 0;
			while((ctr < tq) && (temp_burst[queue[0]-1] > 0)){
				temp_burst[queue[0]-1] -= 1;
				timer += 1;
				ctr++;

				//Checking and Updating the ready queue until all the processes arrive
				checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
			}
			//If a process is completed then store its exit time
			//and mark it as completed
			if((temp_burst[queue[0]-1] == 0) && (complete[queue[0]-1] == false)){
				//turn array currently stores the completion time
				turn[queue[0]-1] = timer;	
				complete[queue[0]-1] = true;
			}
			
			//checks whether or not CPU is idle
			bool idle = true;
			if(queue[n-1] == 0){
				for(int i = 0; i < n && queue[i] != 0; i++){
					if(complete[queue[i]-1] == false){
						idle = false;
					}
				}
			}
			else
				idle = false;

			if(idle){
				timer++;
				checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
			}
	
			//Maintaining the entries of processes
			//after each premption in the ready Queue
			queueMaintainence(queue,n);
		}
	}

	for(int i = 0; i < n; i++){
		turn[i] = turn[i] - arrival[i];
		wait[i] = turn[i] - burst[i];
	}

	cout << "\nProgram No.\tArrival Time\tBurst Time\tWait Time\tTurnAround Time"
		<< endl;
	for(int i = 0; i < n; i++){
		cout<<i+1<<"\t\t"<<arrival[i]<<"\t\t"
		<<burst[i]<<"\t\t"<<wait[i]<<"\t\t"<<turn[i]<<endl;
	}
	for(int i =0; i< n; i++){
		avgWait += wait[i];
		avgTT += turn[i];
	}
	cout<<"\nAverage wait time : "<<(avgWait/n)
	<<"\nAverage Turn Around Time : "<<(avgTT/n);

	return 0;
	
}

