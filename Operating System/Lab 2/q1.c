#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(){
	char path[] = "/home/kali/Desktop/SEM-5-Labs/Operating System/Lab 2/q1_dir";
	DIR* directory = opendir(path);
	struct stat statbuf;
	struct dirent* entry = readdir(directory);
	
	if(directory == NULL){
		printf("\nError in opening directory");
		exit(1);
	}
	
	chdir(path);
	
	
	while(entry != NULL){
		if(strcmp("..", entry->d_name) != 0 && strcmp(".", entry->d_name) != 0){
			lstat(entry->d_name, &statbuf);
			printf("\n%s", entry->d_name);
			
			if(statbuf.st_mode & S_IRUSR)
				printf("\nUser has read access");
			if(statbuf.st_mode & S_IRGRP)
				printf("\nGroup has read access");
			if(statbuf.st_mode & S_IROTH)
				printf("\nOthers have read access");		
		}
		entry = readdir(directory);
	}
}
