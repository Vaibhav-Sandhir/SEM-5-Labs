#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Process{
	char name[256];
	int burst_time;
}Process;

int timer = 0;
int qt = 4;

void initializeProcess(int n, Process list[n]){
	 strcpy(list[0].name, "P1");
	 strcpy(list[1].name, "P2");
	 strcpy(list[2].name, "P3");
	 list[0].burst_time = 24; 
	 list[1].burst_time = 3;
	 list[2].burst_time = 3;
}

void rr(int n, Process list[n]){
	int count = 0;
	for(int i = 0; i < n; i = (i + 1) % n){
		if(count == n){
			break;
		}
		if(list[i].burst_time == 0){
			continue;
		}
		else if(list[i].burst_time <= qt){
			printf("\nProcess %s ran from %d to %d", list[i].name, timer, timer + list[i].burst_time - 1);
			timer += list[i].burst_time;
			list[i].burst_time = 0;
			count++;
		}
		else{
			printf("\nProcess %s ran frm %d to %d", list[i].name, timer, timer + qt - 1);
			timer += qt;
			list[i].burst_time -= qt;
		}
	}
}

void main(){
	int n = 3;
	Process list[n];
	initializeProcess(n, list);
	rr(n, list);
}
