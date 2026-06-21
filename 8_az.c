#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        printf("[CHILD] This is child process.\n");
        printf("[CHILD] My pid is %d.\n", getpid());
        printf("[CHILD] My parent's pid is %d.\n", getppid());
        printf("[CHILD] Exiting.....\n");
        exit(0);
    }
    else
    {
        printf("[PARENT] This is parent process.\n");
        printf("[PARENT] My pid is %d\n", getpid());
        printf("[PARENT] My parent's pid is %d.\n", getppid());
        printf("[PARENT] Sleeping for 10s....");

        sleep(10);

        printf("[PARENT] Child pid %d has ended but it has an entry in the process table.\n ", pid);
        printf("[PARENT] It is a zombie process.\n");
    }
    return 0;
}