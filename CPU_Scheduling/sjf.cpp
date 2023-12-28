// SJF CPU SCHEDULING ALGORITHM For SJF scheduling algorithm, read the number of processes/jobs in the system, their CPU burst times. Arrange all the jobs in order with respect to their burst times. There may be two jobs in queue with the same execution time, and then FCFS approach is to be performed. Each process will be executed according to the length of its burst time. Then calculate the waiting time and turnaround time of each of the processes accordingly.
#include <iostream>
using namespace std;
int main()
{
    int Matrix[100][4]; // For storing Process Id, Burst
                        // Time, Average Waiting Time & Average
                        // Turn Around Time.
    int i, j, n, index, temp, total = 0;
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");
    // User Input Burst Time and alloting Process Id.
    for (i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &Matrix[i][1]);
        Matrix[i][0] = i + 1;
    }
    // Sorting process according to their Burst Time.
    for (i = 0; i < n; i++)
    {
        index = i;
        for (j = i + 1; j < n; j++)
            if (Matrix[j][1] < Matrix[index][1])
                index = j;
        temp = Matrix[i][1];
        Matrix[i][1] = Matrix[index][1];
        Matrix[index][1] = temp;

        temp = Matrix[i][0];
        Matrix[i][0] = Matrix[index][0];
        Matrix[index][0] = temp;
    }
    Matrix[0][2] = 0;
    // Calculation of Waiting Times
    for (i = 1; i < n; i++)
    {
        Matrix[i][2] = 0;
        for (j = 0; j < i; j++)
            Matrix[i][2] += Matrix[j][1];
        total += Matrix[i][2];
    }
    float avg_wt, avg_tat;
    avg_wt = (float)total / n;
    total = 0;
    printf("Process	 BT	 WT	 TAT\n");
    // Calculation of Turn Around Time and printing the
    // data.
    for (i = 0; i < n; i++)
    {
        Matrix[i][3] = Matrix[i][1] + Matrix[i][2];
        total += Matrix[i][3];
        printf("P%d	 %d	 %d	 %d\n", Matrix[i][0],
               Matrix[i][1], Matrix[i][2], Matrix[i][3]);
    }
    avg_tat = (float)total / n;
    printf("Average Waiting Time= %f", avg_wt);
    printf("\nAverage Turnaround Time= %f", avg_tat);
}
