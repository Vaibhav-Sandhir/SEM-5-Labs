#include <stdio.h>
#include <stdlib.h>

int curr = 0;
char str[100];

void S();
void U();
void V();
void W();

void valid(){
	printf("\n--SUCCESS--\n");
	exit(0);
}

void invalid(){
	printf("\n--ERROR--\n");
	exit(0);
}

void S(){
	U();
	V();
	W();
}

void U(){
	if(str[curr] == '('){
		curr++;
		S();
		if(str[curr] == ')'){
			curr++;
			valid();
		}
		else{
			invalid();
		}
	}
	
	else if(str[curr] == 'a'){
		curr++;
		S();
		if(str[curr] == 'b'){
			curr++;
			valid();
		}
		else{
			invalid();
		}
	}
	
	else if (str[curr] == 'd'){
		curr++;
		valid();
	}
	
	else{
		invalid();
	}
}

void V(){
	if(str[curr] == 'a'){
		curr++;
		V();
	}
}

void W(){
	if(str[curr] == 'c'){
		curr++;
		W();
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
