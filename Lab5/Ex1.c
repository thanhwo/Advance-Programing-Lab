#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define RANGE 10000000

long count[NUM_THREADS];

typedef struct { 
    int id;
    int start;
    int end;
    long *array; 
} thread_data;

void* countOdd(void* arg) {
    thread_data* data = (thread_data*)arg;

    long counter = 0;
    for (int i = data->start; i < data->end; i++) {
        if (data->array[i] % 2 != 0) {
            counter++;
        }
    }
    count[data->id] = counter;  
    return NULL;
}

int main() {
    pthread_t tids[NUM_THREADS]; 
    thread_data threads[NUM_THREADS];
    
    long *a = (long *)malloc(RANGE * sizeof(long));
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    
    for (int i = 0; i < RANGE; i++) {
        a[i] = i;
    }

    
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].id = i;
        threads[i].start = i * (RANGE / NUM_THREADS);
        threads[i].end = (i + 1) * (RANGE / NUM_THREADS);
        threads[i].array = a; 
        
        pthread_create(&tids[i], NULL, countOdd, (void*)&threads[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }
    long totalCount = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        totalCount += count[i];
    }
    
    printf("Total odd numbers: %ld\n", totalCount);
    
    free(a);
    return 0;
}
