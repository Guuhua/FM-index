#include "getRank.h"


int *getRank(char *strs)[]
{
    int length = strlen(strs);
    int *p[128] = {NULL};
    int count[128] = 0;
    for (int i = 0; i < length; i++)
    {
        int idx = strs[i];
        if (p[idx] == NULL)
            p[idx] = (int *)malloc(sizeof(int)*(length>>GAP+1));  
    }
    for (int i = 0; i < length; i++)
    {
        int idx = strs[i];
        count[idx]++;
        if ((i & GAP) == 0)
            p[idx][i>>GAP] = count[idx];
    }
    return p;
}

int rank(int *ranks[], char *strs, char c, int offset)
{
    if (offset < 0)
    {
        return 0;
    }
    int numc = 0;
    while (offset & GAP)
    {
        if (strs[offset] == c)
            numc++;
        offset--;
    }
    int idx = c;
    return ranks[idx][offset>>GAP] + numc;
}