#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

int row = 1;
int column = 0;

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

Token makeToken(FILE* file, char type[], int lb, int fp){
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
	column = column + fp - lb;	
	return token;	
}


char* makeString(FILE* file, int lb, int fp){
	fseek(file, lb, SEEK_SET);
	int n = fp - lb + 1;
	char* str = (char*)malloc(sizeof(char) * (n));
	for(int i = 0; i < n; i++){
		char c = fgetc(file);
		*(str + i) = c;
	}
	return str;
}

Token getNextToken(FILE* file){
	int lb = ftell(file);
	int fp = lb;
	char c = fgetc(file);
	
	if(c == '\n'){
		row++;
		column = 0;
		lb++;
		fp++;
		c = fgetc(file);
	}		
	
	while(c == ' '){
		lb++;
		fp++;
		column++;
		c = fgetc(file);
	}
	
	if(c == EOF)
		exit(0);
	
	if(c == '"'){
		column++;
		c = fgetc(file);
		fp++;
		while(c != '"'){
			c = fgetc(file);
			fp++;
		}
		return makeToken(file, "String Literal", lb, fp - 1);
	}	
	
	if(isNumerical(c)){
		column++;
		c = fgetc(file);
		fp++;
		while(isNumerical(c)){
			c = fgetc(file);
			fp++;
		}
		return makeToken(file, "Numerical", lb, fp - 1);
	}
	else if(isAlphabet(c)){
		column++;
		c = fgetc(file);
		fp++;
		while(isNumerical(c) || isAlphabet(c)){
			c = getc(file);
			fp++;
		}
		char* str = makeString(file, lb, fp - 1);
		if(isKeyword(str)){
			return makeToken(file, "KW", lb, fp - 1);
		}
		else{
			return makeToken(file, "id", lb, fp - 1);
		}
	}
	else if(isSpecialSymbol(c)){
		column++;
		fp++;
		return makeToken(file, "SC", lb, fp - 1);	
	}
	else if(isRelop(c)){
		column++;
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '>' && c == '='){
			fp++;
			return makeToken(file, "RELOP:GTE", lb, fp - 1);
		}
		if(prev == '>' && !isRelop(c)){
			return makeToken(file, "RELOP:GT", lb, fp - 1);
		}
		if(prev == '=' && c == '='){
			fp++;
			return makeToken(file, "RELOP:EQ", lb, fp - 1);
		}
		if(prev == '!' && c == '='){
			fp++;
			return makeToken(file, "RELOP:NEQ", lb, fp - 1);
		}
		if(prev == '<' && c == '='){
			fp++;
			return makeToken(file, "RELOP:LTE", lb, fp - 1);
		}
		if(prev == '<' && !isRelop(c)){
			return makeToken(file, "RELOP:LT", lb, fp - 1);
		}
		if(prev == '!' && !isRelop(c)){
			return makeToken(file, "LOG:NOT", lb, fp - 1);
		}
		if(prev == '=' && !isRelop(c)){
			return makeToken(file, "ASSGN:EQ", lb, fp - 1);
		}	
	}
	else if(isLogop(c)){
		column++;
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '&' && c == '&'){
			fp++;
			return makeToken(file, "LOG:AND", lb, fp - 1);
		}
		if(prev == '&' && !isRelop(c)){
			return makeToken(file, "BIT:AND", lb, fp - 1);
		}
		if(prev == '|' && c == '|'){
			fp++;
			return makeToken(file, "LOG:OR", lb, fp - 1);
		}
		if(prev == '|' && !isRelop(c)){
			return makeToken(file, "BIT:OR", lb, fp - 1);
		}
		if(prev == '^' && !isRelop(c)){
			return makeToken(file, "BIT:XOR", lb, fp - 1);
		}
	}
	else if(isArithmop(c)){
		column++;
		char prev = c;
		c = fgetc(file);
		fp++;
		if(prev == '+' && c == '+'){
			fp++;
			return makeToken(file, "INC", lb, fp - 1);
		}
		if(prev == '-' && c == '-'){
			fp++;
			return makeToken(file, "DEC", lb, fp - 1);
		}
		if(prev == '+' && !isArithmop(c)){
			return makeToken(file, "ARITHM:ADD", lb, fp - 1);
		}
		if(prev == '-' && !isArithmop(c)){
			return makeToken(file, "ARITHM:SUB", lb, fp - 1);
		}
		if(prev == '*' && !isArithmop(c)){
			return makeToken(file, "ARITHM:MUL", lb, fp - 1);
		}
		if(prev == '/' && !isArithmop(c)){
			return makeToken(file, "ARITHM:DIV", lb, fp - 1);
		}
		if(prev == '%' && !isArithmop(c)){
			return makeToken(file, "ARITHM:MOD", lb, fp - 1);
		}
	}
}
