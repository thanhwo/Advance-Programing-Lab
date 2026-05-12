#include <stdio.h>
#include <pthread.h>

int count = 310;
pthread_mutex_t lock;

void *increase_100times(void *arg){
    pthread_mutex_lock(&lock);
    int N = 100;
    for(int i = 0; i < N; i++){
        count++;    
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *decrease_50time(void *arg){
    pthread_mutex_lock(&lock);
    int N = 50;
    for(int i = 0; i < N; i++){
        count--;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(){
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, increase_100times, NULL);
    pthread_create(&t1, NULL, decrease_50time, NULL);
    
    pthread_join(t1, NULL); 
    pthread_join(t2, NULL);
    
    pthread_mutex_destroy(&lock);
    printf("Final count: %d\n", count);
    return 0;
}
