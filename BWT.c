#include "bwt.h"


void init(char **strs)
{
    int length = strlen(*strs);
    if ((*strs)[length-1] != '$')
    {
        char *p = (char *)malloc(sizeof(char) * (length + 2));
        strcpy(p, *strs);
        p[length] = '$';
        p[length+1] = '\0';
        free(*strs);
        *strs = p;
    }
}

// int cmp(const void *a, const void *b)
// {
//     if (((IntIdx*)a)->num1 > ((IntIdx*)b)->num1)
//     {
//         return 1;
//     }
//     else if (((IntIdx*)a)->num1 == ((IntIdx*)b)->num1)
//     {
//         return ((IntIdx*)a)->num2 - ((IntIdx*)b)->num2;
//     }
//     return -1;
// }

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
    // IntIdx *sIdxs = (IntIdx *)malloc(sizeof(IntIdx)*length);

    for (int i = 0; i < length; i++)
    {
        // sIdxs[i].index = i;
        // sIdxs[i].num1 = strs[i] - '$' + 1;
        // sIdxs[i].num2 = 1;
        Idxs[i][0] = i;
        Idxs[i][1] = strs[i] - '$' + 1;
        Idxs[i][2] = 1;
        indx[i] = i;
    }

    for (int k = 1; k < (length << 2); k <<= 1)
    {
        for (int i = 0; i < length - k; i++)
            // sIdxs[indx[i]].num2 = sIdxs[indx[i+k]].num1;
            Idxs[indx[i]][2] = Idxs[indx[i+k]][1];

        for (int i = length - k; i < length; i++)
            // sIdxs[indx[i]].num2 = 0;
            Idxs[indx[i]][2] = 0;

        qsort(Idxs, length, sizeof(int[3]), cmp);

        int idx = 1;
        for (int i = 0; i < length; i++) 
        {
            // indx[sIdxs[i].index] = i;
            indx[Idxs[i][0]] = i;
            // if (i < length - 1 && (!EQUAL(sIdxs[i], sIdxs[i + 1])))
            if (i < length - 1 && (!EQUAL(Idxs[i], Idxs[i + 1])))
                // sIdxs[i].num1 = idx++;
                Idxs[i][1] = idx++;
            else
                // sIdxs[i].num1 = idx;
                Idxs[i][1] = idx;
        }
        if (idx >= length)
            break;
    }
    // free(sIdxs);
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
        int idx = toascii(strs[i]);
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
        int idx = toascii(strs[rowi]);
        rowi = F[idx-1] + ranks[rowi];
    }
    free(F);
    free(ranks);
    return p;
}


char *bwt(char **strs)
{
    init(strs);
    int *sa = suffixArray(*strs);
    int length = strlen(*strs);
    char *L = (char *)malloc(sizeof(char)*(length+1));
    L[length] = '\0';
    int idx = 0;
    for (int i = 0; i < length; i++)
    {
        if (sa[i] == 0)
            L[idx++] = '$';
        else 
            L[idx++] = (*strs)[sa[i]-1]; 
    }
    return L;
}



int main(void)
{
    char str[] = "AACTTATAACTAGGGGGGGGGGGGGTTTTTTCACATAATACATATAACCTAACATATTTTTTTTTAACTTATAACTAGGGGGGGGGGGGGTTTTTTCACATAATACATATAACCTAACATATTTTTTTTTTTTTTTTTTTCACATAATATATTAACTAACATATAACCTAACATATATAACTACTAAAACTAACTATAACTAACTATAACTAACATATATTAACTATAACTAACATAACATAACTACTATAACTAACAT";
    char **pp;
    char *p = str;
    pp = &p;

    char *L = bwt(pp);
    printf("L:%s\n", L);
    char *F = reversebwt(L);
    printf("F:%s\n", F);
    free(L);
    free(F);
    free(p);

    system("pause");
    return 0; 
}
