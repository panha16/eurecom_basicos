#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "fs.h"

superblock_t sb;
inode_t *inodes;

int create(int size, char* fs_name){
    sb.inode_count = 10000;
    sb.db_count = (size * 1000000 - 720000 - SUPERBLOCK_SIZE)/512;

    if (sb.db_count <= 0){
        perror("The indicated size is too small !\n");
        exit(EXIT_SUCCESS);
    }


    // init inodes
    inodes = malloc(sizeof(inode_t) * sb.inode_count);
    int i = 0;
    strcpy(inodes[1].filename,"/");     
    for (i=2; i< sb.inode_count; i++){
        strcpy(inodes[i].filename,"\0");       
    }

    // init dbs
    char* dbs = malloc(sizeof(char) * sb.db_count * DATABLOCK_SIZE);
    for (i=0; i<= sb.db_count * DATABLOCK_SIZE; i++){
        strcpy(&dbs[i], "o");
    }
    
    FILE* file;
    file = fopen(fs_name,"w+");

    // superblock
    fwrite(&sb, sizeof(superblock_t), 1, file);

    fclose(file);
    return 0;
}


int main(){
    create(10, "myfs");
    printf("%d",sb.db_count);
    return 0;
}