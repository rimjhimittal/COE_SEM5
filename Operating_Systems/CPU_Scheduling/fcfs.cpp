// FCFS CPU SCHEDULING ALGORITHM For FCFS scheduling algorithm, read the number of processes/jobs in the system, their CPU burst times. The scheduling is performed on the basis of arrival time of the processes irrespective of their other parameters. Each process will be executed according to its arrival time. Calculate the waiting time and turnaround time of each of the processes accordingly
#include <iostream>
using namespace std;

void waitingTime(int processes[], int n, int bt[],
                 int wt[], int at[])
{
    int time[n];
    time[0] = at[0];
    wt[0] = 0;

    for (int i = 1; i < n; i++)
    {
        time[i] = time[i - 1] + bt[i - 1];
        wt[i] = time[i] - at[i];

        if (at[i] > time[i])
        {
            time[i] = at[i];
        }
        if (wt[i] < 0)
            wt[i] = 0;
    }
}

void TurnAroundTime(int processes[], int n, int bt[],
                    int wt[], int tat[])
{

    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void avgTime(int processes[], int n, int bt[], int at[])
{
    int wt[n], tat[n];

    waitingTime(processes, n, bt, wt, at);

    TurnAroundTime(processes, n, bt, wt, tat);

    cout << "Processes "
         << " Burst Time "
         << " Arrival Time "
         << " Waiting Time "
         << " Turn-Around Time "
         << " Completion Time \n";
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        int compl_time = tat[i] + at[i];
        cout << " " << i + 1 << "\t\t" << bt[i] << "\t\t"
             << at[i] << "\t\t" << wt[i] << "\t\t "
             << tat[i] << "\t\t " << compl_time << endl;
    }

    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}

// Driver code
int main()
{
    int processes[] = {0, 1, 2, 3, 4, 5, 6};
    int n = sizeof processes / sizeof processes[0];

    int burst_time[] = {3, 6, 4, 6, 3, 2, 5};

    int arrival_time[] = {0, 3, 6, 10, 16, 18, 20};

    avgTime(processes, n, burst_time, arrival_time);

    return 0;
}