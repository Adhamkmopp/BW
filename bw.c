 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "csapp.h"

/* count-sort subroutine for radix sort, based on suffixes.
the suffix_index variable is the current position of the suffixes
under cosnideration 

The sorted array contains the start positions of the sorted suffixes in
ascending order.*/
void csort(char *text, int *sorted, int length, int suff_index)
{

int count_array[257];
int curr_suff;

int tmp_sort[suff_index + 1];


for (int i =0; i < 257; i++){
    count_array[i] = 0;
}

for (int i =0; i <= suff_index; i++){
    tmp_sort[i] = sorted[i];
}

for(int k = 1;k < suff_index; k++){
    curr_suff = length - (suff_index - tmp_sort[k]);
    count_array[text[curr_suff]] = count_array[text[curr_suff]] + 1;
    printf("%c ", text[curr_suff]);
    
}

count_array[text[length]] = count_array[text[length]] + 1;
tmp_sort[suff_index] = suff_index; // not sure about this one
printf("%c ", text[length]);

printf("DONE: %d \n", suff_index);


for (int i = 1; i < 257; i++){
    count_array[i] = count_array[i] + count_array[i -1];
    
}


for(int k = suff_index;k >=1; k--){
    curr_suff = length - (suff_index - tmp_sort[k]);
    sorted[count_array[text[curr_suff]]] = tmp_sort[k];
    count_array[text[curr_suff]] = count_array[text[curr_suff]] -1;
    
    
}

for (int i = 0; i <=  suff_index; i++){
    printf("%d ", sorted[i]);
}
printf("\n");


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

void *mybuff = (void *) malloc(full_size);
int sorted_buff[full_size];

for(int i = 0; i < full_size; i++){
    sorted_buff[i] = 0;
}

Rio_readinitb(&rio, fd);
rio_readnb(&rio, mybuff, 8092);
//rio_writen(STDOUT_FILENO, mybuff ,full_size);

/* at this point the text file is in memory stored at mybuff */

//sorted_buff[0] = full_size;
full_size -=2;
for (int i = 1; i <  full_size + 2; i++){
    csort(mybuff, sorted_buff, full_size, i );
}




}
