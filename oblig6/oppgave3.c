#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_WAIT 2000000

pthread_cond_t cond;
pthread_mutex_t mutex;
int count;

void *terningkast(void *nr){
   while(1){
	int terning = rand()%6 + 1;

	pthread_mutex_lock(&mutex);

	if(terning == 1){
		count++;
		printf("TrÃ¥d %3ld -> %d (%d)\n", (long) nr, terning, count);
        	pthread_cond_wait(&cond, &mutex);
	}

	else if(terning == 6){
		if(count>0){
			count--;
        		pthread_cond_signal(&cond);
		}
		printf("TrÃ¥d %3ld -> %d (%d)\n", (long) nr, terning, count);
	}

	else{
     		printf("TrÃ¥d %3ld -> %d\n", (long) nr, terning);
	}

	pthread_mutex_unlock(&mutex);
      	usleep(rand() % MAX_WAIT + 1);
   	}
}

void main(){
   	int n;
   	long i;
   	pthread_t t;

   	printf("n? ");
   	scanf("%d", &n);

	pthread_cond_init(&cond, NULL);
   	pthread_mutex_init(&mutex, NULL);

   	for (i = 0; i < n; i++)
     		pthread_create(&t, NULL, terningkast, (void *) i);

	for (i = 0; i < n; i++)
   		pthread_join(t, NULL);
}