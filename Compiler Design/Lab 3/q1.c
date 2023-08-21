#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ind = 0;
char *keywords[] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto","if", "int", "long", "register", "return", "short", "signed",
    		             "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
    			     "void", "volatile", "while"
			};

typedef struct Token{
	int row_no;
	int column_no;
	char type[256];
} Token;

int isOtherRelop(char c){
	if(c != '<' && c != '>' && c != '=' && c != '!'){
		return 1;
	}
	return 0;
}

int isOtherLogop(char c){
	if( c != '!' && c != '&' && c != '|'){
		return 1;
	}
	return 0;
}

int isOtherArithmop(char c){
	if(c != '+' && c != '-' && c!= '/' && c != '%' && c != '*'){
		return 1;
	}
	return 0;
}

int isOtherSpecialSymbol(char c){
	if(c != '$' && c != '@' && c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}' && c != '<' && c != '>'){
		return 1;
	}
	return 0;
}

int isOtherNumerical(char c){
	if(c >= 48 && c <= 57){
		return 0;
	}
	
	return 1;
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

int isKeyword(const char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void getRelop(char line[], int row_no, Token token[256]){	
	for(int i = 0; i < strlen(line); i++){
		
		i = isStringLiteral(line, i);
		
		if(isOtherRelop(line[i])){
			continue;
		}
		if(line[i] == '!' && line[i + 1] == '='){
			strcpy(token[ind].type, "Relop:NE");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '<' && line[i + 1] == '='){
			strcpy(token[ind].type, "Relope:LE");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '<' && isOtherRelop(line[i + 1])){
			strcpy(token[ind].type, "Relop:LT");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '=' && line[i + 1] == '='){
			strcpy(token[ind].type, "Relop:EQ");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '>' && line[i + 1] == '='){
			strcpy(token[ind].type, "Relop:GE");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '>' && isOtherRelop(line[i + 1])){
			strcpy(token[ind].type, "Relop:GT");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
	}
}


void getLogop(char line[], int row_no, Token token[256]){
	for(int i = 0; i < strlen(line); i++){
	
		i = isStringLiteral(line, i);
		
		if(isOtherLogop(line[i])){
			continue;
		}
		if(line[i] == '&' && line[i + 1] == '&'){
			strcpy(token[ind].type, "LogicalAND");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '|' && line[i + 1] == '|'){
			strcpy(token[ind].type, "LogicalOR");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '!' && isOtherLogop(line[i + 1])){
			strcpy(token[ind].type, "LogicalNOT");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
	}	
}

void getArithmop(char line[], int row_no, Token token[256]){
	for(int i = 0; i < strlen(line); i++){
	
		i = isStringLiteral(line, i);
	
		if(isOtherArithmop(line[i])){
			continue;
		}
		if(line[i] == '+' && isOtherArithmop(line[i + 1]) && isOtherArithmop(line[i - 1])){
			strcpy(token[ind].type, "ADD");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '-' && isOtherArithmop(line[i + 1]) && isOtherArithmop(line[i - 1])){
			strcpy(token[ind].type, "SUB");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '/' && isOtherArithmop(line[i + 1])){
			strcpy(token[ind].type, "DIV");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '*' && isOtherArithmop(line[i + 1])){
			strcpy(token[ind].type, "MUL");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '%' && isOtherArithmop(line[i + 1])){
			strcpy(token[ind].type, "MOD");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
	}
}

void getStringLiteral(char line[], int row_no, Token token[256]){
	for(int i = 0; i < strlen(line); i++){
		int end_index = isStringLiteral(line, i);
		if(i == end_index)
			continue;
		char literal[256];
		int k = 0;
		for(int j = i; j <=end_index; j++){
			literal[k++] = line[j];
		}
		literal[k] = '\0';
		strcpy(token[ind].type, literal);
		token[ind].row_no = row_no;
		token[ind].column_no = i;
		ind++;
		i = end_index;	
	}
}

void getSpecialSymbol(char line[], int row_no, Token token[256]){
	for(int i = 0; i < strlen(line); i++){
		i = isStringLiteral(line, i);
		
		if(isOtherSpecialSymbol(line[i])){
			continue;
		}
		
		if(line[i] == '$'){
			strcpy(token[ind].type, "SC:$");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
		if(line[i] == '@'){
			strcpy(token[ind].type, "SC:@");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
		if(line[i] == '['){
			strcpy(token[ind].type, "SC:[");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
		if(line[i] == ']'){
			strcpy(token[ind].type, "SC:]");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
		if(line[i] == '{'){
			strcpy(token[ind].type, "SC:{");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}	
		
		if(line[i] == '}'){
			strcpy(token[ind].type, "SC:}");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
		if(line[i] == '('){
			strcpy(token[ind].type, "SC:(");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
		if(line[i] == ')'){
			strcpy(token[ind].type, "SC:)");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
		if(line[i] == '<'){
			strcpy(token[ind].type, "SC:<");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
		if(line[i] == '>'){
			strcpy(token[ind].type, "SC:>");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		
	}
}

void getNumericalConstant(char line[], int row_no, Token token[256]){
	for(int i = 0; i < strlen(line); i++){
		i = isStringLiteral(line, i);
		
		if(isOtherNumerical(line[i])){
			continue;
		}
		char number[20] = "";
		int j = 0;
		
		if(i >=1 && !((line[i - 1] >= 97 && line[i - 1] <= 122) || (line[i - 1] >= 65 && line[i - 1] <= 90))){
			while(!isOtherNumerical(line[i])){
				number[j++] = line[i++];
			}
			strcat(token[ind].type, "NUM:");
			strcat(token[ind].type, number);
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			continue;
		}
	}
}

void getKeywords(char line[], int row_no, Token token[256]){
	char *word = strtok(line, " \t\n");
	
	int column = 0;

    	while (word != NULL) {
    		column += strlen(word) + 1;
        	if (isKeyword(word)) {
        		strcat(token[ind].type, "KW:");
            		strcat(token[ind].type, word);
			token[ind].row_no = row_no;
			token[ind].column_no = column;
			ind++;
        	}
        	word = strtok(NULL, " \t\n");
    	}
}

int sortTokens(Token token[]){
	for(int i = 0; i < ind - 1; i++){
		for(int j = 0; j < ind - i - 1; j++){
			if(token[j].row_no == token[j + 1].row_no){
				if(token[j].column_no > token[j + 1].column_no){
					Token temp = token[j];
					token[j] = token[j + 1];
					token[j + 1] = temp;
				}
			}
		}
	}
}

int main(){
	Token token[256];
	char line[256];
	int row = 1;
	FILE* input = fopen("input.c", "r");
	if(input == NULL){
		printf("\nError in opening file");
		exit(1);
	}
	while(fgets(line, 256, input)){
		getRelop(line, row, token);
		getLogop(line, row, token);
		getArithmop(line, row, token);
		getStringLiteral(line, row, token);
		getNumericalConstant(line, row, token);
		getSpecialSymbol(line, row, token);
		getKeywords(line, row, token);
		row++;
	}
	printf("\n%d\n", ind);
	sortTokens(token);
	
	for(int i = 0; i < ind; i++){
		printf("\n<%s, %d, %d>", token[i].type, token[i].row_no, token[i].column_no);
	}
}
