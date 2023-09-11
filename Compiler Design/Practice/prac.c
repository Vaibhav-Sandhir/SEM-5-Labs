#include <stdio.h>
#include <string.h>

void main(){
	char string[] = "hello";
	char sub[] = "lo";
	char* res = strstr(string, sub);
	printf("%d", res - string);
	printf("\n%d", '0');
	printf("\n%d", '9');	
}	
