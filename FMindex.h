#include <stdio.h>
#include <string.h>

typedef struct fm
{
    int length;
    char *L;
    int *F;
    int *gRanks[];
}FM;
