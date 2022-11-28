/* File for size function */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include "fs.h"

int myfs_itercount(char* array){
    int i = 0;
    while (array[i] != '\0') i++;
    return i;
}


int myfs_size(char* fs_name, char* path_to_directory, int recursive, char multiple, int stat,
                inode_t* table, char* dbs){
    inode_t inode = get_inode(path_to_directory, table);
    float c = 0; char disp[3];
    
    if (strcmp(path_to_directory, "/") == 0){
        printf("Ok, we're dealing with the bigboss root \n");

        for (int i = 0; i < DATABLOCK_SIZE * DB_COUNT; i++){
            if (dbs[i] != '\0') c++;
        }
        switch(multiple) {
            case 'M': c = c / 1000000; strcpy(disp, "MB"); break;
            case 'K': c = c / 1000; strcpy(disp, "KB"); break;
            case 'G': c = c / 1000000000; strcpy(disp, "B"); break;
            default: break;
        }
        printf("Total size of files in /: %g %s \n", c, disp);
        return 0;
    }
    else if (inode.inode_type == 'd'){
        printf("Ok, function is good \n");
        return 0;
    } else {
        fprintf(stderr, "Invalid path. Path must point to directory \n");
        printf("usage: ./myfs <fs> <opt -b/-k/-m/-g> <opt -r> <path-to-directory> \n");
        return 1;
    }
}