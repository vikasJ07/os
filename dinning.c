#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5
#define thinking 2
#define hungry 1
#define eating 0
#define left (phnum+4)%N
#define right (phnum+1)%N

int state [N];
int phil[N]={0,1,2,3,4};
sem_t mutex;
sem_t s[N];

void test(int phnum){
	if (state[phnum] == hungry && state[left]!=eating && state[right]!=eating){
		state[phnum]=eating;
		
		printf("philospher %d takes fork %d and %d \n",phnum+1,left+1,phnum+1);
		printf("philospher %d is eating \n",phnum+1);
		sem_post(&s[phnum]);
	}
}

void takefork(int phnum){
	sem_wait(&mutex);
	state[phnum]=hungry;
	printf("philospher %d is hungry \n",phnum+1);
	test(phnum);
	sem_post(&mutex);
	sem_wait(&s[phnum]);
}


void putfork (int phnum){
	sem_wait(&mutex);
	state[phnum]=thinking;
	printf("philospher %d putting fork %d and %d down \n",phnum+1,left+1,phnum+1);
	printf("philospher %d is thinking \n",phnum+1);
	test(left);
	test(right);
	sem_post (&mutex);
}

void *philospher(void *num){
	//while(1){
		int *i=num;
		
		takefork(*i);
		
		putfork(*i);
	//}
}

int main(){
	int i;
	pthread_t thread_id [N];
	sem_init(&mutex,0,1);
	for(i=0;i<N;i++)
		sem_init (&s[i],0,0);
	for(i=0;i<N;i++){
		pthread_create(&thread_id[i],NULL,philospher,&phil[i]);
		printf("philospher %d is thinking\n",i+1);
	}
	for (i=0;i<N;i++)
		pthread_join(thread_id[i],NULL);
}		
	
