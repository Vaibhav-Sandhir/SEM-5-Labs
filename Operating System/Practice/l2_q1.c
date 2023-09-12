#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <assert.h>

void main(int argc, char* argv[]){
	assert(argc == 2);
	
	DIR* directory = opendir(argv[1]);
	struct stat statbuf;
	struct dirent* entry;
	
	chdir(argv[1]);
	
	while((entry = readdir(directory)) != NULL){
		lstat(entry->d_name, &statbuf);
		if(!S_ISDIR(statbuf.st_mode)){
			if(strcmp("..", entry->d_name) != 0 && strcmp(".", entry->d_name) != 0){
				printf("\n%s", entry->d_name);
				
				if(statbuf.st_mode & S_IRUSR)
					printf("\nUser has read access");
				if(statbuf.st_mode & S_IWUSR)
					printf("\nUser has write access");
				if(statbuf.st_mode & S_IXUSR)
					printf("\nUser has execute access");
				if(statbuf.st_mode & S_IRGRP)
					printf("\nGroup has read access");
				if(statbuf.st_mode & S_IWGRP)
					printf("\nGroup has write access");
				if(statbuf.st_mode & S_IXGRP)
					printf("\nGroup has execute access");
				if(statbuf.st_mode & S_IROTH)
					printf("\nOthers have read access");
				if(statbuf.st_mode & S_IWOTH)
					printf("\nOthers have write access");
				if(statbuf.st_mode & S_IXOTH)
					printf("\nOthers have execute access");								
			}
		}
	}
}

