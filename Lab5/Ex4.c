#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 6
#define NUM_THREADS 4;
typedef struct {
    int row;
    int **A;
    int **B;
    int **C;
} thread_data;

void* multiply_row(void* arg) {
    thread_data* data = (thread_data*)arg;
    int i = data->row; 

    for (int j = 0; j < N; j++) {
        data->C[i][j] = 0; 
        for (int k = 0; k < N; k++) {
            data->C[i][j] += data->A[i][k] * data->B[k][j];
        }
    }
    
    return NULL;
}

int** allocate_matrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    if (matrix == NULL) exit(1);
    
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
        if (matrix[i] == NULL) exit(1);
    }
    return matrix;
}

void free_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(int **matrix, int size, const char* name) {
    printf("Matrix %s:\n", name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    pthread_t threads[N];
    thread_data t_data[N];

    int **A = allocate_matrix(N);
    int **B = allocate_matrix(N);
    int **C = allocate_matrix(N);

    int counter = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = counter++;
            B[i][j] = N*N - counter; 
        }
    }

    print_matrix(A, N, "A");
    print_matrix(B, N, "B");

    for (int i = 0; i < N; i++) {
        t_data[i].row = i;
        t_data[i].A = A;
        t_data[i].B = B;
        t_data[i].C = C;
        
        if (pthread_create(&threads[i], NULL, multiply_row, (void*)&t_data[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    print_matrix(C, N, "C = A * B");

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}
