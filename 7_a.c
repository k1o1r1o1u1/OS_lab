#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int i = 9;
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("[CHILD] This is a child process. \n");
        printf("[CHILD] My parent's pid is %d.\n", getppid());
        printf("[CHILD] i = %d\n", i);
        printf("[CHILD] Child process is going to load another program using execlp system call.\n");

        execlp("pwd", "pwd", NULL);
    }
    else
    {
        printf("[PARENT] This is parent process.\n");
        printf("[PARENT] My pid is %d. \n", getpid());
        printf("[PARENT] waiting for the child process to terminate.\n");

        wait(NULL);

        i = 11;
        printf("[PARENT] Resuming after termination of %d\n", pid);
        printf("[PARENT] My parent's pid is %d\n", getppid());
        printf("[PARENT] My child's pid is %d\n", pid);
        printf("[PARENT] i = %d\n", i);
    }
    return 0;
}