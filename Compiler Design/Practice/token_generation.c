#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token_generation.h"

char *keywords[] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto","if", "int", "long", "register", "return",   "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

int no = 0;
Token token[256];
int id_no = 0;
int send_count = 0;

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

int isKeyword(char word[]){
	for(int i = 0; i < 32; i++){
		if(strcmp(word, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int isOtherRelop(char c){
	return c != '<' && c != '>' && c != '=' && c != '!';
}

int isOtherArithmop(char c){
	return c != '+' && c != '-' && c != '/' && c != '*';
}

int isOtherLogop(char c){
	return c != '&' && c != '|' && c != '!';
}

int isOtherBitwiseop(char c){
	return c != '&' && c != '|';
}

int isNumerical(char c){
	return c >= 48 && c <= 57;
}

int isAlphabet(char c){
	return ((c >= 97 && c <= 122) || (c >= 65 && c <= 90));
}

void getRelop(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line , i);
		char c = line[i];
		char next = line[i + 1];
		
		if(isOtherRelop(c))
			continue;
		
		if(c == '<' && isOtherRelop(next)){
			makeToken(row, i, "RELOP", "<");
		}	
			
		else if(c == '<' && next == '='){
			makeToken(row, i, "RELOP", "<=");
		}	
		
		else if(c == '>' && isOtherRelop(next)){
			makeToken(row, i, "RELOP", ">");
		}		 	
		
		else if(c == '>' && next == '='){
			makeToken(row, i, "RELOP", ">=");
		}
		
		else if(c == '!' && next == '='){
			makeToken(row, i, "RELOP", "!=");
		}
		
		else if(c == '=' && next == '='){
			makeToken(row, i, "RELOP", "==");
		}
	}
}

void getArithmop(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line, i);
		char c = line[i];
		char next;
		char prev;
		if(i + 1 >= n)
			next = ' ';
		else
			next = line[i + 1];
		if(i - 1 < 0)
			prev = ' ';
		else
			prev = line[i - 1];			
		
		if(isOtherArithmop(c))
			continue;
		
		if(c == '+' && isOtherArithmop(next) && isOtherArithmop(prev)){
			makeToken(row, i, "ARITHM", "+");
		}
		
		else if(c == '-' && isOtherArithmop(next) && isOtherArithmop(prev)){
			makeToken(row, i, "ARITHM", "-");
		}	
		
		else if(c == '*' && isOtherArithmop(next) && isOtherArithmop(prev)){
			makeToken(row, i, "ARITHM", "*");
		}	
		
		else if(c == '/' && isOtherArithmop(next) && isOtherArithmop(prev)){
			makeToken(row, i, "ARITHM", "/");
		}					
	}
}

void getIncDec(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line, i);
		char c = line[i];
		char next;
		if(i + 1 >= n)
			next = ' ';
		else
			next = line[i + 1];
		
		if(c == '+' && next == '+'){
			makeToken(row, i, "INC", "++");
		}
		else if(c == '-' && next == '-'){
			makeToken(row, i, "DEC", "--");
		}		
	}
}

void getLogicalop(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line, i);
		char c = line[i];
		char next;
		if(i + 1 > n)
			next = ' ';
		else
			next = line[i + 1];
		
		if(c == '&' && next == '&'){
			makeToken(row, i, "LOG:AND", "&&");
		}
		
		else if(c == '|' && next == '|'){
			makeToken(row, i, "LOG:OR", "||");
		}
		
		else if(c == '!' && isOtherLogop(next)){
			makeToken(row, i, "LOG:NOT", "!");
		}			
	}
}

void getBitwiseop(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line, i);
		char c = line[i];
		char next;
		char prev;
		
		if(i + 1 > n)
			next = ' ';
		else
			next = line[i + 1];
		if(i - 1 < 0)
			prev = ' ';
		else
			prev = line[i - 1];		
		
		if(c == '&' && isOtherBitwiseop(next) && isOtherBitwiseop(prev)){
			makeToken(row, i, "BIT:AND", "&");
		}		
		
		else if(c == '|' && isOtherBitwiseop(next) && isOtherBitwiseop(prev)){
			makeToken(row, i, "BIT:OR", "|");
		}
	}
}

