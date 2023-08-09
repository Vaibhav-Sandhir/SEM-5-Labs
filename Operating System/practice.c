#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

int main(){
	char buffer[256];
	getcwd(buffer, 256);
	puts(buffer);
	strcat(buffer, "/prac");
	puts(buffer);
	int n = mkdir(buffer, 0777);
	//n = rmdir(buffer);
	DIR* directory = opendir(buffer);
	struct dirent* entry = 
}

