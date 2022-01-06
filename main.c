#include "FMindex.h"


int main(void)
{
    char strs[] = "ATAACTACTAAAacTAAACTAACATATAAACTATAACTAACATAACATAACTACTATAACTAACAT";
    char p[] = "acTAAA";

    FM *fmstr = FMindex(strs);
    printf("L: %s\n", fmstr->L);

    // the number of common strings
    int count = 0;
    // the inital indexs of common strings
    int *idx = occurrences(fmstr, p, &count);

    for (int i = 0; i < count; i++)
    {
        printf("%d\n", idx[i]);
        printf("%.*s\n", strlen(p), strs+idx[i]);
    }

    freememory(fmstr, idx);

    system("pause");
    return 0; 
}