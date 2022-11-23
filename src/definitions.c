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


// get inode from file name 
inode_t get_inode(char* filename, inode_t* inode_table){
    for (int i = 0; i < INODE_COUNT; i++){
        if (strcmp(inode_table[i].filename ,filename) == 0){
            printf("%s found \n", inode_table[i].filename);
            return inode_table[i];
        }
    }
    inode_t null_inode = {
        .inode_number = -1
    };
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
int get_free_inode(inode_t* inode_table){
    for (int i = 1; i < INODE_COUNT; i++)
        if (inode_table[i].inode_number == 0) return i;
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

    FILE* infile = fopen (fsname, "rb");

    ssize_t fs_size = sizeof(superblock_t) + (sizeof(inode_t) * INODE_COUNT) + DB_COUNT*DATABLOCK_SIZE; // code written for test purposes

    fseek(infile, sizeof(superblock_t), SEEK_SET);
    fread(inode_table, sizeof(inode_t), INODE_COUNT, infile);

    fseek(infile, sizeof(superblock_t) + INODE_COUNT * sizeof(inode_t), SEEK_SET);
    fread(datablocks, sizeof(char), DB_COUNT * DATABLOCK_SIZE, infile);

    fclose(infile);
    return 0;
}

int load_inodes(char* fsname, inode_t* inode_table){
    FILE* infile = fopen (fsname, "rb");

    fseek(infile, sizeof(superblock_t), SEEK_SET);
    ssize_t bytes_read = fread(inode_table, sizeof(inode_t), INODE_COUNT, infile);
    printf("Inodes loaded: %ld \n", bytes_read);
    fclose(infile);
    return 0;
}

int myfs_init(char* fs_name, int size){
    FILE *fp = fopen(fs_name, "wb+");
    ssize_t fs_size = sizeof(superblock_t) + (sizeof(inode_t) * 10000) + 1500*4096;
    void* buf = malloc(fs_size+1);
    ssize_t bytes_written = fwrite(buf, sizeof(buf),1, fp);
    printf("Init: Bytes written: %ld \n", bytes_written);
    free(buf);
    
    if (fclose(fp) == 0) printf("filesystem %s fd closed sucessfully \n", fs_name);
    return 0;
}
