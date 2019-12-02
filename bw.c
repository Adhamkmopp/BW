 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "csapp.h"


/* the function sorts suffixes based on radix sort. it takes a pointer to
the text, an array to place sorted suffix indices, the length of the text 
and a suff_index variable for the current round of sorting. at every round 
of sorting, a new suffix is introduced and given the key value of suff_index, 
and sorting is performed on a column of characters of the old suffixes shifted
by one position to the left, in addition to the right-most character of a 
newly introduced suffix (which is always the last character of the text itself).
 */

void suffix_radix_sort(char *text, int *sorted, int length, int suff_index)
{

int count_array[257];
int curr_suff;

/* holds initial values of the previous sort order. acts as a temporary sorting 
array to  avoid overwriting already sorted values, as well as a placeholder for
key-values of current suffixes */
int tmp_sort[suff_index + 1]; 
for (int i =0; i <= suff_index; i++){
    tmp_sort[i] = sorted[i];
}

for (int i =0; i < 257; i++){
    count_array[i] = 0;
}

/* curr_suff holds the correct position of the  column character for the suffix 
under consideration. suffixes are not directly represented, but are calculated 
from the length of the text and their key-value. for example, the second suffix 
in BANANA (which is ANANA) is given the key-value of 2 during the second round 
of sorting (from suff_index). during the third round, the  correct character 
column should be at the first 'N' from the right, which is exactly at the 
character position given by the formula: 

length - (suff_index - tmp_sort[k]) 

or 6 - (3 - 2) = 5. 

the formula applies to the the first suffix's (BANANA) character column as well, 
which should be the 2nd 'A' from the right or: 6 - (3 - 1) = 4.*/

for(int k = 1;k < suff_index; k++){
    curr_suff = length - (suff_index - tmp_sort[k]);
    count_array[text[curr_suff]] = count_array[text[curr_suff]] + 1;
    
}

count_array[text[length]] = count_array[text[length]] + 1;
tmp_sort[suff_index] = suff_index; 

for (int i = 1; i < 257; i++){
    count_array[i] = count_array[i] + count_array[i -1];
    
}


for(int k = suff_index;k >=1; k--){
    curr_suff = length - (suff_index - tmp_sort[k]);
    sorted[count_array[text[curr_suff]]] = tmp_sort[k];
    count_array[text[curr_suff]] = count_array[text[curr_suff]] -1;
    
}

}

int main(int argc, char *argv[]) {

if (argc !=2)
    exit(0);
rio_t rio;
int fd;
struct stat txt_stats;

fd = Open(argv[1], O_RDONLY, S_IRUSR);
Stat(argv[1], &txt_stats);
int full_size = txt_stats.st_size;
full_size -=2;

char *mybuff = (void *) malloc(full_size);
int sorted_buff[full_size];

for(int i = 0; i < full_size; i++){
    sorted_buff[i] = 0;
}

Rio_readinitb(&rio, fd);
rio_readnb(&rio, mybuff, 8092);


for (int i = 1; i <  full_size + 2; i++){
    csort(mybuff, sorted_buff, full_size, i );
}


}
