#include<stdio.h>
#include<pthread.h>
int main(int argc,char*argv[]){
	printf("main:beg\n");
	printf("main:end\n");
	pthread_exit(NULL);
}
