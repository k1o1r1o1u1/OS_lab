#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int id, at, bt, ct, tat, wt, iscompl, rt;
} pro;
pro p[15];

void sjfNP(pro[], int);
int main()
{
    int n;

    printf("Enter the number of processess: ");
    scanf("%d", &n);

    printf("Enter the arrival and burst time of the processess: \n");
    printf("AT BT\n");

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].iscompl = 0;
    }

    sjfNP(p, n);
}
void sjfNP(pro p[], int n)
{
    int total_tat = 0, total_wt = 0, total_rt = 0, temp, completed = 0;
    float avg_tat = 0, avg_wt, avg_rt = 0;

    printf("Gantt Chart: \n");
    int exec, minBT, curTime = 0, idleTime = 0;
    while (completed != n)
    {
        exec = -1;
        minBT = 9999;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= curTime && !p[i].iscompl)
            {
                if (p[i].bt < minBT)
                {
                    exec = i;
                    minBT = p[i].bt;
                }
            }
        }
        if (exec == -1)
        {
            idleTime++;
            curTime++;
        }
        else
        {
            if (idleTime)
            {
                printf("| idle for %d upto %d", idleTime, curTime);
                idleTime = 0;
            }
            temp = curTime;
            p[exec].rt = curTime - p[exec].at;
            curTime += p[exec].bt;
            p[exec].ct = curTime;
            p[exec].iscompl = 1;
            completed++;

            p[exec].tat = p[exec].ct - p[exec].at;
            p[exec].wt = p[exec].tat - p[exec].bt;

            printf("|%d P%d(%d) %d", temp, p[exec].id, p[exec].bt, curTime);

            total_tat += p[exec].tat;
            total_wt += p[exec].wt;
            total_rt += p[exec].rt;
        }
    }
    printf("|\n");
    avg_tat = (float)total_tat / n;
    avg_rt = (float)total_rt / n;
    avg_wt = (float)total_wt / n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("Average TAT = %.2f\nAverage WT = %.2f\nAverage RT = %.2f\n", avg_tat, avg_wt, avg_rt);
}