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
int get_free_db(char* datablocks){
    for (int i = 0; i < DB_COUNT; i = i + 4096){
        if (datablocks[i] == '\0') return i;
    }
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

void inode_to_str(inode_t* inode){
    printf("filename %s \t inodetype %c \t\n", inode->filename, inode->inode_number);
}

int update_inode(int inode_number, inode_t inode, int* free_inode_table, inode_t* inode_table){
    inode_table[inode_number] = inode;
    free_inode_table[inode_number] = 1;
    return 1;
}
/*  Not finished */

int myfs_load(char* fsname, superblock_t superblock, inode_t* inode_table, char* datablocks){
    int fd = open(fsname, O_RDONLY);
    ssize_t fs_size = sizeof(superblock_t) + (sizeof(inode_t) * INODE_COUNT) + DB_COUNT*DATABLOCK_SIZE; // code written for test purposes
    char* buf = malloc(fs_size);
    ssize_t bytes_read = read(fd, buf, fs_size);
    printf("Bytes read: %ld \n", bytes_read);

    memcpy(inode_table, buf + sizeof(superblock_t), INODE_COUNT * sizeof(inode_t));
    memcpy(datablocks, buf + INODE_COUNT * sizeof(inode_t), DB_COUNT * DATABLOCK_SIZE);

    free(buf);
    return 0;
}

int load_inodes(char* fsname, inode_t* inode_table){
    int fd = open(fsname, O_RDONLY);
    char* buf = malloc((INODE_COUNT * sizeof(inode_t)) + 1);
    ssize_t bytes_read = read(fd, buf+ sizeof(superblock_t) , INODE_COUNT * sizeof(inode_t));
    printf("Bytes read: %ld \n", bytes_read);
    memcpy(inode_table, buf, INODE_COUNT * sizeof(inode_t));
    return 0;
}

int myfs_init(char* fs_name, int size){
    int fd = open(fs_name, O_WRONLY | O_CREAT, 0666);
    ssize_t fs_size = sizeof(superblock_t) + (sizeof(inode_t) * 10000) + 1500*4096;
    void* buf = malloc(fs_size+1);
    ssize_t bytes_written = write(fd, buf, fs_size+1);
    printf("Bytes written: %ld \n", bytes_written);
    free(buf);
    if (close(fd) == 0) printf("filesystem %s fd closed sucessfully \n", fs_name);
    return 0;
}

// get inode from file name - gui
// is inode free
// is db free - gui
// return index of free inode
// return index of free db - gui
// does the file exist