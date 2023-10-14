#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

Token token;

void Program();
void declarations();
void assign_stat();
void datatype();
void identifier_list();


void valid(){
	printf("\n----SUCCESS----");
	exit(0);
}

void invalid(char* correct){
	printf("\n----ERROR----");
	printf("\nError at row : %d", token.row);
	printf("\nExpected: %s", correct);
	exit(0);
}

void match(){
	token = getNextToken();
}

void Program(){
	match();
	if(strcmp(token.name, "main") == 0){
		match();
		if(strcmp(token.name, "(") == 0){
			match();
			if(strcmp(token.name, ")") == 0){
				match();
				if(strcmp(token.name, "{") == 0){
					match();
					declarations();
					assign_stat();
					if(strcmp(token.name, "}") == 0){
						return;	
					}
					else{
						invalid("}");
					}
				}
				else{
					invalid("{");
				}
			}
			else{
				invalid(")");
			}
		}
		else{
			invalid("(");
		}
	}
	else{
		invalid("main");
	}
}

void declarations(){
	datatype();
	identifier_list();
	if(strcmp(token.name, ";") == 0){
		match();
		if(strcmp(token.name, "int") == 0 || strcmp(token.name, "char") == 0){
			declarations();
		}
		return;
	}
	else{
		invalid(";");
	}
	return;
}

void datatype(){
	if(strcmp(token.name, "int") == 0){
		match();
		return;
	}
	else if(strcmp(token.name, "char") == 0){
		match();
		return;
	}
	else
		invalid("int/char");	
		return;	
}

void identifier_list(){
	printf("\n %s", token.type);
	if(strcmp(token.type, "id") == 0){
		match();
		if(strcmp(token.name, ",") == 0){
			match();
			identifier_list();
		}
		if(strcmp(token.type, "id") == 0){
			invalid(",");
		}
		else{
			return;
		}
	}
	else{
		invalid("id");
	}
	return;
}

void assign_stat(){
	printf("hello");
	if(strcmp(token.type, "id") == 0){
		match();
		if(strcmp(token.name, "=") == 0){
			match();
			if(strcmp(token.type, "id") == 0 || strcmp(token.type, "NUM") == 0){
				match();
				if(strcmp(token.name, ";") == 0){
					return;
				}
				else{
					invalid(";");
				}
			}
			else{
				invalid("id/NUM");
			}
		}
		else{
			invalid("=");
		} 
	}
	else{
		invalid("id");
	}
	return;
}

int main(){
	initialize();
	Program();
	valid();
}

