#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int id, at, bt, ct, tat, wt, rt;

} pro;

void fcfs(pro[], int);

int main()
{
    int n;
    pro p[15];
    printf("Enter the number of process: ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time: \n ");
    printf("AT BT\n");
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                pro temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    fcfs(p, n);
    return 0;
}

void fcfs(pro p[], int n)
{
    int elapsedTime = 0;
    int total_tat = 0, total_wt = 0, total_rt = 0, temp;
    float avg_tat = 0, avg_wt = 0, avg_rt = 0;

    printf("Gantt Chart: \n");
    for (int i = 0; i < n; i++)
    {
        temp = elapsedTime;
        if (elapsedTime < p[i].at)
        {
            elapsedTime = p[i].at;
            printf("|%d Idle upto %d", temp, elapsedTime);
        }

        p[i].rt = elapsedTime - p[i].at;
        elapsedTime += p[i].bt;
        p[i].ct = elapsedTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("|%d P%d (%d) %d", temp, p[i].id, p[i].bt, elapsedTime);

        total_tat += p[i].tat;
        total_wt += p[i].wt;
        total_rt += p[i].rt;
    }
    avg_tat = (float)total_tat / n;
    avg_rt = (float)total_rt / n;
    avg_wt = (float)total_wt / n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("Average TAT = %d\nAverage WT = %d\nAverage RT = %d\n", avg_tat, avg_wt, avg_rt);
}
