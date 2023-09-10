#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Token{
	int row;
	int column;
	char type[256];
	char name[256];
}
int no = 0;
Token token[256];

void makeToken(int row, int column, char type[], char name[]){
	token[no].row = row;
	token[no].column = column;
	strcpy(token[no].type, type);
	strcpy(token[no].name, name);	
	no++;
}

int isStringLiteral(char line[], int i){
	int end_index = i;
	if(line[end_index] == '"'){
		end_index++;
		while(line[end_index] != '"')
			end_index++;
		}
	return end_index;
}

int isOtherRelOp(char c){
	return c != '<' && c != '>' && c != '=' && c != '!';
}

void getRelOp(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line , i);
		char c = line[i];
		char next = line[i + 1];
		
		if(isOtherRelOp(c))
			continue;
		
		if(c == '<' && isOtherRelop(next)){
			makeToken(row, i, "Relational Operator", "<");
		}	
			
		else if(c == '<' && next == '='){
			makeToken(row, i, "Relational Operator", "<=");
			i++;
		}	
		
		else if(c == '>')		
			
		 	
	}
}

void main(){
	FILE* source = fopen("input_4.c", "r");
			
}
