#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
    int i;
    int *ptr;

    int shmid = shmget(1234, 1024, IPC_CREAT | 0666);

    pid_t pid = fork();

    if (pid == 0)
    {
        execl("./fib", "fib", NULL);
    }
    else
    {
        wait(NULL);

        ptr = (int *)shmat(shmid, NULL, 0);

        int n = ptr[0];

        printf("\nParent: Fibonacci Series from Shared Memory\n");

        for (i = 1; i <= n; i++)
            printf("%d ", ptr[i]);

        printf("\n");

        shmdt(ptr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}