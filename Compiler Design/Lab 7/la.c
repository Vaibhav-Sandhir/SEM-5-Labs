#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Token{	
    int row;
    int column;
    char type[256];
    char name[256];
} Token;

int row = 0;
int column = 0;
FILE* file;

char *keywords[] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto","if", "int", "long", "register", "return",   "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

int isKeyword(char word[]){
	for(int i = 0; i < 32; i++){
		if(strcmp(word, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int isNumerical(char c){
	return c >= 48 && c <= 57;
}

int isRelop(char c){
	return c == '<' || c == '>' || c == '=' || c == '!';
}

int isAlphabet(char c){
	return ((c >= 97 && c <= 122) || (c >= 65 && c <= 90));
}

int isSpecialSymbol(char c){
	return  (c == '(') ||
		(c == ')') ||
		(c == '{') ||
 		(c == '}') ||
		(c == ']') ||
		(c == '[') ||
		(c == ',') ||
		(c == ';');
}

int isLogop(char c){
	return c == '&' || c == '|' || c == '^';
}

int isArithmop(char c){
	return c == '+' || c == '-' || c == '/' || c == '*';
}

Token makeToken(char type[], char* name){
	Token token;
	token.row = row;
	token.column = column;
	strcpy(token.type, type);
	strcpy(token.name, name);
	return token;	
}

char* makeString(int lb, int fp){
	fseek(file, lb, SEEK_SET);
	int n = fp - lb + 1;
	char* str = (char*)malloc(sizeof(char) * (n));
	for(int i = 0; i < n; i++){
		char c = fgetc(file);
		*(str + i) = c;
	}
	return str;
}

Token getNextToken(){
	int lb = ftell(file);
	int fp = lb;
	char c = fgetc(file);
	
	while(c == ' ' || c == '\n'){
		lb++;
		fp++;
		c = fgetc(file);
	}
	//printf("\n %d %d %c", lb, fp, c);
	
	if(isNumerical(c)){
		c = fgetc(file);
		fp++;
		while(isNumerical(c)){
			c = fgetc(file);
			fp++;
		}
		char* str = makeString(lb, fp - 1);
		return makeToken("Numerical", str);
	}
	else if(isAlphabet(c)){
		c = fgetc(file);
		fp++;
		while(isNumerical(c) || isAlphabet(c)){
			c = getc(file);
			fp++;
		}
		char* str = makeString(lb, fp - 1);
		if(isKeyword(str)){
			return makeToken("KW", str);
		}
		else{
			return makeToken("id", str);
		}
	}
	else if(isSpecialSymbol(c)){
		fp++;
		char* str = makeString(lb, fp - 1);
		return makeToken("SC", str);	
	}
	else if(isRelop(c)){
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '>' && c == '='){
			fp++;
			char* str = makeString(lb, fp - 1);
			return makeToken("RELOP:GTE", str);
		}
		if(prev == '>' && !isRelop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("RELOP:GT", str);
		}
		if(prev == '=' && c == '='){
			fp++;
			char* str = makeString(lb, fp - 1);
			return makeToken("RELOP:EQ", str);
		}
		if(prev == '!' && c == '='){
			fp++;
			char* str = makeString(lb, fp - 1);
			return makeToken("RELOP:NEQ", str);
		}
		if(prev == '<' && c == '='){
			fp++;
			char* str = makeString(lb, fp - 1);
			return makeToken("RELOP:LTE", str);
		}
		if(prev == '<' && !isRelop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("RELOP:LT", str);
		}
		if(prev == '!' && !isRelop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("LOG:NOT", str);
		}
		if(prev == '=' && !isRelop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("ASSGN:EQ", str);
		}	
	}
	
	else if(isLogop(c)){
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '&' && c == '&'){
			fp++;
			char* str = makeString(lb, fp - 1);
			return makeToken("LOG:AND", str);
		}
		if(prev == '&' && !isRelop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("BIT:AND", str);
		}
		if(prev == '|' && c == '|'){
			fp++;
			char* str = makeString(lb, fp - 1);
			return makeToken("LOG:OR", str);
		}
		if(prev == '|' && !isRelop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("BIT:OR", str);
		}
		if(prev == '^' && !isRelop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("BIT:XOR", str);
		}
	}
	
	else if(isArithmop(c)){
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '+' && c == '+'){
			fp++;
			char* str = makeString(lb, fp - 1);
			return makeToken("INC", str);
		}
		if(prev == '-' && c == '-'){
			fp++;
			char* str = makeString(lb, fp - 1);
			return makeToken("DEC", str);
		}
		if(prev == '+' && !isArithmop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("ARITHM:ADD", str);
		}
		if(prev == '-' && !isArithmop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("ARITHM:SUB", str);
		}
		if(prev == '*' && !isArithmop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("ARITHM:MUL", str);
		}
		if(prev == '/' && !isArithmop(c)){
			char* str = makeString(lb, fp - 1);
			return makeToken("ARITHM:DIV", str);
		}
	}
	
}

void main(){
	file = fopen("input.c", "r");
	for(int i = 0; i < 33; i++){
		Token token = getNextToken();
		printf("%s %s\n", token.type, token.name);
	}
}
