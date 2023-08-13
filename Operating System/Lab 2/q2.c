#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

void printdir(char path[], int depth);

int main(){
	char path[] = "/home/kali/Desktop/SEM-5-Labs/Operating System/Lab 2/q2_dir";
	
	printdir(path,1);
		
}

void printdir(char path[], int depth){
	DIR* directory = opendir(path);
	
	if(directory == NULL){
		printf("\nError in opening directory");
		exit(1);
	}

	chdir(path);
	struct dirent* entry = readdir(directory);
	struct stat statbuf;
	
	while(entry != NULL){
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
				continue;
			printf("\nDepth - %d Directory - %s", depth, entry->d_name);
			printdir(entry->d_name, depth + 1);	
		}
		else{
			printf("\nDepth - %d File - %s", depth, entry->d_name);	
		}
	}
	chdir("..");
	closedir(directory);
}
