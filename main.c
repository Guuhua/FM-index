#include "FMindex.h"

int cmp2(const void *a, const void *b);


int cmp2(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b); ;
}


int main(void)
{
    char strs[1000], p[1000];

    printf("\nInput the string:\n");
    scanf("%[^\n]", strs);
    getchar();
    printf("\nInput the pattern string:\n");
    scanf("%[^\n]", p);

    FM *fmstr = FMindex(strs);
    printf("\norigin: %s", strs);
    printf("\n   bwt: %s", fmstr->L);
    printf("\n     p: %s\n", p);

    // the number of common strings
    int count = 0;
    // the inital indexs of common strings
    int *idx = occurrences(fmstr, p, &count);

    count = count > 0 ? count : 0;
    printf("\nFind %d common strings (begin index -> end index)\n", count);

    if (count > 0)
    {
        qsort(idx, count, sizeof(int), cmp2);
    }

    for (int i = 0; i < count; i++)
    {
        printf("  %4d -> %-4d\n", idx[i], idx[i] + (int)strlen(p));
    }

    freememory(fmstr, idx);

    return 0; 
}