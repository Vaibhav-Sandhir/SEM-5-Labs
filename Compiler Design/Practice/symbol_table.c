#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token_generation.h"

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
	
}	


