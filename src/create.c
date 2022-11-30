#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< src/create.c
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
        if (i % sizeof(inode_t) == 1){
            strcpy(&inodes[i], "/");  // Initializing the root at the first position of each inode      
            }
        }     
=======
#include <stdbool.h>
#include "fs.h"

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
>>>>>>> src/create.c
    

    // Initializing the datablocks
    char* dbs = malloc(sizeof(char) * sb.db_count * DATABLOCK_SIZE); 
    for (i=0; i<= sb.db_count * DATABLOCK_SIZE; i++){  // Initializing the amount of datablocks according to the size indicated by the user
        strcpy(&dbs[i], "\0"); // Using the empty characters to fill one datablock
        }
    

    FILE* file;
    file = fopen(fs_name,"w+");

<<<<<<< src/create.c
    // Writing the superblock
=======
    // superblock
>>>>>>> src/create.c
    fwrite(&sb, sizeof(superblock_t), 1, file);

    // Writing the inodes
    for (i=0; i< sb.inode_count; i++){
        fwrite (&(inodes[i]), sizeof(inode_t), 1, file);
<<<<<<< src/create.c
=======
    }

    //data_blocks
    for (i=0; i<sb.db_count; i++){
        fwrite (&(dbs[i]), sizeof(char), 1, file); // je l'ai rendu char car un datablock c'est un tableau de 4096 char
>>>>>>> src/create.c
    }
   
    // Writing the datablocks
    fwrite (&(dbs[i]), DATABLOCK_SIZE , sb.db_count, file);
    
    fclose(file);
    return 0;
}
<<<<<<< src/create.c

int main(){
    create(10,"myfs");
    return 0;
    }
=======
>>>>>>> src/create.c