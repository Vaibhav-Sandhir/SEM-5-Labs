#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define size 10

typedef struct Process{
	char name[256];
	int burst_time;
	int arrival_time;
}Process;

int timer = 0;
int ind = 0;

void initializeProcess(int n, Process list[n]){
	 strcpy(list[0].name, "P1");
	 strcpy(list[1].name, "P2");
	 strcpy(list[2].name, "P3");
	 strcpy(list[3].name, "P4");
	 list[0].burst_time = 8; 
	 list[1].burst_time = 4;
	 list[2].burst_time = 9;
	 list[3].burst_time = 5;
	 list[0].arrival_time = 0;
	 list[1].arrival_time = 1;
	 list[2].arrival_time = 2;
	 list[3].arrival_time = 3;
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

int isPresent(int n, Process proc, Process ready[n]){
	for(int i = 0; i < n; i++){
		if(strcmp(proc.name, ready[i].name) == 0){
			return 1;
		}
	}
	return 0;
}

void readyProcesses(int n, Process list[n], Process ready[n]){
	for(int i = 0; i < n; i++){
		if(!isPresent(n, list[i], ready)){
			if(list[i].arrival_time <= timer){
				ready[ind++] = list[i];
			}
		}
	}
}

void sjf(int n, Process list[n]){
	Process ready[n];
	while(timer < 26){
		readyProcesses(n, list, ready);
		sortProcesses(ind, ready);
		for(int i = 0; i < ind; i++){
			if(ready[i].burst_time != 0){
				printf("\nProcess %s ran from t = %d to t = %d", ready[i].name, timer, timer + 1);
				timer++;
				ready[i].burst_time -= 1;
				break;
			}
		}
	}
}

void main(){
	int n = 4;
	Process list[n];
	initializeProcess(n, list);
	sjf(n, list);
}
