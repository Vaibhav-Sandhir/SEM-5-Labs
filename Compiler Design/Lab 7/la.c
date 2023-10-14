#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

int row = 1;
int column = 1;
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
	return c == '(' || c == ')' || c == '{' || c == '}' || c == ']' || c == '[' || c == ',' || c == ';';
}

int isLogop(char c){
	return c == '&' || c == '|' || c == '^';
}

int isArithmop(char c){
	return c == '+' || c == '-' || c == '/' || c == '*';
}

Token makeToken(char type[], int lb, int fp){
	fseek(file, lb, SEEK_SET);
	int n = fp - lb + 1;
	char* str = (char*)malloc(sizeof(char) * (n));
	for(int i = 0; i < n; i++){
		char c = fgetc(file);
		*(str + i) = c;
	}
	Token token;
	token.row = row;
	token.column = column;
	strcpy(token.type, type);
	strcpy(token.name, str);
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

void initialize(){
	file = fopen("input.c", "r");
}

Token getNextToken(){
	int lb = ftell(file);
	int fp = lb;
	char c = fgetc(file);
	
	if(c == '\n')
		row++;	
	
	while(c == ' ' || c == '\n'){
		lb++;
		fp++;
		c = fgetc(file);
	}
	
	if(c == EOF)
		exit(0);
	
		
	if(isNumerical(c)){
		c = fgetc(file);
		fp++;
		while(isNumerical(c)){
			c = fgetc(file);
			fp++;
		}
		return makeToken("Numerical", lb, fp - 1);
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
			return makeToken("KW", lb, fp - 1);
		}
		else{
			return makeToken("id", lb, fp - 1);
		}
	}
	else if(isSpecialSymbol(c)){
		fp++;
		return makeToken("SC", lb, fp - 1);	
	}
	else if(isRelop(c)){
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '>' && c == '='){
			fp++;
			return makeToken("RELOP:GTE", lb, fp - 1);
		}
		if(prev == '>' && !isRelop(c)){
			return makeToken("RELOP:GT", lb, fp - 1);
		}
		if(prev == '=' && c == '='){
			fp++;
			return makeToken("RELOP:EQ", lb, fp - 1);
		}
		if(prev == '!' && c == '='){
			fp++;
			return makeToken("RELOP:NEQ", lb, fp - 1);
		}
		if(prev == '<' && c == '='){
			fp++;
			return makeToken("RELOP:LTE", lb, fp - 1);
		}
		if(prev == '<' && !isRelop(c)){
			return makeToken("RELOP:LT", lb, fp - 1);
		}
		if(prev == '!' && !isRelop(c)){
			return makeToken("LOG:NOT", lb, fp - 1);
		}
		if(prev == '=' && !isRelop(c)){
			return makeToken("ASSGN:EQ", lb, fp - 1);
		}	
	}
	else if(isLogop(c)){
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '&' && c == '&'){
			fp++;
			return makeToken("LOG:AND", lb, fp - 1);
		}
		if(prev == '&' && !isRelop(c)){
			return makeToken("BIT:AND", lb, fp - 1);
		}
		if(prev == '|' && c == '|'){
			fp++;
			return makeToken("LOG:OR", lb, fp - 1);
		}
		if(prev == '|' && !isRelop(c)){
			return makeToken("BIT:OR", lb, fp - 1);
		}
		if(prev == '^' && !isRelop(c)){
			return makeToken("BIT:XOR", lb, fp - 1);
		}
	}
	else if(isArithmop(c)){
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '+' && c == '+'){
			fp++;
			return makeToken("INC", lb, fp - 1);
		}
		if(prev == '-' && c == '-'){
			fp++;
			return makeToken("DEC", lb, fp - 1);
		}
		if(prev == '+' && !isArithmop(c)){
			return makeToken("ARITHM:ADD", lb, fp - 1);
		}
		if(prev == '-' && !isArithmop(c)){
			return makeToken("ARITHM:SUB", lb, fp - 1);
		}
		if(prev == '*' && !isArithmop(c)){
			return makeToken("ARITHM:MUL", lb, fp - 1);
		}
		if(prev == '/' && !isArithmop(c)){
			return makeToken("ARITHM:DIV", lb, fp - 1);
		}
	}
}
