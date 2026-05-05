#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sharedVar = 5;  // Shared among threads

void *threadFunc(void *arg) {
    //Write code change value of global variable here
    sharedVar ++;
    printf("Thread: sharedVar = %d\n", sharedVar);
    return NULL;
}

int main() {
    pthread_t thread;
    
    // Write code to create thread here
    pthread_create(&thread, NULL, threadFunc, NULL);
    //Write code to wait for thread to terminate here
    pthread_join(thread, NULL);
    printf("Main: sharedVar = %d\n", sharedVar); 
    return 0;
}

