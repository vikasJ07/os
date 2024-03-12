#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
int count = 0, r_count = 0; 
sem_t mutex,wr;

void * writer (void *p){
	int * i = (int *)p;
	sem_wait(&wr);
	printf("writer %d writes page number %d\n",*i,++count);
	sem_post(&wr);
}

void * reader (void *p){
	int *i = (int *)p;
	sem_wait(&mutex);
	r_count ++;
	if (r_count == 1)
		sem_wait(&wr);
	sem_post(&mutex);
	printf("reader %d reades page number %d\n" ,*i,count);
	sem_wait(&mutex);
	r_count --;
	if (r_count == 0){
		sem_post(&wr);
	}
	sem_post(&mutex);
}


int main(){
sem_init(&mutex,0,1);
sem_init(&wr,0,1);
int a[6] = {1,2,3,1,2,3};
pthread_t p[6];
for (int i = 0; i < 3; i++)
    pthread_create(&p[i], NULL, writer, &a[i]);
for (int i = 3; i < 6; i++)
    pthread_create(&p[i], NULL, reader, &a[i]);
for (int i = 0; i < 6; i++)
    pthread_join(p[i], NULL);
}
