#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

Token token;
FILE* file;

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

void match(FILE* file){
	token = getNextToken(file);
}

void Program(){
	match(file);
	if(strcmp(token.name, "main") == 0){
		match(file);
		if(strcmp(token.name, "(") == 0){
			match(file);
			if(strcmp(token.name, ")") == 0){
				match(file);
				if(strcmp(token.name, "{") == 0){
					match(file);
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
		match(file);
		if(strcmp(token.name, "int") == 0 || strcmp(token.name, "char") == 0){
			declarations();
		}
		return;
	}
	else{
		invalid(";");
	}
}

void datatype(){
	if(strcmp(token.name, "int") == 0){
		match(file);
		return;
	}
	else if(strcmp(token.name, "char") == 0){
		match(file);
		return;
	}
	else{
		invalid("int/char");	
	}		
}

void identifier_list(){
	if(strcmp(token.type, "id") == 0){
		match(file);
		if(strcmp(token.name, ",") == 0){
			match(file);
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
	if(strcmp(token.type, "id") == 0){
		match(file);
		if(strcmp(token.name, "=") == 0){
			match(file);
			if(strcmp(token.type, "id") == 0 || strcmp(token.type, "NUM") == 0){
				match(file);
				if(strcmp(token.name, ";") == 0){
					match(file);
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
	file = fopen("input.c", "r");
	Program();
	valid();
}

