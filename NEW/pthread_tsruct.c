#include "head.h"
#include <pthread.h>
int main()
{
struct{
pthread_mutex_t mutex;
int hp;
int mal;
}mall
= {PTHREAD_MUTEX_INITIALIZER};
int i = 0;
void *process(void *), *customer(void *);
pthread_t tid_procer[10], tid_comter;
int count[10];
for(i = 0; i < 10; i++){
count[i] = 0;
pthread_create(&tid_procer[i], NULL, process, &count[i]);
}
for(i = 0; i < 10; i++){
pthread_join(tid_procer[i], NULL);
printf("count[%d] = %d", i, count[i]);}
pthread_create(&tid_comter, NULL, cunstomer, NULL);
pthread_join(tid_comter, NULL);

}
void *process(void *arg)
{
printf("hello\n");
}
