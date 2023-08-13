#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

int main(){
	char buffer[256];
	getcwd(buffer, 256);
	puts(buffer);
	strcat(buffer, "/prac");
	puts(buffer);
	int n = mkdir(buffer, 0777);
	//n = rmdir(buffer);
	DIR* directory = opendir(buffer);
	chdir(buffer);
	int file1 = open("prac1.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	int file2 = open("prac2.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	struct dirent* entry = readdir(directory);
	printf("\n%s", entry->d_name);
}

