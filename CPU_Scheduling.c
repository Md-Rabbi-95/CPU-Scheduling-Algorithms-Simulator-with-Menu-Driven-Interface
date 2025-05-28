#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
typedef struct process
{
char name[5];
int bt;
int at;
int prt;
int wt, ta;
int flag;
} processes;
void ganttChart(processes proc[], int n)
{
int i, j;
int g[10], h[10]; // g[] for burst times, h[] for timeline
int timeline = 0;
// Prepare the Gantt chart data
for (i = 0; i < n; i++)
{
g[i] = proc[i].bt;
h[i] = timeline + proc[i].bt;
timeline += proc[i].bt;
}
// Print top bar
printf(" ");
for (i = 0; i < n; i++)
{
for (j = 0; j < g[i]; j++) printf("--");
printf(" ");
}
printf("\n|");
// Print process names
for (i = 0; i < n; i++)
{
for (j = 0; j < g[i] - 1; j++) printf(" ");
printf("P%d", i + 1);
for (j = 0; j < g[i] - 1; j++) printf(" ");
printf("|");
}
printf("\n ");
// Print bottom bar
for (i = 0; i < n; i++)
{
for (j = 0; j < g[i]; j++) printf("--");
printf(" ");
}
printf("\n");
// Print timeline
printf("0");
for (i = 0; i < n; i++)
{
for (j = 0; j < g[i]; j++) printf(" ");
if (h[i] > 9) printf("\b"); // Adjust spacing for 2-digit times
printf("%d", h[i]);
}
printf("\n");
}
void bubble_sort(processes proc[], int n)
{
processes t;
int i, j;
for (i = 1; i < n; i++)
{
for (j = 0; j < n - i; j++)
{
if (proc[j].at > proc[j + 1].at)
{
t = proc[j];
proc[j] = proc[j + 1];
proc[j + 1] = t;
}
}
}
}
void bubble_sort1(processes proc[], int n)
{
processes t;
int i, j;
for (i = 0; i < n - 1; i++)
{
for (j = 0; j < n - i - 1; j++)
{
if (proc[j].prt > proc[j + 1].prt)
{
t = proc[j];
proc[j] = proc[j + 1];
proc[j + 1] = t;
}
}
}
}
int get_Processes(processes P[])
{
int i, n;
printf("\nEnter total number of processes: ");
scanf("%d", &n);
for (i = 0; i < n; i++)
{
printf("\nPROCESS [%d]", i + 1);
printf("\nEnter process name: ");
scanf("%s", P[i].name);
printf("Enter arrival time: ");
scanf("%d", &P[i].at);
printf("Enter burst time: ");
scanf("%d", &P[i].bt);
printf("Enter priority: ");
scanf("%d", &P[i].prt);
}
printf("\nProcess Name\tArrival Time\tBurst Time\tPriority");
for (i = 0; i < n; i++)
{
printf("\n%s\t\t%d\t\t%d\t\t%d", P[i].name, P[i].at, P[i].bt, P[i].prt);
}
return n;
}
void FCFS(processes P[], int n)
{
processes proc[10];
int sumw = 0, sumt = 0;
float avgwt = 0.0, avgta = 0.0;
int i;
for (i = 0; i < n; i++)
{
proc[i] = P[i];
}
bubble_sort(proc, n);
sumw = proc[0].wt = 0;
sumt = proc[0].ta = proc[0].bt;
for (i = 1; i < n; i++)
{
proc[i].wt = proc[i - 1].bt + proc[i - 1].wt - proc[i].at;
if (proc[i].wt < 0) proc[i].wt = 0; // Ensure no negative waiting time
proc[i].ta = proc[i].wt + proc[i].bt;
sumw += proc[i].wt;
sumt += proc[i].ta;
}
avgwt = (float)sumw / n;
avgta = (float)sumt / n;
printf("\n\nPROCESS_NAME\tA.T.\tB.T.\tW.T.\tT.A.T");
for (i = 0; i < n; i++)
{
printf("\n%s\t\t%d\t%d\t%d\t%d", proc[i].name, proc[i].at, proc[i].bt,
proc[i].wt, proc[i].ta);
}
printf("\n\nAverage waiting time = %.2f\nAverage turn-around = %.2f\n",
avgwt, avgta);
ganttChart(proc, n);
}
//Shortest Job First - Preemptive
void SJF_P(processes P[], int n)
{
int t_total = 0, tcurr = 0, sumw = 0, sumt = 0;
float avgwt = 0.0, avgta = 0.0;
processes proc[10];
// Copy processes to proc[] and calculate total burst time
for (int i = 0; i < n; i++)
{
proc[i] = P[i];
t_total += P[i].bt;
}
// Sort processes by arrival time first, then burst time
bubble_sort1(proc, n);
printf("\n\nProcess Name\tArrival Time\tBurst Time\n");
for (int i = 0; i < n; i++)
{
printf("%s\t\t\t%d\t\t%d\n", proc[i].name, proc[i].at, proc[i].bt);
}
// SJF scheduling with preemption
int rt[10], complete = 0, shortest = 0, check = 0, finish_time;
for (int i = 0; i < n; i++)
{
rt[i] = proc[i].bt;
}
while (complete != n)
{
int minm = INT_MAX;
for (int j = 0; j < n; j++)
{
if (proc[j].at <= tcurr && rt[j] < minm && rt[j] > 0)
{
minm = rt[j];
shortest = j;
check = 1;
}
}
if (check == 0)
{
tcurr++;
continue;
}
rt[shortest]--;
minm = rt[shortest];
if (minm == 0)
{
minm = INT_MAX;
}
if (rt[shortest] == 0)
{
complete++;
finish_time = tcurr + 1;
proc[shortest].wt = finish_time - proc[shortest].bt - proc[shortest].at;
if (proc[shortest].wt < 0)
{
proc[shortest].wt = 0;
}
proc[shortest].ta = proc[shortest].wt + proc[shortest].bt;
sumw += proc[shortest].wt;
sumt += proc[shortest].ta;
}
tcurr++;
}
avgwt = (float)sumw / n;
avgta = (float)sumt / n;
printf("\n\n PROCESS_NAME\tA.T.\tB.T.\tW.T\tT.A.T");
for (int i = 0; i < n; i++)
{
printf("\n %s\t\t %d\t %d\t %d\t %d\n", proc[i].name, proc[i].at, proc[i].bt,
proc[i].wt, proc[i].ta);
}
printf("\n\nAverage waiting time = %0.2f\nAverage turn-around = %0.2f",
avgwt, avgta);
printf("\n\n");
ganttChart(P,n);
}
//SJF Non-Preemptive
void SJF_NP(processes P[], int n)
{
processes proc[10], t;
int sumw = 0, sumt = 0;
float avgwt = 0.0, avgta = 0.0;
int i, j;
// Copy input processes into local array
for (i = 0; i < n; i++)
proc[i] = P[i];
// Sort processes by arrival time
bubble_sort(proc, n);
// Sort processes by burst time for processes with the same arrival time
for (i = 0; i < n - 1; i++)
{
for (j = 0; j < n - i - 1; j++)
{
if (proc[j].at == proc[j + 1].at && proc[j].bt > proc[j + 1].bt)
{
t = proc[j];
proc[j] = proc[j + 1];
proc[j + 1] = t;
}
}
}
// Display processes after sorting
printf("\n\n Process Name\tArrival Time\tBurst Time");
for (i = 0; i < n; i++)
printf("\n %s\t\t\t %d\t %d", proc[i].name, proc[i].at, proc[i].bt);
// Calculate waiting time and turnaround time
proc[0].wt = 0; // First process has no waiting time
proc[0].ta = proc[0].bt - proc[0].at; // Turnaround time = burst time - arrival time
sumw = proc[0].wt;
sumt = proc[0].ta;
for (i = 1; i < n; i++)
{
proc[i].wt = (proc[i - 1].wt + proc[i - 1].bt + proc[i - 1].at) - proc[i].at;
if (proc[i].wt < 0) proc[i].wt = 0; // Handle negative waiting times
proc[i].ta = proc[i].wt + proc[i].bt;
sumw += proc[i].wt;
sumt += proc[i].ta;
}
avgwt = (float)sumw / n;
avgta = (float)sumt / n;
// Display final results
printf("\n\n PROCESS_NAME\tA.T.\tB.T.\tW.T\tT.A.T");
for (i = 0; i < n; i++)
printf("\n %s\t\t %d\t %d\t %d\t %d", proc[i].name, proc[i].at, proc[i].bt,
proc[i].wt, proc[i].ta);
printf("\n\n Average waiting time = %.2f", avgwt);
printf("\n Average turn-around time = %.2f\n\n", avgta);
// Uncomment the line below if ganttChart function is defined
ganttChart(P, n);
}
// Priority - Preemptive
void Priority_P(processes proc[], int n)
{
int sumw = 0, sumt = 0; // Total waiting and turnaround times
float avgwt = 0.0, avgta = 0.0;
int i, completed = 0, current_time = 0;
int remaining_time[n]; // Track remaining burst time
int is_completed[n]; // Track if a process is completed
for (i = 0; i < n; i++)
{
remaining_time[i] = proc[i].bt;
is_completed[i] = 0;
}
printf("\n\nPROCESS_NAME\tA.T.\tB.T.\tP.T.\tW.T.\tT.A.T");
// Process scheduling loop
while (completed < n)
{
int current_process = -1;
int highest_priority = 9999;
// Find the highest-priority process that has arrived
for (i = 0; i < n; i++)
{
if (proc[i].at <= current_time && !is_completed[i] && proc[i].prt <
highest_priority)
{
highest_priority = proc[i].prt;
current_process = i;
}
}
if (current_process != -1)
{
// Execute the selected process for 1 unit of time
remaining_time[current_process]--;
current_time++;
// If the process completes
if (remaining_time[current_process] == 0)
{
is_completed[current_process] = 1;
completed++;
// Calculate Turnaround Time (T.A.T) and Waiting Time (W.T)
proc[current_process].ta = current_time -
proc[current_process].at;
proc[current_process].wt = proc[current_process].ta -
proc[current_process].bt;
// Print process details when completed
printf("\n%s\t\t%d\t%d\t%d\t%d\t%d",
proc[current_process].name, proc[current_process].at, proc[current_process].bt,
proc[current_process].prt, proc[current_process].wt, proc[current_process].ta);
// Accumulate total waiting and turnaround times
sumw += proc[current_process].wt;
sumt += proc[current_process].ta;
}
}
else
{
// No process is ready; increment time
current_time++;
}
}
// Calculate and print averages
avgwt = (float)sumw / n;
avgta = (float)sumt / n;
printf("\n\nAverage Waiting Time: %.2f", avgwt);
printf("\nAverage Turnaround Time: %.2f\n", avgta);
ganttChart(proc, n);
}
//Priority Non-Preemptive
void Priority_NP(struct process proc[], int n)
{
int sumw = 0, sumt = 0;
float avgwt = 0.0, avgta = 0.0;
int timeline = 0;
// Sorting the processes by their priority
bubble_sort(proc, n);
// Printing Process Information
printf("\nPROC.\tB.T.\tA.T.\tPRIORITY");
for (int i = 0; i < n; i++)
{
printf("\n%s\t%d\t%d\t%d", proc[i].name, proc[i].bt, proc[i].at, proc[i].prt);
}
// Initializing first process' Waiting Time and Turnaround Time
proc[0].wt = 0;
proc[0].ta = proc[0].bt;
sumw = proc[0].wt;
sumt = proc[0].ta;
timeline = proc[0].at + proc[0].bt;
// Calculate Waiting Time and Turnaround Time for each process
for (int i = 1; i < n; i++)
{
if (timeline < proc[i].at)
{
timeline = proc[i].at;
}
proc[i].wt = timeline - proc[i].at;
proc[i].ta = proc[i].wt + proc[i].bt;
timeline += proc[i].bt;
sumw += proc[i].wt;
sumt += proc[i].ta;
}
// Calculating average waiting time and turnaround time
avgwt = (float)sumw / n;
avgta = (float)sumt / n;
// Printing the result
printf("\n\nPROCESS_NAME\tA.T.\tB.T.\tW.T.\tT.A.T");
for (int i = 0; i < n; i++)
{
printf("\n%s\t\t%d\t%d\t%d\t%d\n", proc[i].name, proc[i].at, proc[i].bt,
proc[i].wt, proc[i].ta);
}
// Printing Average Waiting Time and Turnaround Time
printf("\n\nAverage waiting time = %.2f", avgwt);
printf("\nAverage turnaround time = %.2f\n", avgta);
ganttChart(proc, n);
}
//Round Robin Scheduling
void RR(processes P[], int n)
{
int pflag = 0, t, tcurr = 0, k, i, Q = 0;
int sumw = 0, sumt = 0;
float avgwt = 0.0, avgta = 0.0;
processes proc1[10], proc2[10];
for (i = 0; i < n; i++)
proc1[i] = P[i];
bubble_sort(proc1, n);
for (i = 0; i < n; i++)
proc2[i] = proc1[i];
printf("\n Enter quantum time : ");
scanf("%d", & Q);
if (Q <= 0)
{
printf("Quantum time must be greater than 0.\n");
return;
}
else
{
for (k = 0;; k++)
{
if (k > n - 1)
k = 0;
if (proc1[k].bt > 0)
printf(" %d %s", tcurr, proc1[k].name);
t = 0;
while (t < Q && proc1[k].bt > 0)
{
t++;
tcurr++;
proc1[k].bt--;
}
if (proc1[k].bt <= 0 && proc1[k].flag != 1)
{
proc1[k].wt = tcurr - proc2[k].bt - proc1[k].at;
proc1[k].ta = tcurr - proc1[k].at;
pflag++;
proc1[k].flag = 1;
sumw += proc1[k].wt;
sumt += proc1[k].ta;
}
if (pflag == n)
break;
}
}
printf(" %d", tcurr);
avgwt = (float) sumw / n;
avgta = (float) sumt / n;
printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",
avgwt, avgta);
printf("\n\n");
ganttChart(P, n);
}
int main()
{
processes P[10];
int ch, n;
do
{
printf("\n\n SIMULATION OF CPU SCHEDULING ALGORITHMS\n");
printf("\n Options:");
printf("\n 1. Enter process data:");
printf("\n 2. FCFS");
printf("\n 3. SJF (Preemptive)");
printf("\n 4. SJF (Non-Preemptive)");
printf("\n 5. Priority Scheduling (Preemptive)");
printf("\n 6. Priority Scheduling (Non-Preemptive)");
printf("\n 7. Round Robin");
printf("\n 0. Exit\n Select an option: ");
scanf("%d", & ch);
switch (ch)
{
case 1:
n = get_Processes(P);
break;
case 2:
FCFS(P, n);
break;
case 3:
SJF_P(P, n);
break;
case 4:
SJF_NP(P, n);
break;
case 5:
Priority_P(P, n);
break;
case 6:
Priority_NP(P, n);
break;
case 7:
RR(P, n);
break;
case 0:
exit(0);
}
}
while (ch != 7);
return 0;
}
