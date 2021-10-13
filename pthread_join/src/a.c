#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
void*cb(void*in){
	static int dat={42};
	pthread_exit((void*)&dat);
}
int main(int argc,char*argv[]){
	pthread_t tid;
	if(pthread_create(&tid,NULL,cb,NULL))
		exit(EXIT_FAILURE);
	int*dat;
	pthread_join(tid,(void**)&dat);
	printf("%d\n",*dat);
	pthread_exit(NULL);
}
