#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
	int mv;
	if (argc != 3){
		printf("insufficient arg");
		return 0;
	}
	mv=link(argv[1],argv[2]);
	if (mv == -1){
		perror("link");
		return 0;
	}
	mv=unlink(argv[1]);
	if (mv == -1){
		perror("unlink");
		return 0;
	}
	return 0;
}
