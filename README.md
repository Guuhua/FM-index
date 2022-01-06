# FM-index
> FMindex & BWT c implementation
>
> A compressed full-text substring index based on the Burrows-Wheeler transform
>
> Our implementation refers to [Ben's lecture](https://www.youtube.com/watch?v=UHGgpfxlaiE&list=PL2mpR0RYFQsADmYpW2YWBrXJZ_6EL_3nu&index=11&ab_channel=BenLangmead).
>
> If you want to know more details about this algorithm, please click this [link](https://www.youtube.com/watch?v=UHGgpfxlaiE&list=PL2mpR0RYFQsADmYpW2YWBrXJZ_6EL_3nu&index=11&ab_channel=BenLangmead).

### How to use

**example.1** get the BWT string

```c
#include "bwt.h"

void main(void)
{
    char strs[] = "AATCSCAS";
    char *L = bwt(strs);
    printf("BWT string: %s", L);
    free(L);
}
```

**example.2** build the FM index

```c
#include "FMindex.h"

void main(void)
{
    char strs[] = "ASDADW";
    // FM: struct for fm index to store 
    //    .sa     suffix array
    //    .L      BWT string
    //    .F      first letter's index array
    //    .gRanks letters Ranks array
    //    .length string length
    FM *fmstr = FMindex(strs);
    
    // Given a pattern string P, find the common strings
    char p[] = "AS";
    // to store the num. of common strings
    int count;
    // to store the start index of common strings
    int *inds = occurrences(fmstr, p, &count);
     
    for (int i = 0; i < count; i++)
    {
        printf("%d~%d\n", inds[i], inds[i]+strlen(p));
    }
    
    freememory(fmstr, inds);
}
```

### License

FM-index is released under the MIT license. See the file LICENSE for more details.

### Contact

If you have any problems, please email me.(ttscj12@gmail.com)
