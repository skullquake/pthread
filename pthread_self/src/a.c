#include<stdio.h>
#include<pthread.h>
int main(int argc,char*argv[]){
	printf("main:beg\n");
	pthread_t tid={pthread_self()};
	printf("main:pthread_id:%lu\n",tid);
	printf("main:end\n");
	pthread_exit(NULL);
}
