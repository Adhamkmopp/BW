 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "csapp.h"


void msd_radix_sort(char *text, int *sorted, int lower, int upper, int char_pos, int length)
{

int range = upper - lower;

if (range <=0)
    return;

int items = range + 1;
int *count_array = (void *) calloc(256, sizeof(int));
int *upper_array = (void *) calloc(256, sizeof(int));
int *tmp_array = (void *) calloc(items, sizeof(int));
int new_upper = 0;

for (int j=lower; j <= upper; j++){
    
    if (sorted[j] + char_pos == length){
        sorted[lower] = sorted[j];
        lower++;
        continue;
    }
    
   count_array[text[sorted[j] + char_pos]] = count_array[text[sorted[j] + char_pos]] + 1;
}

for (int i = 1; i < 256 ; i++){
    upper_array[i] = count_array[i];
}


for (int i = 1; i < 256 ; i++){
    count_array[i] = count_array[i] + count_array[i -1]; 
}



for(int j = upper; j >=lower; j--){
    tmp_array[count_array[text[sorted[j] + char_pos]] - 1] = sorted[j];
    count_array[text[sorted[j] + char_pos]] = count_array[text[sorted[j] + char_pos]] - 1;
    
} 

int i = lower;
for (int j = 0;  j < items; j++){
    sorted[i] = tmp_array[j];
    i++;
}

int j = lower;
while (j <= upper)
{
    new_upper = upper_array[text[sorted[j] + char_pos]] ;
    msd_radix_sort(text, sorted, j , new_upper , char_pos + 1, length);
    j = j + new_upper;
 
}

free(upper_array);
}


/* suffix_radix_sort performs radix sort on a set of suffixes, from least,
to most signficiant digit, with the addition of one new suffix at a time. The 
suffix_radix_sort  function takes a pointer to the text, an array to place sorted 
suffix indices,  a void pointer to a space of 256 integer entries for keeping counts,
the length of the text and a suff_index variable to keep a record of the current 
round of sorting. At every round  of sorting, a new suffix is introduced and is 
given the key value  of suff_index. Sorting is performed on a column of characters 
of the old suffixes shifted by one position to the left, in addition to the right-most 
character of a  newly introduced suffix (which is always the last character of the 
text itself).
 */

void suffix_radix_sort(char *text, int *sorted, void *counts, int length, int suff_index)
{

int *count_array = counts;
int curr_suff;

/* tmp_sort holds initial values of the previous sort order. It serves a double
function as a  temporary sorting  array to  avoid overwriting already sorted 
values, as well as a placeholder for key-values of current suffixes */
int tmp_sort[suff_index + 1]; 
for (int i =0; i <= suff_index; i++){
    tmp_sort[i] = sorted[i];
}


/* curr_suff holds the correct position of the column character for the suffix 
under consideration. Suffixes are not directly represented, but are calculated 
from the length of the text and their key-value. For example, the second suffix 
in BANANA (which is ANANA) is given the key-value of 2 during the second round 
of sorting (from suff_index). During the third round, the correct character 
column should be at the first 'N' from the right, which is exactly at the 
character position given by the formula: 

length - (suff_index - tmp_sort[k]) 

or 6 - (3 - 2) = 5. 

the formula applies to the the first suffix's (BANANA) character column as well, 
which should be the 2nd 'A' from the right or: 6 - (3 - 1) = 4.*/

for(int k = 0;k < suff_index; k++){
    curr_suff = length - (suff_index - tmp_sort[k]);   
    count_array[text[curr_suff]] = count_array[text[curr_suff]] + 1;
}

count_array[text[length]] = count_array[text[length]] + 1;
tmp_sort[suff_index] = suff_index; 


for (int i = 1; i < 256; i++){
    count_array[i] = count_array[i] + count_array[i -1]; 
}

for(int k = suff_index;k >=0; k--){
    curr_suff = length - (suff_index - tmp_sort[k]);
    sorted[count_array[text[curr_suff]] - 1] = tmp_sort[k];
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
int text_end = full_size - 2;


char *mybuff = (void *) malloc(full_size);
void *counts = (void *) malloc(sizeof(int)*256);

int sorted_buff[text_end + 1];

for(int i = 0; i <= text_end; i++){
    sorted_buff[i] = 0;
}

Rio_readinitb(&rio, fd);
rio_readnb(&rio, mybuff, 8092);


/* since counts are continuously used and reused with each loop,
memset is used to 'wipe out' the array faster than iterating over
every element */
for (int i = 0; i <  text_end + 1; i++){
    counts =  memset(counts, 0, sizeof(int) *256);
    suffix_radix_sort(mybuff, sorted_buff, counts, text_end , i );
}


printf("\nSuffix sort by index (radix sort): ");
for (int i = 0; i <  text_end + 1; i++){
   printf("%d ", sorted_buff[i]);
}


int real_size = text_end +1;
int x=0;

printf("\nTransformed text (radix sort): ");

for (int i = 0; i <  real_size; i++){
    x= (sorted_buff[i] - 1);

    printf("%c", mybuff[(x < 0) ? (x % real_size + real_size) : (x % real_size)]);
}



counts =  memset(counts, 0, sizeof(int) *256);
for(int i = 0; i <= text_end; i++){
    sorted_buff[i] = i;
}

msd_radix_sort(mybuff, sorted_buff, 0, text_end, 0,text_end + 1);


printf("\nSuffix sort by index (MSD sort): ");
for (int i = 0; i <  text_end + 1; i++){
   printf("%d ", sorted_buff[i]);
}


printf("\nTransformed text (MSD sort): ");
for (int i = 0; i <  real_size; i++){
    x= (sorted_buff[i] - 1);
    printf("%c", mybuff[(x < 0) ? (x % real_size + real_size) : (x % real_size)]);
}


free(mybuff);
free(counts);

}
