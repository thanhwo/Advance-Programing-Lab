#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 1000000 
#define NUM_BINS 256       

long global_hist[NUM_BINS] = {0};

typedef struct {
    int id;
    int start;
    int end;
    int *array;
    long local_hist[NUM_BINS]; 
} thread_data;

void* compute_histogram(void* arg) {
    thread_data* data = (thread_data*)arg;

    for (int i = 0; i < NUM_BINS; i++) {
        data->local_hist[i] = 0;
    }

    for (int i = data->start; i < data->end; i++) {
        int value = data->array[i];
        data->local_hist[value]++;
    }

    return NULL;
}

int main() {
    pthread_t tids[NUM_THREADS];
    thread_data threads[NUM_THREADS];

    int *pixels = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (pixels == NULL) {
        fprintf(stderr, "Lỗi cấp phát bộ nhớ!\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        pixels[i] = rand() % NUM_BINS;
    }

    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].id = i;
        threads[i].start = i * chunk_size;        
        threads[i].end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chunk_size;
        threads[i].array = pixels;

        pthread_create(&tids[i], NULL, compute_histogram, (void*)&threads[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
        for (int j = 0; j < NUM_BINS; j++) {
            global_hist[j] += threads[i].local_hist[j];
        }
    }

    long total_pixels_counted = 0;
    for (int i = 0; i < NUM_BINS; i++) {
        total_pixels_counted += global_hist[i];
    }
    printf("Kết quả mẫu cho các giá trị từ 0 đến 255:\n");
    for (int i = 0; i < 256; i++) {
        printf("Pixel có giá trị %d xuất hiện: %ld lần\n", i, global_hist[i]);
    }
    free(pixels);
    return 0;
}
