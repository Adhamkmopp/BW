 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "csapp.h"


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

struct sl_type{
    int sl;
    int cnt;
};

Rio_readinitb(&rio, fd);
rio_readnb(&rio, mybuff, 8092);
rio_writen(STDOUT_FILENO, mybuff ,full_size);

/* initializing suffix and rank arrays */
char *curr_char = mybuff;
full_size -=1;
struct sl_type suff_type[full_size];

for(int i = 0; i < (full_size - 1); i++){
    suff_type[i].sl = 0;
    suff_type[i].cnt = 0;
}

/* initializing the empty suffix and the one before last */
suff_type[full_size - 1].sl = 0;
suff_type[full_size - 1].cnt = 1; 
suff_type[full_size - 2].sl = 1;
suff_type[full_size - 2].cnt = 1; 

int last_index = full_size - 3; 
int old_cmp = 1;
int new_cmp;
int v;

for(int i = last_index; i > -1;i--){
    new_cmp = curr_char[i] - curr_char[i+1];
    v = (new_cmp ^ old_cmp);
    if (v >= 0)
        suff_type[i].cnt = suff_type[i + 1].cnt+1;
    else
    {
        suff_type[i].cnt = 1;
    }
    
        //printf("%c, %c, %d, %d, %d\n", curr_char[i], curr_char[i + 1], old_cmp, new_cmp, v);

    old_cmp = new_cmp;

    if(new_cmp < 0){
        suff_type[i].sl = 0;
    } else if (new_cmp > 0){
        suff_type[i].sl = 1;
    } else {
        if (suff_type[i+1].sl = 1){
            suff_type[i].sl = 1;
        } else suff_type[i].sl = 0;
    }

}
for(int i = 0; i < (full_size); i++)
    printf("%d", suff_type[i].sl);
printf("\n");
    for(int i = 0; i < (full_size); i++)
    printf("%d", suff_type[i].cnt);
}
