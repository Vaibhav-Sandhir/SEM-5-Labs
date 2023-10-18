#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

Token token;
FILE* file;

void match(FILE* file){
	token = getNextToken(file);
}

void valid(){
	printf("\n---SUCCESS---\n");
	exit(0);
}

void invalid(char* correct){
	printf("\n---ERROR---");
	printf("\nError at row %d %d", token.row, token.column);
	printf("\nExpected: %s", correct);
	exit(0);
}

void Program();
void declarations();
void datatype();
void identifier_list();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();
void decision_stat();
void looping_stat();
void dprime();

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
					statement_list();
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
	if((strcmp(token.name, "int") == 0) || strcmp(token.name, "char") == 0){
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
		else if(strcmp(token.name, "[") == 0){
			match(file);
			if(strcmp(token.type, "Numerical") == 0){
				match(file);
				if(strcmp(token.name, ",") == 0){
					match(file);
					identifier_list();
				}
				
				else if(strcmp(token.type, "id") == 0){
					invalid(",");
				}
				else if(strcmp(token.name, "]") == 0){
					match(file);
					return;
				}
				else{
					invalid("]");
				}
			}
			else{
				invalid("NUM");
			}
		}
		else if(strcmp(token.type, "id") == 0){
			invalid(", / [");
		}
		else{
			return;
		}
	}
}

void statement_list(){
	if(strcmp(token.type, "id") == 0 || strcmp(token.type, "KW") == 0){
		statement();
		statement_list();
	}
	else{
		return;
	}
}

void statement(){
	if(strcmp(token.type, "id") == 0){
		assign_stat();
		if(strcmp(token.name, ";") == 0){
			match(file);
			return;
		}
		else{
			invalid(";");
		}
	}
	else if(strcmp(token.name, "if") == 0){
		decision_stat();
	}
	else if(strcmp(token.name, "while") == 0 || strcmp(token.name, "for") == 0){
		looping_stat();
	} 
	else{
		invalid("Invalid Beginning of statement");
	}
	
}

void assign_stat(){
	if(strcmp(token.type, "id") == 0){
		match(file);
		if(strcmp(token.name, "=") == 0){
			match(file);
			expn();
		}
		else{
			invalid("=");
		}
	}
	else{
		invalid("id");
	}
}

void expn(){
	simple_expn();
	eprime();
}

void eprime(){
	if(strstr(token.type, "RELOP") != NULL){
		relop();
		simple_expn();
	}
	else{
		return;
	}
}

void simple_expn(){
	term();
	seprime();
}

void seprime(){
	if(strstr(token.type, "ADD") != NULL || strstr(token.type, "SUB") != NULL){
		addop();
		term();
		seprime();
	}
	else{
		return;
	}
}

void term(){
	factor();
	tprime();
}

void tprime(){
	if(strstr(token.type, "MUL") != NULL || strstr(token.type, "DIV") != NULL){
		mulop();
		factor();
		tprime();
	}
	else{
		return;
	}
}

void factor(){
	if(strcmp(token.type, "id") == 0 || strcmp(token.type, "NUM")){
		match(file);
		return;
	}
	else{
		invalid("id/num");
	}
}

void relop(){
	if(strstr(token.type, "RELOP") != NULL){
		match(file);
		return;
	}
	else{
		invalid("Invalid Relop");
	}
}

void addop(){
	if(strstr(token.type, "ADD") != NULL || strstr(token.type, "SUB") != NULL){
		match(file);
		return;
	}
	else{
		invalid("Invalid Addop");
	}
}

void mulop(){
	if(strstr(token.type, "MUL") != NULL || strstr(token.type, "DIV") != NULL || strstr(token.type, "MOD") != NULL){
		match(file);
		return;
	}
	else{
		invalid("Inavlid Mulop");
	}
}

void decision_stat(){
	if(strcmp(token.name, "if") == 0){
		match(file);
		if(strcmp(token.name, "(") == 0){
			match(file);
			expn();
			if(strcmp(token.name, ")") == 0){
				match(file);
				if(strcmp(token.name, "{") == 0){
					match(file);
					statement_list();
					if(strcmp(token.name, "}") == 0){
						match(file);
						if(strcmp(token.name, "else") == 0){
							dprime();
						}
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
		invalid("if");
	}
}

void dprime(){
	if(strcmp(token.name, "else") == 0){
		match(file);
		if(strcmp(token.name, "{") == 0){
			match(file);
			statement_list();
			if(strcmp(token.name, "}") == 0){
				match(file);
				return;
			}
			else{
				invalid("}");
			}
		}
		else if(strcmp(token.name, "if") == 0){
			match(file);
			if(strcmp(token.name, "(") == 0){
				match(file);
				expn();
				if(strcmp(token.name, ")") == 0){
					match(file);
					if(strcmp(token.name, "{") == 0){
						match(file);
						statement_list();
						if(strcmp(token.name, "}") == 0){
							match(file);
							dprime();
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
			invalid("{ / if");
		}
	}
	else{
		invalid("else");
	}
}

void looping_stat(){
	if(strcmp(token.name, "while") == 0){
		match(file);
		if(strcmp(token.name, "(") == 0){
			match(file);
			expn();
			if(strcmp(token.name, ")") == 0){
				match(file);
				if(strcmp(token.name, "{") == 0){
					match(file);
					statement_list();
					if(strcmp(token.name, "}") == 0){
						match(file);
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
	else if(strcmp(token.name, "for") == 0){
		match(file);
		if(strcmp(token.name, "(") == 0){
			match(file);
			assign_stat();
			if(strcmp(token.name, ";") == 0){
				match(file);
				expn();
				if(strcmp(token.name, ";") == 0){
					match(file);
					assign_stat();
					if(strcmp(token.name, ")") == 0){
						match(file);
						if(strcmp(token.name, "{") == 0){
							match(file);
							statement_list();
							if(strcmp(token.name, "}") == 0){
								match(file);
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
					invalid(";");
				}
			}
			else{
				invalid(";");
			}
		}
		else{
			invalid("(");
		}
	}
	else{
		invalid("while/for");
	}
}

int main(){
	file = fopen("input.c", "r");
	Program();
	valid();
}

