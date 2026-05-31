#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *buffer;

int SIZE;

int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex;

pthread_cond_t notFull;
pthread_cond_t notEmpty;

void *publisher(void *arg) {

    for (int i = 1; i <= 10; i++) {

        pthread_mutex_lock(&mutex);

        while (count == SIZE) {
            pthread_cond_wait(&notFull, &mutex);
        }

        buffer[in] = i;

        printf("Publisher published: %d\n", i);

        in = (in + 1) % SIZE;

        count++;

        pthread_cond_signal(&notEmpty);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

void *subscriber(void *arg) {

    for (int i = 1; i <= 10; i++) {

        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&notEmpty, &mutex);
        }

        int item = buffer[out];

        printf("Subscriber received: %d\n", item);

        out = (out + 1) % SIZE;

        count--;

        pthread_cond_signal(&notFull);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

int main() {

    printf("Enter buffer size: ");
    scanf("%d", &SIZE);

    // Dynamic memory allocation
    buffer = (int *) malloc(SIZE * sizeof(int));

    pthread_t pub, sub;

    pthread_mutex_init(&mutex, NULL);

    pthread_cond_init(&notFull, NULL);
    pthread_cond_init(&notEmpty, NULL);

    pthread_create(&pub, NULL, publisher, NULL);
    pthread_create(&sub, NULL, subscriber, NULL);

    pthread_join(pub, NULL);
    pthread_join(sub, NULL);

    pthread_mutex_destroy(&mutex);

    pthread_cond_destroy(&notFull);
    pthread_cond_destroy(&notEmpty);

    free(buffer);

    return 0;
}
