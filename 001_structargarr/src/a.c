#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5
struct ThreadArg{
	int a;
	int b;
	int c;
	int d;
};
void *PrintHello(void *_ta){
	if(_ta!=NULL){
		struct ThreadArg* ta=(struct ThreadArg*)_ta;
		printf("PrintHello():[%ld,%ld,%ld,%ld]\n",ta->a,ta->b,ta->c,ta->d);
	}else{
		printf("ta NULL:Aborting...\n");
	}
	pthread_exit(NULL);
}
int main (int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	struct ThreadArg threadArgs[NUM_THREADS];
	int rc;
	long t;
		for(t=0; t<NUM_THREADS; t++){
			printf("In main: creating thread %ld\n", t);
			threadArgs[t].a=t;
			threadArgs[t].b=threadArgs[t].a*2;
			threadArgs[t].c=threadArgs[t].b*2;
			threadArgs[t].d=threadArgs[t].c*2;
			rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&threadArgs[t]);
			if (rc){
				printf("ERROR; return code from pthread_create() is %d\n", rc);
				exit(-1);
			}
		}
	/* Last thing that main() should do */
	pthread_exit(NULL);
 }
