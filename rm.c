#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
	int del;

	if (argc < 2){
		printf("insufficient arg");
		return 0;
	}
	else {
		del=unlink(argv[1]);
		if (del==-1){
		perror("unlink");
		return 0;
	      }
	}
}
		
