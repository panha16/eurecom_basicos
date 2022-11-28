/* File for size function */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <libgen.h>
#include "fs.h"

int myfs_itercount(char* array){
    int i = 0;
    while (array[i] != '\0') i++;
    return i;
}


int myfs_size(char* fs_name, char* path_to_directory, int recursive, char multiple, int stat,
                inode_t* table, char* dbs){
    inode_t inode;
    float c = 0; char disp[3];
    
    if (strcmp(path_to_directory, "/") == 0){

        for (int i = 0; i < DATABLOCK_SIZE * DB_COUNT; i++){
            if (dbs[i] != '\0') c++;
        }
        switch(multiple) {
            case 'M': c = c / 1000000; strcpy(disp, "MB"); break;
            case 'K': c = c / 1000; strcpy(disp, "KB"); break;
            case 'G': c = c / 1000000000; strcpy(disp, "GB"); break;
            default: strcpy(disp, "Bytes"); break;
        }
        printf("Total size of files in /: %g %s \n", c, disp);
        return 0;
    } else {
        // this is a work around to get the right dirname, man -s3 dirname for more info
        char tmp[32];
        strcpy(tmp, path_to_directory);
        strcat(tmp, "/trailing/");
        char* parent = dirname(tmp); 
        // if (inode.inode_type == 'd'){}
        for (int i = 2; i < INODE_COUNT; i++){
            if (strstr(table[i].filename, parent)){
                for (int p = table[i].db_pt ; p < ((table[i].db_pt + (table[i].db_count * DATABLOCK_SIZE))); p++){
                    if (dbs[p] != '\0') c++;
                    }
            }
        }
        switch(multiple) {
            case 'M': c = c / 1000000; strcpy(disp, "MB"); break;
            case 'K': c = c / 1000; strcpy(disp, "KB"); break;
            case 'G': c = c / 1000000000; strcpy(disp, "GB"); break;
            default: strcpy(disp, "Bytes"); break;
        }
        printf("Total size of files in %s: %g %s \n", parent, c, disp);
        return 0;
    // else {
    //     fprintf(stderr, "Invalid path. Path must point to directory \n");
    //     printf("usage: ./myfs <fs> <opt -b/-k/-m/-g> <opt -r> <path-to-directory> \n");
    //     return 1;
    //     }
    }

        return 0;
}