#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("\nWrong number of arguments");
		exit(1);
	}
	
	DIR* directory = opendir(argv[1]);
	struct stat statbuf;
	struct dirent* entry;
	
	if(directory == NULL){
		printf("\nCould not open directory");
		exit(1);
	}
	
	chdir(argv[1]);
	
	while((entry = readdir(directory)) != NULL){
		if(strcmp("..", entry->d_name) != 0 && strcmp(".", entry->d_name) != 0){
			lstat(entry->d_name, &statbuf);
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
