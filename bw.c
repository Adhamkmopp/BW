 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "csapp.h"

void csort(char *start, char *sorted, int length, int suff_index)
{

int count_array[257];
for (int i =0; i < 257; i++){
    count_array[i] = 0;
}

for (int j = 0; j < suff_index + 1; j++){
    count_array[start[length - j]] = count_array[start[length - j]] + 1;
    printf("%c ", start[length - j]);
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

void *mybuff = (void *) malloc(full_size);
void *sorted_buff = (void *) malloc(full_size);


Rio_readinitb(&rio, fd);
rio_readnb(&rio, mybuff, 8092);
//rio_writen(STDOUT_FILENO, mybuff ,full_size);

/* at this point the text file is in memory stored at mybuff */


full_size -=2;
for (int i = 0; i <  full_size + 1; i++){
    csort(mybuff, sorted_buff, full_size, i );
}


}
