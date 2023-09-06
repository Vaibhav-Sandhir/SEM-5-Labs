#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("\nWrong number of arguments");
		exit(1);
	}
	
	struct stat metadata;
	int result = stat(argv[1], &metadata);
	
	if(result == -1){
		perror("stat");
		exit(1);
	}
	
	printf("\nInode number of %s is %d", argv[1], metadata.st_ino);
}
