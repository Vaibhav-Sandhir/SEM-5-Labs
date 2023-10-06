#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void getNewPath(char file_name[], char old_path[], char new_path[]);

int main(){
	char old_path[256];
	char new_path[256];
	char file_name[256];
	
	printf("\nEnter the path of the file whose hard link is to be created: ");
	scanf("%[^\n]%*c", old_path);
	// /home/student/Desktop/210905152_OS/Lab 4/q3.c
	
	getNewPath(file_name, old_path, new_path);
	printf("\nThe new_path is : %s", new_path);
		
	int result = link(old_path, new_path);
	
	if(result == -1){
		perror("link");
		exit(1);
	}
	else{
		printf("\nSuccessful Linking");
	}
	
	result = unlink(new_path);
	
	if(result == -1){
		perror("unlink");
		exit(1);
	}
	else{
		printf("\nSuccessful Unlinking");
	}
}

void getNewPath(char file_name[], char old_path[], char new_path[]){
	int total = 0;
	int count = 0;
	int ind = 0;
	for(int i = 0; i < strlen(old_path); i++){
		if(old_path[i] == '/')
			total++;
	}
	for(int i = 0; i < strlen(old_path); i++){
		if(old_path[i] == '/')
			count++;
		if(count == total){
			i++;
			while(old_path[i] != '.'){
				file_name[ind++] = old_path[i++]; 
			}
			strcat(file_name, "_hardLinked");
			ind = ind + strlen("_hardLinked");
			while(i < strlen(old_path)){
				file_name[ind++] = old_path[i++];	
			}
		}	
	}
	count = 0;
	ind = 0;
	for(int i = 0; i < strlen(old_path); i++){
		if(old_path[i] == '/')
			count++;
		if(count != total){
			new_path[ind++] = old_path[i];
		}	
	}
	new_path[ind] = '\0';
	strcat(new_path, "/");
	strcat(new_path, file_name);
}
