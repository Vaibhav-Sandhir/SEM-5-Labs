#ifndef LA_H
#define LA_H

typedef struct Token {
    int row;
    int column;
    char type[256];
    char name[256];
} Token;

Token getNextToken();
void initialize();

#endif
