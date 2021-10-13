#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 8
#define N 1000
#define MEGEXTRA 1000000
pthread_attr_t attr;
struct ThreadArg{
	int a;
	int b;
	int c;
	int d;
	pthread_attr_t attr;
};
void *work(void *_targ){
	if(_targ!=NULL){
		struct ThreadArg* targ=(struct ThreadArg*)_targ;
		size_t tsz;
		pthread_attr_getstacksize(&(targ->attr),&tsz);
		printf("work():[%d][%d][%d][%d][ssz=%li] starting...\n",targ->a,targ->b,targ->c,targ->d,tsz);
		usleep(1000000);
		printf("work():[%d][%d][%d][%d][ssz=%li] ending...\n",targ->a,targ->b,targ->c,targ->d,tsz);
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
	void *status;
	size_t ssz;
	int rc;
	long t;
	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr,&ssz);
	printf("main()[ssz=%li]\n",ssz);
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,ssz+4096);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	for(t=0;t<NUM_THREADS;t++){
		pthread_attr_init(&threadArgs[t].attr);
		pthread_attr_setstacksize(&threadArgs[t].attr,ssz+pow(2,16));
		pthread_attr_setdetachstate(&threadArgs[t].attr,PTHREAD_CREATE_JOINABLE);
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
