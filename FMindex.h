#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fm
{
    // suffix array int size n
    int *sa;
    // char size n
    char *L;
    // int size 128
    int *F;
    // int* size 128 
    int **gRanks;
    
    int length;
}FM;


// build fmindex data structure
FM *FMindex(char *strs);

// find the offset section
void range(FM *fmstr, char *p, int *s, int *t);

// Return a start index array, find all pattern p common strings in strs 
int *occurrences(FM *fmstr, char *p, int *count);


void freememory(FM *fm, int *idx);