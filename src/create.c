#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fs.h"

#define DATABLOCK_SIZE 4096
#define SUPERBLOCK_SIZE 32

struct data_block{
    int next_block_num;
    char data[512];
};

superblock_t sb;
inode_t *inodes;


int create(int size, char* fs_name, char* dbs){
    sb.inode_count = 10;
    sb.db_count = 100;

    // init inodes
    int i;
    inodes = malloc(sizeof(inode_t) * sb.inode_count);
    for (i=0; i< sb.inode_count; i++){
        // inodes[i].inode_size = -1; commentée pcq un inode n'a pas de taille variable
        strcpy(inodes[i].filename, "emptyfi"); // a revoir, un fichier peut s'appeler "emptfyfi"
    }

    // init dbs
    dbs = malloc(sizeof(char) * sb.db_count); // je l'ai rendu char car un datablock c'est un tableau de 4096 char
    for (i=0; i< sb.db_count; i++){
        dbs[i] = -1;
    }
    
    FILE* file;
    file = fopen(fs_name,"w+");

    // superblock
    fwrite(&sb, sizeof(superblock_t), 1, file);

    //inodes
    for (i=0; i< sb.inode_count; i++){
        fwrite (&(inodes[i]), sizeof(inode_t), 1, file);
    }

    //data_blocks
    for (i=0; i<sb.db_count; i++){
        fwrite (&(dbs[i]), sizeof(char), 1, file); // je l'ai rendu char car un datablock c'est un tableau de 4096 char
    }

    fclose(file);
    return 0;
}
