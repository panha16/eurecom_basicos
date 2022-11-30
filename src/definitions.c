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
        if (strcmp(inode_table[i].filename ,filename) == 0) return inode_table[i];
    }
    inode_t null_inode = { .inode_number = -1 };
    return null_inode;
}

/* Returns pointer to size_in_dbs free datablocks */
int get_free_db(char* datablocks, int size_in_dbs){
    int c = 0; int i;
    for (i = 0; (i < (DB_COUNT * DATABLOCK_SIZE)) && (c != size_in_dbs); i = i + DATABLOCK_SIZE){
        for (int j = 0; j < size_in_dbs; j++){
            if (datablocks[i+(j*DATABLOCK_SIZE)] == '\0') c++;
            else {
                c=0; break;
            }
        }
    }
    return (c == size_in_dbs) ? (i-DATABLOCK_SIZE) : -1;
}

/* This function returns the index of the next available inode in the inode_table
    returns -1 otherwise.
*/
int get_free_inode(inode_t* inode_table){
    for (int i = 2; i < INODE_COUNT; i++)
        if (inode_table[i].inode_number == 0) return i;
    return -1;
}

void inode_to_str(inode_t* inode){
    printf("filename %s \t inodetype %c \t\n", inode->filename, inode->inode_number);
}

/* Reads the file system and retrieves all the components */
int myfs_load(char* fsname, superblock_t superblock, inode_t* inode_table, char* datablocks){

    FILE* infile = fopen (fsname, "rb");

    fseek(infile, sizeof(superblock_t), SEEK_SET);
    fread(inode_table, sizeof(inode_t), INODE_COUNT, infile);

    fseek(infile, sizeof(superblock_t) + INODE_COUNT * sizeof(inode_t), SEEK_SET);
    fread(datablocks, sizeof(char), DB_COUNT * DATABLOCK_SIZE, infile);

    fclose(infile);
    return 0;
}
/* Retrieves only inodes from the saved file system */ 
int load_inodes(char* fsname, inode_t* inode_table){
    FILE* infile = fopen (fsname, "rb");
    fseek(infile, sizeof(superblock_t), SEEK_SET);
    fread(inode_table, sizeof(inode_t), INODE_COUNT, infile);
    fclose(infile);
    return 0;
}
/*  initializes the file system — budget version of create */
int myfs_init(char* fs_name, int size){
    FILE *fp = fopen(fs_name, "wb+");
    ssize_t fs_size = sizeof(superblock_t) + (sizeof(inode_t) * INODE_COUNT) + DB_COUNT * DATABLOCK_SIZE;
    void* buf = malloc(fs_size+1);
    ssize_t bytes_written = fwrite(buf, sizeof(buf),1, fp);
    printf("init: %ld bytes written \n", sizeof(buf));

    superblock_t sb = {
        .size = 768000,
        .db_count = 1500
    };

    inode_t inode_f = {
        .inode_number = 0,
        .inode_type = 'f',
        .db_size = DATABLOCK_SIZE
    };
    inode_t inode_s = {
        .inode_number = 1,
        .inode_type = 'f',
        .db_size = DATABLOCK_SIZE
    };

    strncpy(inode_f.filename, "init", 32 * sizeof(char));
    strncpy(inode_s.filename, "root", 32 * sizeof(char));

    fseek(fp, 0, SEEK_SET);
    fwrite(&sb, sizeof(superblock_t), 1, fp);
    fseek(fp, sizeof(superblock_t), SEEK_SET);
    fwrite(&inode_f, sizeof(inode_t), 1, fp);
    fseek(fp, sizeof(superblock_t)+sizeof(inode_t), SEEK_SET);
    fwrite(&inode_s, sizeof(inode_t), 1, fp);
    
    printf("init: Bytes written: %ld \n", bytes_written);
    free(buf);
    
    if (fclose(fp) == 0) printf("filesystem %s descriptor closed sucessfully \n", fs_name);
    return 0;
}