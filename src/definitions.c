/*  definitions.c
    Utility functions definitions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "fs.h"

inode_t null_inode;
// get inode from file name 
inode_t get_inode(char* filename, inode_t* inode_table){
    for (int i = 0; i < INODE_COUNT; i++){
        if (strcmp(inode_table[i].filename ,filename) == 0){
            printf("%d \n", i);
            printf("%s found \n", inode_table[i].filename);
            return inode_table[i];
        }
    }
    fprintf(stderr, "inode for %s not found \n", filename);
    return null_inode;
}

// is inode free
// is db free - gui
// return index of free inode
// return index of free db - gui
int get_free_db(int* db_table){
    for (int i = 0; i < DB_COUNT; i++)
        if (db_table[i] == 0) return i;
    return -1;
}
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

int myfs_load(char* fsname, superblock_t superblock, inode_t* inode_table){
    int fd = open(fsname, O_RDONLY);
    ssize_t fs_size = sizeof(superblock_t) + (sizeof(inode_t) * 10000) + 1500*4096;
    char* buf = malloc(fs_size+1);
    ssize_t bytes_read = read(fd, buf, fs_size);
    printf("%ld \n", bytes_read);

    free(buf);
    return 0;
}

int myfs_init(char* fs_name, int size){
    int fd = open(fs_name, O_WRONLY | O_CREAT);
    ssize_t fs_size = sizeof(superblock_t) + (sizeof(inode_t) * 10000) + 1500*4096;
    char* buf = malloc(fs_size+1);
    ssize_t bytes_written = write(fd, buf, fs_size);
    printf("Bytes written: %ld \n", bytes_written);
    free(buf);
    if (close(fd) == 0) printf("filesystem %s fd closed sucessfully \n", fs_name);
    return 0;
}