#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int cnt = 0;
int readcount = 0;

pthread_mutex_t mutex;
sem_t wrt;

void *reader(void *arg)
{
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);

    readcount++;

    if (readcount == 1)
        sem_wait(&wrt);

    pthread_mutex_unlock(&mutex);

    printf("Reader %d read cnt as %d\n", id, cnt);

    pthread_mutex_lock(&mutex);

    readcount--;

    if (readcount == 0)
        sem_post(&wrt);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&wrt);

    cnt += 2;

    printf("Writer %d modified cnt to %d\n", id, cnt);

    sem_post(&wrt);

    pthread_exit(NULL);
}

int main()
{
    pthread_t r[3], w[3];
    int id[3] = {1, 2, 3};

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&w[i], NULL, writer, &id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(w[i], NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}