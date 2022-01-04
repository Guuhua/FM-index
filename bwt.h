#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EQUAL(a, b) ((a)[1] == (b)[1] && (a)[2] == (b)[2])

char *bwt(char**);
void init(char**);
int *suffixArray(char*);
char *reversebwt(char*);
int *rankbwt(char*);
int *getFirstCol(char*);
int cmp(const void *, const void *);