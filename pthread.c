#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int i;
float add(int num1,int num2){
	return num1+num2;
}
float sub (int num1,int num2){
	return num1-num2;
}
float mul (int num1,int num2){
	return num1*num2;
}


void *print(void *i){
	int *j=(int *)i;
	int num1=5,num2=3;
	float result;
	
	switch (*j){
		case 0:
		  result = add(num1,num2);
		  break;
		case 1:
		  result = sub(num1,num2);
		  break;
		case 2:
		  result = mul(num1,num2);
		  break;
	
	}
	printf("iam thread %d\n", *j);
	printf("result is %f\n",result);
}
int main (){
	pthread_t tid[3];
	for (i=0;i<3;i++){
		pthread_create (&tid[i],NULL,print,(void *)&i);
		sleep(10);
	}
	for (i=0;i<3;i++){
		pthread_join(tid[i],NULL);
	}
}
	
		
