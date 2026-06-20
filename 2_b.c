#include <stdio.h>
#include <stdlib.h>
typedef struct process
{
    int Id, at, bt, ct, tat, wt, p, iscompl;
} pro;
pro p[15];
int main()
{
    int n, total_tat = 0, total_wt = 0, tempBT[15], completed = 0;
    float avg_wt = 0, avg_tat = 0;
    int minIndex, minPriority, curTime = 0;

    printf("Enter the number of process: ");
    scanf("%d", &n);

    printf("Enter the arrival time, burst time and priority of the process: \n");
    printf("AT BT P\n");
    for (int i = 0; i < n; i++)
    {
        p[i].Id = i + 1;
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].p);
        p[i].iscompl = 0;
        tempBT[i] = p[i].bt;
    }

    printf("Gantt Chart: \n");
    while (completed != n)
    {
        minIndex = -1;
        minPriority = 9999;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= curTime && p[i].iscompl == 0)
            {
                if (minIndex == -1 || p[i].p < minPriority || (p[i].p == minPriority && p[i].at < p[minIndex].at))
                {
                    minPriority = p[i].p;
                    minIndex = i;
                }
            }
        }
        curTime++;
        if (minIndex != -1)
        {
            p[minIndex].bt--;

            printf("| P%d(1) %d", p[minIndex].Id, curTime);

            if (p[minIndex].bt == 0)
            {
                p[minIndex].ct = curTime;
                p[minIndex].tat = p[minIndex].ct - p[minIndex].at;
                p[minIndex].wt = p[minIndex].tat - tempBT[minIndex];

                total_tat += p[minIndex].tat;
                total_wt += p[minIndex].wt;

                completed++;
                p[minIndex].iscompl = 1;
            }
        }
    }
    printf("|\n");
    avg_tat = (float)total_tat / n;
    avg_wt = (float)total_wt / n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tP\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].Id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].p);
    }
    printf("Average TAT = %.2f\n", avg_tat);
    printf("Average WT: %2.2f\n", avg_wt);
    return 0;
}