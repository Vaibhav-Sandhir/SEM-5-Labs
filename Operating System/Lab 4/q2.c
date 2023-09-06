#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

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
	
	char *access_time = ctime(&metadata.st_atime);
	char *mod_time = ctime(&metadata.st_mtime);
	char *change_time = ctime(&metadata.st_ctime);
	
	printf("\nInode number is %ld", metadata.st_ino);
	printf("\nDevice node in which file resides %ld", metadata.st_dev);
	printf("\nNumber of hard links pointing at the file is %ld", metadata.st_nlink);
	printf("\nUser ID of the owner of the file is %ld", metadata.st_uid);
	printf("\nSize of the file is %ld", metadata.st_size);
	printf("\nPreffered block size is %ld", metadata.st_blksize);
	printf("\nNumber of filesystem blocks allocated to the file %ld", metadata.st_blocks);
	printf("\nLast file access time %s", access_time);
	printf("Last file modification time %s", mod_time);
	printf("Last file change time %s", change_time);
	printf("Type of file: ");
		switch(metadata.st_mode & S_IFMT){
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
}
