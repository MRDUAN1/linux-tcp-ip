#ifndef _THPOOL_
#define _THPOOL_
typedef void *(*FUNC)(void *arg);
typedef struct _thpool_job_t{
void *(*function)(void *arg);
FUNC function;
void *arg;
struct _thpool_job_t *next;
}thpool_job_t;

typedef struct _thpool_job_queue{
thpool_job_t *head;
thpool_job_t *tail;
int jobn;
sem_t queuesem;
}thpool_job_queue;

typedef struct _thpool_t{
pthread_t *threads;
int threadn;
thpool_job_queue *jobqueue;
}thpool_t;
thpool_t *thpool_init(int threadn);
void thpool_thread_do(thpool_t *tp_p);
int thpool_add_work(thpool_t *tp_p, void * (*function_p)(void*), void *arg_p);
void thpool_destory(thpool_t *tp_p);
void thpool_jobqueue_add(thpool *tp_p, thpool_job_t *newjob_p);
thpool_job_t *thpool_job_queue_peek(thpool_t *tp_p);
void thpool_jobqueue_empty(thpool_tp_p);
int thpool_jobqueue_renovelast(thpool_t *tp_p);
void thpool_jobqueue_init(thpool_t 

#endif

