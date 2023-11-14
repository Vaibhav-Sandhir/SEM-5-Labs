#include <stdio.h>
#include <stdlib.h>

typedef struct Seg{
	int seg_no;
	int base;
	int limit;
}Seg;

int convert(Seg st[5], int segment, int offset){
	if(segment >= 5 || segment < 0){
		printf("\nSegment number out of bounds");
		return -1;
	}
	else if(offset > st[segment].limit || offset < 0){
		printf("\nOffset out of limits");
		return -1;
	}
	else{
		int x = st[segment].base + offset;
		return x;
	}
}

void main(){
	Seg st[5];
	int physical_address;
	int segment;
	int offset;
	for(int i = 0; i < 5; i++){
		st[i].seg_no = i;
	}
	st[0].base = 1400;
	st[1].base = 6300;
	st[2].base = 4300;
	st[3].base = 3200;
	st[4].base = 4700;
	st[0].limit = 2400 - 1400;
	st[1].limit = 6700 - 6300;
	st[2].limit = 4700 - 4300;
	st[3].limit = 4300 - 3200;
	st[4].limit = 5700 - 4700;
	
	segment = 2;
	offset = 53;
	
	physical_address = convert(st, segment, offset);
	printf("\nByte %d of segment %d is %d", offset, segment, physical_address);
}
