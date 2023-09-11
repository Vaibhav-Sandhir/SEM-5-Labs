#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token_generation.h"

typedef struct ST_row{
	int sno;
	char name[256];
	char type[256];
	char data_type[256];
	char return_type[256];
	int no_arguments;
} ST_row;

ST_row st[1000003];
int ind = 0;

long long compute_hash(char str[]){
	int p = 31;
	int m = 1000003;
	int n = strlen(str);
	long long power = 1;
	long long hash_value = 0;
	
	for(int i = 0; i < n; i++){
		char c = tolower((unsigned char)str[i]);
		hash_value = (hash_value + (c - 'a' + 1) * power) % m;
		power = (power * p) % m;
	}
	return hash_value;
}

int containsKey(char str[]){
	long long hash_value = compute_hash(str);
	
	if(strcmp(st[hash_value].name, str) == 0)
		return 1;
	else
		return 0;	
}

void display(char str[]){
	long long hash_value = compute_hash(str);
	if(strcmp(st[hash_value].data_type, "") == 0){
		return;
	}
	if(containsKey(str)){
		printf("%d\t%s\t\t%s\t\t%s         \t%s\t%d\n", st[hash_value].sno, st[hash_value].name, st[hash_value].return_type, st[hash_value].data_type, st[hash_value].type, st[hash_value].no_arguments);
	}
	else{
		printf("\nSymbol not present");
	}
}


int main(){
	token_creation();
	int total_tokens = no;
	Token token[no];
	for(int i = 0; i < total_tokens; i++){
		token[i] = getNextToken();
	}
	for(int i = 0; i < no; i++){
		printf("\n<%s, %s, %d, %d>", token[i].name, token[i].type, token[i].row, token[i].column);
	}
	printf("\n");
	printf("SN\tName\t\tReturn Type\tData Type\tNature\t\tArguments\n");
	
	for(int i = 0; i < total_tokens; i++){
		Token curr = token[i];
		if(strstr(curr.name, "id") == NULL)
			continue;
		long long hash = compute_hash(curr.type);
		if(containsKey(curr.type)){
			continue;
		}	
		
		st[hash].sno = ind + 1;
		strcpy(st[hash].name, curr.type);
		
		int j = i + 1;
		Token next = token[j];
		
		if(strcmp(next.name, "(") == 0){
			strcpy(st[hash].type, "Function");
			strcpy(st[hash].data_type, "--");
			int k = i - 1;
			Token prev = token[k];
			
			if(strcmp(curr.type, "printf") == 0 || strcmp(curr.type, "scanf") == 0){
				strcpy(st[hash].return_type, "NULL");
			}	
			else{
				strcpy(st[hash].return_type, prev.name);
			}
			int arguments = 0;
			next = token[++j];
			while(strcmp(next.name, ")") != 0){
				if(strstr(next.name, "id") != NULL)
					arguments++;
				next = token[++j];	
			}
			st[hash].no_arguments = arguments;
		}
		
		else{
			strcpy(st[hash].type, "Variable");
			strcpy(st[hash].return_type, "--");
			st[hash].no_arguments = 0;
			
			int k = i - 1;
			while(k >= 0 && strcmp(token[k].type, "KW") != 0){
				k--;
			}
			strcpy(st[hash].data_type, token[k].name);
		}
		display(curr.type);
		ind++;			
	}	
}	


