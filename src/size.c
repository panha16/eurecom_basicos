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


int myfs_size(char* fs_name, char* path_to_directory, int recursive, char multiple, int stat, inode_t* table){
    inode_t inode = get_inode(path_to_directory, table);

    if (strcmp(path_to_directory, "/") == 0){
        myfs_init(fs_name, 10);
        printf("Ok, we're dealing with the bigboss root \n");
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