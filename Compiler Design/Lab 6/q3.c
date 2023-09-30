#include <stdio.h>
#include <stdlib.h>

int curr = 0;
char str[100];

void S();
void A();
void Aprime();
void B();

void valid(){
	printf("\n--SUCCESS--\n");
	exit(0);
}

void invalid(){
	printf("\n--ERROR--\n");
	exit(-1);
}

void S(){
	if(str[curr] == 'a'){
		curr++;
		A();
		if(str[curr] == 'c'){
			curr++;
			B();
			if(str[curr] == 'e'){
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
	else{
		invalid();
	}
}

void A(){
	if(str[curr] == 'b'){
		curr++;
		Aprime();
	}
	else{
		invalid();
	}
}

void Aprime(){
	if(str[curr] == 'b'){
		curr++;
		Aprime();
	}
}

void B(){
	if(str[curr] == 'd'){
		curr++;
		return;
	}
}

void main(){
	printf("\nEnter String: ");
	scanf("%s", str);
	S();
	if(str[curr] == '$')
		valid();
	else
		invalid();	
}
