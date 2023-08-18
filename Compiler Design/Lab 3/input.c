int main(){
	Token token[256];
	char line[256];
	int row = 0;
	FILE* input = fopen("input.c", "r");
	if(input + == NULL){
		printf("\nError in opening file");
		exit(1);
	}
	while(fgets(line, 256, input)){
		isRelop(line, row, token);
		isLogop(line, row, token);
		isArithmop(line, row, token);
	}
	printf("\n%d\n", ind);
	for(int i = 0; i < ind; i++){
		printf("<%s, %d, %d>", token[i].type, token[i].row_no, token[i].column_no);
	}
}
