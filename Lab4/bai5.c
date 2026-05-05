#include <pthread.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t mutex;

void *increase(void *arg){
    pthread_mutex_lock(&mutex);
    for( int i = 0; i < 100; i++){
        counter++;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void *decrease(void *arg){
    pthread_mutex_lock(&mutex);
    for( int i = 0; i < 50; i++){
        counter--;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, increase, NULL);
    pthread_create(&t2, NULL, decrease, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("final counter: %d\n", counter);
    pthread_mutex_destroy(&mutex);
    return 0;
}
