#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *sumNumber(void *arg){
    int N = *((int *) arg); 
    int *sum = malloc(sizeof(int));
    *sum = 0;
    for (int i = 1; i <= N; i++){
        *sum += i;
    }
    return sum;
}

int main(){
    pthread_t t1;
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    pthread_create(&t1, NULL, sumNumber, &N);
    int *result;
    pthread_join(t1, (void**)&result);
    printf("Sum = %d\n", *result);
    free(result);
    return 0;
}
