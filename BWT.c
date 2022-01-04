#include "bwt.h"


char *init(char *strs)
{
    int length = strlen(strs);
    if ((strs)[length-1] != '$')
    {
        char *p = (char *)malloc(sizeof(char) * (length + 2));
        strcpy(p, strs);
        p[length] = '$';
        p[length+1] = '\0';
        free(strs);
        strs = p;
    }
    return strs;
}

int cmp(const void *a, const void *b)
{
    if (((int*)a)[1] > ((int*)b)[1])
    {
        return 1;
    }
    else if (((int*)a)[1] == ((int*)b)[1])
    {
        return ((int*)a)[2] - ((int*)b)[2];
    }
    return -1;
}


int *suffixArray(char *strs)
{
    int length = strlen(strs);
    int *indx = (int *)malloc(sizeof(int)*length);
    int (*Idxs)[3] = (int (*)[])malloc(sizeof(int[3])*length);

    for (int i = 0; i < length; i++)
    {
        Idxs[i][0] = i;
        Idxs[i][1] = strs[i] - '$' + 1;
        Idxs[i][2] = 1;
        indx[i] = i;
    }

    for (int k = 1; k < (length << 2); k <<= 1)
    {
        for (int i = 0; i < length - k; i++)
            Idxs[indx[i]][2] = Idxs[indx[i+k]][1];

        for (int i = length - k; i < length; i++)
            Idxs[indx[i]][2] = 0;

        qsort(Idxs, length, sizeof(int[3]), cmp);

        int idx = 1;
        for (int i = 0; i < length; i++) 
        {
            indx[Idxs[i][0]] = i;
            if (i < length - 1 && (!EQUAL(Idxs[i], Idxs[i + 1])))
                Idxs[i][1] = idx++;
            else
                Idxs[i][1] = idx;
        }
        if (idx >= length)
            break;
    }
    free(Idxs);
    int *sa = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
        sa[indx[i]] = i;
    free(indx);

    return sa;
}


int *rankbwt(char *strs)
{
    int ascii[128] = {0}, length = strlen(strs);
    int *ranks = (int *)malloc(sizeof(int)*length);
    for (int i = 0; i < length; i++)
    {
        int idx = strs[i];
        ranks[i] = ascii[idx]++;
    }
    return ranks;
}


int *getFirstCol(char *strs)
{
    int *F = (int*)calloc(128, sizeof(int));
    for (int i = 0; i < strlen(strs); i++)
    {
        int idx = strs[i];
        F[idx]++;
    }
        
    for (int i = 32; i < 128; i++)
    {
        F[i] += F[i-1];
        if (F[i] == strlen(strs))
        {
            break;
        }
    }
    return F;
}


char *reversebwt(char *strs)
{
    int rowi = 0;
    int length = strlen(strs);
    char *p = (char *)malloc(sizeof(char)*(length+1));
    int *ranks = rankbwt(strs);
    int *F = getFirstCol(strs);
    p[length] = '\0';
    p[--length] = '$';

    while (strs[rowi] != '$')
    {
        p[--length] = strs[rowi];
        int idx = strs[rowi];
        rowi = F[idx-1] + ranks[rowi];
    }
    free(F);
    free(ranks);
    return p;
}


char *bwt(char *strs)
{
    strs = init(strs);
    int *sa = suffixArray(strs);
    int length = strlen(strs);
    char *L = (char *)malloc(sizeof(char)*(length+1));
    L[length] = '\0';
    int idx = 0;
    for (int i = 0; i < length; i++)
    {
        if (sa[i] == 0)
            L[idx++] = '$';
        else 
            L[idx++] = strs[sa[i]-1]; 
    }
    free(strs);
    return L;
}


int main(void)
{
    char str[] = "AACTTATAACTAGGGGGGGGGGGGGTTTTTTCACATAATACATATAACCTAACATATTTTTTTTTAACTTATAACTAGGGGGGGGGGGGGTTTTTTCACATAATACATATAACCTAACATATTTTTTTTTTTTTTTTTTTCACATAATATATTAACTAACATATAACCTAACATATATAACTACTAAAACTAACTATAACTAACTATAACTAACATATATTAACTATAACTAACATAACATAACTACTATAACTAACAT";

    char *L = bwt(str);
    printf("L:%s\n", L);
    char *T = reversebwt(L);
    printf("F:%s\n", T);
    free(L);
    free(T);

    system("pause");
    return 0; 
}
