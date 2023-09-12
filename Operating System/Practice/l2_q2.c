#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>

void printdir(char dir[], int depth){
	DIR* directory = opendir(dir);
	struct stat statbuf;
	struct dirent* entry;
	chdir(dir);
	
	while((entry = readdir(directory)) != NULL){
		lstat(entry->d_name, &statbuf);
		
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp("..", entry->d_name) != 0 && strcmp(".", entry->d_name) != 0){
				printf("\n%s , %d", entry->d_name, depth);
				printdir(entry->d_name, depth + 4);
			}
		}
		
		else{
			printf("\n%s , %d", entry->d_name, depth);	
		}
	}
	chdir("..");
	closedir(directory);
}


void main(){
	printdir("/home/kali/Desktop/SEM-5-Labs/Operating System", 0);	
}




