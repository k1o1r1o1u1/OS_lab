#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *sum(void *arg)
{
    int n = *(int *)arg;
    int sum = 0;

    printf("Inside Sum Thread.\n");

    for (int i = 1; i <= n; i++)
        sum += 1;
    printf("The sum of first %d natural numbers is %d.\n", n, sum);
    printf("Sum thread completed.\n");
    pthread_exit(NULL);
}

void *fact(void *arg)
{
    int n = *(int *)arg;
    int fact = 1;

    printf("Inside fact Thread.\n");

    for (int i = 0; i <= n; i++)
        fact *= i;
    printf("The factorial upto %d is %d.\n", n, sum);

    printf("Fact thread Completed!");

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2;
    int n;
    printf("Inside the main thread.\n");

    printf("Enter n: ");
    scanf("%d", &n);

    pthread_create(&t1, NULL, sum, &n);
    pthread_create(&t2, NULL, fact, &n);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main thread comleted!!\n");

    pthread_exit(NULL);
}