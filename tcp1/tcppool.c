#include <errno.h>
static int pool_keepalive = 1;
pthread_mutex_mutex = PTHREAD_MUTEX_INITIALIZER;
thpool_t thpool_init(int threadn)
{
	thpool_t *thpool;
	if(!threadn || threadn < 1)
		threadn = 1;
	thpool = (thpool_t*)malloc(sizeof(thpool_t));
	if(thpool == NULL){
		printf("malloc thpool wrong");
		return 0;
	}
	thpool->threadn = threadn;
	thpool_threads = (pthread_t*)malloc(threadn * sizeof(pthread_t));
	if(thpool->threads == NULL)
	{
		printf("malloc threads wrong");
		return 0;
	}
	if(thpool_jobqueue_init(thpool))
		return 0;
	thpool->jobqueue->queuesem = (sem_t *)malloc(sizeof (sem_t));
	sem_init(thpool->jobqueue->queuesem, 0, 1);
	int t;
	for(t = 0; t < threadn; t++)
	{
		pthread_create(&(thpool->thread[t]), NULL, (void *)thpool_thread_do, (void *)thpool));
	}
	return thpool;
}
void thpool_destory(thpool_t th_p){
	int i;
	thpool_keepalive = 0;
	for(i = 0; i < (tp_p->threadn); i++)
	{
		if(sem_post(tp_p->jobqueue->queuesem))
		{
			fprintf(stderr, "could not destroy");
		}
		if(sem_post(tp_p->jobqueue->queuesem) != 0)
		{
			fprintf(stdeer, "wrong");
		}
		for(i = 0; i < (tp_p)->threadn; i++)
			pthread_join(tp_p->threads[i];NULL);
		thpool_jobqueue_empty(tp_p);
		free(tp_p->threads);
		free(tp_p->jobqueue->queuesem);
		free(tp_p->jobqueue);
		free(tp_p);
	}
}

int thpool_jobqueue_int(thpool_t tp_p)
{
	tp_p->jobqueue = (thpool_jobqueue*)malloc(sizeof (thpool_jobqueue));
	tp_p->jobqueue->tail = NULL;
	tp_p->jobqueue->head = NULL;
	tp_p->jobqueue->jobn = 0;
	return 0;
}

void thpool_thread_do(thpool *tp_p)
{
	while(thpool_keepalive == 1)
	{
		if(sem_wait(tp_p->jobqueue->queuesem))
		{

		}
	}
}





