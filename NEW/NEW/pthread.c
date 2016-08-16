
#include <pthread.h>
#include <stdio.h>
int main()
{
pthread_t id;
id = pthread_self();
printf("%d", id);
}
