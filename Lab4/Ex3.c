#include <pthread.h>
#include <stdio.h>

void *print_message(void *arg){
    printf("hello, my thread id is %lu\n", pthread_self());
    return NULL;
}

int main(){
    pthread_t t1, t2, t3;
    
    pthread_create(&t1, NULL, print_message, NULL);
    pthread_create(&t2, NULL, print_message, NULL);
    pthread_create(&t3, NULL, print_message, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Main thread is running\n");
}
