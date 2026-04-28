#include <pthread.h>
#include <stdio.h>

void *print_numbers(void *arg){
    int N = *((int)arg);
    for (int i =0; i < N; i++){
        printf("%d\n", i);
    }
}
int main(){
    pthread_t t1;
    int N;
    scanf("%d", &N);
    pthread_create(&t1, NULL, print_numbers, &N);

}
