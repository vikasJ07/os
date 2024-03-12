#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int counter=0;
sem_t empty,full,mutex;
void *producer (void *args){
	sem_wait(&empty);
	sem_wait(&mutex);
	printf("producer process produces %d \n",++counter);
	sem_post(&mutex);
	sem_post(&full);
}
void *consumer (void *args){
	sem_wait(&full);
	sem_wait(&mutex);
	printf("consumer process consumes %d \n",counter--);
	sem_post(&mutex);
	sem_post(&empty);
}
int main(){
sem_init(&empty,0,5);
sem_init(&full,1,0);
sem_init(&mutex,1,1);
int i;
int m=5, n=3;

pthread_t tid[m];
for (i=0;i<m;i++){
	pthread_create (&tid[i],NULL,producer,NULL);
}
for (i=0;i<m;i++){
	pthread_join(tid[i],NULL);
}

pthread_t ctid[n];
for(i=0;i<n;i++){
	pthread_create (&ctid[i],NULL,consumer,NULL);
}
for(i=0;i<n;i++){
	pthread_join(ctid[i],NULL);
}
}
	