void getStringLiteral(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		int end_index = isStringLiteral(line, i);
		if(i == end_index)
			continue;
		char literal[256];
		int k = 0;
		for(int j = i; j <= end_index; j++){
			literal[k++] = line[j];
		}
		literal[k] = '\0';
		makeToken(row, i, "Literal", literal);	
		i = end_index;
	}
}

void getSpecialSymbols(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line, i);
		char c = line[i];
		if(c == '('){
			makeToken(row, i, "SC", "(");
		}
		else if(c == ')'){
			makeToken(row, i, "SC", ")");
		}
		else if(c == '{'){
			makeToken(row, i, "SC", "{");
		}
		else if(c == '}'){
			makeToken(row, i, "SC", "}");
		}
		else if(c == ']'){
			makeToken(row, i, "SC", "]");
		}
		else if(c == '['){
			makeToken(row, i, "SC", "[");
		}
		else if(c == ','){
			makeToken(row, i, "SC", ",");
		}
		else if(c == ';'){
			makeToken(row, i, "SC", ";");
		}
	}
}

void getNumerical(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line, i);
		char number[256];
		int j = 0;
		int flag = 0;
		
		while(isNumerical(line[i])){
			number[j++] = line[i++];
			flag = 1;
		}
		number[j] = '\0';
		
		if(flag){
			makeToken(row, i, "NUM", number);
		}
	}
}

void getIdentifier(char line[], int row){
	int n = strlen(line);
	for(int i = 0; i < n; i++){
		i = isStringLiteral(line, i);
		char name[256];
		int j = 0;
		int start = 0;
		if(isAlphabet(line[i])){
			start = i;
			name[j++] = line[i];
			i++;
			while(isAlphabet(line[i]) || isNumerical(line[i])){
				name[j++] = line[i++];
			}
			name[j] = '\0';
			if(!isKeyword(name)){
				char id_s[256] = "id";
				char id_str[20];
				id_no++;
				sprintf(id_str, "%d", id_no);
				strcat(id_s, id_str);
				makeToken(row, start, name, id_s);
			}
			
		}
	}
}

void getKeywords(char line[], int row){
	char new_line[256];
	int j = 0;
	for(int i = 0; i < strlen(line); i++){
		if(line[i] == '"'){
			i++;
			while(line[i] != '"')
				i++;
		}
		else{
			new_line[j++] = line[i];
		}
	}
	new_line[j] = '\0';
	
	char* word = strtok(new_line, " \t\n");
	int column = 0;
	while(word != NULL){
		column += strlen(word) + 1;
		
		if(isKeyword(word)){
			makeToken(row, column - strlen(word), "KW", word);
		}
		
		else{
			for(int i = 0; i < 32; i++){
				char* res = strstr(word, keywords[i]);
				if(res != NULL){
					int index = res - word;
					if(!((word[index - 1] >= 97 && word[index - 1] <= 122) || (word[index - 1] >= 65 && word[index - 1] <= 90))){
    						index = index + strlen(keywords[i]) - 1;
    						if(index + 1 == strlen(word) || word[index + 1] == '*'){
    							makeToken(row, column - strlen(keywords[i]), "KW", keywords[i]);
    						}
    					}		
				}
			}
		}
		word = strtok(NULL, " \t\n");
	}
}

void sortTokens(){
	for(int i = 0; i < no - 1; i++){
		for(int j = 0; j < no - i - 1; j++){
			if(token[j].row == token[j + 1].row){
				if(token[j].column > token[j + 1].column){
					Token temp = token[j];
					token[j] = token[j + 1];
					token[j + 1] = temp;
				}
			}
		}
	}
}

Token getNextToken(){
	if(send_count < no)
		return token[send_count++];
}

void token_creation(){
	FILE* source = fopen("input_4.c", "r");
	char line[256];
	int i = 1;
	while(fgets(line, 256, source)){
		getRelop(line, i);
		getArithmop(line, i);
		getIncDec(line, i);
		getLogicalop(line, i);
		getBitwiseop(line, i);
		getStringLiteral(line, i);
		getKeywords(line, i);
		getNumerical(line, i);
		getSpecialSymbols(line, i);
		getIdentifier(line, i);
		i++;
	}
	sortTokens();		
}
