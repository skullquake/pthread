#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void*cb(void*vdata){
	int*data=(int*)vdata;
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
		printf("main:joining thread\n");
		pthread_join(t,NULL);
	}
	printf("main:joined thread\n");
	printf("main:end\n");
	exit(EXIT_SUCCESS);
}
