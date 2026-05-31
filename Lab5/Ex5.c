#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

#define ARRAY_SIZE 100 
#define THRESHOLD 10    

typedef struct {
    int *array;
    int left;
    int right;
} qsort_args;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort_seq(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort_seq(arr, low, pi - 1);
        quicksort_seq(arr, pi + 1, high);
    }
}

void* quicksort_parallel(void* arg) {
    qsort_args* args = (qsort_args*)arg;
    int low = args->left;
    int high = args->right;
    int *arr = args->array;

    if (low < high) {
        if (high - low <= THRESHOLD) {
            quicksort_seq(arr, low, high);
        } else {
            int pi = partition(arr, low, high);
            qsort_args left_args = {arr, low, pi - 1};
            qsort_args right_args = {arr, pi + 1, high};
            pthread_t left_thread;
            pthread_create(&left_thread, NULL, quicksort_parallel, &left_args);
            quicksort_parallel(&right_args);
            pthread_join(left_thread, NULL);
        }
    }
    return NULL;
}

bool verify_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int *arr = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 100;
    }

    printf("Before sorting:\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    qsort_args initial_args = {arr, 0, ARRAY_SIZE - 1};
    quicksort_parallel(&initial_args);

    if (verify_sorted(arr, ARRAY_SIZE)) {
        printf("Success: Array is correctly sorted!\n");
    } else {
        printf("Error: Array is NOT sorted.\n");
    }
    for (int i = 0; i < 100; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
