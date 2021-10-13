#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void*cb(void*data){
	printf("cb:beg\n");
	usleep(1000000);
	printf("cb:end\n");
	pthread_exit(NULL);
}
int main(int argc,char*argv[]){
	printf("main:beg\n");
	pthread_t t;
	pthread_attr_t attr;
	pthread_attr_init(&attr);//defaults
	printf("main:creating thread\n");
	if(pthread_create(&t,&attr,cb,NULL)){
		fprintf(stderr,"main:err:failed to create thread\n");
		exit(EXIT_FAILURE);
	}else{
		printf("main:thread created\n");
		pthread_join(t,NULL);
	}
	printf("main:end\n");
	pthread_exit(NULL);//will wait to join
}
