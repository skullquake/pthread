#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 8
struct GlobalData{
	int a;
	int b;
	int c;
	int d;
};
struct GlobalData globalData;
pthread_mutex_t mutexGlobalData;
struct ThreadArg{
	int tid;
	int a;
	int b;
	int c;
	int d;
};
static pthread_once_t init=PTHREAD_ONCE_INIT;
void initf(){
	printf("initf()\n");
}
void *work(void *_targ){
	(void) pthread_once(&init,initf);
	if(_targ!=NULL){
		struct ThreadArg* targ=(struct ThreadArg*)_targ;
		printf("work()[%d]: starting...\n",targ->tid);
		printf("work()[%d]: data: [%d][%d][%d][%d]\n",targ->tid,targ->a,targ->b,targ->c,targ->d);
		usleep(random()%250000);
		pthread_mutex_lock(&mutexGlobalData);
		printf("work()[%d]:processing ...\n",targ->tid);
		usleep(random()%250000);
		globalData.a=globalData.a+1;
		globalData.b=globalData.a*2;
		globalData.c=globalData.b*2;
		globalData.d=globalData.c*2;
		targ->a=globalData.a;
		targ->b=globalData.b;
		targ->c=globalData.c;
		targ->d=globalData.d;
		usleep(random()%250000);
		printf("work()[%d]:done processing ...\n",targ->tid);
		pthread_mutex_unlock(&mutexGlobalData);
		usleep(random()%250000);
		printf("work()[%d]: ending...\n",targ->tid);
		pthread_exit(0);
	}else{
		fprintf(stderr,"work():_targ NULL: aborting starting...\n");
		pthread_exit(-1);
	}
}
int main(int argc,char *argv[]){
	globalData.a=0;
	globalData.b=0;
	globalData.c=0;
	globalData.d=0;
	pthread_t thread[NUM_THREADS];
	struct ThreadArg threadArgs[NUM_THREADS];
	pthread_attr_t attr;
	int rc;
	long t;
	void *status;
	pthread_mutex_init(&mutexGlobalData,NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	for(t=0;t<NUM_THREADS;t++){
		threadArgs[t].tid=t;
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
	pthread_mutex_destroy(&mutexGlobalData);
	pthread_exit(NULL);
	return 0;
}
