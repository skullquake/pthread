#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 8
struct ThreadArg{
	int a;
	int b;
	int c;
	int d;
};
void *work(void *_targ){
	if(_targ!=NULL){
		struct ThreadArg* targ=(struct ThreadArg*)_targ;
		printf("work():[%d][%d] [%d] [%d] starting...\n",targ->a,targ->b,targ->c,targ->d);
		usleep(1000000);
		printf("work():[%d][%d] [%d] [%d] ending...\n",targ->a,targ->b,targ->c,targ->d);
		pthread_exit(0);
	}else{
		fprintf(stderr,"work():_targ NULL: aborting starting...\n");
		pthread_exit(-1);
	}
}
int main(int argc,char *argv[]){
	pthread_t thread[NUM_THREADS];
	struct ThreadArg threadArgs[NUM_THREADS];
	pthread_attr_t attr;
	int rc;
	long t;
	void *status;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	for(t=0;t<NUM_THREADS;t++){
		threadArgs[t].a=t;
		threadArgs[t].b=threadArgs[t].a*2;
		threadArgs[t].c=threadArgs[t].b*2;
		threadArgs[t].d=threadArgs[t].c*2;
		printf("main(): creating %ld\n",t);
		rc=pthread_create(&thread[t],&attr,work,(void *)&threadArgs[t]);  
		if(rc){
			fprintf(stderr,"main(): return code from pthread_create() is %d: aborting...\n",rc);
			exit(-1);
		}
	}
	pthread_attr_destroy(&attr);
	for(t=0;t<NUM_THREADS;t++){
		rc=pthread_join(thread[t],&status);
		if(rc){
			printf("main(): return code from pthread_join() is %d: aborting...\n",rc);
			exit(-1);
		}
		printf("main(): completed join with thread %ld having a status of %ld\n",t,status);
	}
	printf("main(): program completed. Exiting.\n");
	pthread_exit(NULL);
	return 0;
}
