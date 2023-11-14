#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Mab* Mabptr;

typedef struct Mab{
	int size;
	int allocated;
	Mabptr next;
	Mabptr prev;
}Mab;

typedef struct Process{
	char name[256];
	int size;
}Process;

int memCheck(Mabptr m, int size){
	return m->size >= size && m->allocated == 0;
}

void memAlloc(Mabptr m, int size){
	m->allocated = size;
}

void memFree(Mabptr m){
	m->allocated = 0;
}

void firstFit(Mabptr head, int n, Process list[n]){
	Mabptr m = head;
	for(int i = 0; i < n; i++){
		while(m != NULL){
			if(memCheck(m, list[i].size)){
				memAlloc(m, list[i].size);
				printf("\nProcess %s of size %d has been allocated to block of size %d", list[i].name, list[i].size, m->size);
				break;
			}
			else{
				m = m->next;
			}
		}
		if(m == NULL){
			printf("\nCould not allocate process %s", list[i].name);
		}
		m = head;
	}
}

void bestFit(Mabptr head, int n, Process list[n]){
	Mabptr m = head;
	for(int i = 0; i < n; i++){
		int min = 999999999;
		Mabptr min_mab = NULL;
		while(m != NULL){
			if(memCheck(m, list[i].size)){
				int diff = m->size - list[i].size;
				if(min >= diff){
					min_mab = m;
					min = diff;
				}
			}
			m = m->next;
		}
		if(min_mab != NULL){
			memAlloc(min_mab, list[i].size);
			printf("\nProcess %s of size %d has been allocated to block of size %d", list[i].name, list[i].size, min_mab->size);
		}
		else{
			printf("\nCould not allocate process %s", list[i].name);
		}
		m = head;
	}
}

void worstFit(Mabptr head, int n, Process list[n]){
	Mabptr m = head;
	for(int i = 0; i < n; i++){
		int max = 0;
		Mabptr max_mab = NULL;
		while(m != NULL){
			if(memCheck(m, list[i].size)){
				int diff = m->size - list[i].size;
				if(max <= diff){
					max_mab = m;
					max = diff;
				}
			}
			m = m->next;
		}
		if(max_mab != NULL){
			memAlloc(max_mab, list[i].size);
			printf("\nProcess %s of size %d has been allocated to block of size %d", list[i].name, list[i].size, max_mab->size);
		}
		else{
			printf("\nCould not allocate process %s", list[i].name);
		}
		m = head;
	}
}

Mabptr initializeMem(){
	Mabptr head = (Mabptr)malloc(sizeof(Mab));
	Mabptr m1 = (Mabptr)malloc(sizeof(Mab));
	Mabptr m2 = (Mabptr)malloc(sizeof(Mab));
	Mabptr m3 = (Mabptr)malloc(sizeof(Mab));
	Mabptr m4 = (Mabptr)malloc(sizeof(Mab));
	head->next = m1;
	m1->prev = head;
	m1->next = m2;
	m2->prev = m1;
	m2->next = m3;
	m3->prev = m2;
	m3->next = m4;
	m4->prev = m3;
	memFree(head);
	memFree(m1);
	memFree(m2);
	memFree(m3);
	memFree(m4);
	head->size = 200;
	m1->size = 70;
	m2->size = 250;
	m3->size = 20;
	m4->size = 400;
	return head;
}

void initializeProcess(int n, Process list[]){
	 strcpy(list[0].name, "P0");
	 strcpy(list[1].name, "P1");
	 strcpy(list[2].name, "P2");
	 strcpy(list[3].name, "P3");
	 strcpy(list[4].name, "P4");
	 list[0].size = 300; 
	 list[1].size = 10;
	 list[2].size = 60;
	 list[3].size = 5;
	 list[4].size = 25;
}

void main(){
	 int n = 5;
	 Mabptr head = initializeMem();
	 Process list[n];
	 initializeProcess(n, list);
	 //firstFit(head, n, list);
	 //bestFit(head, n, list);
	 worstFit(head, n, list);
}
