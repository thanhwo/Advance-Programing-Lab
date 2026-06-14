#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sharedVar = 5;  

void *threadFunc(void *arg) {
    sharedVar ++;
    printf("Thread: sharedVar = %d\n", sharedVar);
    return NULL;
}

int main() {
    pthread_t thread;
    
    pthread_create(&thread, NULL, threadFunc, NULL);
    pthread_join(thread, NULL);
    printf("Main: sharedVar = %d\n", sharedVar); 
    return 0;
}

