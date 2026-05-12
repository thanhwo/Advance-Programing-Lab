#include <pthread.h>
#include <stdio.h>

int counter = 0;
int N;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *barrier(void *arg){
    int id = *(int *) arg;
    printf("Thread %d reached the barrier\n", id);
    
    pthread_mutex_lock(&mutex);
    counter ++;
    if (counter == N){
        printf("All threads reached the barrier! Releasing them...\n");
        pthread_cond_broadcast(&cond);
    } else if (counter < N) {
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    printf( "Thread %d passed the barrier\n", id);
    
    return NULL;
}

int main(){
    printf("Enter N: ");
    scanf("%d", &N);
    pthread_t thread[N];
    int id[N];
    
    for (int i = 0; i < N; i++){
        id[i] = i + 1;
        pthread_create(&thread[i], NULL, barrier, &id[i]);
    }
    
    for (int i = 0; i < N-1; i++){
        pthread_join (thread[i], NULL);
    } 
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
