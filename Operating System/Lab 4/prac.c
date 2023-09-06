#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("\nInvalid Number of Arguments");
		exit(1);
	}
	struct stat file_metadata;
	int result;
	result = stat(argv[1], &file_metadata);
	
	if(result == -1){
		perror("stat");
		exit(1);
	}
	
	printf("\nSize of file %s is %ld bytes", argv[1], file_metadata.st_size);
	
	switch(file_metadata.st_mode & S_IFMT){
		case S_IFBLK:
			printf("\nBlock Device Node");
                        // Block devices are storage devices that read and write data in fixed-size blocks, such as hard drives and SSDs.
			break;
		case S_IFCHR:
			printf("\nCharacter Device Node");
			// Character devices are devices that provide input/output operations one character at a time, such as terminals, serial ports, or input devices like keyboards and mice.
			break;
		case S_IFDIR:
			printf("\nDirectory");
			break;
		case S_IFIFO:
			printf("\nFIFO file");
			// Represents a FIFO (First-In-First-Out) special file, also known as a named pipe used for IPC
			break;
		case S_IFLNK:
			printf("\nSymbolic link");
			// Symbolic links are pointers to other files or directories, allowing you to create shortcuts or references to other locations in the file system.
			break;
		case S_IFREG:
			printf("\nRegular file");
			break;
		case S_IFSOCK:
			printf("\nSocket");
			break;
		default:
			printf("\nUnknown");
			break;								
	}
	return 0;
}
