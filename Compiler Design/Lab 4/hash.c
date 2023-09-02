#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* table[1000000009];

long long compute_hash(char string[]){
	int p = 31;        // Any prime number
	int m = 1000000009;  // Large prime number
	long long hash_value = 0;
	long long power = 1;
	int len = strlen(string);
	
	for(int i = 0; i < len; i++){
		char c = string[i];
		hash_value = (hash_value + (c - 'a'  + 1) * power) % m;
		power = (power * p) % m;
	}
	
	return hash_value;
}

int containsKey(char string[]){
	long long hash_value = compute_hash(string);
	if(table[hash_value] == NULL)
		return 0;
	else
		return 1;	
}

void add(char string[]){
	long long hash_value = compute_hash(string);
	if(containsKey(string))
		return;
	else
		table[hash_value] = string;	
}

char* get(char string[]){
	long long hash_value = compute_hash(string);
	if(!containsKey(string))
		return "";
	else
		return table[hash_value];	
}

void delete(char string[]){
	long long hash_value = compute_hash(string);
	if(!containsKey(string))
		return;
	else
		table[hash_value] = "";	
}

