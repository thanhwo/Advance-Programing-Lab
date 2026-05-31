#include <pthread.h>
#include <stdio.h>
#include <time.h>

#define N 10000000
#define NUM_THREAD 4

int a[N];
long long gsum = 0;

typedef struct {
    int id;
    int start;
    int end;
} ThreadArg;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//void *insert(void *arg) {
  //  ThreadArg *data = (ThreadArg *)arg;
  //  for (int i = data->start; i < data->end; i++) {
    //    a[i] = i;
   // }

    //return NULL;
//}

void *sum(void *arg) {
    ThreadArg *data = (ThreadArg *)arg;

    for (int i = data->start; i < data->end; i++) {
        pthread_mutex_lock(&mutex);
        gsum += a[i];
        pthread_mutex_unlock(&mutex); 
    }

    return NULL;
}

int main() {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    //pthread_t insert_threads[NUM_THREAD];
    pthread_t sum_threads[NUM_THREAD];
    
    ThreadArg args[NUM_THREAD];
    for (int i = 0; i < N; i++){
        a[i] = i;
    }
    for (int i = 0; i < NUM_THREAD; i++) {
        args[i].id = i;
        args[i].start = i * N / NUM_THREAD;
        args[i].end = (i + 1) * N / NUM_THREAD;
        pthread_create(&sum_threads[i], NULL, sum, &args[i]);
    
        //pthread_create(&insert_threads[i], NULL, insert, &args[i]);
    }

    // chờ sum xong
    for (int i = 0; i < NUM_THREAD; i++) {
        pthread_join(sum_threads[i], NULL);
    }

    printf("Sum = %lld\n", gsum);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) +
                 (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Execution time: %f seconds\n", time_taken);

    return 0;
}
