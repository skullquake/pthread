#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void*cb(void*vdata){
	int*data=(int*)vdata;
	//Note. At any point in time, a thread is either joinable or detached (default state is joinable). Joinable threads must be reaped or killed by other threads (using pthread_join) in order to free memory
	//resources. Detached threads cannot be reaped or killed by other threads, and resources are automatically reaped on termination. So unless threads need to synchronize among themselves, it is better to call
	pthread_detach(pthread_self());
	printf("cb:beg\n");
	printf("cb:id:%d\n",*data);
	usleep(1000000);
	printf("cb:end\n");
	pthread_exit(NULL);
}
int main(int argc,char*argv[]){
	printf("main:beg\n");
	pthread_t t;
	printf("main:creating thread\n");
	int data=42;
	if(pthread_create(&t,NULL,cb,&data)){
		fprintf(stderr,"main:err:failed to create thread\n");
		exit(EXIT_FAILURE);
	}else{
		printf("main:thread created\n");
	}
	printf("main:end\n");
	pthread_exit(NULL);//will wait to join
}
