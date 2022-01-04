#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// #define EQUAL(a, b) ((a).num1 == (b).num1 && (a).num2 == (b).num2)
#define EQUAL(a, b) ((a)[1] == (b)[1] && (a)[2] == (b)[2])

// typedef struct idx
// {
//     int index, num1, num2;
// }IntIdx;

char *bwt(char**);
void init(char**);
int *suffixArray(char*);
char *reversebwt(char*);
int *rankbwt(char*);
int *getFirstCol(char*);
int cmp(const void *, const void *);




