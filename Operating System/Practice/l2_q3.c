#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <assert.h>
#include <unistd.h>

void main(int argc, char* argv[]){
	assert(argc == 2);
	
	char names[256][256];
	int ind = 0;
	DIR* directory = opendir(argv[1]);
	struct stat statbuf;
	struct dirent* entry;
	chdir(argv[1]);
	
	while((entry = readdir(directory)) != NULL){
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp("..", entry->d_name) != 0 && strcmp(".", entry->d_name) != 0)
				strcpy(names[ind++], entry->d_name);
		}
	}
	for(int i = 0; i < ind - 1; i++){
		for(int j = 0; j < ind - i - 1; j++){
			if(strcmp(names[j], names[j + 1]) > 0){
				char temp[256];
				strcpy(temp, names[j]);
				strcpy(names[j], names[j + 1]);
				strcpy(names[j + 1], temp);
			}
		}
	}
	for(int i = 0; i < ind; i++){
		printf("\n%s", names[i]);
	}
}
