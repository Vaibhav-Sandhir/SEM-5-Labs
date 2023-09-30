#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[256];

void S();
void T();
void Tprime();

void invalid(){
	printf("\n--ERROR--\n");
	exit(-1);
}

void valid(){
	printf("\n--SUCCESS--\n");
	exit(0);
}

void S(){
	if(str[curr] == 'a'){
		curr++;
		return;
	}
	else if(str[curr] == '>'){
		curr++;
		return;
	}
	else if(str[curr] == '('){
		printf("hello");
		curr++;
		T();
		if(str[curr] == ')'){
			curr++;
			return;
		}
		else{
			invalid();
		}
	}
	else{
		invalid();
	}
}

void T(){
	if(str[curr] == 'a'){
		curr++;
		Tprime();
	}
	else if(str[curr] == '>'){
		curr++;
		Tprime();
	}
	else if(str[curr] == '('){
		curr++;
		T();
		if(str[curr] == ')'){
			curr++;
			Tprime();
		}
		else{
			invalid();
		}
	}
	else{
		invalid();
	}
}

void Tprime(){
	if(str[curr] == ','){
		curr++;
		S();
		Tprime();
	}
}



void main(){
	printf("\nEnter input String: ");
	scanf("%s", str);
	S();
	if(str[curr] == '$')
		valid();
	else
		invalid();	
}
