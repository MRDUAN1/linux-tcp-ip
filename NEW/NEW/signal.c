#include <pthread.h>
#include <mqueue.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#define  die(msg) {perror(msg); exit(0);}
static void tfunc(union sigval sv){
struct mq_attr attr;
ssize_t nr;
void *buf;
mqd_t mqdes = *((mqd_t *)sv.sival_ptr);
if(mq_getattr(mqdes, &attr) == -1) die("mq_getattr");
buf = malloc(attr.mq_msgsize);
buf = malloc(attr.mq_msgsize);
if(buf == NULL) die("malloc");
nr = mq_receive(mqdes, buf, attr.mq_msgsize, NULL);
if(nr == -1) die("mq_receive");
printf("read %ld bytes", (long) nr);
free(buf);
exit(0);
}

int main(int argc, char **argv)
{
mqd_t mqdes;
struct sigevent not;
assert(argc == 2);
mqdes = mq_open(argv[1], O_RDONLY);
not.sigev_notify = SIGEV_THREAD;
not.sigev_notify_function = tfunc;
not.sigev_notify_attributes = NULL;
not.sigev_value.sival_ptr = &mqdes;
if(mq_notify(mqdes, &not) == -1) die("mq_notify");
pause();
}
































