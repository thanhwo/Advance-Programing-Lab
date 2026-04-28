#include <pthread.h>
#include <stdio.h>

void *print_numbers(void *arg){
    int N = *((int *) arg);
    for (int i = 1; i <= N; i++){
        printf("%d\n", i);
    }
    return NULL;
}
int main(){
    pthread_t t1;
    int N;
    printf("Enter N:");
    scanf("%d", &N);
    pthread_create(&t1, NULL, print_numbers, &N);
    pthread_join(t1, NULL);
    printf("Main thread exiting\n");
}
