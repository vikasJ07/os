#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char *argv[]){

	int c,fd1,fd2;
	char buf[20];
	if (argc != 3){
		printf("insufficient arg");
		return 0;
	}
	fd1=open(argv[1],O_RDONLY);
	if (fd1==-1){
		perror("open");
		return 0;
	}
	fd2=open(argv[2],O_WRONLY | O_CREAT,0666);
	if (fd2==-1){
		perror("open");
		return 0;
	}
	while ((c=read(fd1,buf,10))>0){
		write(fd2,buf,c);
	}
	if (c==-1){
		perror("write");
		return 0;
	}
	close (fd1);
	close (fd2);
}
	
