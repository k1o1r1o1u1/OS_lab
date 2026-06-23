#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define SIZE 3

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 3; i++)
    {
        int item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d : Insert item %d at %d\n", id, item, in);

        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 3; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];

        printf("Consumer %d : Remove item %d from %d\n", id, item, out);

        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t p[3], c[3];
    int id[3] = {1, 2, 3};

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&p[i], NULL, producer, &id[i]);

    for (int i = 0; i < 3; i++)
        pthread_create(&c[i], NULL, consumer, &id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(p[i], NULL);

    for (int i = 0; i < 3; i++)
        pthread_join(c[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}