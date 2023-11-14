#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define size 10

typedef struct Process{
	char name[256];
	int burst_time;
}Process;

int timer = 0;

void initializeProcess(int n, Process list[n]){
	 strcpy(list[0].name, "P1");
	 strcpy(list[1].name, "P2");
	 strcpy(list[2].name, "P3");
	 list[0].burst_time = 6; 
	 list[1].burst_time = 8;
	 list[2].burst_time = 7;
}

void sortProcesses(int n, Process list[n]){
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(list[j].burst_time > list[j + 1].burst_time){
				Process temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

void sjf(int n, Process list[n]){
	sortProcesses(n, list);
	for(int i = 0; i < n; i++){
		printf("\nProcess %s ran from t = %d to t = %d", list[i].name, timer, timer + list[i].burst_time - 1);
		timer += list[i].burst_time;
	}
}

void main(){
	int n = 3;
	Process list[n];
	initializeProcess(n, list);
	sjf(n, list);
}
