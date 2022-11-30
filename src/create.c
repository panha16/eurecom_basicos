#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "fs.h"


int create(int size, char* fs_name){
    superblock_t sb;
    sb.inode_count = 10000;
    sb.db_count = (size * 1000000 - sb.inode_count * sizeof(inode_t) - SUPERBLOCK_SIZE)/512; // The amount of datablocks depends on the size entered by the user

    if (sb.db_count <= 0){  // There is a minimum size so there won't be a negative amount of datablocks
        perror("The indicated size is too small !\n");
        exit(EXIT_SUCCESS);
    }

    // Initializing the inodes
    char* inodes = malloc(sizeof(inode_t) * sb.inode_count);
    int i = 0;   
    for (i=0; i< sb.inode_count * sizeof(inode_t); i++){  // Initializing the 10000 inodes, the size of each file being sizeof(inode_t)
        strcpy(&inodes[i], "\0");  // Using the empty characters to fill one inode
    strcpy(&inodes[1], "/");  // Initializing the root at the first position of each inode      
    }     
    

    // Initializing the datablocks
    char* dbs = malloc(sizeof(char) * sb.db_count * DATABLOCK_SIZE); 
    for (i=0; i<= sb.db_count * DATABLOCK_SIZE; i++){  // Initializing the amount of datablocks according to the size indicated by the user
        strcpy(&dbs[i], "\0"); // Using the empty characters to fill one datablock
        }
    

    FILE* file;
    file = fopen(fs_name,"w+");

    // Writing the superblock
    fwrite(&sb, sizeof(superblock_t), 1, file);

    // Writing the inodes
    for (i=0; i< sb.inode_count; i++){
        fwrite (&(inodes[i]), sizeof(inode_t), 1, file);
    }
   
    // Writing the datablocks
    fwrite (&(dbs[i]), DATABLOCK_SIZE , sb.db_count, file);
    
    fclose(file);
    return 0;
}
