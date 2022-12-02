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
    inode_t* table, char* dbs,int DB_COUNT){
    float c = 0; char disp[3]; int found = 0;
    if (strcmp(path_to_directory, "/") == 0){ // If root directory
        for (int i = 0; i < DATABLOCK_SIZE * DB_COUNT; i++){
            if (dbs[i] != '\0') c++;
        }
        switch(multiple) { // Depending on the size argument we display the according unit
            case 'M': c = c / 1000000; strcpy(disp, "MB"); break;
            case 'K': c = c / 1000; strcpy(disp, "KB"); break;
            case 'G': c = c / 1000000000; strcpy(disp, "GB"); break;
            default: strcpy(disp, "B "); break;
        }
        printf("Total size of files in /: %g %s \n", c, disp);
    } else {
        // this is a work around to get the right dirname, `man -s3 dirname` for more info
        char tmp[32];
        strcpy(tmp, path_to_directory);
        strcat(tmp, "/trailing/");
        char* parent = dirname(tmp);
        for (int i = 2; i < INODE_COUNT; i++){ // check if parent substring is present in filename
            if (strstr(table[i].filename, parent)){
                found = 1;
                for (int p = table[i].db_pt ; p < ((table[i].db_pt + (table[i].db_count * DATABLOCK_SIZE))); p++){
                    if (dbs[p] != '\0') c++;
                    }
            }
        }
        switch(multiple) { // Depending on the size argument we display the according unit
            case 'M': c = c / 1000000; strcpy(disp, "MB"); break;
            case 'K': c = c / 1000; strcpy(disp, "KB"); break;
            case 'G': c = c / 1000000000; strcpy(disp, "GB"); break;
            default: strcpy(disp, "B "); break;
        }
        if (found) printf("Total size of files in %s: %g %s \n", parent, c, disp);
        else {
            fprintf(stderr, "Invalid path. Path must point to directory \n");
            printf("usage: ./myfs <fs> <opt -b/-k/-m/-g> <opt -r> <path-to-directory> \n");
            exit(1);
        }
    }

    if (stat) {
        FILE* fp = fopen(fs_name, "rb");
        float data = 0; int res;
        c = 0;

        for (int i = 0; i < (INODE_COUNT * sizeof(inode_t)); i++){ // count all characters in the partition table region
            if ((res = fgetc(fp)) != '\0') c++;
        }
        fclose(fp);
        // count number of characters in data segment
        for (int i = 0; i < DATABLOCK_SIZE * DB_COUNT; i++){
            if (dbs[i] != '\0'){
                data++;
            }
        }
        switch(multiple) { // Depending on the size argument we display the according unit
            case 'M': c = c / 1000000; data = data / 1000000;strcpy(disp, "MB"); break;
            case 'K': c = c / 1000; data = data / 1000;strcpy(disp, "KB"); break;
            case 'G': c = c / 1000000000; data = data / 1000000000; strcpy(disp, "GB"); break;
            default: strcpy(disp, "B "); break;
        }
        printf("Size of partition table: %g %s \n", c, disp);
        printf("Size of files: %g %s \n", data, disp);
    }
        return 0;
}