
#ifndef TOKEN_GENERATION_H
#define TOKEN_GENERATION_H

typedef struct Token{	
    int row;
    int column;
    char type[256];
    char name[256];
} Token;

extern int no;

void token_creation();
Token getNextToken();

#endif
