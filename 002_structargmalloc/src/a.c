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
		free(ta);
	}else{
		printf("ta NULL:Aborting...\n");
	}
	pthread_exit(NULL);
}
int main (int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	for(int i=0;i<32;i++){
		for(t=0; t<NUM_THREADS; t++){
			printf("In main: creating thread %ld\n", t);
			struct ThreadArg* ta=(struct ThreadArg*)malloc(sizeof(struct ThreadArg));
			if(ta!=NULL){
				ta->a=t;
				ta->b=ta->a*2;
				ta->c=ta->b*2;
				ta->d=ta->c*2;
				rc = pthread_create(&threads[t], NULL, PrintHello, (void *)ta);
				if (rc){
					printf("ERROR; return code from pthread_create() is %d\n", rc);
					exit(-1);
				}
			}else{
				printf("ERROR; failed to create StructArg for %d\n", rc);
				exit(-1);
			}
		}
	}
	/* Last thing that main() should do */
	pthread_exit(NULL);
 }
