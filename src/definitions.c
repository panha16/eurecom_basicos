/*  definitions.c
    Utility functions definitions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fs.h"

inode_t null_inode;
// get inode from file name 
inode_t get_inode(char* filename, superblock_t superblock){
    inode_t table[10000];
    memcpy(superblock.inode_table_pt, table, 10000); 
    for (int i = 0; i < INODE_COUNT; i++){
        if (strcmp(table[i].filename ,filename) == 0){
            printf("%d \n", i);
            printf("%s found \n", table[i].filename);
            return table[i];
        }
    }
    fprintf(stderr, "inode for %s not found \n", filename);
    return null_inode;
}

// is inode free
// is db free - gui
// return index of free inode
// return index of free db - gui
// does the file exist
bool is_inode_free(int inode_nb, int* inode_table){
    return (inode_table[inode_nb] == 0);
}

/* Function to check if inode_nb is free in inode_table
    returns true or false.
*/
int get_free_inode(int* inode_table){
    for (int i = 0; i < INODE_COUNT; i++)
        if (inode_table[i] == 0) return i;
    return -1;
}
/* This function returns the index of the next available inode in the inode_table
    returns -1 otherwise.
*/

int update_inode(int inode_number, inode_t inode, int* free_inode_table, inode_t* inode_table){
    inode_table[inode_number] = inode;
    free_inode_table[inode_number] = 1;
    return 1;
}
/*  Not finished */