#include <pthread.h>
#include <stdio.h>

const int size = 10;
int buffer[size];
int counter = 0;
int in = 0;
int out = 0; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg){
    for (int i = 1; i <= 10; i++){

    
        while (counter == size){
            pthread_cond_wait(&notFull, &mutex);
        }
    }

}

void *consumer(void *agr){
    for (int i = 1; i <= 10; i++){

    }
}

int main(){
    pthread_t pro, con;

    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);
}
