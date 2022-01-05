#include "FMindex.h"


int main(void)
{
    char strs[] = "ATAACTACTAAAACTAegwrgwrwegwrgwrwegwrgwrwegwrgwrACTATAACTAACTATegwrgwrwegwrgwrwegwrgwrwegwrgwrATAACATAACTACTATAACTAACATATAACTACTAAAACTAACTATAACTAACTATAACegwrgwrwegwrgwrwegwrgwrwegwrgwrTAACATATCSfwegwrgwrwegwrgwrwegwrgwrwegwrgwrhaATTAACTATAACTAACATAACATAACTACTATAACTAACAT";
    char p[] = "rgwrATAACA";

    FM *fmstr = FMindex(strs);
    printf("L : %s\n", fmstr->L);
    int count = 0;
    int *idx = occurrences(fmstr, p, &count);

    for (int i = 0; i < count; i++)
    {
        printf("%d\n", idx[i]);
        printf("%.*s\n", strlen(p), strs+idx[i]);
    }
    // freememory(fm, idx);

    system("pause");
    return 0; 
}