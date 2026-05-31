#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 1000000 
#define MAX_STR_LEN 32

char **string_array;
const char *target_string = "Thanh";

volatile int target_found = 0;
int found_index = -1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int id;
    int start;
    int end;
} thread_data;

void* search_string(void* arg) {
    thread_data* data = (thread_data*)arg;

    for (int i = data->start; i < data->end; i++) {
        if (target_found) {
            printf("Thread %d stopping early. Target already found!\n", data->id);
            break; 
        }

        if (strcmp(string_array[i], target_string) == 0) {
            pthread_mutex_lock(&lock);        
            if (!target_found) {
                target_found = 1; 
                found_index = i;
                printf("\nThread %d FOUND the string at index %d!\n\n", data->id, i);
            }
            
            pthread_mutex_unlock(&lock);
            break; 
        }
    }
    return NULL;
}

int main() {
    pthread_t tids[NUM_THREADS];
    thread_data threads[NUM_THREADS];

    string_array = (char **)malloc(ARRAY_SIZE * sizeof(char *));
    if (string_array == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    } 
    for (int i = 0; i < ARRAY_SIZE; i++) {
        string_array[i] = (char *)malloc(MAX_STR_LEN * sizeof(char));
        sprintf(string_array[i], "string_%d", i);
    }

    int target_insertion_index = 850400; 
    strcpy(string_array[target_insertion_index], target_string);
    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].id = i;
        threads[i].start = i * chunk_size;
        threads[i].end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chunk_size;
        
        pthread_create(&tids[i], NULL, search_string, (void*)&threads[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    if (found_index != -1) {
        printf("Main: Search complete. Target found at global index: %d\n", found_index);
    } else {
        printf("Main: Search complete. Target not found.\n");
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        free(string_array[i]);
    }
    free(string_array);

    return 0;
}
