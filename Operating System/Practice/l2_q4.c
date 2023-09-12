#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <assert.h>

void main(int argc, char* argv[]){
	assert(argc == 2);
	
	DIR* directory = opendir(argv[1]);
	struct stat statbuf;
	struct dirent* entry;
	int ans;
	
	while((entry = readdir(directory)) != NULL){
		lstat(entry->d_name, &statbuf);
		if(!S_ISDIR(statbuf.st_mode)){
			if(strcmp("..", entry->d_name) != 0 && strcmp(".", entry->d_name) != 0){
				printf("\nDo you want to delete %s [1/0]", entry->d_name);
				scanf("%d", &ans);
				if(ans){
					char path[256];
					strcpy(path, argv[1]);
					strcat(path, "/");
					strcat(path, entry->d_name);
					remove(path);
				}
					
			}
		}
	}
}
