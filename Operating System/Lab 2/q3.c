#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("\nWrong number of arguments");
		exit(1);
	}
	
	char sub_dirs[256][256];
	char temp[256];
	
	DIR* directory = opendir(argv[1]);
	struct stat statbuf;
	struct dirent* entry;
	
	if(directory == NULL){
		printf("\nCould not open directory");
		exit(1);
	}
	
	chdir(argv[1]);
	int ind = 0;
	while((entry = readdir(directory)) != NULL){
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0){
				continue;
			}	
			strcpy(sub_dirs[ind++], entry->d_name);
		}
	}
	for(int i = 0; i < ind; i++){
		for(int j = i + 1; j < ind; j++){
			if(strcmp(sub_dirs[i], sub_dirs[j]) > 0){
				strcpy(temp, sub_dirs[i]);
				strcpy(sub_dirs[i], sub_dirs[j]);
				strcpy(sub_dirs[j], temp);
			}
		}		
	}
	printf("\nList of subdirectories: ");
	for(int i = 0; i < ind; i++){
		printf("\n%s", sub_dirs[i]);
	}
}

