#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        printf("[CHILD] This is a child process.\n");
        printf("[CHILD] My parent's pid is %d.\n", getppid());
        printf("[CHILD] My pid is %d.\n", getpid());

        print("[CHILD] Sleeping for 5s.\n");
        sleep(5);

        printf("[CHILD] My parent has ended. So I am an orphan process adopted by init process.\n");
        exit(0);
    }
    else
    {
        printf("[PARENT] This is a parent process.\n");
        printf("[PARENT] My parent's pid is %d.\n", getppid());
        printf("[PARENT] My pid is %d.\n", getpid());
        printf("[PARENT] My child's pid is %d.\n", pid);

        printf("[PARENT] Exiting....\n");
        exit(0);
    }
    return 0;
}